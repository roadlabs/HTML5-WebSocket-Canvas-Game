<?php
class WebSocket extends Socket {
    /**
     * Construct
     * @param string $host
     * @param int $port default 8000
     * @return void
     */
    public function __construct($host, $port = 8000) {
        parent::__construct($host, $port);
        $this->run();
    }

    /**
     * Runs the while loop, wait for connections and handle them
     * @return void
     */
    private function run() {
        while (TRUE) {
            # because socket_select gets the sockets it should watch from $changed_sockets
            # and writes the changed sockets to that array we have to copy the allsocket array
            # to keep our connected sockets list
            $changedSockets = SocketPool::get()->getSocketList();

            # blocks execution until data is received from any socket
            $numSockets = socket_select($changedSockets, $write = NULL, $exceptions = NULL, NULL);

            # foreach changed socket...
            foreach ($changedSockets as $socket) {
                # master socket changed means there is a new socket request
                if ($socket == $this->master) {
                    # if accepting new socket fails
                    if(($client = socket_accept($this->master)) < 0) {
                        Console::log('socket_accept() failed: reason: ' . socket_strerror(socket_last_error($client)));
                        continue;
                    } else {
                        # if it is successful push the client to the allsockets array
                        SocketPool::get()->appendSocket($client);
                        SocketPool::get()->appendClient($client);
                        Console::log($client . ' CONNECTED!');
                    }
                } else {
                    # client socket has sent data
                    $socketIndex = SocketPool::get()->getSocketIndex($socket);
                    # the client status changed, but theres no data ---> disconnect
                    $bytes = @socket_recv($socket, $buffer, 2048, 0);
                    if ($bytes === 0) {
                        $this->close($socket);
                    } else {
                        # there is data to be read
                        # this is a new connection, no handshake yet
                        if (!SocketPool::get()->hasHandshake($socketIndex)) {
                            $this->doHandshake($buffer, $socket, $socketIndex);
                        } else {
                            $action = substr($buffer, 1, $bytes - 2); // remove chr(0) and chr(255)
                            Console::log("Input: $action");
                            try {
                                $response = Message::get()->process($socketIndex, $action);
                                if ($response) {
                                    $this->send($socket, $response);
                                }
                            } catch (Exception $e) {
                                $errorMessage = array ('cmd' => 99, 'params' => $e->getMessage());
                                $this->send($socket, $errorMessage);
                            }
                        }
                    }
                }
            }
        }
    }

    /**
     * Extends the socket class send method to send WebSocket messages
     * @param resource $client The socket to which we send data
     * @param string $msg The message we send
     * @return void
     */
    protected function send($client, $msg) {
        // convert array to json
        if (is_array($msg)) {
            $msg = json_encode($msg);
        }
        Console::log("Output: $msg");
        parent::send($client, chr(0) . $msg . chr(255));
    }

    /**
     * Manage the handshake procedure
     * @param string $buffer The received stream to init the handshake
     * @param resource $socket The socket from which the data came
     * @param int $socketIndex The socket index in the allsockets array
     * @return void
     */
    private function doHandshake($buffer, $socket, $socketIndex) {
        Console::log('Requesting handshake...');
        $upgrade = (string) new WebSocketHandshake($buffer);
        Console::log('Handshaking...');
        socket_write($socket, $upgrade, strlen($upgrade));
        SocketPool::get()->appendHankshake($socketIndex);
        Console::log('Done handshaking...');
    }

    /**
     * Disconnects a socket an delete all related data
     * @param resource $socket The socket to disconnect
     * @return void
     */
    private function close($socket) {
        $socketIndex = SocketPool::get()->getSocketIndex($socket);
        if ($socketIndex >= 0) {
            SocketPool::get()->removeSocket($socketIndex);
            SocketPool::get()->removeClient($socketIndex);
            SocketPool::get()->removeHandshake($socketIndex);
            SocketPool::get()->removeGame($socketIndex);
        }
        socket_close($socket);
        Console::log($socket . " disconnected!");
    }
}