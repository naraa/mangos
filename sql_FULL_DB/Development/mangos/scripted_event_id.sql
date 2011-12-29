# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-29 12:03:36
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table mangos.scripted_event_id
DROP TABLE IF EXISTS `scripted_event_id`;
CREATE TABLE IF NOT EXISTS `scripted_event_id` (
  `id` mediumint(8) NOT NULL,
  `ScriptName` char(64) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Script library scripted events';

# Dumping data for table mangos.scripted_event_id: 23 rows
/*!40000 ALTER TABLE `scripted_event_id` DISABLE KEYS */;
INSERT IGNORE INTO `scripted_event_id` (`id`, `ScriptName`) VALUES
	(11225, 'event_taxi_stormcrow'),
	(2228, 'event_spell_altar_boss_aggro'),
	(2268, 'event_spell_altar_boss_aggro'),
	(8328, 'npc_kroshius'),
	(2488, 'event_go_zulfarrak_gong'),
	(13513, 'event_spell_soul_captured_credit'),
	(13514, 'event_spell_soul_captured_credit'),
	(13515, 'event_spell_soul_captured_credit'),
	(13516, 'event_spell_soul_captured_credit'),
	(5618, 'event_spell_gandling_shadow_portal'),
	(5619, 'event_spell_gandling_shadow_portal'),
	(5620, 'event_spell_gandling_shadow_portal'),
	(5621, 'event_spell_gandling_shadow_portal'),
	(5622, 'event_spell_gandling_shadow_portal'),
	(5623, 'event_spell_gandling_shadow_portal'),
	(3094, 'event_antalarion_statue_activation'),
	(3095, 'event_antalarion_statue_activation'),
	(3097, 'event_antalarion_statue_activation'),
	(3098, 'event_antalarion_statue_activation'),
	(3099, 'event_antalarion_statue_activation'),
	(3100, 'event_antalarion_statue_activation'),
	(8502, 'event_avatar_of_hakkar'),
	(9735, 'event_spell_saronite_barrier');
/*!40000 ALTER TABLE `scripted_event_id` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
