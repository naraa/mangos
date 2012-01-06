-- -----------------------
-- Instance Ruby Sanctum -
-- -----------------------

UPDATE `instance_template` SET `ScriptName`='instance_ruby_sanctum' WHERE `map`=724;

-- --------
-- Halion -
-- --------

UPDATE `creature_template` SET `ScriptName`='boss_halion_real', `AIName` ='' WHERE `entry`=39863;
UPDATE `creature_template` SET `ScriptName`='boss_halion_twilight', `AIName` ='' WHERE `entry`=40142;
UPDATE `creature_template` SET `ScriptName`='mob_halion_meteor', `AIName` ='' WHERE `entry` = 40029;
UPDATE `creature_template` SET `ScriptName`='mob_halion_flame', `AIName` ='' WHERE `entry` IN (40041);
UPDATE `creature_template` SET `ScriptName`='mob_halion_control', `AIName` ='' WHERE `entry` IN (40146);
UPDATE `creature_template` SET `ScriptName`='mob_halion_orb', `AIName` ='' WHERE `entry` IN (40083,40100);
UPDATE `creature_template` SET `ScriptName`='mob_orb_rotation_focus', `AIName` ='' WHERE `entry` = 40091;
UPDATE `creature_template` SET `ScriptName`='mob_orb_carrier', `AIName` ='' WHERE `entry` = 40081;
UPDATE `creature_template` SET `ScriptName`='mob_fiery_combustion', `AIName` ='' WHERE `entry` = 40001;
UPDATE `creature_template` SET `ScriptName`='mob_soul_consumption', `AIName` ='' WHERE `entry` = 40135;
UPDATE `creature_template` SET `ScriptName`='', `AIName` ='' WHERE `entry` IN (40143, 40144, 40145);

UPDATE `gameobject_template` SET `data10` = 74807, `faction` = '0', `ScriptName` = 'go_halion_portal_twilight' WHERE `gameobject_template`.`entry` IN (202794,202795);
UPDATE `gameobject_template` SET `faction` = '0', `ScriptName` = 'go_halion_portal_real' WHERE `gameobject_template`.`entry` IN (202796);

-- -----------
-- Baltharus -
-- -----------

UPDATE `creature_template` SET `ScriptName`='boss_baltharus', `AIName` ='', `dmg_multiplier` = 80  WHERE `entry`=39751;
UPDATE `creature_template` SET `ScriptName`='mob_baltharus_clone', `AIName` ='', `dmg_multiplier` = 80  WHERE `entry`=39899;
INSERT IGNORE INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `unk16`, `unk17`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(39900, 0, 0, 0, 0, 0, 11686, 0, 11686, 0, 'Baltharus Target Dummy', '', NULL, 0, 1, 1, 25, 27, 0, 0, 17, 35, 35, 0, 1, 1.14286, 1, 0, 1, 2, 0, 0, 1, 2000, 2000, 1, 33554432, 0, 0, 0, 0, 0, 0, 1, 2, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 258, '');
UPDATE `creature_template` SET `ScriptName`='', `AIName` ='' WHERE `entry`=39900;

-- -----------
-- Zarithian -
-- -----------

UPDATE `creature_template` SET `ScriptName`='boss_zarithrian', `AIName` ='' WHERE `entry`=39746;
UPDATE `creature` SET `position_x` = '3008.552734',`position_y` = '530.471680',`position_z` = '89.195290',`orientation` = '6.16' WHERE `id` = 39746;
UPDATE `creature_template` SET `ScriptName`='mob_flamecaller_ruby', `AIName` ='' WHERE `entry`=39814;

-- ------------------
-- Saviana Ragefire -
-- ------------------

UPDATE `creature_template` SET `ScriptName`='boss_ragefire', `AIName` ='' WHERE `entry`=39747;
DELETE FROM `spell_script_target` WHERE `entry` IN (74455);
INSERT INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES 
('74455', '1', '39747');

-- -------------
-- Xerestrasza -
-- -------------

UPDATE `creature_template` SET `ScriptName`='mob_xerestrasza', `AIName` ='' WHERE `entry`=40429;

-- --------------------------------------------------------------------------------------------------------

-- --------------------
-- Trash mobs updates -
-- --------------------
  -- ------------------------ Updated 1/6/2012 --------- loot and few things need more love

