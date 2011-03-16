<?php
class SocketPool {
    protected static $instance;

    protected $sockets = array ();
    protected $clients = array ();
    protected $handshakes = array ();
    protected $games = array ();

    public static function get() {
        if (!self::$instance) {
            self::$instance = new SocketPool();
        }
        return self::$instance;
    }

    /**
     * Add socket into socket pool
     * @param resource $socket
     * @return void
     */
    public function appendSocket($socket) {
        $this->sockets[] = $socket;
    }

    /**
     * Get all sockets
     * @return array $sockets
     */
    public function getSocketList() {
        return $this->sockets;
    }

    /**
     * Search for given socket index
     * @param resource $socket
     * @return int $index
     */
    public function getSocketIndex($socket) {
        return array_search($socket, $this->sockets);
    }

    /**
     * Remove one socket in pool
     * @param int $socketIndex
     * @return void
     */
    public function removeSocket($socketIndex) {
        unset($this->sockets[$socketIndex]);
    }

    /**
     * Add socket into client pool
     * @param resource $client
     * @return void
     */
    public function appendClient($client) {
        $socketIndex = $this->getSocketIndex($client);
        $this->clients[$socketIndex] = $client;
    }

    /**
     * Get client socket from the pool
     * @param int $socketIndex
     * @return resource $client
     */
    public function getClient($socketIndex) {
        if ($this->clients[$socketIndex]) {
            return $this->clients[$socketIndex];
        } else {
            throw new Exception("Target client socket cannot be found, id: $id!");
        }
    }

    /**
     * Remove one client in pool
     * @param int $socketIndex
     * @return void
     */
    public function removeClient($socketIndex) {
        unset($this->clients[$socketIndex]);
    }

    /**
     * Check whether this socket has handshake
     * @param int $socketIndex
     * @return boolean
     */
    public function hasHandshake($socketIndex) {
        return isset($this->handshakes[$socketIndex]);
    }

    /**
     * Add one handshake
     * @param int $socketIndex
     * @return void
     */
    public function appendHankshake($socketIndex) {
        $this->handshakes[$socketIndex] = TRUE;
    }

    /**
     * Remove one handshake in pool
     * @param int $socketIndex
     * @return void
     */
    public function removeHandshake($socketIndex) {
        unset($this->handshakes[$socketIndex]);
    }

    /**
     * Add one game
     * @param int $socketIndex
     * @param int $uid
     * @return GameBl $game
     */
    public function appendGame($socketIndex, $uid) {
        $game = new GameBl($uid);
        $this->games[$socketIndex] = $game;
        return $game;
    }

    /**
     * Get one game
     * @param int $socketIndex
     * @return GameBl $game
     */
    public function getGame($socketIndex) {
        return $this->games[$socketIndex];
    }

    /**
     * Remove one game in pool
     * @param int $socketIndex
     * @return void
     */
    public function removeGame($socketIndex) {
        unset($this->games[$socketIndex]);
    }
}