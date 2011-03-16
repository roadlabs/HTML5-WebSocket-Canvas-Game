<?php
class Console {
    /**
     * Log a message
     * @param string $msg The message
     * @param string $type The type of the message
     * @return void
     */
    public static function log($msg, $type = 'System') {
        $msg = explode("\n", $msg);
        foreach ($msg as $line) {
            echo date('Y-m-d H:i:s') . " {$type}: {$line}\n";
        }
    }

    /**
     * Log debug message
     * @param mixed $msg
     * @return void
     */
    public static function debug($msg) {
        $msg = var_export($msg, true);
        echo $msg . "\n";
    }

    /**
     * Track syslog message
     * @param string $msg
     * @return void
     */
    public static function track($msg) {
        syslog(LOG_NOTICE, $msg);
    }
}