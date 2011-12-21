-- ----------------
-- Instance Nexus -
-- ----------------

-- ---------
-- Magus tele
-- ---------

UPDATE `creature_template` SET `modelid_2` = 24066 WHERE `entry` = 26731;
UPDATE `creature_template` SET `modelid_2` = 24066, `equipment_id` = 1735 WHERE `entry` = 26928;
UPDATE `creature_template` SET `modelid_2` = 24066, `equipment_id` = 1735 WHERE `entry` = 26929;
UPDATE `creature_template` SET `modelid_2` = 24066, `equipment_id` = 1735 WHERE `entry` = 26930;
UPDATE `creature_template` SET `modelid_2` = 24066 WHERE `entry` = 30510;
UPDATE `creature_template` SET `modelid_2` = 24066, `equipment_id` = 1735 WHERE `entry` = 30511;
UPDATE `creature_template` SET `modelid_2` = 24066, `equipment_id` = 1735 WHERE `entry` = 30512;
UPDATE `creature_template` SET `modelid_2` = 24066, `equipment_id` = 1735 WHERE `entry` = 30513;

DELETE FROM `creature_model_info` WHERE (`modelid`=24066);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (24066, 1.125, 1.5, 1, 0, 0);


-- -------
-- ormok -
-- -------
UPDATE `creature_template` SET `modelid_2` = 26298 WHERE `entry` = 30532;
UPDATE `creature_template` SET `modelid_2` = 26298 WHERE `entry` = 26794;

DELETE FROM `creature_model_info` WHERE (`modelid`=26298);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (26298, 2.5, 5.25, 2, 0, 0);

UPDATE `creature_template` SET `ScriptName` = 'npc_crystal_spike' WHERE `entry` = '27099';
UPDATE `creature_template` SET `ScriptName` = 'npc_crystalline_tangler' WHERE `entry` = '32665';

-- ----------
-- Anomalus -
-- ----------

UPDATE `creature_template` SET `ScriptName` = 'npc_chaotic_rift' WHERE `entry` = '26918';
UPDATE `creature_template` SET `modelid_1` = 25206 WHERE `entry` = 26918;
UPDATE `creature_template` SET `modelid_1` = 25206 WHERE `entry` = 30522;
UPDATE `creature_template` SET `spell1` = 0 WHERE `entry` = 26918;
UPDATE `creature_template` SET `spell1` = 0 WHERE `entry` = 30522;

DELETE FROM `creature_model_info` WHERE (`modelid`=26259);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (26259, 2.5, 5, 2, 0, 0);

