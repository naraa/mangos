
--- FallenAngelX
ALTER TABLE db_version_Infinity_Update CHANGE COLUMN r00 r01 bit;
REPLACE INTO `db_version_Infinity_Update` (`version`) VALUES ('r01');

UPDATE db_version SET `cache_id`= 'r01';
UPDATE db_version SET `version`= '';