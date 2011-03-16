<?php
class DB {
    protected static $instance;
    protected $isConnected;
    protected $handle;

    /**
     * Get DB instance
     * @return DB $instance
     */
    public static function get() {
        if (!self::$instance) {
            self::$instance = new DB();
        }
        return self::$instance;
    }

    /**
     * Construct
     * @return void
     */
    function __construct() {
        $this->isConnected = FALSE;
    }

    /**
     * Connect to db
     * @return resource $handle
     */
    protected function connect() {
        $handle = mysql_connect(DB_HOST, DB_USER, DB_PWD);
        if (!$handle) {
            throw new Exception('Could not connect: ' . mysql_error());
        }
        $selectDb = mysql_select_db(DB_NAME);
        if (!$selectDb) {
            throw new Exception('Could not select db: ' . mysql_error());
        }
        $this->handle = $handle;
        $this->isConnected = TRUE;
        return $handle;
    }

    /**
     * Select data from db
     * @param string $query
     * @return array $return
     */
    public function select($query) {
        if (!$this->isConnected) {
            $this->connect();
        }
        $return = NULL;
        $result = mysql_query($query);
        if (!$result) {
            throw new Exception('Query failed: ' . mysql_error());
        }
        if (mysql_num_rows($result) != 0) {
            while ($row = mysql_fetch_assoc($result)) {
                $return[] = $row;
            }
        }
        return $return;
    }

    /**
     * Execute query
     * @param string $query
     * @return int $affectedRows
     */
    public function execute($query) {
        if (!$this->isConnected) {
            $this->connect();
        }
        $return = NULL;
        $result = mysql_query($query);
        if (!$result) {
            throw new Exception('Query failed: ' . mysql_error());
        }
        return array('rowCount' => mysql_affected_rows(), 'lastInsertID' => mysql_insert_id());
    }
}