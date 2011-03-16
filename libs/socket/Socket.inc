<?php
class Socket {
    protected $master;
    protected $maxCon = 5;

    /**
     * Construct
     * @param string $host
     * @param int $port default 8000
     * @return void
     */
    public function __construct($host, $port = 8000) {
        $this->createSocket($host, $port);
    }

    /**
     * Create a socket on given host/port
     * @param string $host The host/bind address to use
     * @param int $port The actual port to bind on
     */
    protected function createSocket($host, $port) {
        if (($this->master = socket_create(AF_INET, SOCK_STREAM, SOL_TCP)) < 0) {
            throw new Exception("socket_create() failed, reason: " . socket_strerror($this->master));
        }
        Console::log("Socket {$this->master} created.");
        socket_set_option($this->master, SOL_SOCKET, SO_REUSEADDR, 1);
        if (($result = socket_bind($this->master, $host, $port)) < 0) {
            throw new Exception("socket_bind() failed, reason: " . socket_strerror($result));
        }
        Console::log("Socket bound to {$host}:{$port}.");
        if (($result = socket_listen($this->master, $this->maxCon)) < 0) {
            throw new Exception("socket_listen() failed, reason: " . socket_strerror($result));
        }
        Console::log('Start listening on Socket.');

        SocketPool::get()->appendSocket($this->master);
    }

    /**
     * Sends a message over the socket
     * @param resource $socket The destination socket
     * @param string $msg The message
     * @return void
     */
    protected function send($socket, $msg) {
        socket_write($socket, $msg, strlen($msg));
    }
}