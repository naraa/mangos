# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-10 02:15:04
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table mangos.gameobject_battleground
DROP TABLE IF EXISTS `gameobject_battleground`;
CREATE TABLE IF NOT EXISTS `gameobject_battleground` (
  `guid` int(10) unsigned NOT NULL COMMENT 'GameObject''s GUID',
  `event1` tinyint(3) unsigned NOT NULL COMMENT 'main event',
  `event2` tinyint(3) unsigned NOT NULL COMMENT 'sub event',
  PRIMARY KEY  (`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='GameObject battleground indexing system';

# Dumping data for table mangos.gameobject_battleground: 609 rows
/*!40000 ALTER TABLE `gameobject_battleground` DISABLE KEYS */;
INSERT IGNORE INTO `gameobject_battleground` (`guid`, `event1`, `event2`) VALUES
	(150000, 0, 0),
	(150001, 1, 0),
	(150013, 254, 0),
	(150012, 254, 0),
	(150011, 254, 0),
	(150010, 254, 0),
	(150009, 254, 0),
	(150008, 254, 0),
	(150018, 0, 3),
	(150014, 0, 3),
	(150020, 0, 1),
	(150015, 0, 1),
	(150021, 0, 0),
	(150019, 0, 4),
	(150016, 0, 4),
	(150017, 0, 2),
	(150026, 1, 3),
	(150022, 1, 3),
	(150028, 1, 1),
	(150023, 1, 1),
	(150029, 1, 0),
	(150027, 1, 4),
	(150024, 1, 4),
	(150025, 1, 2),
	(150034, 2, 3),
	(150030, 2, 3),
	(150036, 2, 1),
	(150031, 2, 1),
	(150037, 2, 0),
	(150035, 2, 4),
	(150032, 2, 4),
	(150033, 2, 2),
	(150042, 3, 3),
	(150038, 3, 3),
	(150044, 3, 1),
	(150039, 3, 1),
	(150045, 3, 0),
	(150043, 3, 4),
	(150040, 3, 4),
	(150041, 3, 2),
	(150050, 4, 3),
	(150046, 4, 3),
	(150052, 4, 1),
	(150047, 4, 1),
	(150053, 4, 0),
	(150051, 4, 4),
	(150048, 4, 4),
	(150049, 4, 2),
	(150054, 254, 0),
	(150055, 254, 0),
	(150058, 0, 0),
	(150057, 0, 0),
	(150056, 0, 0),
	(150061, 1, 0),
	(150060, 1, 0),
	(150059, 1, 0),
	(150064, 2, 0),
	(150063, 2, 0),
	(150062, 2, 0),
	(150067, 3, 0),
	(150066, 3, 0),
	(150065, 3, 0),
	(150070, 0, 1),
	(150069, 0, 1),
	(150068, 0, 1),
	(150073, 1, 1),
	(150072, 1, 1),
	(150071, 1, 1),
	(150076, 2, 1),
	(150075, 2, 1),
	(150074, 2, 1),
	(150079, 3, 1),
	(150078, 3, 1),
	(150077, 3, 1),
	(150082, 0, 2),
	(150081, 0, 2),
	(150080, 0, 2),
	(150085, 1, 2),
	(150084, 1, 2),
	(150083, 1, 2),
	(150088, 2, 2),
	(150087, 2, 2),
	(150086, 2, 2),
	(150091, 3, 2),
	(150090, 3, 2),
	(150089, 3, 2),
	(150092, 4, 4),
	(150093, 4, 0),
	(150094, 4, 1),
	(150095, 4, 2),
	(150096, 4, 3),
	(150101, 254, 0),
	(150102, 254, 0),
	(150104, 254, 0),
	(150103, 254, 0),
	(150108, 253, 0),
	(150107, 253, 0),
	(150110, 254, 0),
	(150109, 254, 0),
	(150114, 253, 0),
	(150113, 253, 0),
	(150116, 254, 0),
	(150115, 254, 0),
	(150118, 253, 0),
	(150117, 253, 0),
	(150225, 254, 0),
	(150226, 254, 0),
	(150236, 7, 3),
	(150235, 7, 3),
	(150234, 7, 3),
	(150233, 7, 3),
	(150232, 7, 3),
	(150231, 7, 3),
	(150230, 7, 3),
	(150229, 7, 3),
	(150228, 7, 3),
	(150227, 7, 3),
	(150245, 8, 3),
	(150244, 8, 3),
	(150243, 8, 3),
	(150242, 8, 3),
	(150241, 8, 3),
	(150240, 8, 3),
	(150239, 8, 3),
	(150238, 8, 3),
	(150237, 8, 3),
	(150255, 9, 3),
	(150254, 9, 3),
	(150253, 9, 3),
	(150252, 9, 3),
	(150251, 9, 3),
	(150250, 9, 3),
	(150249, 9, 3),
	(150248, 9, 3),
	(150247, 9, 3),
	(150246, 9, 3),
	(150265, 10, 3),
	(150264, 10, 3),
	(150263, 10, 3),
	(150262, 10, 3),
	(150261, 10, 3),
	(150260, 10, 3),
	(150259, 10, 3),
	(150258, 10, 3),
	(150257, 10, 3),
	(150256, 10, 3),
	(150275, 11, 1),
	(150274, 11, 1),
	(150273, 11, 1),
	(150272, 11, 1),
	(150271, 11, 1),
	(150270, 11, 1),
	(150269, 11, 1),
	(150268, 11, 1),
	(150267, 11, 1),
	(150266, 11, 1),
	(150285, 12, 1),
	(150284, 12, 1),
	(150283, 12, 1),
	(150282, 12, 1),
	(150281, 12, 1),
	(150280, 12, 1),
	(150279, 12, 1),
	(150278, 12, 1),
	(150277, 12, 1),
	(150276, 12, 1),
	(150295, 13, 1),
	(150294, 13, 1),
	(150293, 13, 1),
	(150292, 13, 1),
	(150291, 13, 1),
	(150290, 13, 1),
	(150289, 13, 1),
	(150288, 13, 1),
	(150287, 13, 1),
	(150286, 13, 1),
	(150305, 14, 1),
	(150304, 14, 1),
	(150303, 14, 1),
	(150302, 14, 1),
	(150301, 14, 1),
	(150300, 14, 1),
	(150299, 14, 1),
	(150298, 14, 1),
	(150297, 14, 1),
	(150296, 14, 1),
	(150306, 7, 1),
	(150307, 8, 1),
	(150308, 9, 1),
	(150309, 10, 1),
	(150310, 11, 3),
	(150311, 12, 3),
	(150312, 13, 3),
	(150313, 14, 3),
	(150314, 11, 0),
	(150315, 12, 0),
	(150316, 13, 0),
	(150317, 14, 0),
	(150318, 7, 2),
	(150319, 8, 2),
	(150320, 9, 2),
	(150321, 10, 2),
	(150323, 7, 1),
	(150322, 7, 1),
	(150325, 8, 1),
	(150324, 8, 1),
	(150327, 9, 1),
	(150326, 9, 1),
	(150329, 10, 1),
	(150328, 10, 1),
	(150331, 11, 3),
	(150330, 11, 3),
	(150333, 12, 3),
	(150332, 12, 3),
	(150335, 13, 3),
	(150334, 13, 3),
	(150337, 14, 3),
	(150336, 14, 3),
	(150339, 11, 0),
	(150338, 11, 0),
	(150341, 12, 0),
	(150340, 12, 0),
	(150343, 13, 0),
	(150342, 13, 0),
	(150345, 14, 0),
	(150344, 14, 0),
	(150347, 7, 2),
	(150346, 7, 2),
	(150349, 8, 2),
	(150348, 8, 2),
	(150351, 9, 2),
	(150350, 9, 2),
	(150353, 10, 2),
	(150352, 10, 2),
	(150355, 0, 1),
	(150354, 0, 1),
	(150357, 1, 1),
	(150356, 1, 1),
	(150359, 2, 1),
	(150358, 2, 1),
	(150361, 3, 1),
	(150360, 3, 1),
	(150363, 4, 1),
	(150362, 4, 1),
	(150365, 5, 1),
	(150364, 5, 1),
	(150367, 6, 1),
	(150366, 6, 1),
	(150369, 0, 3),
	(150368, 0, 3),
	(150371, 1, 3),
	(150370, 1, 3),
	(150373, 2, 3),
	(150372, 2, 3),
	(150375, 3, 3),
	(150374, 3, 3),
	(150377, 4, 3),
	(150376, 4, 3),
	(150379, 5, 3),
	(150378, 5, 3),
	(150381, 6, 3),
	(150380, 6, 3),
	(150383, 0, 0),
	(150382, 0, 0),
	(150385, 1, 0),
	(150384, 1, 0),
	(150387, 2, 0),
	(150386, 2, 0),
	(150389, 3, 0),
	(150388, 3, 0),
	(150391, 4, 0),
	(150390, 4, 0),
	(150393, 5, 0),
	(150392, 5, 0),
	(150395, 6, 0),
	(150394, 6, 0),
	(150397, 0, 2),
	(150396, 0, 2),
	(150399, 1, 2),
	(150398, 1, 2),
	(150401, 2, 2),
	(150400, 2, 2),
	(150403, 3, 2),
	(150402, 3, 2),
	(150405, 4, 2),
	(150404, 4, 2),
	(150407, 5, 2),
	(150406, 5, 2),
	(150409, 6, 2),
	(150408, 6, 2),
	(150413, 3, 1),
	(150412, 3, 1),
	(150411, 3, 1),
	(150410, 3, 1),
	(150417, 3, 0),
	(150416, 3, 0),
	(150415, 3, 0),
	(150414, 3, 0),
	(150421, 3, 3),
	(150420, 3, 3),
	(150419, 3, 3),
	(150418, 3, 3),
	(150425, 3, 2),
	(150424, 3, 2),
	(150423, 3, 2),
	(150422, 3, 2),
	(150427, 3, 5),
	(150426, 3, 5),
	(150437, 63, 0),
	(150436, 63, 0),
	(150435, 63, 0),
	(150434, 63, 0),
	(150433, 63, 0),
	(150432, 63, 0),
	(150431, 63, 0),
	(150430, 63, 0),
	(150429, 63, 0),
	(150428, 63, 0),
	(150447, 64, 0),
	(150446, 64, 0),
	(150445, 64, 0),
	(150444, 64, 0),
	(150443, 64, 0),
	(150442, 64, 0),
	(150441, 64, 0),
	(150440, 64, 0),
	(150439, 64, 0),
	(150438, 64, 0),
	(222020, 253, 0),
	(222021, 253, 0),
	(222022, 254, 0),
	(222023, 254, 0),
	(222024, 250, 0),
	(222025, 250, 0),
	(300046, 0, 0),
	(300047, 0, 1),
	(300048, 0, 2),
	(300049, 0, 3),
	(300050, 0, 4),
	(300051, 1, 0),
	(300052, 1, 1),
	(300053, 1, 2),
	(300054, 1, 3),
	(300055, 1, 4),
	(300056, 2, 0),
	(300057, 2, 1),
	(300058, 2, 2),
	(300059, 2, 3),
	(300060, 2, 4),
	(300061, 3, 0),
	(300062, 3, 1),
	(300063, 3, 2),
	(300064, 3, 3),
	(300065, 3, 4),
	(300066, 4, 0),
	(300067, 4, 1),
	(300068, 4, 2),
	(300069, 4, 3),
	(300070, 4, 4),
	(300071, 5, 1),
	(300072, 5, 2),
	(300073, 5, 3),
	(300074, 5, 4),
	(300075, 6, 1),
	(300076, 6, 2),
	(300077, 6, 3),
	(300078, 6, 4),
	(300079, 0, 3),
	(300080, 0, 4),
	(300081, 0, 0),
	(300082, 1, 3),
	(300083, 1, 4),
	(300084, 1, 0),
	(300085, 2, 3),
	(300086, 2, 4),
	(300087, 2, 0),
	(300088, 3, 3),
	(300089, 3, 4),
	(300090, 3, 0),
	(300091, 4, 3),
	(300092, 4, 4),
	(300093, 4, 0),
	(300094, 5, 3),
	(300095, 5, 4),
	(300096, 6, 3),
	(300097, 6, 4),
	(300098, 254, 0),
	(300099, 254, 0),
	(300100, 254, 0),
	(300101, 254, 0),
	(300102, 251, 0),
	(300103, 251, 0),
	(300104, 252, 0),
	(300105, 7, 0),
	(300106, 7, 0),
	(300107, 7, 0),
	(300108, 7, 0),
	(300109, 7, 0),
	(300110, 7, 0),
	(300111, 7, 0),
	(300112, 7, 0),
	(300113, 7, 0),
	(300114, 7, 0),
	(300115, 7, 0),
	(300116, 7, 0),
	(300117, 254, 0),
	(300118, 254, 0),
	(300119, 254, 0),
	(300120, 254, 0),
	(300121, 254, 0),
	(300122, 254, 0),
	(300123, 254, 0),
	(300124, 254, 0),
	(300125, 254, 0),
	(300126, 254, 0),
	(300127, 254, 0),
	(300128, 254, 0),
	(300129, 1, 3),
	(300130, 1, 3),
	(300131, 1, 3),
	(300132, 1, 4),
	(300133, 1, 4),
	(300134, 1, 4),
	(300135, 2, 3),
	(300136, 2, 3),
	(300137, 2, 4),
	(300138, 2, 4),
	(200008, 14, 1),
	(200009, 11, 0),
	(200010, 11, 0),
	(200011, 11, 0),
	(200012, 11, 0),
	(200013, 11, 0),
	(200014, 11, 0),
	(200015, 14, 2),
	(200016, 0, 1),
	(200017, 0, 2),
	(200018, 0, 3),
	(200019, 0, 4),
	(200020, 0, 1),
	(200021, 0, 2),
	(200022, 0, 3),
	(200023, 0, 4),
	(200024, 11, 0),
	(200025, 1, 1),
	(200026, 1, 2),
	(200027, 1, 3),
	(200028, 1, 4),
	(200029, 1, 1),
	(200030, 1, 2),
	(200031, 1, 3),
	(200032, 1, 4),
	(200033, 11, 0),
	(200034, 2, 1),
	(200035, 2, 2),
	(200036, 2, 3),
	(200037, 2, 4),
	(200038, 2, 1),
	(200039, 2, 2),
	(200040, 2, 3),
	(200041, 2, 4),
	(200042, 11, 0),
	(200043, 11, 0),
	(200044, 11, 0),
	(200045, 11, 0),
	(200046, 11, 0),
	(200047, 11, 0),
	(200048, 11, 0),
	(200049, 11, 0),
	(200050, 6, 3),
	(200051, 6, 3),
	(200052, 6, 3),
	(200053, 6, 3),
	(200054, 6, 3),
	(200055, 6, 3),
	(200056, 6, 3),
	(200057, 6, 3),
	(200058, 6, 3),
	(200059, 6, 3),
	(200060, 6, 3),
	(200061, 6, 3),
	(200062, 6, 4),
	(200063, 6, 4),
	(200064, 6, 4),
	(200065, 6, 4),
	(200066, 6, 4),
	(200067, 6, 4),
	(200068, 6, 4),
	(200069, 6, 4),
	(200070, 6, 4),
	(200071, 6, 4),
	(200072, 6, 4),
	(200073, 6, 4),
	(200074, 8, 3),
	(200075, 8, 3),
	(200076, 8, 3),
	(200077, 8, 3),
	(200078, 8, 3),
	(200079, 8, 3),
	(200080, 8, 3),
	(200081, 8, 3),
	(200082, 8, 3),
	(200083, 8, 3),
	(200084, 8, 3),
	(200085, 8, 3),
	(200086, 8, 3),
	(200087, 8, 3),
	(200088, 8, 3),
	(200089, 8, 3),
	(200090, 8, 3),
	(200091, 8, 3),
	(200092, 8, 3),
	(200093, 8, 3),
	(200094, 8, 3),
	(200095, 8, 3),
	(200096, 8, 4),
	(200097, 8, 4),
	(200098, 8, 4),
	(200099, 8, 4),
	(200100, 8, 4),
	(200101, 8, 4),
	(200102, 8, 4),
	(200103, 8, 4),
	(200104, 8, 4),
	(200105, 8, 4),
	(200106, 8, 4),
	(200107, 8, 4),
	(200108, 8, 4),
	(200109, 8, 4),
	(200110, 8, 4),
	(200111, 8, 4),
	(200112, 8, 4),
	(200113, 8, 4),
	(200114, 8, 4),
	(200115, 8, 4),
	(200116, 8, 4),
	(200117, 8, 4),
	(200118, 5, 4),
	(200119, 5, 3),
	(200120, 5, 3),
	(200121, 5, 3),
	(200122, 5, 3),
	(200123, 5, 3),
	(200124, 5, 3),
	(200125, 5, 3),
	(200126, 5, 3),
	(200127, 5, 4),
	(200128, 5, 4),
	(200129, 5, 4),
	(200130, 5, 4),
	(200131, 5, 4),
	(200132, 5, 4),
	(200133, 5, 4),
	(200134, 5, 4),
	(200135, 5, 4),
	(200136, 7, 3),
	(200137, 7, 3),
	(200138, 7, 3),
	(200139, 7, 3),
	(200140, 7, 3),
	(200141, 7, 3),
	(200142, 7, 3),
	(200143, 7, 3),
	(200144, 7, 3),
	(200145, 7, 3),
	(200146, 7, 3),
	(200147, 7, 3),
	(200148, 7, 3),
	(200149, 7, 3),
	(200150, 7, 3),
	(200151, 7, 3),
	(200152, 7, 3),
	(200153, 7, 3),
	(200154, 7, 3),
	(200155, 7, 3),
	(200156, 7, 3),
	(200157, 7, 3),
	(200158, 7, 3),
	(200159, 7, 3),
	(200160, 7, 3),
	(200161, 7, 4),
	(200162, 7, 4),
	(200163, 7, 4),
	(200164, 7, 4),
	(200165, 7, 4),
	(200166, 7, 4),
	(200167, 7, 4),
	(200168, 7, 4),
	(200169, 7, 4),
	(200170, 7, 4),
	(200171, 7, 4),
	(200172, 7, 4),
	(200173, 7, 4),
	(200174, 7, 4),
	(200175, 7, 4),
	(200176, 7, 4),
	(200177, 7, 4),
	(200178, 7, 4),
	(200179, 7, 4),
	(200180, 7, 4),
	(200181, 7, 4),
	(200182, 7, 4),
	(200183, 7, 4),
	(200184, 7, 4),
	(200185, 7, 4),
	(222001, 253, 0),
	(222002, 253, 0),
	(222003, 254, 0),
	(222004, 254, 0);
/*!40000 ALTER TABLE `gameobject_battleground` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;