-- ----------------------------- 
-- Charscale Invoker ID: 40417 -
-- -----------------------------

UPDATE `creature_template` SET `modelid_2` = 27227, `minmana` = 219840, `maxmana` = 219840, `speed_run` = 1.9, `spell1` = 75416, `spell2` = 75412, `spell3` = 75413 WHERE `entry` = 40417;
DELETE FROM `skinning_loot_template` WHERE (`entry`=40417);
INSERT INTO `skinning_loot_template` VALUES 
(40417, 33568, 75, 1, 1, 3, 0, 0, 0),
(40417, 38557, 24, 1, 1, 2, 0, 0, 0),
(40417, 44128, 0.9, 1, 1, 1, 0, 0, 0);
DELETE FROM `creature_loot_template` WHERE (`entry`=40417);
INSERT INTO `creature_loot_template` VALUES 
(40417, 33414, 1.4, 0, 1, 1, 0, 0, 0),
(40417, 33428, 1, 0, 1, 1, 0, 0, 0),
(40417, 33445, 3.2, 0, 1, 1, 0, 0, 0),
(40417, 33454, 5.2, 0, 1, 1, 0, 0, 0),
(40417, 33470, 27.2, 0, 1, 7, 0, 0, 0),
(40417, 36390, 1.4, 0, 1, 1, 0, 0, 0),
(40417, 39152, 25, 0, 1, 1, 28, 45546, 39152),
(40417, 42172, 1, 0, -42172, 1, 0, 0, 0),
(40417, 43507, 1, 0, -43507, 1, 0, 0, 0),
(40417, 43852, 12.5, 0, 1, 1, 0, 0, 0),
(40417, 43510, 1, 0, 1, 1, 0, 0, 0),
(40417, 43509, 1, 0, 1, 1, 0, 0, 0);
UPDATE `creature_template` SET `KillCredit1` = 40417, `modelid_2` = 27227, `minmana` = 400000, `maxmana` = 400000, `spell3` = 75416, `speed_run` = 1.9 WHERE `entry` = 40418;
DELETE FROM `creature` WHERE `id`=40417;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(93599, 40417, 724, 15, 1, 0, 0, 3229.01, 389.905, 82.4493, 3.73609, 604800, 0, 0, 539200, 219840, 0, 0),
(93600, 40417, 724, 15, 1, 0, 0, 3262.91, 479.629, 80.026, 1.50098, 604800, 0, 0, 539200, 219840, 0, 0),
(93601, 40417, 724, 15, 1, 0, 0, 3248.99, 481.621, 80.5851, 1.44862, 604800, 0, 0, 539200, 219840, 0, 0),
(93602, 40417, 724, 15, 1, 0, 0, 3096.49, 611.115, 77.7981, 3.73852, 604800, 0, 0, 539200, 219840, 0, 2),
(93603, 40417, 724, 15, 1, 0, 0, 3090.89, 415.057, 80.8881, 5.79561, 604800, 0, 0, 539200, 219840, 0, 0),
(93604, 40417, 724, 15, 1, 0, 0, 3086.16, 411.159, 81.8881, 5.79577, 604800, 0, 0, 539200, 219840, 0, 0),
(93605, 40417, 724, 15, 1, 0, 0, 3239.26, 625.144, 78.7274, 2.59941, 604800, 0, 0, 539200, 219840, 0, 2),
(93606, 40417, 724, 15, 1, 0, 0, 3269.8, 601.389, 81.3356, 5.37561, 604800, 0, 0, 539200, 219840, 0, 0),
(93607, 40417, 724, 15, 1, 0, 0, 3088.62, 591.48, 75.9926, 1.94592, 604800, 0, 0, 539200, 219840, 0, 2);

-- ------------------------------
-- Charscale Assaulter ID 40419 -
-- ------------------------------

