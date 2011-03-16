DROP TABLE IF EXISTS `dungeon`.`dungeon_roles`;
CREATE TABLE `dungeon`.`dungeon_roles` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `role` int(10) unsigned NOT NULL,
  `level` int(10) unsigned NOT NULL,
  `exp` int(10) unsigned NOT NULL,
  `hp` int(10) unsigned NOT NULL,
  `mp` int(10) unsigned NOT NULL,
  `attack` int(10) unsigned NOT NULL,
  `defence` int(10) unsigned NOT NULL,
  `speed` int(10) unsigned NOT NULL,
  `icon` varchar(20) NOT NULL,
  `x` int(10) unsigned NOT NULL,
  `y` int(10) unsigned NOT NULL,
  `width` int(10) unsigned NOT NULL,
  `height` int(10) unsigned NOT NULL,
  `current_hp` int(10) unsigned NOT NULL,
  `current_mp` int(10) unsigned NOT NULL,
  primary key (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=UTF8;

INSERT INTO `dungeon`.`dungeon_roles` (`role`, `level`, `exp`, `hp`, `mp`, `attack`, `defence`, `speed`, `icon`, `x`, `y`, `width`, `height`, `current_hp`, `current_mp`)
VALUES (0, 1, 0, 100, 50, 2, 2, 2, 'android.jpg', 0, 0, 50, 50, 100, 50);
INSERT INTO `dungeon`.`dungeon_roles` (`role`, `level`, `exp`, `hp`, `mp`, `attack`, `defence`, `speed`, `icon`, `x`, `y`, `width`, `height`, `current_hp`, `current_mp`)
VALUES (1, 1, 50, 100, 20, 1, 1, 1, 'armor1.jpg', 480, 120, 53, 80, 100, 20);
INSERT INTO `dungeon`.`dungeon_roles` (`role`, `level`, `exp`, `hp`, `mp`, `attack`, `defence`, `speed`, `icon`, `x`, `y`, `width`, `height`, `current_hp`, `current_mp`)
VALUES (1, 3, 150, 250, 30, 4, 4, 4, 'armor2.jpg', 530, 630, 80, 69, 250, 30);
INSERT INTO `dungeon`.`dungeon_roles` (`role`, `level`, `exp`, `hp`, `mp`, `attack`, `defence`, `speed`, `icon`, `x`, `y`, `width`, `height`, `current_hp`, `current_mp`)
VALUES (1, 4, 350, 350, 50, 7, 7, 7, 'armor3.jpg', 820, 510, 80, 73, 350, 50);
INSERT INTO `dungeon`.`dungeon_roles` (`role`, `level`, `exp`, `hp`, `mp`, `attack`, `defence`, `speed`, `icon`, `x`, `y`, `width`, `height`, `current_hp`, `current_mp`)
VALUES (2, 2, 200, 250, 50, 2, 2, 2, 'BOSS1.jpg', 280, 10, 100, 100, 250, 50);
INSERT INTO `dungeon`.`dungeon_roles` (`role`, `level`, `exp`, `hp`, `mp`, `attack`, `defence`, `speed`, `icon`, `x`, `y`, `width`, `height`, `current_hp`, `current_mp`)
VALUES (2, 3, 200, 250, 50, 4, 4, 4, 'BOSS2.jpg', 900, 680, 100, 141, 250, 50);
INSERT INTO `dungeon`.`dungeon_roles` (`role`, `level`, `exp`, `hp`, `mp`, `attack`, `defence`, `speed`, `icon`, `x`, `y`, `width`, `height`, `current_hp`, `current_mp`)
VALUES (2, 5, 400, 700, 50, 11, 11, 11, 'BOSS3.jpg', 870, 100, 100, 97, 700, 50);