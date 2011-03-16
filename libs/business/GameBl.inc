<?php
class GameBl {
    protected $expLadderSetting = array ();
    protected $originalEnemySettings = array ();
    protected $enemySettings = array ();
    protected $bossSettings = array ();
    protected $springSetting = array ();
    protected $gateSetting = array ();
    protected $wallSettings = array ();
    protected $stageSetting = array ();

    /**
     * Construct
     * @return void
     */
    function __construct($uid) {
        $this->uid = $uid;
        $this->expLadderSetting = unserialize(EXP_LADDER);
        $roleDb = new RoleDb();
        $allEnemies = $roleDb->selectEnemies();
        $this->enemySettings = $this->originalEnemySettings = $allEnemies[GAME_ROLE_ENEMY];
        $this->bossSettings = $allEnemies[GAME_ROLE_BOSS];
        $this->springSetting = unserialize(SPRING_INFO);
        $this->gateSetting = unserialize(GATE_INFO);
        $this->wallSettings = unserialize(WALL_INFO);
        $this->stageSetting = unserialize(STAGE_SIZE);
    }

    /**
     * Init of the game
     * @return void
     */
    public function initGame() {
        Console::log('Logic: initGame');
        $playerDb = new RoleDb();
        $player = $playerDb->selectPlayer($this->uid);

        $params = array (
                'spring' => $this->springSetting,
                'gate' => $this->gateSetting,
                'wall' => $this->wallSettings,
                'stage' => $this->stageSetting,
        );
        $params['player'] = $player->toArray();
        $params['enemies'] = array();
        if ($this->enemySettings) {
            foreach ($this->enemySettings as $enemy) {
                $params['enemies'][] = $enemy->toArray();
            }
        }
        $params['bosses'] = array();
        if ($this->bossSettings) {
            foreach ($this->bossSettings as $boss) {
                $params['bosses'][] = $boss->toArray();
            }
        }

        return array ('cmd' => 0, 'params' => $params);
    }

    /**
     * Start battle
     * @param RoleBo $player
     * @param RoleBo $enemy
     * @return void
     */
    public function startBattle($player, $enemy) {
        $response = null;
        // check battle result
        if ($player->getAttack() > $enemy->getAttack()
            && $player->getDefence() > $enemy->getDefence()
            && $player->getSpeed() > $enemy->getSpeed()) { //FIXME currently this logic does not make sense, fix it later
            $response = $this->winBattle($player, $enemy);
        } else {
            $response = $this->loseBattle($player);
        }
        return $response;
    }

    /**
     * Win the battle
     * @param PlayerBo $player
     * @param EnemyBo $enemy
     * @return void
     */
    protected function winBattle($player, $enemy) {
        $response = null;
        // calculate battle hp consumption
        $hpDelta = $player->getHp() * BATTLE_HP_CONSUME;

        if ($player->getCurrentHp() - $hpDelta <= 0) {
            // not enough hp, lose the battle
            $response = $this->loseBattle($player);
        } else {
            // set current hp & check levelup, also handle it
            $player->setCurrentHp($player->getCurrentHp() - $hpDelta);
            $expLadder = $this->expLadderSetting[$player->getLevel()];
            if ($expLadder) {
                // means user still can levelup
                $player->setExp($player->getExp() + $enemy->getExp());
                // handle user exp add & levelup
                if ($player->getExp() >= $expLadder['exp']) {
                    $player->setExp($player->getExp() - $expLadder['exp']);
                    $player->setLevel($player->getLevel() + 1);
                    $player->setHp($player->getHp() + $expLadder['hp']);
                    $player->setMp($player->getMp() + $expLadder['mp']);
                    $player->setAttack($player->getAttack() + $expLadder['attack']);
                    $player->setDefence($player->getDefence() + $expLadder['defence']);
                    $player->setSpeed($player->getSpeed() + $expLadder['speed']);
                }
            }
            $player->update();
            $response = array (
                'cmd' => 4,
                'params' => array (
                    'player' => $player->toArray()
                )
            );
            // update enemies & bosses data
            if ($enemy->getRole() == GAME_ROLE_ENEMY) {
                $this->deleteEnemy($enemy);
                if ($this->enemySettings) {
                    foreach ($this->enemySettings as $emy) {
                        $response['params']['enemies'][] = $emy->toArray();
                    }
                } else {
                    $response['params']['enemies'] = array ();
                }
            } else if ($enemy->getRole() == GAME_ROLE_BOSS) {
                $this->deleteBoss($enemy);
                if ($this->bossSettings) {
                    foreach ($this->bossSettings as $boss) {
                        $response['params']['bosses'][] = $boss->toArray();
                    }
                } else {
                    $response['params']['bosses'] = array ();
                }
            }
        }

        return $response;
    }

    /**
     * Remove the enemy killed by the player
     * @param RoleBo $enemy
     * @return void
     */
    protected function deleteEnemy($enemy) {
        unset($this->enemySettings[$enemy->getId()]);
    }

    /**
     * Remove the boss killed by the player
     * @param RoleBo $enemy
     * @return void
     */
    protected function deleteBoss($enemy) {
        unset($this->bossSettings[$enemy->getId()]);
    }

    /**
     * Lose the battle
     * @param PlayerBo $player
     * @return void
     */
    protected function loseBattle($player) {
        $player->setX(0);
        $player->setY(0);
        $player->update();
        return array ('cmd' => 5, 'params' => '');
    }

