# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-29 12:03:16
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table mangos.gameobject_addon
DROP TABLE IF EXISTS `gameobject_addon`;
CREATE TABLE IF NOT EXISTS `gameobject_addon` (
  `guid` int(10) unsigned NOT NULL default '0',
  `path_rotation0` float NOT NULL default '0',
  `path_rotation1` float NOT NULL default '0',
  `path_rotation2` float NOT NULL default '0',
  `path_rotation3` float NOT NULL default '1',
  PRIMARY KEY  (`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Gameobject System';

# Dumping data for table mangos.gameobject_addon: 9 rows
/*!40000 ALTER TABLE `gameobject_addon` DISABLE KEYS */;
INSERT IGNORE INTO `gameobject_addon` (`guid`, `path_rotation0`, `path_rotation1`, `path_rotation2`, `path_rotation3`) VALUES
	(43835, 0, 0, -0.932008, 0.362437),
	(52137, 0, 0, 0.99999, 0.00436634),
	(52135, 0, 0, 0.99999, 0.00436634),
	(53535, 0, 0, 0.99999, 0.00436634),
	(53536, 0, 0, 0.99999, 0.00436634),
	(16181, 0, 0, 0.95502, 0.296542),
	(42073, 0, 0, 0.694658, 0.71934),
	(47467, 0, 0, 0.999657, 0.0261769),
	(5869, 0, 0, -0.522498, 0.85264);
/*!40000 ALTER TABLE `gameobject_addon` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
