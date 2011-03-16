<?php
class ClassLoader {
    private static $classes = array (
        'GameBl'                => 'business/GameBl.inc',
        'RoleBo'                => 'business/RoleBo.inc',
        'DB'                    => 'db/DB.inc',
        'RoleDb'                => 'db/RoleDb.inc',
        'Message'               => 'socket/Message.inc',
        'Socket'                => 'socket/Socket.inc',
        'SocketPool'            => 'socket/SocketPool.inc',
        'WebSocket'             => 'socket/WebSocket.inc',
        'WebSocketHandshake'    => 'socket/WebSocketHandshake.inc',
        'Console'               => 'util/Console.inc',
    );

    public static function load($name) {
        $path = '';
        if (self::$classes[$name]) {
            $path = self::$classes[$name];
        } else {
            throw new Exception("Class $name not found!");
        }
        return $path;
    }
}

function autoLoad($name) {
    $path = ClassLoader::load($name);
    include_once LIB_ROOT . $path;
}
spl_autoload_register('autoLoad');