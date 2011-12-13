-- ---------------
-- Oculus instance
-- ---------------

-- ---------------------- Script Names ----------------------


-- -----------------------  Boss fixes DB -----------------------------
-- Drakos the Interrogator

UPDATE `creature_template` SET `maxhealth` = 431392 WHERE `entry` = 31558;  -- Hard Instance Version  data from wow.com
UPDATE `creature_template` SET `mechanic_immune_mask` = 617299931 WHERE `entry` = 27654;  -- added immune to pacify
UPDATE `creature_template` SET `mechanic_immune_mask` = 617299931 WHERE `entry` = 31558;  -- added immune to pacify to hard version
  -- Unstable Sphere Fixes
UPDATE `creature_template` SET `minlevel` = 81, `maxlevel` = 81, `unit_flags` = 33587202 WHERE `entry` = 28166;

-- -------
-- Varos -
-- -------
UPDATE `creature_template` SET `mechanic_immune_mask` = 617299931 WHERE `entry` = 27447; -- added immune to pacify
UPDATE `creature_template` SET `mechanic_immune_mask` = 617299931 WHERE `entry` = 31559; -- added immune to pacify to hard version 


-- -------------- Instance Data Fixes & Ect --------------------------------- --

-- herbalism flower   a ytdb bugs flowers cant wander around lol
UPDATE `creature_template` SET `unit_flags` = 33555204, `dynamicflags` = 8 WHERE `entry` = 29888;
UPDATE `creature_template` SET `speed_walk` = 0, `speed_run` = 0, `movementId` = 0 WHERE `entry` = 29888;


-- -------
-- Fix speed of oculus drakes
-- UPDATE `creature_template_addon` SET `auras`='50325' WHERE `entry` IN (27755,27692,27756);