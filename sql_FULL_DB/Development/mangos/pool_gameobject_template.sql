# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-29 12:03:33
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table mangos.pool_gameobject_template
DROP TABLE IF EXISTS `pool_gameobject_template`;
CREATE TABLE IF NOT EXISTS `pool_gameobject_template` (
  `id` int(10) unsigned NOT NULL default '0',
  `pool_entry` mediumint(8) unsigned NOT NULL default '0',
  `chance` float unsigned NOT NULL default '0',
  `description` varchar(255) NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `pool_idx` (`pool_entry`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

# Dumping data for table mangos.pool_gameobject_template: 39 rows
/*!40000 ALTER TABLE `pool_gameobject_template` DISABLE KEYS */;
INSERT IGNORE INTO `pool_gameobject_template` (`id`, `pool_entry`, `chance`, `description`) VALUES
	(186684, 1132, 0, ''),
	(187264, 1129, 0, ''),
	(187333, 1130, 0, ''),
	(171938, 1131, 0, ''),
	(185939, 1133, 0, 'GO=185939'),
	(182139, 1227, 0, 'GO=182139'),
	(164, 1228, 0, 'GO=164'),
	(333, 1229, 0, 'GO=333'),
	(334, 1230, 0, 'GO=334'),
	(35252, 1231, 0, 'GO=35252'),
	(337, 1232, 0, 'GO=337'),
	(1673, 1233, 0, 'GO=1673'),
	(2724, 1234, 0, 'GO=2724'),
	(2912, 1235, 0, 'GO=2912'),
	(2910, 1236, 0, 'GO=2910'),
	(140971, 1241, 0, 'GO=140971'),
	(183945, 1237, 0, 'GO=183945'),
	(186938, 2686, 0, 'GO=186938'),
	(182265, 13671, 0, ''),
	(192818, 13672, 0, ''),
	(193610, 13673, 0, ''),
	(184793, 14135, 0, ''),
	(181250, 14136, 0, ''),
	(181251, 14137, 0, ''),
	(181252, 14138, 0, ''),
	(182355, 14139, 0, ''),
	(191568, 14140, 0, ''),
	(157936, 1102, 0, ''),
	(202080, 1104, 0, ''),
	(202081, 14141, 0, ''),
	(202083, 14142, 0, ''),
	(202082, 14143, 0, ''),
	(181107, 14144, 0, ''),
	(182069, 14145, 0, ''),
	(182053, 14146, 0, ''),
	(2712, 14148, 0, ''),
	(182941, 14149, 0, ''),
	(187039, 14150, 0, ''),
	(180654, 14151, 0, '');
/*!40000 ALTER TABLE `pool_gameobject_template` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
