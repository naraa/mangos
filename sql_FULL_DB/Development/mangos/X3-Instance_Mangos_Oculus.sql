-- ---------------
-- Oculus instance
-- ---------------

-- ---------------------- Script Names ----------------------
UPDATE `instance_template` SET `ScriptName` = 'instance_oculus' WHERE `map` = 578;

-- -----------------------  Boss fixes DB -----------------------------

-- -------------------------
-- Drakos the Interrogator -
-- -------------------------
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

