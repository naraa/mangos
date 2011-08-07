-- Instance The Shattered Halls
-- ------------------------

-- ------------
-- Shattered Hand Executioner ---
-- ------------
UPDATE `creature_template` SET `unit_flags` = 3 WHERE `entry` = 20585; -- adding not attackable flag, removed by script on boss death

-- adding Shattered Hand Executioner
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(4456502, 17301, 540, 2, 65535, 0, 2184, 160.99, -83.5436, 1.92994, 6.28004, 300, 5, 0, 27350, 0, 0, 0);
-- ---------------------------------------------
-- InstanceFixes and Related Data --------------
-- ---------------------------------------------