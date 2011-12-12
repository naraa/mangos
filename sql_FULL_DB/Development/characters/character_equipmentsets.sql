# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-11 22:54:04
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table characters.character_equipmentsets
DROP TABLE IF EXISTS `character_equipmentsets`;
CREATE TABLE IF NOT EXISTS `character_equipmentsets` (
  `guid` int(11) NOT NULL default '0',
  `setguid` bigint(20) unsigned NOT NULL auto_increment,
  `setindex` tinyint(4) NOT NULL default '0',
  `name` varchar(100) NOT NULL,
  `iconname` varchar(100) NOT NULL,
  `ignore_mask` int(11) unsigned NOT NULL default '0',
  `item0` int(11) unsigned NOT NULL default '0',
  `item1` int(11) unsigned NOT NULL default '0',
  `item2` int(11) unsigned NOT NULL default '0',
  `item3` int(11) unsigned NOT NULL default '0',
  `item4` int(11) unsigned NOT NULL default '0',
  `item5` int(11) unsigned NOT NULL default '0',
  `item6` int(11) unsigned NOT NULL default '0',
  `item7` int(11) unsigned NOT NULL default '0',
  `item8` int(11) unsigned NOT NULL default '0',
  `item9` int(11) unsigned NOT NULL default '0',
  `item10` int(11) unsigned NOT NULL default '0',
  `item11` int(11) unsigned NOT NULL default '0',
  `item12` int(11) unsigned NOT NULL default '0',
  `item13` int(11) unsigned NOT NULL default '0',
  `item14` int(11) unsigned NOT NULL default '0',
  `item15` int(11) unsigned NOT NULL default '0',
  `item16` int(11) unsigned NOT NULL default '0',
  `item17` int(11) unsigned NOT NULL default '0',
  `item18` int(11) unsigned NOT NULL default '0',
  PRIMARY KEY  (`setguid`),
  UNIQUE KEY `idx_set` (`guid`,`setguid`,`setindex`),
  KEY `Idx_setindex` (`setindex`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

# Dumping data for table characters.character_equipmentsets: 0 rows
/*!40000 ALTER TABLE `character_equipmentsets` DISABLE KEYS */;
/*!40000 ALTER TABLE `character_equipmentsets` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