UPDATE `creature_template` SET `modelid_2` = 14308, `speed_run` = 1.9, `spell2` = 75417, `spell3` = 75416 WHERE `entry` = 40419;
DELETE FROM `creature_model_info` WHERE (`modelid`=14308);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (14308, 2, 5, 0, 0, 0);
DELETE FROM `skinning_loot_template` WHERE (`entry`=40419);
INSERT INTO `skinning_loot_template` VALUES 
(40419, 33568, 74, 1, 1, 3, 0, 0, 0),
(40419, 38557, 24, 1, 1, 2, 0, 0, 0),
(40419, 44128, 0.9, 1, 1, 1, 0, 0, 0);
UPDATE `creature_template` SET `KillCredit1` = 40419, `modelid_2` = 14308, `speed_run` = 1.9, `spell3` = 75416 WHERE `entry` = 40420;
DELETE FROM `creature_loot_template` WHERE (`entry`=40419);
INSERT INTO `creature_loot_template` VALUES 
(40419, 33419, 1.3, 0, 1, 1, 0, 0, 0),
(40419, 33428, 1.7, 0, 1, 1, 0, 0, 0),
(40419, 33429, 0.9, 0, 1, 1, 0, 0, 0),
(40419, 33445, 4.8, 0, 1, 1, 0, 0, 0),
(40419, 33447, 2.2, 0, 1, 1, 0, 0, 0),
(40419, 33454, 4.9, 0, 1, 1, 0, 0, 0),
(40419, 33470, 25.5, 0, 1, 7, 0, 0, 0),
(40419, 36696, 1.1, 0, 1, 1, 0, 0, 0),
(40419, 43852, 12.7, 0, 1, 1, 0, 0, 0),
(40419, 36682, 0.5, 0, 1, 1, 0, 0, 0),
(40419, 36429, 0.5, 0, 1, 1, 0, 0, 0);

-- ------------------------------
-- Charscale Elite     ID 40421 -
-- ------------------------------

UPDATE `creature_template` SET `modelid_2` = 12891, `speed_run` = 1.9 WHERE `entry` = 40421;
UPDATE `creature_template` SET `KillCredit1` = 40421, `modelid_2` = 12891, `speed_run` = 1.9 WHERE `entry` = 40422;
DELETE FROM `skinning_loot_template` WHERE (`entry`=40421);
INSERT INTO `skinning_loot_template` VALUES 
(40421, 33568, 74, 1, 1, 3, 0, 0, 0),
(40421, 38557, 25, 1, 1, 2, 0, 0, 0),
(40421, 44128, 0.9, 1, 1, 1, 0, 0, 0);
DELETE FROM `creature_loot_template` WHERE (`entry`=40421);
INSERT INTO `creature_loot_template` VALUES 
(40421, 36556, 0.9, 0, 1, 1, 0, 0, 0),
(40421, 33436, 3.9, 0, 1, 1, 0, 0, 0),
(40421, 33470, 28.1, 0, 1, 7, 0, 0, 0),
(40421, 33383, 1, 0, 1, 1, 0, 0, 0),
(40421, 36500, 1.1, 0, 1, 1, 0, 0, 0),
(40421, 36171, 1.3, 0, 1, 1, 0, 0, 0),
(40421, 33445, 1.9, 0, 1, 1, 0, 0, 0),
(40421, 33447, 1.4, 0, 1, 1, 0, 0, 0),
(40421, 33448, 4.9, 0, 1, 1, 0, 0, 0),
(40421, 33454, 7.3, 0, 1, 1, 0, 0, 0),
(40421, 43852, 16.6, 0, 1, 1, 0, 0, 0),
(40421, 36472, 0.9, 0, 1, 1, 0, 0, 0),
(40421, 36668, 0.9, 0, 1, 1, 0, 0, 0),
(40421, 36542, 0.9, 0, 1, 1, 0, 0, 0);

-- ------------------------------
-- Charscale Commander ID 40423 -
-- ------------------------------

UPDATE `creature_template` SET `modelid_2` = 27226, `speed_run` = 1.9 WHERE `entry` = 40423;
DELETE FROM `creature_model_info` WHERE (`modelid`=27226);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (27226, 2, 4, 0, 0, 0);
UPDATE `creature_template` SET `KillCredit1` = 40423, `modelid_2` = 27226, `speed_run` = 1.9 WHERE `entry` = 40424;
DELETE FROM `skinning_loot_template` WHERE (`entry`=40423);
INSERT INTO `skinning_loot_template` VALUES 
(40423, 33568, 75, 1, 1, 3, 0, 0, 0),
(40423, 38557, 24, 1, 1, 2, 0, 0, 0),
(40423, 44128, 0.9, 1, 1, 1, 0, 0, 0);