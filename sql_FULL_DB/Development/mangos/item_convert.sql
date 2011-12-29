# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-29 12:03:18
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table mangos.item_convert
DROP TABLE IF EXISTS `item_convert`;
CREATE TABLE IF NOT EXISTS `item_convert` (
  `entry` mediumint(8) unsigned NOT NULL default '0',
  `item` mediumint(8) unsigned NOT NULL default '0',
  PRIMARY KEY  (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Npc System';

# Dumping data for table mangos.item_convert: 10 rows
/*!40000 ALTER TABLE `item_convert` DISABLE KEYS */;
INSERT IGNORE INTO `item_convert` (`entry`, `item`) VALUES
	(50338, 44135),
	(50337, 44136),
	(50335, 44133),
	(50336, 44134),
	(50370, 44152),
	(50367, 44149),
	(50368, 44159),
	(50369, 44150),
	(50372, 44701),
	(50373, 44702);
/*!40000 ALTER TABLE `item_convert` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
