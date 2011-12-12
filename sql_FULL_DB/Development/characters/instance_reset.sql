# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-11 22:54:08
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table characters.instance_reset
DROP TABLE IF EXISTS `instance_reset`;
CREATE TABLE IF NOT EXISTS `instance_reset` (
  `mapid` int(11) unsigned NOT NULL default '0',
  `difficulty` tinyint(1) unsigned NOT NULL default '0',
  `resettime` bigint(40) unsigned NOT NULL default '0',
  PRIMARY KEY  (`mapid`,`difficulty`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

# Dumping data for table characters.instance_reset: 71 rows
/*!40000 ALTER TABLE `instance_reset` DISABLE KEYS */;
INSERT IGNORE INTO `instance_reset` (`mapid`, `difficulty`, `resettime`) VALUES
	(249, 0, 1323835200),
	(309, 0, 1323921600),
	(409, 0, 1323835200),
	(469, 0, 1323835200),
	(509, 0, 1323921600),
	(531, 0, 1323835200),
	(532, 0, 1323835200),
	(533, 0, 1323835200),
	(534, 0, 1323835200),
	(544, 0, 1323835200),
	(548, 0, 1323835200),
	(550, 0, 1323835200),
	(564, 0, 1323835200),
	(565, 0, 1323835200),
	(568, 0, 1323921600),
	(580, 0, 1323835200),
	(603, 0, 1323835200),
	(615, 0, 1323835200),
	(616, 0, 1323835200),
	(624, 0, 1323835200),
	(631, 0, 1323835200),
	(649, 0, 1323835200),
	(724, 0, 1323835200),
	(249, 1, 1323835200),
	(269, 1, 1323748800),
	(533, 1, 1323835200),
	(540, 1, 1323748800),
	(542, 1, 1323748800),
	(543, 1, 1323748800),
	(545, 1, 1323748800),
	(546, 1, 1323748800),
	(547, 1, 1323748800),
	(552, 1, 1323748800),
	(553, 1, 1323748800),
	(554, 1, 1323748800),
	(555, 1, 1323748800),
	(556, 1, 1323748800),
	(557, 1, 1323748800),
	(558, 1, 1323748800),
	(560, 1, 1323748800),
	(574, 1, 1323748800),
	(575, 1, 1323748800),
	(576, 1, 1323748800),
	(578, 1, 1323748800),
	(585, 1, 1323748800),
	(595, 1, 1323748800),
	(598, 1, 1323748800),
	(599, 1, 1323748800),
	(600, 1, 1323748800),
	(601, 1, 1323748800),
	(602, 1, 1323748800),
	(603, 1, 1323835200),
	(604, 1, 1323748800),
	(608, 1, 1323748800),
	(615, 1, 1323835200),
	(616, 1, 1323835200),
	(619, 1, 1323748800),
	(624, 1, 1323835200),
	(631, 1, 1323835200),
	(632, 1, 1323748800),
	(649, 1, 1323835200),
	(650, 1, 1323748800),
	(658, 1, 1323748800),
	(668, 1, 1323748800),
	(724, 1, 1323835200),
	(631, 2, 1323835200),
	(649, 2, 1323835200),
	(724, 2, 1323835200),
	(631, 3, 1323835200),
	(649, 3, 1323835200),
	(724, 3, 1323835200);
/*!40000 ALTER TABLE `instance_reset` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
