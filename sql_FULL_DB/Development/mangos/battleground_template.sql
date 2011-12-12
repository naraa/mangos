# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-11 23:52:50
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table mangos.battleground_template
DROP TABLE IF EXISTS `battleground_template`;
CREATE TABLE IF NOT EXISTS `battleground_template` (
  `id` mediumint(8) unsigned NOT NULL,
  `MinPlayersPerTeam` smallint(5) unsigned NOT NULL default '0',
  `MaxPlayersPerTeam` smallint(5) unsigned NOT NULL default '0',
  `AllianceStartLoc` mediumint(8) unsigned NOT NULL,
  `AllianceStartO` float NOT NULL,
  `HordeStartLoc` mediumint(8) unsigned NOT NULL,
  `HordeStartO` float NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

# Dumping data for table mangos.battleground_template: 13 rows
/*!40000 ALTER TABLE `battleground_template` DISABLE KEYS */;
INSERT IGNORE INTO `battleground_template` (`id`, `MinPlayersPerTeam`, `MaxPlayersPerTeam`, `AllianceStartLoc`, `AllianceStartO`, `HordeStartLoc`, `HordeStartO`) VALUES
	(1, 40, 40, 611, 3.6, 610, 1.24),
	(2, 10, 10, 769, 3.14159, 770, 0),
	(3, 15, 15, 890, 3.40156, 889, 0.263892),
	(4, 5, 5, 929, 5.21, 936, 2.06),
	(5, 5, 5, 939, 4, 940, 0.903205),
	(6, 5, 5, 0, 0, 0, 0),
	(7, 15, 15, 1103, 3.40156, 1104, 0.263892),
	(8, 5, 5, 1258, 4.83, 1259, 1.7),
	(9, 5, 15, 1367, 0, 1368, 0),
	(10, 5, 5, 1362, 0, 1363, 3.14),
	(11, 5, 5, 1364, 4.72, 1365, 1.6),
	(30, 40, 40, 1485, 0, 1486, 3.14159),
	(32, 5, 40, 0, 0, 0, 0);
/*!40000 ALTER TABLE `battleground_template` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
