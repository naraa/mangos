# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-11 23:53:32
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table mangos.spell_linked
DROP TABLE IF EXISTS `spell_linked`;
CREATE TABLE IF NOT EXISTS `spell_linked` (
  `entry` int(10) unsigned NOT NULL COMMENT 'Spell entry',
  `linked_entry` int(10) unsigned NOT NULL COMMENT 'Linked spell entry',
  `type` int(10) unsigned NOT NULL default '0' COMMENT 'Type of link',
  `effect_mask` int(10) unsigned NOT NULL default '0' COMMENT 'mask of effect (NY)',
  `comment` varchar(255) NOT NULL default '',
  PRIMARY KEY  (`entry`,`linked_entry`,`type`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 PACK_KEYS=0 COMMENT='Linked spells storage';

# Dumping data for table mangos.spell_linked: 3 rows
/*!40000 ALTER TABLE `spell_linked` DISABLE KEYS */;
INSERT IGNORE INTO `spell_linked` (`entry`, `linked_entry`, `type`, `effect_mask`, `comment`) VALUES
	(25780, 57339, 1, 0, 'Paladin - threat addon after 3.0'),
	(21178, 57339, 1, 0, 'Druid Bear form - threat addon after 3.0'),
	(7376, 57339, 1, 0, 'Warrior Defensive Stance Passive - threat addon after 3.0');
/*!40000 ALTER TABLE `spell_linked` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
