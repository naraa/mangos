-- Instance Sunwell Plateau
-- ------------------------

-- ------------
-- Kalegcos ---
-- ------------
UPDATE `creature_template` SET `flags_extra` = 128 WHERE `entry` = 25795; -- make normal realm bunnie invis to players and ect 
UPDATE `creature_template` SET `flags_extra` = 128 WHERE `entry` = 25796; -- make spectral realm bunnies invis to players and ect

-- correct spawn of kalegcos spawn
DELETE FROM `creature` WHERE `id`=24891;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(102510, 24891, 580, 1, 1, 0, 3001, 1704.49, 925.522, -74.5584, 4.72577, 25, 0, 0, 828555, 169350, 0, 0);

-- corrected spawn of Sathrovarr the Corruptor
DELETE FROM `creature` WHERE `id`=24892;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(100698, 24892, 580, 1, 1, 0, 0, 1704.63, 916.777, -74.5584, 1.68785, 604800, 0, 0, 2018275, 1693500, 0, 0);

-- ------------
-- Brutallus --
-- ------------

-- -------------
-- Flemyst -----
-- -------------



-- ---------------------------------------------
-- InstanceFixes and Related Data --------------
-- ---------------------------------------------