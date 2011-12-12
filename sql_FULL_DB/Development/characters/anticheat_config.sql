# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-11 22:54:02
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table characters.anticheat_config
DROP TABLE IF EXISTS `anticheat_config`;
CREATE TABLE IF NOT EXISTS `anticheat_config` (
  `checktype` mediumint(8) unsigned NOT NULL COMMENT 'Type of check',
  `description` varchar(255) default NULL,
  `check_period` int(11) unsigned NOT NULL default '0' COMMENT 'Time period of check, in ms, 0 - always',
  `alarmscount` int(11) unsigned NOT NULL default '1' COMMENT 'Count of alarms before action',
  `disableoperation` tinyint(3) unsigned NOT NULL default '0' COMMENT 'Anticheat disable operations in main core code after check fail',
  `messagenum` int(11) NOT NULL default '0' COMMENT 'Number of system message',
  `intparam1` mediumint(8) NOT NULL default '0' COMMENT 'Int parameter 1',
  `intparam2` mediumint(8) NOT NULL default '0' COMMENT 'Int parameter 2',
  `floatparam1` float NOT NULL default '0' COMMENT 'Float parameter 1',
  `floatparam2` float NOT NULL default '0' COMMENT 'Float parameter 2',
  `action1` mediumint(8) NOT NULL default '0' COMMENT 'Action 1',
  `actionparam1` mediumint(8) NOT NULL default '0' COMMENT 'Action parameter 1',
  `action2` mediumint(8) NOT NULL default '0' COMMENT 'Action 1',
  `actionparam2` mediumint(8) NOT NULL default '0' COMMENT 'Action parameter 1',
  `disabledzones` varchar(255) NOT NULL default '' COMMENT 'List of zones, in which check disabled.',
  PRIMARY KEY  (`checktype`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 PACK_KEYS=0 COMMENT='Anticheat configuration';

# Dumping data for table characters.anticheat_config: 28 rows
/*!40000 ALTER TABLE `anticheat_config` DISABLE KEYS */;
INSERT IGNORE INTO `anticheat_config` (`checktype`, `description`, `check_period`, `alarmscount`, `disableoperation`, `messagenum`, `intparam1`, `intparam2`, `floatparam1`, `floatparam2`, `action1`, `actionparam1`, `action2`, `actionparam2`, `disabledzones`) VALUES
	(0, 'Null check', 0, 1, 0, 11000, 0, 0, 0, 0, 1, 0, 0, 0, ''),
	(1, 'Movement cheat', 0, 1, 0, 11000, 0, 0, 0, 0, 2, 1, 0, 0, ''),
	(2, 'Spell cheat', 0, 1, 0, 11000, 0, 0, 0, 0, 2, 1, 0, 0, ''),
	(3, 'Quest cheat', 0, 1, 0, 11000, 0, 0, 0, 0, 2, 1, 0, 0, ''),
	(4, 'Transport cheat', 0, 3, 0, 11000, 0, 0, 60, 0, 2, 1, 0, 0, ''),
	(5, 'Damage cheat', 0, 1, 0, 11000, 0, 0, 0, 0, 2, 1, 0, 0, ''),
	(6, 'Item cheat', 0, 1, 0, 11000, 0, 0, 0, 0, 2, 1, 0, 0, ''),
	(7, 'Warden check', 0, 1, 0, 11000, 0, 0, 0, 0, 2, 1, 0, 0, ''),
	(101, 'Speed hack', 500, 5, 0, 11000, 10000, 0, 0.0012, 0, 2, 1, 6, 20000, ''),
	(102, 'Fly hack', 500, 5, 0, 11000, 20000, 0, 10, 0, 2, 1, 0, 0, ''),
	(103, 'Wall climb hack', 500, 2, 0, 11000, 10000, 0, 0.0015, 2.37, 2, 1, 0, 0, ''),
	(104, 'Waterwalking hack', 1000, 3, 0, 11000, 20000, 0, 0, 0, 2, 1, 0, 0, ''),
	(105, 'Teleport to plane hack', 500, 1, 0, 11000, 0, 0, 0.0001, 0.1, 2, 1, 0, 0, ''),
	(106, 'AirJump hack', 500, 3, 0, 11000, 30000, 0, 10, 25, 2, 1, 0, 0, ''),
	(107, 'Teleport hack', 0, 1, 0, 11000, 0, 0, 50, 0, 2, 1, 0, 0, ''),
	(108, 'Fall hack', 0, 3, 0, 11000, 10000, 0, 0, 0, 2, 1, 0, 0, ''),
	(109, 'Z Axis hack', 0, 1, 0, 11000, 0, 0, 1e-005, 10, 2, 1, 0, 0, ''),
	(201, 'Spell invalid', 0, 1, 0, 11000, 0, 0, 0, 0, 2, 1, 0, 0, ''),
	(202, 'Spellcast in dead state', 0, 1, 0, 11000, 0, 0, 0, 0, 2, 1, 0, 0, ''),
	(203, 'Spell not valid for player', 0, 1, 0, 11000, 0, 0, 0, 0, 2, 1, 0, 0, ''),
	(204, 'Spell not in player book', 0, 1, 0, 11000, 0, 0, 0, 0, 2, 1, 0, 0, ''),
	(501, 'Spell damage hack', 0, 1, 0, 11000, 0, 50000, 0, 0, 2, 1, 0, 0, ''),
	(502, 'Melee damage hack', 0, 1, 0, 11000, 0, 50000, 0, 0, 2, 1, 0, 0, ''),
	(601, 'Item dupe hack', 0, 1, 0, 11000, 0, 0, 0, 0, 2, 1, 0, 0, ''),
	(701, 'Warden memory check', 0, 1, 0, 11000, 0, 0, 0, 0, 2, 1, 0, 0, ''),
	(702, 'Warden key check', 0, 1, 0, 11000, 0, 0, 0, 0, 2, 1, 0, 0, ''),
	(703, 'Warden checksum check', 0, 1, 0, 11000, 0, 0, 0, 0, 2, 1, 0, 0, ''),
	(704, 'Warden timeout check', 0, 1, 0, 11000, 0, 0, 0, 0, 2, 1, 0, 0, '');
/*!40000 ALTER TABLE `anticheat_config` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
