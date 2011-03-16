var Message = function() {
    this.responses = {
		98: function(params) {
			// do nothing
		},
        99: function(params) {
            // echo error
            cons.debug('Exception: ' + params);
        },
		100: function(params) {
			// echo string
			cons.log(params);
		},
		0: function(params) {
			// init game
            cons.log('User logged in, Start init game...');
			STAGE_SIZE = params['stage'];
			WALL_INFO = params['wall'];
			SPRING_INFO = params['spring'];
			GATE_INFO = params['gate'];
			PLAYER_INFO = params['player'];
			ENEMY_INFO = params['enemies'];
			BOSS_INFO = params['bosses'];
            cons.log('Game initializing...');
			game.init();
		},
		1: function(params) {
			// move player
			PLAYER_INFO = params['player'];
			game.resetPlayer();
		},
		2: function(params) {
			// player touch the spring
            cons.log('Touch the spring, player recovered!');
            PLAYER_INFO = params['player'];
            game.resetPlayer();
		},
		3: function(params) {
			// win the game
			cons.log('You win the game!');
			game.end();
		},
		4: function(params) {
			// win the battle
			cons.log('You beat the enemy!');
			console.log(params);
            PLAYER_INFO = params['player'];
            game.resetPlayer();
			if (params['enemies']) {
                ENEMY_INFO = params['enemies'];
				game.resetEnemies();
			} else if (params['bosses']) {
                BOSS_INFO = params['bosses'];
				game.resetBosses();
			}
		},
		5: function(params) {
			// lose the battle
			cons.log('You lose the battle! Please login again to play!');
            game.end();
		}
    };
}
Message.prototype = {
	process: function(json) {
		// get command
		var cmd = json['cmd'];
		// get params
		var params = json['params'];
		// get function
		var func = this.responses[cmd];
		// call it
		func(params);
	},
	login: function(userId) {
		// user login
        websocket.socket.send('{"cmd":0,"params":{"uid":' + userId + '}}');
	},
	move: function(x, y) {
		// player move
        websocket.socket.send('{"cmd":1,"params":{"x":' + x + ',"y":' + y + '}}');
	}
};
