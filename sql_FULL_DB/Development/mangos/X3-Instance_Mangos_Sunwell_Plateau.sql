-- --------------------------
-- Instance Sunwell Plateau -
-- --------------------------

-- ------------
-- Kalegcos ---
-- ------------
UPDATE `creature_template` SET `flags_extra` = 128 WHERE `entry` = 25795; -- make normal realm bunnie invis to players and ect 
UPDATE `creature_template` SET `flags_extra` = 128 WHERE `entry` = 25796; -- make spectral realm bunnies invis to players and ect

UPDATE `creature_template` SET `modelid_1` = 20577 WHERE `entry` in (25796, 25795);

UPDATE gameobject_template SET ScriptName='go_spectral_rift' WHERE entry = 187055;

-- correct spawn of kalegcos spawn
DELETE FROM `creature` WHERE `id`=24891;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(102510, 24891, 580, 1, 1, 0, 3001, 1704.49, 925.522, -74.5584, 4.72577, 604800, 0, 0, 828555, 169350, 0, 0);

-- Sathrovarr the Corruptor
DELETE FROM `creature` WHERE `id`=24892;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(100698, 24892, 580, 1, 1, 0, 0, 1704.63, 916.777, -74.5584, 1.68785, 604800, 0, 0, 2018275, 1693500, 0, 0);

UPDATE `creature_template` SET `modelid_2` = 26628 WHERE `entry` = 24892; -- missing dispaly id for horde for sathrovarr

-- ------------
-- Brutallus --
-- ------------

-- madrigosa fixes
DELETE FROM `creature` WHERE `id`=24895;  -- origanl YTDB Data
-- INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
-- (80778, 24895, 580, 1, 1, 0, 0, 1459.35, 636.81, 19.9428, 4.93474, 604800, 0, 0, 424900, 3387, 0, 0);

DELETE FROM `creature` WHERE `id`=25160; -- new data for madrigosa
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(600114, 25160, 580, 1, 1, 0, 0, 1461.27, 647.103, 38.6641, 5.05014, 60000, 0, 0, 424900, 3387, 0, 0),
(100738, 25160, 530, 1, 1, 0, 0, 12164.9, -7066.29, 72.0305, 1.32201, 14400, 0, 0, 424900, 3387, 0, 0);

-- he was damging brutallus to much during intro 8P
UPDATE `creature_template` SET `mindmg` = 1, `maxdmg` = 1, `attackpower` = 1, `dmg_multiplier` = 1 WHERE `entry` = 25160;
-- UPDATE `creature_template` SET `mindmg` = 226, `maxdmg` = 339, `attackpower` = 85, `dmg_multiplier` = 4.1 WHERE `entry` = 25160; -- Restore what YTDB(605) had

-- not sure if these are needed
-- spell_scripts for burn and stomp
-- scripts for 'burn' and 'stomp'
-- DELETE FROM `spell_scripts` WHERE `id` IN (45141, 45185);
-- INSERT INTO `spell_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`,`comments`) VALUES
-- ('45141', '0', '15', '46394', '2', '0', '0', '0', '0', '0',""),
-- ('45185', '0', '14', '46394', '1', '0', '0', '0', '0', '0',"");

UPDATE `creature_template` SET `InhabitType` = 1 WHERE `entry` = 24882; -- brutallus should be a ground only walker

-- -------------
-- Felmyst -----
-- -------------

DELETE FROM `creature` WHERE `id`=25038; -- remove static spawn as she is summoned when needed ,,,, below to orignal YTDB Data
-- INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
-- (57715, 25038, 580, 1, 1, 0, 0, 1459.35, 636.81, 19.9428, 4.93474, 604800, 0, 0, 4903346, 3387, 0, 0);

UPDATE `creature_template` SET `faction_A` = 7, `faction_H` = 7 WHERE `entry` = 25038;  -- Felmyst doesnt attack til attacked
UPDATE creature_template SET `ScriptName` = 'boss_felmyst', `modelid_2` = 22838 WHERE `entry` = 25038; 
UPDATE creature_template SET `ScriptName` = 'npc_felmyst_vapor' WHERE `entry` = 25265;  --  npc thats spawns randomly along the beam and spawn unyielding death if players get to close ( gonna use interact_distance might need more )
UPDATE creature_template SET `ScriptName` = 'npc_fog_of_corruption' WHERE `entry` = 25703;  -- DeathCloud/breath attack
UPDATE `creature_template` SET `ScriptName` = 'npc_felmyst_vapor_cloud', `AIName` = ''  WHERE `entry` = 25267; -- invis beam npc that chases player

UPDATE `creature_template` SET `AIName` = 'EventAI', `ScriptName`="" WHERE `entry` = 25268;

