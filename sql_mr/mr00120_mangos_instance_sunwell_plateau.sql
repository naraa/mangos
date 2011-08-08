-- Instance Sunwell Plateau
-- ------------------------

-- ------------
-- Kalegcos ---
-- ------------
UPDATE `creature_template` SET `flags_extra` = 128 WHERE `entry` = 25795; -- make normal realm bunnie invis to players and ect 
UPDATE `creature_template` SET `flags_extra` = 128 WHERE `entry` = 25796; -- make spectral realm bunnies invis to players and ect

UPDATE `creature_template` SET `modelid_1` = 20577 WHERE `entry` in (25796, 25795);

-- correct spawn of kalegcos spawn
DELETE FROM `creature` WHERE `id`=24891;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(102510, 24891, 580, 1, 1, 0, 3001, 1704.49, 925.522, -74.5584, 4.72577, 604800, 0, 0, 828555, 169350, 0, 0);

-- corrected spawn of Sathrovarr the Corruptor
DELETE FROM `creature` WHERE `id`=24892;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(100698, 24892, 580, 1, 1, 0, 0, 1704.63, 916.777, -74.5584, 1.68785, 604800, 0, 0, 2018275, 1693500, 0, 0);

-- ------------
-- Brutallus --
-- ------------

-- madrigosa spawn fixes
DELETE FROM `creature` WHERE `id`=24895;  -- origanl YTDB Data
-- INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
-- (80778, 24895, 580, 1, 1, 0, 0, 1459.35, 636.81, 19.9428, 4.93474, 604800, 0, 0, 424900, 3387, 0, 0);

DELETE FROM `creature` WHERE `id`=25160; -- new data for madrigosa
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(4456501, 25160, 580, 1, 1, 0, 0, 1461.27, 647.103, 38.6641, 5.05014, 60000, 0, 0, 424900, 3387, 0, 0),
(100738, 25160, 530, 1, 1, 0, 0, 12164.9, -7066.29, 72.0305, 1.32201, 14400, 0, 0, 424900, 3387, 0, 0);

-- -------------
-- Felmyst -----
-- -------------

-- Felmyst
UPDATE creature_template SET `ScriptName` = 'boss_felmyst', `modelid_2` = 22838 WHERE `entry` = 25038; 
UPDATE creature_template SET `ScriptName` = 'mob_felmyst_vapor' WHERE `entry` = 25265;  
UPDATE creature_template SET `ScriptName` = 'mob_fog_of_corruption' WHERE `entry` = 25703; 
-- REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('44883', '1', '24882');
-- REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('45063', '1', '24882');
-- REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('44885', '1', '25038');
-- REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('46350', '1', '25038');

UPDATE `creature_template` SET `faction_A` = 7, `faction_H` = 7 WHERE `entry` = 25038;  -- Felmyst doesnt attack til attacked

DELETE FROM `creature` WHERE `id`=25038; -- remove static spawn as she is summoned when needed
-- INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
-- (57715, 25038, 580, 1, 1, 0, 0, 1459.35, 636.81, 19.9428, 4.93474, 604800, 0, 0, 4903346, 3387, 0, 0);

-- ------------------
/* felmyst fight fixes

	Demonic Vampor
    - unit flags (not attackable, pacified, not selectable)
    - bosslevel, fractions
    - speed
    - spawn/dmg aura
*/
-- UPDATE `creature_template` SET `unit_flags` = 0x2020002, `faction_A` = '16', `faction_H` = '16', `speed_run` = '0.95', `minlevel` = '73', `maxlevel` = '73', `ScriptName` = 'mob_felmyst_vapor' WHERE `entry` = 25265;
-- DELETE FROM `creature_template_addon` WHERE `entry` = '25265';
-- INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `emote`, `moveflags`, `auras`) VALUES ('25265', '0', '0', '0', '0', '0', '45411 0 45411 1');
/*
	Demonic Vampor Trail
    - unit flags (not attackable, pacified, not selectable)
    - bosslevel, fractions
    - dmg auras
*/
-- UPDATE `creature_template` SET `unit_flags` = 0x2020002, `faction_A` = '16', `faction_H` = '16', `minlevel` = '73', `maxlevel` = '73', `ScriptName` = 'mob_felmyst_vapor_trail' WHERE `entry` = '25267';
-- DELETE FROM `creature_template_addon` WHERE `entry` = '25267';
--INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `emote`, `moveflags`, `auras`) VALUES
--(25267, 0, 0, 0, 0, 0, '45399 0');
/*
    Unyielding Death:
    - EventAI (Combat Pulse),"aggro range"
    - Grüne Aura
*/
-- UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `creature_template`.`entry` = 25268;
-- DELETE FROM `creature_template_addon` WHERE `entry` = '25268';
-- INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `emote`, `moveflags`, `auras`) VALUES
-- ('25268', '0', '0', '0', '0', '0', '45415 0');
-- DELETE FROM `creature_ai_scripts` WHERE `id` = 2526801;
-- INSERT INTO `creature_ai_scripts` (`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `comment`) VALUES
-- ('2526801', '25268', '1', '0', '100', '2', '500', '500', '10000', '10000', '38', '0', '0', '0', 'Unyielding Death - zone combat pulse if ooc');
/* scipt targets */
-- DELETE FROM `spell_script_target` WHERE `entry` IN (45388);
-- INSERT INTO `spell_script_target` (`entry` ,`type` ,`targetEntry`)VALUES
('45388', '1', '25038');
/* Felmyst, bounding radius */
-- UPDATE `creature_model_info` SET `bounding_radius` = '8', `combat_reach` = '5' WHERE `creature_model_info`.`modelid` = 22838;


-- ---------------------------------------------
-- InstanceFixes and Related Data --------------
-- ---------------------------------------------