<?php
class Message {
    protected static $instance;

    public static function get() {
        if (!self::$instance) {
            self::$instance = new Message();
        }
        return self::$instance;
    }

    protected $actions = array (
        0 => array ('function' => 'login'),
        1 => array ('function' => 'move'),
    );

    /**
     * Main entrance of socket message
     * @param int $socketIndex
     * @param string $msg json string
     * @return string $response json
     */
    public function process($socketIndex, $msg) {
        // parse message info
        $msg = json_decode($msg, TRUE);
        $actionId = $msg['cmd'];
        $params = $msg['params'];
        if (!isset($actionId) || is_null($actionId)) {
            throw new Exception('Wrong message format, no param cmd!');
        }

        // user login
        if (0 == $actionId) { // means this is user login, create game for this user
            if (!$params['uid']) {
                throw new Exception('Wrong message format, no param uid!');
            }
            Console::log("Logic: User login, uid: {$params['uid']}");
            $game = SocketPool::get()->appendGame($socketIndex, $params['uid']); //FIXME means each time you connect to server, you will get a new game, not make sense
            $response = $game->initGame();
            return $response;
        }

        // get the game
        $game = SocketPool::get()->getGame($socketIndex);
        if (!$game) {
            throw new Exception('Not login yet, please login first!');
        }

        // handle message
        $response = '';
        $request = '';
        $action = $this->actions[$actionId];
        $function = $action['function'];
        if ($params) {
            $request = 'return $game->' . $function . '(' . implode(',', $params) . ');';
        } else {
            $request = 'return $game->' . $function . '();';
        }
        $response = eval($request);

        return $response;
    }
}