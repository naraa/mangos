-- ---------------
-- Oculus instance
-- ---------------

-- ---------------------- Script Names ----------------------
UPDATE `instance_template` SET `ScriptName` = 'instance_oculus' WHERE `map` = 578;

-- fixes/support to the/for quests in/for oculus instance
  -- Constructs still need ACID support ( note to self check rest of mob in oculus by hand) -- spells contstruct use are added here to template
UPDATE `creature_template` SET `KillCredit1` = 27641, `modelid_2` = 24943, `spell1` = 50045 WHERE `entry` = 27641;
UPDATE `creature_template` SET `modelid_2` = 24943, `spell1` = 59214 WHERE `entry` = 30905;
UPDATE `creature_template` SET `ScriptName` = 'generic_creature' WHERE `entry` = 27641;
UPDATE `creature_template` SET `KillCredit1` = 27447 WHERE `entry` = 27447;  -- kill credit for varos
UPDATE `creature_template` SET `KillCredit1` = 27654 WHERE `entry` = 27654; -- KC for drakos
UPDATE `creature_template` SET `KillCredit1` = 27655 WHERE `entry` = 27655; -- KC for urom
UPDATE `creature_template` SET `KillCredit1` = 27656 WHERE `entry` = 27656; -- KC for eregos

-- -----------------------  Boss fixes DB -----------------------------

-- some ACID CLEAN UP
DELETE FROM `creature_ai_texts` WHERE (`entry`='-1153') OR (`entry`='-1154') 
OR (`entry`='-1155') OR (`entry`='-1156') OR (`entry`='-1157') OR (`entry`='-1158') OR (`entry`='-1159') 
OR (`entry`='-1160') OR (`entry`='-1161') OR (`entry`='-1162') OR (`entry`='-1163') 
OR (`entry`='-1164') OR (`entry`='-1165') OR (`entry`='-1166') OR (`entry`='-1167') 
OR (`entry`='-1168') OR (`entry`='-1169') OR (`entry`='-1170') OR (`entry`='-1171');


-- -------------------------
-- Drakos the Interrogator -
-- -------------------------
UPDATE `creature_template` SET `modelid_2` = 27032 WHERE `entry` = 27654;
UPDATE `creature_template` SET `modelid_2` = 27032 WHERE `entry` = 31558;

DELETE FROM `creature_model_info` WHERE (`modelid`=27032);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (27032, 1.5, 2.0, 0, 0, 0);

UPDATE `creature_template` SET `ScriptName` = 'boss_drakos' WHERE entry = 27654;
UPDATE `creature_template` SET `ScriptName` = 'npc_unstable_sphere' WHERE entry = 28166;
UPDATE `creature_template` SET `maxhealth` = 431392 WHERE `entry` = 31558;  -- Hard Instance Version  data from wow.com
UPDATE `creature_template` SET `mechanic_immune_mask` = 617299931 WHERE `entry` = 27654;  -- added immune to pacify
UPDATE `creature_template` SET `mechanic_immune_mask` = 617299931 WHERE `entry` = 31558;  -- added immune to pacify to hard version
  -- Unstable Sphere Fixes
UPDATE `creature_template` SET `minlevel` = 81, `maxlevel` = 81, `unit_flags` = 33587202 WHERE `entry` = 28166;

UPDATE `creature_template` SET `AIName` = '' WHERE `entry` = 27654;
DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=27654);

-- -------
-- Varos -
-- -------
UPDATE `creature_template` SET `modelid_2` = 27033 WHERE `entry` = 27447;
UPDATE `creature_template` SET `modelid_2` = 27033 WHERE `entry` = 31559;

DELETE FROM `creature_model_info` WHERE (`modelid`=27033);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (27033, 2.5, 2.5, 0, 0, 0);

UPDATE `creature_template` SET `ScriptName` = 'boss_varos' WHERE entry = 27447;
UPDATE `creature_template` SET `ScriptName` = 'npc_varos_orb' WHERE entry = 28183;
UPDATE `creature_template` SET `ScriptName` = 'npc_varos_beam_target' WHERE entry = 28239;

UPDATE `creature_template` SET `AIName` = '' WHERE `entry` = 27447;
DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=27447);

