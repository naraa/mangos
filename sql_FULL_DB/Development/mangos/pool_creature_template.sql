# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-29 12:03:32
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table mangos.pool_creature_template
DROP TABLE IF EXISTS `pool_creature_template`;
CREATE TABLE IF NOT EXISTS `pool_creature_template` (
  `id` int(10) unsigned NOT NULL default '0',
  `pool_entry` mediumint(8) unsigned NOT NULL default '0',
  `chance` float unsigned NOT NULL default '0',
  `description` varchar(255) NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `pool_idx` (`pool_entry`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

# Dumping data for table mangos.pool_creature_template: 3 rows
/*!40000 ALTER TABLE `pool_creature_template` DISABLE KEYS */;
INSERT IGNORE INTO `pool_creature_template` (`id`, `pool_entry`, `chance`, `description`) VALUES
	(28362, 334, 0, 'NPC=28362'),
	(832, 335, 0, 'NPC=832'),
	(13602, 9867, 0, 'The Abominable Greench(13602)');
/*!40000 ALTER TABLE `pool_creature_template` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
