# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-10 02:15:20
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table mangos.player_factionchange_reputations
DROP TABLE IF EXISTS `player_factionchange_reputations`;
CREATE TABLE IF NOT EXISTS `player_factionchange_reputations` (
  `race_A` int(8) NOT NULL default '0',
  `alliance_id` int(8) NOT NULL,
  `commentA` varchar(255) default NULL,
  `race_H` int(8) NOT NULL default '0',
  `horde_id` int(8) NOT NULL,
  `commentH` varchar(255) default NULL,
  PRIMARY KEY  (`alliance_id`,`horde_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

# Dumping data for table mangos.player_factionchange_reputations: 14 rows
/*!40000 ALTER TABLE `player_factionchange_reputations` DISABLE KEYS */;
INSERT IGNORE INTO `player_factionchange_reputations` (`race_A`, `alliance_id`, `commentA`, `race_H`, `horde_id`, `commentH`) VALUES
	(0, 47, 'Ironforge', 0, 530, 'Darkspear Trolls'),
	(0, 509, 'The League of Arathor', 0, 510, 'The Defilers'),
	(0, 730, 'Stormpike Guard', 0, 729, 'Frostwolf Clan'),
	(0, 890, 'Silverwing Sentinels', 0, 889, 'Warsong Outriders'),
	(0, 946, 'Honor Hold', 0, 947, 'Thrallmar'),
	(0, 978, 'Kurenai', 0, 941, 'The Mag\'har'),
	(0, 1037, 'Alliance Vanguard', 0, 1052, 'Horde Expedition'),
	(0, 1050, 'Valiance Expedition', 0, 1085, 'Warsong Offensive'),
	(0, 1068, 'Explorers\' League', 0, 1064, 'The Taunka'),
	(0, 1126, 'The Frostborn', 0, 1067, 'The Hand of Vengeance'),
	(0, 54, 'Gnomeregan Exiles', 0, 81, 'Thunder Bluff'),
	(0, 69, 'Darnassus', 0, 68, 'Undercity'),
	(0, 72, 'Stormwind', 0, 76, 'Orgrimmar'),
	(0, 930, 'Exodar', 0, 911, 'Silvermoon City');
/*!40000 ALTER TABLE `player_factionchange_reputations` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
