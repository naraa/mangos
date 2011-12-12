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

# Dumping structure for table characters.anticheat_log
DROP TABLE IF EXISTS `anticheat_log`;
CREATE TABLE IF NOT EXISTS `anticheat_log` (
  `playername` varchar(32) NOT NULL,
  `checktype` mediumint(8) unsigned NOT NULL,
  `alarm_time` datetime NOT NULL,
  `reason` varchar(255) NOT NULL default 'Unknown',
  `guid` int(11) unsigned NOT NULL,
  `action1` mediumint(8) NOT NULL default '0',
  `action2` mediumint(8) NOT NULL default '0',
  PRIMARY KEY  (`checktype`,`alarm_time`,`guid`),
  KEY `idx_Player` (`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Anticheat log table';

# Dumping data for table characters.anticheat_log: 0 rows
/*!40000 ALTER TABLE `anticheat_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `anticheat_log` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
