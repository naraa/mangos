-- Instance The Shattered Halls
-- ------------------------

-- ------------
-- Shattered Hand Executioner ---
-- ------------
UPDATE `creature_template` SET `unit_flags` = 3 WHERE `entry` = 20585; -- adding not attackable flag, removed by script on boss death

-- adding Shattered Hand Executioner
DELETE FROM creature WHERE id IN (17301);
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(600008, 17301, 540, 2, 1, 0, 2184, 160.99, -83.5436, 1.92994, 6.28004, 300, 0, 0, 27350, 0, 0, 0);

-- scripted areatriggers
DELETE FROM scripted_areatrigger WHERE entry IN (4182, 4183, 4524);
INSERT INTO scripted_areatrigger (`entry`, `ScriptName`) VALUES 
('4182', 'at_shattered_halls'),
('4183', 'at_shattered_halls'),
('4524', 'at_shattered_halls');
-- ---------------------------------------------
-- InstanceFixes and Related Data --------------
-- ---------------------------------------------