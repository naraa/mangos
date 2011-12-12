# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-11 22:54:09
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table characters.saved_variables
DROP TABLE IF EXISTS `saved_variables`;
CREATE TABLE IF NOT EXISTS `saved_variables` (
  `NextArenaPointDistributionTime` bigint(40) unsigned NOT NULL default '0',
  `NextDailyQuestResetTime` bigint(40) unsigned NOT NULL default '0',
  `NextWeeklyQuestResetTime` bigint(40) unsigned NOT NULL default '0',
  `NextRandomBGResetTime` bigint(40) unsigned NOT NULL default '0',
  `NextMonthlyQuestResetTime` bigint(40) unsigned NOT NULL default '0',
  `cleaning_flags` int(11) unsigned NOT NULL default '0'
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Variable Saves';

# Dumping data for table characters.saved_variables: 1 rows
/*!40000 ALTER TABLE `saved_variables` DISABLE KEYS */;
INSERT IGNORE INTO `saved_variables` (`NextArenaPointDistributionTime`, `NextDailyQuestResetTime`, `NextWeeklyQuestResetTime`, `NextRandomBGResetTime`, `NextMonthlyQuestResetTime`, `cleaning_flags`) VALUES
	(0, 1323687600, 1323860400, 1323687600, 1325394000, 0);
/*!40000 ALTER TABLE `saved_variables` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
