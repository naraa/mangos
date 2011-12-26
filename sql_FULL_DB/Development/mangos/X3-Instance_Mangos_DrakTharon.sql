-- ------------------------
-- Instance Draktharon -
-- ------------------------

-- -----------
-- TrollGore -
-- -----------

DELETE FROM `creature_model_info` WHERE (`modelid`=26352);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (26352, 2.5, 3, 2, 0, 0);

  -- TrollGore DB fixes
UPDATE `creature_template` SET `KillCredit1` = 26630, `modelid_2` = 26352, `maxhealth` = 244510 WHERE `entry` = 26630;
DELETE FROM `creature` WHERE `id`=26630;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(79249, 26630, 600, 3, 1, 0, 0, -250.051, -660.224, 26.538, 3.087, 43200, 0, 0, 244510, 0, 0, 0);
UPDATE `creature_template` SET `modelid_2` = 26352 WHERE `entry` = 31362;
UPDATE `creature_template` SET `minhealth` = 244510 WHERE `entry` = 26630;
