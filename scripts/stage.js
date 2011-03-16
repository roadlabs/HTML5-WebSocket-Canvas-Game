/**
 * Stage
 * Canvas related things
 */
var Stage = function() {
    this.x         = STAGE_SIZE[0];
    this.y         = STAGE_SIZE[1];
    this.width     = STAGE_SIZE[2];
    this.height    = STAGE_SIZE[3];
    this.step      = GAME_STEP; // (1000 / GAME_STEP) FPS
    
    this.lastExeTime = null;
    this.lastExeFrame = null,
    this.isRunning = false;
    
    this.date = new Date();
    this.timer = new Timer(null, this.step, 0, true);
    this.canvas = document.getElementById(CANVAS_ID);
    this.ctx = this.canvas.getContext('2d');
    this.ctx.fillStyle = '#000000';

    this.bodies = [];
    return this;
}
Stage.prototype = {
    start: function() {
        if (this.isRunning) {
            return false;
        }
        else {
            self = this;
            this.timer.action = function() {
                self.render();
            };
            this.isRunning = true;
            this.timer.start();
        }
    },
    stop: function() {
        this.timer.stop();
        this.isRunning = false;
    },
    clear: function() {
        this.ctx.clearRect(0, 0, this.width, this.height);
    },
    render: function() {
        this.ctx.clearRect(0, 0, this.width, this.height);
        for (var i = 0; i < this.bodies.length; i++) {
            this.bodies[i].draw(this.ctx);
        }
    },
    appendBody: function(body) {
        this.bodies.push(body);
    },
    removeBody: function(body){
        for (var i = 0; i < this.bodies.length; i++) {
            if (this.bodies[i] == body) {
                this.bodies.splice(i, 1);
                return true;
            }
        }
        return false;
    },
    fps: function() {
        var nowTime = new Date().getTime();
        $('#' + FPS_ID).html(Math.round(1000 * (this.timer.exeTimes - this.lastExeFrame) / (nowTime - this.lastExeTime)) + " FPS " + this.timer.exeTimes + " Total Frames");
        this.lastExeTime = nowTime;
        this.lastExeFrame = this.timer.exeTimes;
    },
	showPlayer: function(player) {
		var playerStatus = 'Player: HP: ' + player.currentHp + '/' + player.hp + ', MP: ' + player.currentMp + '/' + player.mp + '<br>' +
		                   'Level: ' + player.level + ', Exp: ' + player.exp + '<br>' +
		                   'Attack: ' + player.attack + ', Defence: ' + player.defence + ', Speed: ' + player.speed + '<br>' +
						   'X: ' + player.x + ', Y: ' + player.y;
		$('#' + PLAYER_ID).html(playerStatus);
	}
};