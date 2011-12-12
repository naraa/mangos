# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-11 22:55:06
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table realmd.account_forcepermission
DROP TABLE IF EXISTS `account_forcepermission`;
CREATE TABLE IF NOT EXISTS `account_forcepermission` (
  `AccountID` int(11) unsigned NOT NULL default '0',
  `realmID` int(3) unsigned NOT NULL default '0',
  `Security` int(3) unsigned NOT NULL default '0',
  `Comment` varchar(32) NOT NULL default '',
  PRIMARY KEY  (`AccountID`,`realmID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

# Dumping data for table realmd.account_forcepermission: 0 rows
/*!40000 ALTER TABLE `account_forcepermission` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_forcepermission` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
