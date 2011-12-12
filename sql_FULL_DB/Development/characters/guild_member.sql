# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-11 22:54:07
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table characters.guild_member
DROP TABLE IF EXISTS `guild_member`;
CREATE TABLE IF NOT EXISTS `guild_member` (
  `guildid` int(6) unsigned NOT NULL default '0',
  `guid` int(11) unsigned NOT NULL default '0',
  `rank` tinyint(2) unsigned NOT NULL default '0',
  `pnote` varchar(255) NOT NULL default '',
  `offnote` varchar(255) NOT NULL default '',
  `BankResetTimeMoney` int(11) unsigned NOT NULL default '0',
  `BankRemMoney` int(11) unsigned NOT NULL default '0',
  `BankResetTimeTab0` int(11) unsigned NOT NULL default '0',
  `BankRemSlotsTab0` int(11) unsigned NOT NULL default '0',
  `BankResetTimeTab1` int(11) unsigned NOT NULL default '0',
  `BankRemSlotsTab1` int(11) unsigned NOT NULL default '0',
  `BankResetTimeTab2` int(11) unsigned NOT NULL default '0',
  `BankRemSlotsTab2` int(11) unsigned NOT NULL default '0',
  `BankResetTimeTab3` int(11) unsigned NOT NULL default '0',
  `BankRemSlotsTab3` int(11) unsigned NOT NULL default '0',
  `BankResetTimeTab4` int(11) unsigned NOT NULL default '0',
  `BankRemSlotsTab4` int(11) unsigned NOT NULL default '0',
  `BankResetTimeTab5` int(11) unsigned NOT NULL default '0',
  `BankRemSlotsTab5` int(11) unsigned NOT NULL default '0',
  UNIQUE KEY `guid_key` (`guid`),
  KEY `guildid_key` (`guildid`),
  KEY `guildid_rank_key` (`guildid`,`rank`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Guild System';

# Dumping data for table characters.guild_member: 0 rows
/*!40000 ALTER TABLE `guild_member` DISABLE KEYS */;
/*!40000 ALTER TABLE `guild_member` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
