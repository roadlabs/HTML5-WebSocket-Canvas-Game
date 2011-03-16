<?php
// GLOBAL
define('LIB_ROOT', '/var/www/ws/libs/');
//define('LIB_ROOT', 'D:\wamp\www\ws\libs\\');

// SOCKET
define('SOCKET_HOST', '10.20.0.68');

// DB
define('DB_HOST', '10.20.0.61');
define('DB_USER', 'root');
define('DB_PWD', '123');
define('DB_NAME', 'dungeon');

//**************************************************
// GAME
//**************************************************
// CLIENT
$stageSize = array (0, 0, 1050, 850); // x, y, width, height
$springInfo = array (440, 350, 100, 100); // x, y, width, height
$gateInfo = array (900, 0, 80, 80); // x, y, width, height
$wallInfo = array ( // x, y, width, height
    array (150, 0,   30,  450),
    array (100, 600, 20,  250),
    array (240, 0,   20,  200),
    array (240, 180, 200, 20),
    array (550, 0,   20,  200),
    array (800, 0,   20,  500),
    array (500, 600, 550, 20),
    array (500, 700, 20,  150),
);

define('STAGE_SIZE', serialize($stageSize));
define('GAME_STEP', 10); // (1000 / 10) = 100 FPS
define('SPRING_INFO', serialize($springInfo));
define('GATE_INFO', serialize($gateInfo));
define('WALL_INFO', serialize($wallInfo));

// SERVER
$expLadder = array (
    1 => array ('id' => 1, 'exp' => 100, 'hp' => 50, 'mp' => 10, 'attack' => 1, 'defence' => 1, 'speed' => 1),
    2 => array ('id' => 2, 'exp' => 200, 'hp' => 75, 'mp' => 10, 'attack' => 2, 'defence' => 2, 'speed' => 2),
    3 => array ('id' => 3, 'exp' => 500, 'hp' => 150, 'mp' => 15, 'attack' => 3, 'defence' => 3, 'speed' => 3),
    4 => array ('id' => 4, 'exp' => 1000, 'hp' => 300, 'mp' => 20, 'attack' => 4, 'defence' => 4, 'speed' => 4),
);
define('EXP_LADDER', serialize($expLadder));

define('PLAYER_STEP', 10); // move 10px for one step

define('GAME_ROLE_PLAYER', 0);
define('GAME_ROLE_ENEMY', 1);
define('GAME_ROLE_BOSS', 2);
define('GAME_ROLE_SPRING', 3);
define('GAME_ROLE_GATE', 4);
define('GAME_ROLE_WALL', 5);

define('BATTLE_HP_CONSUME', 0.4);