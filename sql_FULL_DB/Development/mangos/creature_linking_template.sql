# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-29 12:03:03
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table mangos.creature_linking_template
DROP TABLE IF EXISTS `creature_linking_template`;
CREATE TABLE IF NOT EXISTS `creature_linking_template` (
  `entry` int(10) unsigned NOT NULL auto_increment COMMENT 'creature_template.entry of the slave mob that is linked',
  `map` mediumint(8) unsigned NOT NULL COMMENT 'Id of map of the mobs',
  `master_entry` int(10) unsigned NOT NULL COMMENT 'master to trigger events',
  `flag` mediumint(8) unsigned NOT NULL COMMENT 'flag - describing what should happen when',
  PRIMARY KEY  (`entry`,`map`)
) ENGINE=MyISAM AUTO_INCREMENT=30683 DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Creature Linking System';

# Dumping data for table mangos.creature_linking_template: 29 rows
/*!40000 ALTER TABLE `creature_linking_template` DISABLE KEYS */;
INSERT IGNORE INTO `creature_linking_template` (`entry`, `map`, `master_entry`, `flag`) VALUES
	(12119, 409, 12118, 519),
	(11673, 409, 11982, 1024),
	(11661, 409, 12259, 7),
	(12099, 409, 12057, 7),
	(11672, 409, 11988, 39),
	(11662, 409, 12098, 7),
	(11663, 409, 12018, 7),
	(11664, 409, 12018, 7),
	(10814, 229, 10363, 7),
	(11373, 309, 14507, 7),
	(8120, 209, 7267, 1),
	(7268, 209, 7267, 1),
	(8319, 109, 5709, 1),
	(5280, 109, 5709, 1),
	(5277, 109, 5709, 1),
	(5283, 109, 5709, 1),
	(5722, 109, 5709, 1),
	(5719, 109, 5709, 1),
	(15984, 531, 15516, 519),
	(29240, 602, 28586, 519),
	(30680, 615, 28860, 1),
	(30682, 615, 28860, 1),
	(30681, 615, 28860, 1),
	(30453, 615, 28860, 1),
	(16506, 533, 15953, 7),
	(16803, 533, 16061, 7),
	(16809, 540, 16808, 1),
	(14892, 1, 14857, 512),
	(2532, 0, 2533, 656);
/*!40000 ALTER TABLE `creature_linking_template` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
