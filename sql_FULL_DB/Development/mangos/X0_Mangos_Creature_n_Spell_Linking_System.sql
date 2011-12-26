-- example for creature_linking
/* Example behaviour, MOLTEN CORE
 *
 *  TEST WITHOUT SD2, as SD2 has parts of the same functionality already
 *
 * Currently implemented flags
 *   FLAG_AGGRO_ON_AGGRO            = 0x0001,    1
 *   FLAG_TO_AGGRO_ON_AGGRO         = 0x0002,    2
 *   FLAG_RESPAWN_ON_EVADE          = 0x0004,    4
 *   FLAG_TO_RESPAWN_ON_EVADE       = 0x0008,    8
 *   FLAG_DESPAWN_ON_DEATH          = 0x0010,   16
 *   FLAG_SELFKILL_ON_DEATH         = 0x0020,   32
 *   FLAG_RESPAWN_ON_DEATH          = 0x0040,   64
 *   FLAG_RESPAWN_ON_RESPAWN        = 0x0080,  128
 *   FLAG_DESPAWN_ON_RESPAWN        = 0x0100,  256
 *   FLAG_FOLLOW                    = 0x0200,  512
 *   FLAG_CANT_SPAWN_IF_BOSS_DEAD   = 0x0400, 1024
 *   FLAG_CANT_SPAWN_IF_BOSS_ALIVE  = 0x0800, 2048
 */

INSERT IGNORE INTO creature_linking_template VALUES
(12119, 409, 12118, 521), -- Lucifron
(11661, 409, 12259, 7), -- Gehennas
(11673, 409, 11982, 1024), -- Magmadar, testing, prevent respawning of his dogs
(12099, 409, 12057, 2), -- Garr (testing)
(11672, 409, 11988, 39), -- Golemagg
(11666, 409, 12057, 7), -- Garr- testing, despawn other npcs in area
(11662, 409, 12098, 135), -- Sulfuron (test)
(11658, 409, 448, 256); -- testing..


-- Implement spell linked definitions storage
CREATE TABLE IF NOT EXISTS `spell_linked` (
    `entry`            int(10) unsigned NOT NULL COMMENT 'Spell entry',
    `linked_entry`     int(10) unsigned NOT NULL COMMENT 'Linked spell entry',
    `type`             int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Type of link',
    `effect_mask`      int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'mask of effect (NY)',
    `comment`          varchar(255) NOT NULL DEFAULT '',
     PRIMARY KEY (`entry`,`linked_entry`,`type`)
) DEFAULT CHARSET=utf8 PACK_KEYS=0 COMMENT='Linked spells storage';

DELETE FROM `spell_linked` WHERE `entry` = 25780;
INSERT INTO `spell_linked` (`entry`, `linked_entry`, `type`, `effect_mask`, `comment`) VALUES
(25780, 57339, 1, 0, 'Paladin - threat addon after 3.0');

DELETE FROM `spell_linked` WHERE `entry` = 21178;
INSERT INTO `spell_linked` (`entry`, `linked_entry`, `type`, `effect_mask`, `comment`) VALUES
(21178, 57339, 1, 0, 'Druid Bear form - threat addon after 3.0');

DELETE FROM `spell_linked` WHERE `entry` = 7376;
INSERT INTO `spell_linked` (`entry`, `linked_entry`, `type`, `effect_mask`, `comment`) VALUES
(7376, 57339, 1, 0, 'Warrior Defensive Stance Passive - threat addon after 3.0');