-- ACID For Crazied mana wraiths
UPDATE `creature_template` SET `AIName` = 'EventAI', `ScriptName` = '' WHERE `entry` = '26746';
DELETE FROM `creature_ai_scripts` WHERE (`id`='2674601');
INSERT INTO `creature_ai_scripts` VALUES ('2674601', '26746', '0', '0', '100', '7', '3000', '4000', '5000', '5500', '11', '33833', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Crazed Mana-Wraith - Cast Arcane Missles');
DELETE FROM `creature_ai_scripts` WHERE (`id`='2674602');
INSERT INTO `creature_ai_scripts` VALUES ('2674602', '26746', '4', '0', '100', '6', '0', '0', '0', '0', '20', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Crazed Mana-Wraith - melee');

-- ------------
-- Commanders -
-- ------------
  -- just some fixes to all this


  -- ACID Improvement for Commanders and 
  
DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=27947);
INSERT INTO `creature_ai_scripts` VALUES 
(2794701, 27947, 4, 0, 100, 6, 0, 0, 0, 0, 28, 0, 47543, 0, 1, -631, 0, 0, 11, 31403, 0, 1, 'Horde Commander - Remove Frozen Prison and Yell and Cast Battle Shout on Aggro'),
(2794702, 27947, 0, 0, 100, 7, 3000, 4000, 11000, 15000, 11, 60067, 5, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Horde Commander - Cast Charge'),
(2794703, 27947, 0, 0, 100, 7, 6000, 8000, 19500, 25000, 11, 38618, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Horde Commander - Cast Whirlwind'),
(2794704, 27947, 0, 0, 100, 5, 13000, 15000, 45000, 55000, 11, 19134, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Horde Commander - Cast Frightening Shout'),
(2794705, 27947, 5, 0, 100, 7, 5000, 5000, 0, 0, 1, -632, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Horde Commander - Yell on Player Kill'),
(2794706, 27947, 6, 0, 100, 6, 0, 0, 0, 0, 1, -633, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Horde Commander - Yell on Death');

DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=27949);
INSERT INTO `creature_ai_scripts` VALUES 
(2794901, 27949, 4, 0, 100, 6, 0, 0, 0, 0, 28, 0, 47543, 0, 1, -628, 0, 0, 11, 31403, 0, 1, 'Alliance Commander - Remove Frozen Prison and Yell and Cast Battle Shout on Aggro'),
(2794902, 27949, 0, 0, 100, 7, 3000, 4000, 11000, 15000, 11, 60067, 5, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Alliance Commander - Cast Charge'),
(2794903, 27949, 0, 0, 100, 7, 6000, 8000, 19500, 25000, 11, 38618, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Alliance Commander - Cast Whirlwind'),
(2794904, 27949, 0, 0, 100, 5, 13000, 15000, 45000, 55000, 11, 19134, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Alliance Commander - Cast Frightening Shout'),
(2794905, 27949, 5, 0, 100, 7, 5000, 5000, 0, 0, 1, -629, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Alliance Commander - Yell on Player Kill'),
(2794906, 27949, 6, 0, 100, 6, 0, 0, 0, 0, 1, -630, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Alliance Commander - Yell on Death');

-- commander stout
UPDATE `creature_template` SET `modelid_2` = 24366 WHERE `entry` = 26796;
DELETE FROM `creature` WHERE `id` = 26796;
UPDATE `creature_template` SET `difficulty_entry_1` = '' WHERE `entry` = 26796;
UPDATE `creature_template` SET `ScriptName` = '' WHERE `entry` = '26796';
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` = 26796;

DELETE FROM `creature_template_addon` WHERE (`entry`=26796);
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_pvp_state`, `emote`, `moveflags`, `auras`) VALUES (26796, 0, 0, 0, 0, 0, 0, 47543);

DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=26796);
INSERT INTO `creature_ai_scripts` VALUES 
(2679601, 26796, 4, 0, 100, 6, 0, 0, 0, 0, 28, 0, 47543, 0, 1, -628, 0, 0, 11, 31403, 0, 1, 'Commander Stoutbeard - Remove Frozen Prison and Yell and Cast Battle Shout on Aggro'),
(2679602, 26796, 0, 0, 100, 7, 3000, 4000, 11000, 15000, 11, 60067, 5, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Commander Stoutbeard - Cast Charge'),
(2679603, 26796, 0, 0, 100, 7, 6000, 8000, 19500, 25000, 11, 38618, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Commander Stoutbeard - Cast Whirlwind'),
(2679604, 26796, 0, 0, 100, 5, 13000, 15000, 45000, 55000, 11, 19134, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Commander Stoutbeard - Cast Frightening Shout'),
(2679605, 26796, 5, 0, 100, 7, 5000, 5000, 0, 0, 1, -629, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Commander Stoutbeard - Yell on Player Kill'),
(2679606, 26796, 6, 0, 100, 6, 0, 0, 0, 0, 1, -630, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Commander Stoutbeard - Yell on Death');

-- commander kolurg
UPDATE `creature_template` SET `modelid_2` = 24352 WHERE `entry` = 26798;
DELETE FROM `creature` WHERE `id`=26798;
UPDATE `creature_template` SET `difficulty_entry_1` = '' WHERE `entry` = 26798;
UPDATE `creature_template` SET `ScriptName` = '' WHERE `entry` = '26798';
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` = 26798;

DELETE FROM `creature_template_addon` WHERE (`entry`=26798);
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_pvp_state`, `emote`, `moveflags`, `auras`) VALUES (26798, 0, 0, 0, 0, 0, 0, 47543);

DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=26798);
INSERT INTO `creature_ai_scripts` VALUES 
(2679801, 26798, 4, 0, 100, 6, 0, 0, 0, 0, 28, 0, 47543, 0, 1, -631, 0, 0, 11, 31403, 0, 1, 'Commander Kolurg - Remove Frozen Prison and Yell and Cast Battle Shout on Aggro'),
(2679802, 26798, 0, 0, 100, 7, 3000, 4000, 11000, 15000, 11, 60067, 5, 7, 0, 0, 0, 0, 0, 0, 0, 0, 'Commander Kolurg - Cast Charge'),
(2679803, 26798, 0, 0, 100, 7, 6000, 8000, 19500, 25000, 11, 38618, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 'Commander Kolurg - Cast Whirlwind'),
(2679804, 26798, 0, 0, 100, 5, 13000, 15000, 45000, 55000, 11, 19134, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Commander Kolurg - Cast Frightening Shout'),
(2679805, 26798, 5, 0, 100, 7, 5000, 5000, 0, 0, 1, -632, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Commander Kolurg - Yell on Player Kill'),
(2679806, 26798, 6, 0, 100, 6, 0, 0, 0, 0, 1, -633, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Commander Kolurg - Yell on Death');

-- alliance ranger 
UPDATE `creature_template` SET `modelid_2` = 24355 WHERE `entry` = 26802;
DELETE FROM `creature` WHERE `id` = 26802;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(95891, 26802, 576, 3, 1, 0, 0, 389.677, 168.528, -35.0195, 4.6535, 7200, 0, 0, 37164, 16155, 0, 0),
(95892, 26802, 576, 3, 1, 0, 0, 462, 146.856, -35.0195, 2.07113, 7200, 0, 0, 37164, 16155, 0, 0),
(79917, 26802, 576, 3, 1, 0, 0, 397.238, 170.022, -35.0195, 4.64565, 7200, 0, 0, 37164, 16155, 0, 0),
(79923, 26802, 576, 3, 1, 0, 0, 402.83, 184.085, -35.0195, 4.5357, 7200, 0, 0, 37164, 16155, 0, 0),
(79927, 26802, 576, 3, 1, 0, 0, 410.797, 181.588, -35.0199, 3.71126, 7200, 0, 0, 37164, 16155, 0, 0),
(79932, 26802, 576, 3, 1, 0, 0, 407.409, 187.257, -35.0195, 4.0896, 7200, 0, 0, 37164, 16155, 0, 0),
(79938, 26802, 576, 3, 1, 0, 0, 421.783, 189.668, -35.0195, 3.86184, 7200, 0, 0, 37164, 16155, 0, 0),
(95890, 26802, 576, 3, 1, 0, 0, 388.62, 149.04, -35.0196, 2.53157, 7200, 0, 0, 37164, 16155, 0, 0),
(79950, 26802, 576, 3, 1, 0, 0, 444.773, 181.846, -35.0196, 4.24275, 7200, 0, 0, 37164, 16155, 0, 0),
(79943, 26802, 576, 3, 1, 0, 0, 430.212, 187.79, -35.0195, 3.27671, 7200, 0, 0, 37164, 16155, 0, 0),
(79964, 26802, 576, 3, 1, 0, 0, 460.639, 164.358, -35.0195, 2.5188, 7200, 0, 0, 37164, 16155, 0, 0),
(79959, 26802, 576, 3, 1, 0, 0, 449.28, 176.942, -35.0196, 2.90758, 7200, 0, 0, 37164, 16155, 0, 0),
(78936, 26802, 576, 3, 1, 0, 0, 442.156, 175.618, -35.0195, 2.68373, 7200, 0, 0, 37164, 16155, 0, 0);

-- Alliance commander
UPDATE `creature_template` SET `modelid_2` = 24366 WHERE `entry` = 27949;
DELETE FROM `creature` WHERE `id` = 27949;
UPDATE `creature_template` SET `difficulty_entry_1` = '' WHERE `entry` = 27949;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(95896, 27949, 576, 3, 1, 0, 0, 425.4, 185.827, -35.0195, 3.41809, 7200, 0, 0, 74328, 0, 0, 0);

-- alliance berserker
UPDATE `creature_template` SET `modelid_2` = 24353 WHERE `entry` = 26800;
DELETE FROM `creature` WHERE `id`=26800;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(79906, 26800, 576, 3, 1, 0, 0, 388.62, 149.04, -35.0196, 2.53157, 7200, 0, 0, 37164, 0, 0, 0),
(79911, 26800, 576, 3, 1, 0, 0, 389.677, 168.528, -35.0195, 4.6535, 7200, 0, 0, 37164, 0, 0, 0),
(79921, 26800, 576, 3, 1, 0, 0, 402.83, 184.085, -35.0195, 4.5357, 7200, 0, 0, 37164, 0, 0, 0),
(79936, 26800, 576, 3, 1, 0, 0, 421.783, 189.668, -35.0195, 3.86184, 7200, 0, 0, 37164, 0, 0, 0),
(79941, 26800, 576, 3, 1, 0, 0, 430.212, 187.79, -35.0195, 3.27671, 7200, 0, 0, 37164, 0, 0, 0),
(95898, 26800, 576, 3, 1, 0, 0, 397.238, 170.022, -35.0195, 4.64565, 7200, 0, 0, 37164, 0, 0, 0),
(95899, 26800, 576, 3, 1, 0, 0, 410.797, 181.588, -35.0199, 3.71126, 7200, 0, 0, 37164, 0, 0, 0),
(95900, 26800, 576, 3, 1, 0, 0, 460.639, 164.358, -35.0195, 2.5188, 7200, 0, 0, 37164, 0, 0, 0),
(95902, 26800, 576, 3, 1, 0, 0, 449.28, 176.942, -35.0195, 2.90758, 7200, 0, 0, 37164, 0, 0, 0),
(95903, 26800, 576, 3, 1, 0, 0, 407.409, 187.257, -35.0195, 4.0896, 7200, 0, 0, 37164, 0, 0, 0),
(79948, 26800, 576, 3, 1, 0, 0, 444.773, 181.846, -35.0196, 4.24275, 7200, 0, 0, 37164, 0, 0, 0),
(79968, 26800, 576, 3, 1, 0, 0, 462, 146.856, -35.0195, 2.07113, 7200, 0, 0, 37164, 0, 0, 0),
(79953, 26800, 576, 3, 1, 0, 0, 442.156, 175.618, -35.0195, 2.68373, 7200, 0, 0, 37164, 0, 0, 0);

-- alliance cleric
UPDATE `creature_template` SET `modelid_2` = 24356 WHERE `entry` = 26805;
DELETE FROM `creature` WHERE `id`=26805;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(79909, 26805, 576, 3, 1, 0, 0, 388.62, 149.04, -35.0196, 2.52373, 7200, 0, 0, 37164, 16155, 0, 0),
(79914, 26805, 576, 3, 1, 0, 0, 389.677, 168.528, -35.0195, 4.6535, 7200, 0, 0, 37164, 16155, 0, 0),
(79919, 26805, 576, 3, 1, 0, 0, 397.238, 170.022, -35.0195, 4.64565, 7200, 0, 0, 37164, 16155, 0, 0),
(79929, 26805, 576, 3, 1, 0, 0, 410.797, 181.588, -35.0199, 3.71126, 7200, 0, 0, 37164, 16155, 0, 0),
(79934, 26805, 576, 3, 1, 0, 0, 407.409, 187.257, -35.0195, 4.0896, 7200, 0, 0, 37164, 16155, 0, 0),
(95893, 26805, 576, 3, 1, 0, 0, 430.212, 187.79, -35.0195, 3.27671, 7200, 0, 0, 37164, 16155, 0, 0),
(95894, 26805, 576, 3, 1, 0, 0, 421.783, 189.668, -35.0195, 3.86184, 7200, 0, 0, 37164, 16155, 0, 0),
(95895, 26805, 576, 3, 1, 0, 0, 402.83, 184.085, -35.0195, 4.5357, 7200, 0, 0, 37164, 16155, 0, 0),
(79971, 26805, 576, 3, 1, 0, 0, 462, 146.856, -35.0195, 2.07113, 7200, 0, 0, 37164, 16155, 0, 0),
(79966, 26805, 576, 3, 1, 0, 0, 460.639, 164.358, -35.0195, 2.5188, 7200, 0, 0, 37164, 16155, 0, 0),
(79961, 26805, 576, 3, 1, 0, 0, 449.28, 176.942, -35.0196, 2.90758, 7200, 0, 0, 37164, 16155, 0, 0),
(79956, 26805, 576, 3, 1, 0, 0, 442.156, 175.618, -35.0195, 2.68373, 7200, 0, 0, 37164, 16155, 0, 0),
(78937, 26805, 576, 3, 1, 0, 0, 444.773, 181.846, -35.0195, 4.24275, 7200, 0, 0, 37164, 16155, 0, 0);

   -- REMOVE HORDE STATIC SPAWN FOR COMMANDERS EVENT
DELETE FROM `creature` WHERE `id` = 27947;
UPDATE `creature_template` SET `modelid_2` = 24352 WHERE `entry` = 27947;
UPDATE `creature_template` SET `difficulty_entry_1` =''  WHERE `entry` = 27947;
DELETE FROM `creature` WHERE `id` = 26801;
UPDATE `creature_template` SET `modelid_2` = 24354 WHERE `entry` = 26801;
DELETE FROM `creature` WHERE `id` = 26803;
UPDATE `creature_template` SET `modelid_2` = 24357 WHERE `entry` = 26803;
DELETE FROM `creature` WHERE `id` = 26799;
UPDATE `creature_template` SET `modelid_2` = 24358 WHERE `entry` = 26799;
 -- pool deletes for above removal
DELETE FROM `pool_creature` WHERE  `guid`=79905 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79907 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79908 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79910 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79912 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79913 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79915 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79916 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79918 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79920 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79922 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79924 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79930 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79931 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79933 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79925 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79926 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79928 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79935 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79937 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79939 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79940 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79942 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79944 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79947 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79949 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79951 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79952 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79954 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79955 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79957 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79958 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79960 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79962 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79963 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79965 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79967 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79969 LIMIT 1;
DELETE FROM `pool_creature` WHERE  `guid`=79970 LIMIT 1;

-- -------------
-- Keristrasza -
-- -------------

UPDATE `creature_template` SET `modelid_2` = 24307 WHERE `entry` = 26723;
UPDATE `creature_template` SET `modelid_2` = 24307 WHERE `entry` = 30540;

DELETE FROM `creature_model_info` WHERE (`modelid`=24307);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (24307, 2.5, 5.25, 2, 0, 0);

  -- set Breath Casters to flying (dummy NPCs near Keristrasza)
UPDATE creature_template SET InhabitType = 4 WHERE entry = 27048;


