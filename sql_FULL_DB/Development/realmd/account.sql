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

# Dumping structure for table realmd.account
DROP TABLE IF EXISTS `account`;
CREATE TABLE IF NOT EXISTS `account` (
  `id` int(11) unsigned NOT NULL auto_increment COMMENT 'Identifier',
  `username` varchar(32) NOT NULL default '',
  `sha_pass_hash` varchar(40) NOT NULL default '',
  `gmlevel` tinyint(3) unsigned NOT NULL default '0',
  `sessionkey` longtext,
  `v` longtext,
  `s` longtext,
  `email` text,
  `joindate` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `last_ip` varchar(30) NOT NULL default '0.0.0.0',
  `failed_logins` int(11) unsigned NOT NULL default '0',
  `locked` tinyint(3) unsigned NOT NULL default '0',
  `last_login` timestamp NOT NULL default '0000-00-00 00:00:00',
  `active_realm_id` int(11) unsigned NOT NULL default '0',
  `expansion` tinyint(3) unsigned NOT NULL default '0',
  `mutetime` bigint(40) unsigned NOT NULL default '0',
  `locale` tinyint(3) unsigned NOT NULL default '0',
  `os` varchar(4) NOT NULL default '',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `idx_username` (`username`),
  KEY `idx_gmlevel` (`gmlevel`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Account System';

# Dumping data for table realmd.account: 4 rows
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT IGNORE INTO `account` (`id`, `username`, `sha_pass_hash`, `gmlevel`, `sessionkey`, `v`, `s`, `email`, `joindate`, `last_ip`, `failed_logins`, `locked`, `last_login`, `active_realm_id`, `expansion`, `mutetime`, `locale`, `os`) VALUES
	(1, 'ADMINISTRATOR', 'a34b29541b87b7e4823683ce6c7bf6ae68beaaac', 3, '', '0', '0', '', '2006-04-25 06:18:56', '127.0.0.1', 0, 0, '0000-00-00 00:00:00', 0, 0, 0, 0, ''),
	(2, 'GAMEMASTER', '7841e21831d7c6bc0b57fbe7151eb82bd65ea1f9', 2, '', '0', '0', '', '2006-04-25 06:18:56', '127.0.0.1', 0, 0, '0000-00-00 00:00:00', 0, 0, 0, 0, ''),
	(3, 'MODERATOR', 'a7f5fbff0b4eec2d6b6e78e38e8312e64d700008', 1, '', '0', '0', '', '2006-04-25 06:19:35', '127.0.0.1', 0, 0, '0000-00-00 00:00:00', 0, 0, 0, 0, ''),
	(4, 'PLAYER', '3ce8a96d17c5ae88a30681024e86279f1a38c041', 0, '', '0', '0', '', '2006-04-25 06:19:35', '127.0.0.1', 0, 0, '0000-00-00 00:00:00', 0, 0, 0, 0, ''),
	(5, 'ADMIN', '8301316D0D8448A34FA6D0C6BF1CBFA2B4A1A93A', 3, NULL, NULL, NULL, NULL, '2011-12-11 22:54:33', '0.0.0.0', 0, 0, '0000-00-00 00:00:00', 0, 2, 0, 0, '');
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
