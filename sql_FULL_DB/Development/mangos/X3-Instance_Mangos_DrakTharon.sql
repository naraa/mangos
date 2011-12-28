-- ------------------------
-- Instance Draktharon -
-- ------------------------

-- -----------
-- TrollGore -
-- -----------

-- UPDATE creature_template SET AIName='', ScriptName='npc_drakkari_invader' WHERE entry=27709;
-- UPDATE creature_template SET VehicleId=40 WHERE entry=27724;

DELETE FROM `creature_model_info` WHERE (`modelid`=26352);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (26352, 2.5, 3, 2, 0, 0);

  -- TrollGore DB fixes
UPDATE `creature_template` SET `KillCredit1` = 26630, `modelid_2` = 26352, `maxhealth` = 244510 WHERE `entry` = 26630;
DELETE FROM `creature` WHERE `id`=26630;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(79249, 26630, 600, 3, 1, 0, 0, -267.731, -659.496, 26.6921, 6.21337, 43200, 0, 0, 244510, 0, 0, 0);
UPDATE `creature_template` SET `modelid_2` = 26352 WHERE `entry` = 31362;
UPDATE `creature_template` SET `minhealth` = 244510 WHERE `entry` = 26630;

DELETE FROM achievement_criteria_requirement where criteria_id=7581;
-- INSERT INTO `achievement_criteria_requirement` (`criteria_id`, `type`, `value1`, `value2`) VALUES (7581, 11, 0, 0);
-- TYPE 8 isnt supported so hack for will be needed
-- INSERT INTO `achievement_criteria_requirement` (`criteria_id`, `type`, `value1`, `value2`) VALUES (7581, 8, 0, 0);
-- INSERT INTO `achievement_criteria_requirement` (`criteria_id`, `type`, `value1`, `value2`) VALUES (7581, 18, 0, 0);

   -- already in YTDB (Here for dev reasons but needed)
DELETE FROM `spell_script_target` WHERE  `entry`=49555 AND `type`=1 AND `targetEntry`=27709 LIMIT 1;
DELETE FROM `spell_script_target` WHERE  `entry`=49555 AND `type`=1 AND `targetEntry`=27753 LIMIT 1;
DELETE FROM `spell_script_target` WHERE  `entry`=49555 AND `type`=1 AND `targetEntry`=27754 LIMIT 1;
INSERT IGNORE INTO spell_script_target values 
(49555, 1, 27753),
(49555, 1, 27754),
(49555, 1, 27709);