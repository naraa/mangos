

SET FOREIGN_KEY_CHECKS=0;

DROP TABLE IF EXISTS `db_version_Infinity_Update`;
CREATE TABLE `db_version_Infinity_Update` (
  `version` varchar(120) NOT NULL,
  `r00` bit(1) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Used YTDB lock system and revision log';

INSERT INTO `db_version_Infinity_Update` VALUES ('r00', null);
