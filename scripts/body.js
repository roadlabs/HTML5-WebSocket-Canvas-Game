/**
 * Body
 * Means one item in the game world, abstract class
 * @param {int} x
 * @param {int} y
 * @param {int} width
 * @param {int} height
 * @param {int} group
 */
var Body = function(x, y, width, height) {
    this.x         = (x == null)      ? 0 : x;
    this.y         = (y == null)      ? 0 : y;
    this.width     = (width == null)  ? 0 : width;
    this.height    = (height == null) ? 0 : height;

    this.id = null;
    this.canMove = false;
    return this;
}
Body.prototype = {
    move: function(x, y) {
		if (this.canMove) {
			cons.debug('Player move, x: ' + x + ' , y: ' + y);
		    websocket.message.move(x, y);
		}
    },
    draw: function() {
        return;
    }
};

/**
 * Player
 */
var Player = function() {
	Body.call(this, PLAYER_INFO.x, PLAYER_INFO.y, PLAYER_INFO.width, PLAYER_INFO.height);
	
	this.id         = PLAYER_INFO.id;
    this.level      = PLAYER_INFO.level;
    this.exp        = PLAYER_INFO.exp;
	this.hp         = PLAYER_INFO.hp;
	this.mp         = PLAYER_INFO.mp;
	this.currentHp  = PLAYER_INFO.currentHp;
    this.currentMp  = PLAYER_INFO.currentMp;
	this.attack     = PLAYER_INFO.attack;
    this.defence    = PLAYER_INFO.defence;
    this.speed      = PLAYER_INFO.speed;
    this.icon       = PLAYER_INFO.icon;
	
	this.canMove = true;
	return this;
}
Player.prototype = new Body();
Player.prototype.draw = function(ctx) {
    var img = new Image();
	img.src = IMAGE_PATH + this.icon;
    ctx.drawImage(img, this.x, this.y, this.width, this.height);
};

/**
 * Enemy
 * @param {Object} enemy
 */
var Enemy = function(enemy) {
    Body.call(this, enemy.x, enemy.y, enemy.width, enemy.height);
    
    this.id         = enemy.id;
    this.level      = enemy.level;
    this.exp        = enemy.exp;
    this.hp         = enemy.hp;
    this.mp         = enemy.mp;
    this.currentHp  = enemy.currentHp;
    this.currentMp  = enemy.currentMp;
    this.attack     = enemy.attack;
    this.defence    = enemy.defence;
    this.speed      = enemy.speed;
    this.icon       = enemy.icon;
    
    return this;
}
Enemy.prototype = new Body();
Enemy.prototype.draw = function(ctx) {
    var img = new Image();
    img.src = IMAGE_PATH + this.icon;
    ctx.drawImage(img, this.x, this.y, this.width, this.height);
};

/**
 * Boss
 * @param {Object} boss
 */
var Boss = function(boss) {
    Body.call(this, boss.x, boss.y, boss.width, boss.height);
    
    this.id         = boss.id;
    this.level      = boss.level;
    this.exp        = boss.exp;
    this.hp         = boss.hp;
    this.mp         = boss.mp;
    this.currentHp  = boss.currentHp;
    this.currentMp  = boss.currentMp;
    this.attack     = boss.attack;
    this.defence    = boss.defence;
    this.speed      = boss.speed;
    this.icon       = boss.icon;
    
    return this;
}
Boss.prototype = new Body();
Boss.prototype.draw = function(ctx) {
    var img = new Image();
    img.src = IMAGE_PATH + this.icon;
    ctx.drawImage(img, this.x, this.y, this.width, this.height);
};

/**
 * Wall
 * @param {Array} wall
 */
var Wall = function(wall) {
	Body.call(this, wall[0], wall[1], wall[2], wall[3]);
    return this;
}
Wall.prototype = new Body();
Wall.prototype.draw = function(ctx) {
	ctx.fillStyle = '#000000';
    ctx.fillRect(this.x, this.y, this.width, this.height);
};

/**
 * Spring
 */
var Spring = function() {
	Body.call(this, SPRING_INFO[0], SPRING_INFO[1], SPRING_INFO[2], SPRING_INFO[3]);
    return this;
}
Spring.prototype = new Body();
Spring.prototype.draw = function(ctx) {
    ctx.fillStyle = '#00CCFF';
    ctx.fillRect(this.x, this.y, this.width, this.height);
}

/**
 * Gate
 */
var Gate = function() {
    Body.call(this, GATE_INFO[0], GATE_INFO[1], GATE_INFO[2], GATE_INFO[3]);
    return this;
}
Gate.prototype = new Body();
Gate.prototype.draw = function(ctx) {
    ctx.fillStyle = '#CC0000';
    ctx.fillRect(this.x, this.y, this.width, this.height);
}