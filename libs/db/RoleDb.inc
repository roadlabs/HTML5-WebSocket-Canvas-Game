<?php
class RoleDb {
    protected $db;

    /**
     * Construct
     * @return void
     */
    function __construct() {
        $this->db = DB::get();
    }

    /**
     * Select player from db
     * @param int $uid
     * @return RoleBo $player
     */
    public function selectPlayer($uid) {
        $player = NULL;
        $query = "SELECT `role`.`id`, `role`.`role`, `role`.`level`, `role`.`exp`, `role`.`hp`, `role`.`mp`, `role`.`attack`, `role`.`defence`, `role`.`speed`, `role`.`icon`, `role`.`x`, `role`.`y`, `role`.`width`, `role`.`height`, `role`.`current_hp`, `role`.`current_mp` " .
                 "FROM `dungeon`.`dungeon_roles` AS `role` " .
                 "WHERE `role`.`id` = $uid;";
        $result = $this->db->select($query);
        if ($result) {
            foreach ($result as $role) {
                $player = $this->convertArrayToRole($role);
            }
        }
        return $player;
    }

    /**
     * Select enemies from db
     * @return array $roles
     */
    public function selectEnemies() {
        $roles = NULL;
        $query = "SELECT `role`.`id`, `role`.`role`, `role`.`level`, `role`.`exp`, `role`.`hp`, `role`.`mp`, `role`.`attack`, `role`.`defence`, `role`.`speed`, `role`.`icon`, `role`.`x`, `role`.`y`, `role`.`width`, `role`.`height`, `role`.`current_hp`, `role`.`current_mp` " .
                 "FROM `dungeon`.`dungeon_roles` AS `role` " .
                 "WHERE `role`.`role` IN (" . GAME_ROLE_ENEMY . ", " . GAME_ROLE_BOSS . ")";
        $result = $this->db->select($query);
        if ($result) {
            foreach ($result as $role) {
                $roles[$role['role']][$role['id']] = $this->convertArrayToRole($role);
            }
        }
        return $roles;
    }

    /**
     * Update role in db
     * @param RoleBo $role
     * @return boolean TRUE
     */
    public function updateRole($role) {
        $query = "UPDATE `dungeon`.`dungeon_roles` AS `role` SET " .
                 "`role`.`level` = {$role->getLevel()}, " .
                 "`role`.`exp` = {$role->getExp()}, " .
                 "`role`.`hp` = {$role->getHp()}, " .
                 "`role`.`mp` = {$role->getMp()}, " .
                 "`role`.`attack` = {$role->getAttack()}, " .
                 "`role`.`defence` = {$role->getDefence()}, " .
                 "`role`.`speed` = {$role->getSpeed()}, " .
                 "`role`.`x` = {$role->getX()}, " .
                 "`role`.`y` = {$role->getY()}, " .
                 "`role`.`current_hp` = {$role->getCurrentHp()}, " .
                 "`role`.`current_mp` = {$role->getCurrentMp()} " .
                 "WHERE `role`.`id` = {$role->getId()};";
        $result = $this->db->execute($query);
        return TRUE;
    }

    /**
     * Conver array to EnemyBo
     * @param array $array
     * @return EnemyBo $enemy
     */
    protected function convertArrayToRole($array) {
        return new RoleBo($array['id'], $array['role'], $array['level'], $array['exp'],
                           $array['hp'], $array['mp'], $array['attack'], $array['defence'],
                           $array['speed'], $array['icon'], $array['x'], $array['y'],
                           $array['width'], $array['height'], $array['current_hp'], $array['current_mp']);
    }
}