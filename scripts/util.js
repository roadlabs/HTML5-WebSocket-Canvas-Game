/**
 * Console
 * Game console, to log debug info and log game system info
 */
var Console = function() {
    this.date = new Date();
    this.debugPanel = $('#' + DEBUG_MSG_ID);
    this.systemPanel = $('#' + SYSTEM_MSG_ID);
    return this;
}
Console.prototype = {
    getTime: function() {
        return this.date.getFullYear() + '-' + (this.date.getMonth() + 1) + '-' + this.date.getDate() + ' ' +
               this.date.getHours() + ':' + this.date.getMinutes() + ':' + this.date.getSeconds();
    },
    debug: function(msg) {
        this.debugPanel.prepend(this.getTime() + ' ' + msg + '<br>');
    },
    clearDebug: function() {
        this.debugPanel.html('');
    },
    log: function(msg) {
        this.systemPanel.prepend(this.getTime() + ' ' + msg + '<br>');
    },
    clearLog: function() {
        this.systemPanel.html('');
    }
};

/**
 * Timer
 * Can be used to only record times, also can be used to execute function frequently
 * @param {function} action
 * @param {int} interval
 * @param {int} maxTimes
 * @param {boolean} isFirstExe
 */
var Timer = function(action, interval, maxTimes, isFirstExe) {
    this.action     = action;
    this.interval   = (interval == null)   ? 1000 : interval;
    this.maxTimes   = (maxTimes == null)   ? 0    : maxTimes;
    this.isFirstExe = (isFirstExe == null) ? 0    : isFirstExe;
    
    this.timerId = null;
    this.exeTimes = 0;
    
    return this;
};
Timer.prototype = {
    start: function() {
        var self = this;
        if (this.maxTimes != 0 && this.maxTimes - this.exeTimes <= 0) {
            return false;
        }
        if (this.isFirstExe) {
            if (!this.doOnce()) {
                return;
            }
        }
        this.timerId = setInterval(function(){self.doOnce();}, this.interval);
    },
    stop: function() {
        clearInterval(this.timerId);
        this.timerId = null;
    },
    restart: function() {
        this.exeTimes = 0;
        this.start();
    },
    doOnce: function() {
        this.exeTimes++;
        if (this.action) {
            this.action();
        }
        if (this.maxTimes != 0 && this.maxTimes - this.exeTimes <= 0) {
            this.stop();
            return false;
        }
        return true;
    }
};