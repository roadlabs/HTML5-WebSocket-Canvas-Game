var game;
var cons;
var websocket;

$(document).ready(function(){
    game = new Game();
	cons = new Console();
	websocket = new Ws();
});