-- -
-- scipt targets
-- -

-- DELETE FROM `spell_script_target` WHERE `entry` IN (45388);
-- INSERT INTO `spell_script_target` (`entry` ,`type` ,`targetEntry`)VALUES
-- ('45388', '1', '25038');
-- REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('44883', '1', '24882'); -- cast at brutallus
-- REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('45063', '1', '24882'); -- cast at brutallus
-- REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('44885', '1', '25038'); -- 
-- REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('46350', '1', '25038'); -- 


-- -
-- Demonic Vapor :: unit flags (not attackable, pacified, not selectable), bosslevel, factions, speed, spawn/dmg aura
-- -

UPDATE `creature_template` SET `modelid_2` = 11686, `minlevel` = 73, `maxlevel` = 73, `faction_A` = 16, `faction_H` = 16, `unit_flags` = 33685506 WHERE `entry` = 25265;
DELETE FROM `creature_template_addon` WHERE `entry` = '25265';
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_pvp_state`, `emote`, `moveflags`, `auras`) VALUES
(25265, 0, 0, 0, 0, 0, 0, '45411');

-- -
-- Demonic Vapor Cloud :: unit flags (not attackable, pacified, not selectable), bosslevel, factions, dmg auras
-- -

UPDATE `creature_template` SET `modelid_2` = 11686, `minlevel` = 73, `maxlevel` = 73, `faction_A` = 16, `faction_H` = 16, `unit_flags` = 33685506 WHERE `entry` = 25267;
DELETE FROM `creature_template_addon` WHERE `entry` = '25267';
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_pvp_state`, `emote`, `moveflags`, `auras`) VALUES
(25267, 0, 0, 0, 0, 0, 0, '45399');

-- -
-- Death cloud
-- -

UPDATE `creature_template` SET `modelid_1` = 11686, `modelid_2` = 11686, `faction_A` = 14, `faction_H` = 14, `unit_flags` = 33554434 WHERE `entry` = 25703;

-- -
-- Unyielding Death: - EventAI (Combat Pulse), and Aura
-- -

DELETE FROM `creature_template_addon` WHERE (`entry` = 25268);
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_pvp_state`, `emote`, `moveflags`, `auras`) VALUES 
(25268, 0, 0, 0, 0, 0, 0, '45415');

DELETE FROM `creature_ai_scripts` WHERE `id` = 2526801;
INSERT INTO `creature_ai_scripts` (`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `comment`) VALUES
('2526801', '25268', '1', '0', '100', '2', '500', '500', '10000', '10000', '38', '0', '0', '0', 'R2 - Unyielding Death - zone combat pulse if ooc');

-- -
-- The Twins
-- -

-- go 187366 Blaze fix
UPDATE `gameobject_template` SET `data5` = 0, `data7` = 0 WHERE `entry` = 187366;

-- Shadowy Image fixes
UPDATE `creature_template` SET `minlevel` = 73, `maxlevel` = 73, `faction_A` = 14, `faction_H` = 14 WHERE `entry` = 25214;

-- ------
-- M'uru-
-- ------
UPDATE `creature_template` SET `ScriptName` = 'boss_muru', `AIName` = '' WHERE `entry` = 25741;
UPDATE `creature_template` SET `ScriptName` = 'boss_entropius', `modelid_2` = 23428, `modelid_3` = 23428, `modelid_4` = 23428 , `AIName` = '' WHERE `entry` = 25840;
UPDATE `creature_template` SET `ScriptName` = 'mob_dark_fiend', `AIName` = '' WHERE `entry` = 25744; 
UPDATE `creature_template` SET `ScriptName` = 'mob_voidsentinel', `AIName` = '' WHERE `entry` = 25772; 

-- ----------------
-- Dark fiend fixes
UPDATE `creature_template` SET `speed_walk` = 0.7, `speed_run` = 0.7 WHERE `entry` = 25744; -- move slower then the player they are suppose run away from then 8)

-- shorter attack range ( needs to be for chase explode )
DELETE FROM `creature_model_info` WHERE (`modelid`=1126);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (1126, 2, 0.5, 2, 0, 0);
DELETE FROM `creature_model_info` WHERE (`modelid`=23842);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (23842, 2, 0.5, 2, 0, 0);

-- -----------
-- Singularity
UPDATE `creature_template` SET `faction_A` = 14, `faction_H` = 14, `speed_walk` = 0.7, `speed_run` = 0.7 WHERE `entry` = 25855; -- move slower then the player they are suppose run away from then 8)
UPDATE `creature_template` SET `unit_flags` = 33554434, `ScriptName` = 'mob_singularity' WHERE `entry` = 25855;  -- non attackable and selectable
UPDATE `creature_template` SET `modelid_1` = 25206, `modelid_2` = 25206 WHERE `entry` = 25855;