    /**
     * Player win the game
     * @param RoleBo $player
     * @return void
     */
    protected function winTheGame($player) {
        $player->setX(0);
        $player->setY(0);
        $player->update();
        return array ('cmd' => 3, 'params' => '');
    }

    /**
     * Handle player move
     * @param int $x move offset of direction X
     * @param int $y move offset of direction Y
     * @return void
     */
    public function move($x, $y) {
        Console::log("Logic: Player move, x: $x, y: $y");
        $playerDb = new RoleDb();
        $player = $playerDb->selectPlayer($this->uid);

        // validation step one, validate whether user knock against the stage edge
        $stepOne = $this->movePlayer($player, $x, $y);
        if ($stepOne !== FALSE) {
            return $stepOne;
        }

        // detect collision result, if not false, means has hit response
        $stepTwo = $this->detectCollision($player, $x, $y);
        if ($stepTwo === FALSE) { // no collision
            $player->update();
            $stepTwo = array ('cmd' => 1, 'params' => array('player' => $player->toArray()));
        }

        return $stepTwo;
    }

    /**
     * Move player and validate whether user knock against the stage edge
     * @param RoleBo $player
     * @param int $x
     * @param int $y
     * @return boolean $response
     */
    protected function movePlayer(&$player, $x, $y) {
        $response = FALSE; // no collision
        if ($x !== 0) { // x move
            $player->setX($player->getX() + $x * PLAYER_STEP);
            if ($player->getX() < $this->stageSetting[0]
                || ($player->getX() + $player->getWidth()) > $this->stageSetting[2]) {
                $response = TRUE;
            }
        } else if ($y !== 0) { // y move
            $player->setY($player->getY() + $y * PLAYER_STEP);
            if ($player->getY() < $this->stageSetting[1]
                || ($player->getY() + $player->getHeight()) > $this->stageSetting[3]) {
                $response = TRUE;
            }
        }
        if ($response) { // means player knock against the stage edge
            $response = array ('cmd' => 100, 'params' => 'Oh! Knock against the stage edge!');
        }

        return $response;
    }

    /**
     * Detect player collision
     * @param RoleBo $player
     * @return boolean TRUE means there is collision
     */
    protected function detectCollision($player, $x, $y) {
        $response = FALSE;
        // check wall
        if ($this->wallSettings) {
            foreach ($this->wallSettings as $wall) {
                if ($this->calcCollision($player, $wall)) {
                    $response = array ('cmd' => 100, 'params' => 'Oh! Knock against the wall!');
                }
            }
        }
        // check spring
        if ($this->springSetting) {
            if ($this->calcCollision($player, $this->springSetting)) {
                $player->setCurrentHp($player->getHp());
                $player->setCurrentMp($player->getMp());
                $player->setX($player->getX() - $x * PLAYER_STEP);
                $player->setY($player->getY() - $y * PLAYER_STEP);
                $player->update();
                $response = array ('cmd' => 2, 'params' => array ('player' => $player->toArray()));
            }
        }
        // check gate
        if ($this->gateSetting) {
            if ($this->calcCollision($player, $this->gateSetting)) {
                $response = $this->winTheGame($player);
            }
        }
        // check enemy
        if ($this->enemySettings) {
            foreach ($this->enemySettings as $enemy) {
                if ($this->calcCollision($player, $enemy)) {
                    $response = $this->startBattle($player, $enemy);
                }
            }
        }
        // check boss
        if ($this->bossSettings) {
            foreach ($this->bossSettings as $boss) {
                if ($this->calcCollision($player, $boss)) {
                    //FIXME logics to get the key, after boss is defeated
                    $response = $this->startBattle($player, $boss);
                }
            }
        }

        return $response;
    }

    /**
     * Calculate whether there is any collision between player & opposite
     * @param RoleBo $player
     * @param RoleBo $opposite
     * @return boolean TRUE means there is collision
     */
    protected function calcCollision($player, $opposite) {
        $result = FALSE;
        if ($opposite instanceof RoleBo) {
            $xDirectionCalc1 = abs(($opposite->getX() + $opposite->getWidth() / 2) - ($player->getX() + $player->getWidth() / 2));
            $xDirectionCalc2 = abs(($opposite->getWidth() + $player->getWidth()) / 2);
            $yDirectionCalc1 = abs(($opposite->getY() + $opposite->getHeight() / 2) - ($player->getY() + $player->getHeight() / 2));
            $yDirectionCalc2 = abs(($opposite->getHeight() + $player->getHeight()) / 2);
            if ($xDirectionCalc1 < $xDirectionCalc2 && $yDirectionCalc1 < $yDirectionCalc2) {
                $result = TRUE;
            }
        } else if (is_array($opposite)) {
            $xDirectionCalc1 = abs(($opposite[0] + $opposite[2] / 2) - ($player->getX() + $player->getWidth() / 2));
            $xDirectionCalc2 = abs(($opposite[2] + $player->getWidth()) / 2);
            $yDirectionCalc1 = abs(($opposite[1] + $opposite[3] / 2) - ($player->getY() + $player->getHeight() / 2));
            $yDirectionCalc2 = abs(($opposite[3] + $player->getHeight()) / 2);
            if ($xDirectionCalc1 < $xDirectionCalc2 && $yDirectionCalc1 < $yDirectionCalc2) {
                $result = TRUE;
            }
        } else {
            throw new Exception('Error opposite to check collision!');
        }

        return $result;
    }
}
