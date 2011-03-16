<?php
require_once './libs/classes.inc';
require_once './libs/config.inc';

ob_implicit_flush(true);

$socket = new WebSocket(SOCKET_HOST);