UPDATE `creature_template` SET `mechanic_immune_mask` = 617299931 WHERE `entry` = 27447; -- added immune to pacify
UPDATE `creature_template` SET `mechanic_immune_mask` = 617299931 WHERE `entry` = 31559; -- added immune to pacify to hard version 

REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) values
(51024, 1, 28239),
(51022, 1, 28239),
(57963, 1, 27656);

-- ------
-- urom -
-- ------
UPDATE `creature_template` SET `ScriptName` = 'boss_urom' WHERE entry = 27655;
UPDATE `creature_template` SET `modelid_2` = 25010 WHERE `entry` = 27655;
UPDATE `creature_template` SET `modelid_2` = 25010 WHERE `entry` = 31560;

DELETE FROM `creature_model_info` WHERE (`modelid`=25010);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (25010, 2, 2, 0, 0, 0);

-- --------
-- Eregos -
-- --------
UPDATE `creature_template` SET `ScriptName` = 'boss_eregos' WHERE entry = 27656;
UPDATE `creature_template` SET `modelid_2` = 27034, `mechanic_immune_mask` = 617299931 WHERE `entry` = 27656;
UPDATE `creature_template` SET `modelid_2` = 27034, `mechanic_immune_mask` = 617299931 WHERE `entry` = 31561;

DELETE FROM `creature_model_info` WHERE (`modelid`=27034);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (27034, 3, 10, 0, 0, 0);

UPDATE `creature_template` SET `ScriptName` = 'npc_planar_anomaly' WHERE entry = 30879;
UPDATE `creature_template` SET `modelid_1` = 11686, `modelid_2` = 11686 WHERE `entry` = 30879;

DELETE FROM `creature_model_info` WHERE (`modelid`=11686);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (11686, 1, 1.5, 2, 0, 0);
UPDATE `creature_template` SET `speed_run` = 1.5 WHERE `entry` = 30879;
-- -------------- Instance Data Fixes & Ect --------------------------------- --

-- herbalism flower   a ytdb bugs flowers cant wander around lol
UPDATE `creature_template` SET `unit_flags` = 33555204, `dynamicflags` = 8 WHERE `entry` = 29888;
UPDATE `creature_template` SET `speed_walk` = 0, `speed_run` = 0, `movementId` = 0 WHERE `entry` = 29888;

-- Fixes missing heroic flag settings for the instance in one gobal swoop  -- temp fix
UPDATE `creature` SET `spawnMask` = 3 WHERE `map` = 578 AND `spawnMask` = 1;

-- -----------------------
-- Oculus Drake Vehicles -
-- -----------------------

UPDATE `creature_template` SET `AIName` = '', `vehicle_id` = 70, `ScriptName` = 'mob_oculus_dragon' WHERE `entry` IN (27692,27756,27755);

-- Fix speed of oculus drakes
-- UPDATE `creature_template_addon` SET `auras`='50325' WHERE `entry` IN (27755,27692,27756);

UPDATE `creature_template` SET
    spell1 = 50232,
    spell2 = 50248,
    spell3 = 50240,
    spell4 = 50253,
    spell5 = 0,
    -- spell6 = 57403,
    InhabitType = 3
WHERE `entry` IN (27756);

UPDATE `creature_template` SET
    spell1 = 49840,
    spell2 = 49838,
    spell3 = 49592,
    spell4 = 0,
    spell5 = 0,
    -- spell6 = 57403,
    InhabitType = 3
WHERE `entry` IN (27755);
 
UPDATE `creature_template` SET
    spell1 = 50328,
    spell2 = 50341,
    spell3 = 50344,
    spell4 = 0,
    spell5 = 0,
    -- spell6 = 57403,
    InhabitType = 3
WHERE `entry` IN (27692);

REPLACE INTO `creature_template_addon` VALUES (27755,0,0,0,0,0,0,'57403');
REPLACE INTO `creature_template_addon` VALUES (27756,0,0,0,0,0,0,'57403');
REPLACE INTO `creature_template_addon` VALUES (27692,0,0,0,0,0,0,'57403');

DELETE FROM `spell_script_target` WHERE `entry` IN (49460, 49346, 49464);
INSERT INTO `spell_script_target` VALUES (49460, 1, 27755);
INSERT INTO `spell_script_target` VALUES (49346, 1, 27692);
INSERT INTO `spell_script_target` VALUES (49464, 1, 27756);

