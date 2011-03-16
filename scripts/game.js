/**
 * Game
 * Game object
 */
var Game = function() {
    this.isRunning = false;
    this.stage = null;
    this.spring = null;
    this.gate = null;
    this.player = null;
    this.enemies = [];
    this.bosses = [];

    return this;
}
Game.prototype.init = function() {
    // init stage
    this.stage = new Stage();
    // init player
    this.player = new Player();
    this.stage.appendBody(this.player);
    // init sprint
    this.spring = new Spring();
    this.stage.appendBody(this.spring);
    // init gate
    this.gate = new Gate();
    this.stage.appendBody(this.gate);
    // init walls
    for (var i = 0; i < WALL_INFO.length; i++) {
        var wall = new Wall(WALL_INFO[i]);
        this.stage.appendBody(wall);
    }
    // init enemies
    for (var i = 0; i < ENEMY_INFO.length; i++) {
        var enemy = new Enemy(ENEMY_INFO[i]);
		this.enemies.push(enemy);
        this.stage.appendBody(enemy);
    }
    // init bosses
    for (var i = 0; i < BOSS_INFO.length; i++) {
        var boss = new Boss(BOSS_INFO[i]);
        this.bosses.push(boss);
        this.stage.appendBody(boss);
    }
    // init envorniment
    setInterval(function(){ game.stage.fps(); }, 1000);
    setInterval(function(){ game.stage.showPlayer(game.player); }, 20);
    // start game
    this.start();
};
Game.prototype.login = function() {
    var userId = $('#userId').val();
    websocket.message.login(userId);
};
Game.prototype.start = function() {
    cons.log('Game start!');
    if (this.isRunning) {
        return false;
    } else {
        $(window).keydown(this.playerKeyDown);
        this.stage.start();
        this.isRunning = true;
    }
};
Game.prototype.stop = function() {
    cons.log('Game stop!');
    $(window).unbind();
    this.stage.stop();
    this.stage.clear();
    this.isRunning = false;
};
Game.prototype.end = function() {
	this.stop();
	websocket.socket.close();
}
Game.prototype.playerKeyDown = function(e) {
    var key;
    if ((document.all) ? true : false) {
        key = window.event.keyCode;
    } else {
        key = e.which;
    }
    switch (key) {
        case 83: // s
            game.player.move(0, 1);
            break;
        case 65: // a
            game.player.move(-1, 0);
            break;
        case 87: // w
            game.player.move(0, -1);
            break;
        case 68: // d
            game.player.move(1, 0);
            break;
        case 13: // enter
            'nothing';
            break;
    }
};
Game.prototype.resetPlayer = function() {
    this.stage.removeBody(this.player);
    this.player = new Player();
    this.stage.appendBody(this.player);
}
Game.prototype.resetEnemies = function() {
    for (var i = 0; i < this.enemies.length; i++) {
		this.stage.removeBody(this.enemies[i]);
	}
	this.enemies = [];
    for (var i = 0; i < ENEMY_INFO.length; i++) {
        var enemy = new Enemy(ENEMY_INFO[i]);
        this.enemies.push(enemy);
        this.stage.appendBody(enemy);
    }
}
Game.prototype.resetBosses = function() {
    for (var i = 0; i < this.bosses.length; i++) {
        this.stage.removeBody(this.bosses[i]);
    }
    this.bosses = [];
    for (var i = 0; i < BOSS_INFO.length; i++) {
        var boss = new Boss(BOSS_INFO[i]);
        this.bosses.push(boss);
        this.stage.appendBody(boss);
    }
}
