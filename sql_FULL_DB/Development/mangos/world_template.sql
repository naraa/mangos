# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-29 12:03:37
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table mangos.world_template
DROP TABLE IF EXISTS `world_template`;
CREATE TABLE IF NOT EXISTS `world_template` (
  `map` smallint(5) unsigned NOT NULL,
  `ScriptName` varchar(128) NOT NULL default '',
  PRIMARY KEY  (`map`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

# Dumping data for table mangos.world_template: 4 rows
/*!40000 ALTER TABLE `world_template` DISABLE KEYS */;
INSERT IGNORE INTO `world_template` (`map`, `ScriptName`) VALUES
	(1, 'world_map_kalimdor'),
	(0, 'world_map_eastern_kingdoms'),
	(530, 'world_map_outland'),
	(571, 'world_map_northrend');
/*!40000 ALTER TABLE `world_template` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
