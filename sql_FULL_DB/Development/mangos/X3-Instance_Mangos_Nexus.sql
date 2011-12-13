-- ----------------
-- Instance Nexus -
-- ----------------

-- -------
-- ormok -
-- -------

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

-- ------------
-- Commanders -
-- ------------
  -- just some fixes to all this

-- commander stout
UPDATE `creature_template` SET `modelid_2` = 24366 WHERE `entry` = 26796;
DELETE FROM `creature` WHERE `id` = 26796;
UPDATE `creature_template` SET `difficulty_entry_1` = '' WHERE `entry` = 26796;
UPDATE `creature_template` SET `faction_A` = 1802, `faction_H` = 1802 WHERE `entry` = 26796;

-- commander kolurg
UPDATE `creature_template` SET `modelid_2` = 24352 WHERE `entry` = 26798;
DELETE FROM `creature` WHERE `id`=26798;
UPDATE `creature_template` SET `difficulty_entry_1` = '' WHERE `entry` = 26798;
UPDATE `creature_template` SET `faction_A` = 1801, `faction_H` = 1801 WHERE `entry` = 26798;

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
UPDATE `creature_template` SET `difficulty_entry_1` = 26796 WHERE `entry` = 27949;
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
UPDATE `creature_template` SET `difficulty_entry_1` = 26798 WHERE `entry` = 27947;
DELETE FROM `creature` WHERE `id` = 26801;
UPDATE `creature_template` SET `modelid_2` = 24354 WHERE `entry` = 26801;
DELETE FROM `creature` WHERE `id` = 26803;
UPDATE `creature_template` SET `modelid_2` = 24357 WHERE `entry` = 26803;
DELETE FROM `creature` WHERE `id` = 26799;
UPDATE `creature_template` SET `modelid_2` = 24358 WHERE `entry` = 26799;

-- -------------
-- Keristrasza -
-- -------------

  -- set Breath Casters to flying (dummy NPCs near Keristrasza)
UPDATE creature_template SET InhabitType = 4 WHERE entry = 27048;


