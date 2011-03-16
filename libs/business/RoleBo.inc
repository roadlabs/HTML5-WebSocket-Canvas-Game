<?php
class RoleBo {
    protected $id;
    protected $role;
    protected $level;
    protected $exp;
    protected $hp;
    protected $mp;
    protected $attack;
    protected $defence;
    protected $speed;
    protected $icon;
    protected $x;
    protected $y;
    protected $width;
    protected $height;
    protected $currentHp;
    protected $currentMp;

    /**
     * Construct
     * @param int $id
     * @param int $role
     * @param int $level
     * @param int $exp
     * @param int $hp
     * @param int $mp
     * @param int $attack
     * @param int $defence
     * @param int $speed
     * @param string $icon
     * @param int $currentHp
     * @param int $currentMp
     * @param int $x
     * @param int $y
     * @return unknown_type
     */
    function __construct($id, $role, $level, $exp, $hp, $mp, $attack, $defence, $speed,
                         $icon, $x, $y, $width, $height, $currentHp, $currentMp) {
        $this->id = $id;
        $this->role = $role;
        $this->level = $level;
        $this->exp = $exp;
        $this->hp = $hp;
        $this->mp = $mp;
        $this->attack = $attack;
        $this->defence = $defence;
        $this->speed = $speed;
        $this->icon = $icon;
        $this->x = $x;
        $this->y = $y;
        $this->width = $width;
        $this->height = $height;
        $this->currentHp = $currentHp;
        $this->currentMp = $currentMp;
    }

    public function getId() { return $this->id; }
    public function setId($id) { $this->id = $id; }

    public function getRole() { return $this->role; }
    public function setRole($role) { $this->role = $role; }

    public function getLevel() { return $this->level; }
    public function setLevel($level) { $this->level = $level; }

    public function getExp() { return $this->exp; }
    public function setExp($exp) { $this->exp = $exp; }

    public function getHp() { return $this->hp; }
    public function setHp($hp) { $this->hp = $hp; }

    public function getMp() { return $this->mp; }
    public function setMp($mp) { $this->mp = $mp; }

    public function getAttack() { return $this->attack; }
    public function setAttack($attack) { $this->attack = $attack; }

    public function getDefence() { return $this->defence; }
    public function setDefence($defence) { $this->defence = $defence; }

    public function getSpeed() { return $this->speed; }
    public function setSpeed($speed) { $this->speed = $speed; }

    public function getIcon() { return $this->icon; }
    public function setIcon($icon) { $this->icon = $icon; }

    public function getX() { return $this->x; }
    public function setX($x) { $this->x = $x; }

    public function getY() { return $this->y; }
    public function setY($y) { $this->y = $y; }

    public function getWidth() { return $this->width; }
    public function setWidth($width) { $this->width = $width; }

    public function getHeight() { return $this->height; }
    public function setHiehgt($height) { $this->height = $height; }

    public function getCurrentHp() { return $this->currentHp; }
    public function setCurrentHp($currentHp) { $this->currentHp = $currentHp; }

    public function getCurrentMp() { return $this->currentMp; }
    public function setCurrentMp($currentMp) { $this->currentMp = $currentMp; }

    /**
     * Update player bo
     * @return void
     */
    public function update() {
        $handle = new RoleDb();
        $handle->updateRole($this);
    }

    /**
     * Convert PlayerBo to array
     * @return array $player
     */
    public function toArray() {
        return array (
            'id' => $this->getId(),
            'role' => $this->getRole(),
            'level' => $this->getLevel(),
            'exp' => $this->getExp(),
            'hp' => $this->getHp(),
            'mp' => $this->getMp(),
            'attack' => $this->getAttack(),
            'defence' => $this->getDefence(),
            'speed' => $this->getSpeed(),
            'icon' => $this->getIcon(),
            'x' => $this->getX(),
            'y' => $this->getY(),
            'width' => $this->getWidth(),
            'height' => $this->getHeight(),
            'currentHp' => $this->getCurrentHp(),
            'currentMp' => $this->getCurrentMp(),
        );
    }

    /**
     * Convert PlayerBo to json string
     * @return string $player
     */
    public function toJson() {
        return json_encode($this->toArray());
    }
}
