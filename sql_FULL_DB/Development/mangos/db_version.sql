# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-12 07:18:05
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table mangos.db_version
DROP TABLE IF EXISTS `db_version`;
CREATE TABLE IF NOT EXISTS `db_version` (
  `version` varchar(120) NOT NULL,
  `creature_ai_version` varchar(120) default NULL,
  `cache_id` int(10) default '0',
  `required_11852_01_mangos_gossip_menu` bit(1) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Used DB version notes';

# Dumping data for table mangos.db_version: 1 rows
/*!40000 ALTER TABLE `db_version` DISABLE KEYS */;
INSERT IGNORE INTO `db_version` (`version`, `creature_ai_version`, `cache_id`, `required_11852_01_mangos_gossip_menu`) VALUES
	('Infinity_DB_v_r1', 'ACID 3.0.9 \'Streamlined Perfection\' - Full Release for MaNGOS (3.3.5a Client)', 612, b'00000000');
/*!40000 ALTER TABLE `db_version` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