-- added throw character aura if they get to close and acrance form aura
DELETE FROM `creature_template_addon` WHERE (`entry`=25855);
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_pvp_state`, `emote`, `moveflags`, `auras`) VALUES (25855, 0, 0, 0, 0, 0, 0, '46228 48019');

-- short their attack range to they have to be close before effect iss triggered
DELETE FROM `creature_model_info` WHERE (`modelid`=25206);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (25206, 0.75, 0.5, 2, 0, 0);

-- ---------------------------
-- fixes to the portal targets

-- added no movement to template as well
UPDATE `creature_template` SET `unit_flags` = 33554692 WHERE `entry` = 25770;

DELETE FROM `creature` WHERE `id`=25770; -- so far only movement ( there not suppose to needs somes twinks to a few locs )
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(81074, 25770, 580, 1, 1, 0, 0, 1802.91, 591.566, 78.5747, 1.25664, 604800, 0, 0, 1, 0, 0, 0),
(81075, 25770, 580, 1, 1, 0, 0, 1803.18, 657.192, 78.5476, 4.06662, 604800, 0, 0, 1, 0, 0, 0),
(81076, 25770, 580, 1, 1, 0, 0, 1775.98, 635.201, 78.5586, 0.069813, 604800, 0, 0, 1, 0, 0, 0),
(81077, 25770, 580, 1, 1, 0, 0, 1849.18, 641.002, 78.6183, 3.56047, 604800, 0, 0, 1, 0, 0, 0),
(81089, 25770, 580, 1, 1, 0, 0, 1852.49, 623.461, 78.6198, 3.03687, 604800, 0, 0, 1, 0, 0, 0),
(81090, 25770, 580, 1, 1, 0, 0, 1839.93, 652.875, 78.5929, 3.9619, 604800, 0, 0, 1, 0, 0, 0),
(81091, 25770, 580, 1, 1, 0, 0, 1824.05, 653.748, 78.5587, 5.044, 604800, 0, 0, 1, 0, 0, 0),
(81092, 25770, 580, 1, 1, 0, 0, 1794.84, 604.343, 78.549, 0.087266, 604800, 0, 0, 1, 0, 0, 0),
(81093, 25770, 580, 1, 1, 0, 0, 1824.17, 588.977, 78.621, 1.79769, 604800, 0, 0, 1, 0, 0, 0),
(81094, 25770, 580, 1, 1, 0, 0, 1781.65, 621.09, 78.5541, 1.15192, 604800, 0, 0, 1, 0, 0, 0);

-- ----------------------
-- clean up of M'uru ACID
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25741;

-- -----------------------
-- clean up of Entrop ACID
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25840;

-- -----------------------
-- trash ACID clean up
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25744; -- dark fiend
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25772; -- void sentinel


-- --------------------------------
-- kil jaeden
-- --------------------------------

UPDATE `creature_template` SET `ScriptName` = 'boss_kiljaeden', `unit_flags` = 4 WHERE `entry` = 25315; 
UPDATE `creature_template` SET `ScriptName` = 'mob_deceiver' WHERE `entry` = 25588; 
UPDATE `creature_template` SET `ScriptName` = 'mob_shield_orb' WHERE `entry` = 25502; 
UPDATE `creature_template` SET `ScriptName` = 'mob_felfire_portal' WHERE `entry` = 25603; 
-- UPDATE `creature_template` SET `ScriptName` = 'mob_armagedon_target' WHERE `entry` = 25735; 
UPDATE `creature_template` SET `ScriptName` = 'mob_felfire_fiend' WHERE `entry` = 25598;

-- ------
-- UPDATE `creature_template` SET `ScriptName` = 'mob_kiljaeden_controller' WHERE `entry` = 25608;
UPDATE `creature_template` SET `ScriptName` = '' WHERE `entry` = 25608;
-- -------

UPDATE `creature_template` SET `unit_flags` = 33554438 WHERE `entry` = 25603; 
UPDATE creature set position_z = 60.0 where id = 26046;
UPDATE `gameobject_template` SET `type` = 10 WHERE `entry` = 188415;
-- UPDATE `gameobject_template` set `flags` = 6553648, `ScriptName` = 'go_orb_of_the_blue_flight' where `entry` = 188415;
-- Controller
DELETE FROM creature where id = 25608;
INSERT INTO creature values (500110,25608,580,1,1,0,0,1698.61,628.414,27.5395,3.99799,604800,0,0,9347800,1693500,0,0);

-- ---------------------------------------------
-- InstanceFixes and Related Data --------------
-- ---------------------------------------------
