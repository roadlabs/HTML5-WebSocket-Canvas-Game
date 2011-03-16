var Ws = function() {
	this.socket = null;
	this.message = null;
    this.address = 'ws://' + SOCKET_HOST + ':' + SOCKET_PORT + '/';
	
	this.init();
	return this;
}
Ws.prototype = {
	init: function() {
		var self = this;
	    this.socket = new WebSocket(this.address);
		this.message = new Message();
	    this.socket.onopen = function(event) {
	        self.onOpen();
	    };
	    this.socket.onmessage = function(event) {
            self.onMessage(event.data); // json message
	    };
	    this.socket.onclose = function(event) {
            self.onClose();
	    };
	},
	onOpen: function() {
		cons.log('Connected to server!');
	},
    onMessage: function(msg) {
		var json = JSON.parse(msg);
		this.message.process(json);
    },
    onClose: function() {
        cons.log('Disconnected!');
    }
};
