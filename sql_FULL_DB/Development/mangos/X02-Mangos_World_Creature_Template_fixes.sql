-- ------------------------------------------------------------------------------------------------------------
-- World Creatures Template Spell Data && General Fixes ( all instance trash will be handled in instance sql) -
-- ------------------------------------------------------------------------------------------------------------
-- VERSION == 1.0.0

-- ----------------------
--  :ID  -
-- ----------------------

-- -------------------
-- Flesh Eater :ID 3 -
-- -------------------
UPDATE `creature_template` SET `modelid_2` = 987 WHERE `entry` = 3;

DELETE FROM `creature_model_info` WHERE (`modelid`=987);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (987, 1.5, 1.5, 2, 0, 0);

   -- small trash loot fix
DELETE FROM `creature_loot_template` WHERE (`entry`=3);
INSERT INTO `creature_loot_template` VALUES 
(3, 2794, 1, 0, 1, 1, 0, 0, 0),
(3, 2879, 0.0039, 0, -2879, 1, 0, 0, 0),
(3, 885, 1.0931, 0, 1, 1, 0, 0, 0),
(3, 2819, 0.06, 0, -2819, 1, 0, 0, 0),
(3, 6579, 0.0145, 0, 1, 1, 0, 0, 0),
(3, 2194, 0.0238, 0, -2194, 1, 0, 0, 0),
(3, 2098, 0.0052, 0, -2098, 1, 0, 0, 0),
(3, 2072, 0.2, 0, -2072, 1, 0, 0, 0),
(3, 3057, 0.59, 0, -3057, 1, 0, 0, 0),
(3, 3058, 0.58, 0, -3058, 1, 0, 0, 0),
(3, 790, 0.19, 0, -790, 1, 0, 0, 0),
(3, 1129, -22, 0, 1, 1, 0, 0, 0),
(3, 884, -40, 0, 1, 1, 0, 0, 0),
(3, 929, 1.4381, 0, 1, 1, 0, 0, 0),
(3, 2911, 0.0118, 0, -2911, 1, 0, 0, 0),
(3, 3048, 0.26, 0, -3048, 1, 0, 0, 0),
(3, 857, 0.2, 0, -857, 1, 0, 0, 0),
(3, 3385, 0.752, 0, 1, 1, 0, 0, 0),
(3, 1705, 0.0421, 0, 1, 1, 0, 0, 0),
(3, 1121, 0.03, 0, 1, 1, 0, 0, 0),
(3, 1751, 10, 0, -1751, 1, 0, 0, 0),
(3, 1205, 2.3745, 0, 1, 1, 0, 0, 0),
(3, 1206, 0.1172, 0, 1, 1, 0, 0, 0),
(3, 6530, 14.1418, 0, 1, 1, 0, 0, 0),
(3, 4632, 0.0211, 0, 1, 1, 0, 0, 0),
(3, 2409, 0.0053, 0, -2409, 1, 0, 0, 0),
(3, 2601, 0.0554, 0, -2601, 1, 0, 0, 0),
(3, 887, 10.3515, 0, 1, 1, 0, 0, 0),
(3, 3396, 0.0185, 0, -3396, 1, 0, 0, 0),
(3, 3393, 0.0066, 0, 1, 1, 0, 0, 0),
(3, 21524, 0.0026, 0, 1, 1, 26, 141, 0),
(3, 6588, 0.0092, 0, 1, 1, 0, 0, 0),
(3, 1477, 0.3358, 0, -1477, 1, 0, 0, 0),
(3, 954, 0.4556, 0, -954, 1, 0, 0, 0),
(3, 6566, 0.0421, 0, 1, 1, 0, 0, 0),
(3, 4306, 4.9598, 0, 1, 1, 0, 0, 0),
(3, 4606, 4.8939, 0, 1, 1, 0, 0, 0),
(3, 5529, 10.258, 0, 1, 1, 0, 0, 0),
(3, 890, 0.0237, 0, -890, 1, 0, 0, 0),
(3, 2011, 0.0145, 0, -2011, 1, 0, 0, 0),
(3, 2592, 25.0412, 0, 1, 2, 0, 0, 0),
(3, 6577, 0.03, 0, 1, 1, 0, 0, 0),
(3, 6382, 0.03, 0, 1, 1, 0, 0, 0);

-- ---------------------
-- Kobold Vermin :ID 6 -
-- ---------------------

DELETE FROM `creature_model_info` WHERE (`modelid`=10913);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (10913, 1, 1, 2, 0, 0);

-- ----------------------
-- Forest Spider :ID 30 -
-- ----------------------

UPDATE `creature_template` SET `modelid_2` = 382 WHERE `entry` = 30;
UPDATE `creature_template` SET `spell1` = 11918, `spell2` = 4167 WHERE `entry` = 30;

DELETE FROM `creature_model_info` WHERE (`modelid`=382);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (382, 1.15, 1, 2, 0, 0);

DELETE FROM `creature_loot_template` WHERE (`entry`=30);
INSERT INTO `creature_loot_template` VALUES 
(30, 774, 0.473, 0, 1, 1, 0, 0, 0),
(30, 1476, 47.8467, 0, 1, 1, 0, 0, 0),
(30, 2406, 0.3647, 0, -2406, 1, 0, 0, 0),
(30, 2590, 41.022, 0, 1, 1, 0, 0, 0),
(30, 5465, 54.7255, 0, 1, 2, 0, 0, 0),
(30, 5571, 0.3, 0, -5571, 1, 0, 0, 0),
(30, 818, 0.473, 0, 1, 1, 0, 0, 0);

-- ----------------------
-- Mine spider :ID 43 -
-- ----------------------

DELETE FROM `creature_model_info` WHERE (`modelid`=368);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (368, 1.122, 1, 2, 0, 0);

UPDATE `creature_template` SET `modelid_2` = 368, `spell1` = 11918 WHERE `entry` = 43;

-- -------------------------
-- Skeleton Warroir :ID 48 -
-- -------------------------

DELETE FROM `creature_model_info` WHERE (`modelid`=200);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (200, 1.15, 1.275, 2, 0, 0);

UPDATE `creature_template` SET `modelid_2` = 200 WHERE `entry` = 48;

-- ----------------------------------
-- Bonechewer Riding Wolf :ID 18706 -
-- ----------------------------------
UPDATE `creature_template` SET `speed_walk` = 1, `speed_run` = 1.14286 WHERE `entry` = 18706;

-- ------------------------------
-- Gjalerbron Rune-Caster:ID 23989 -
-- ------------------------------
-- Template Update (23989)
UPDATE `creature_template` SET `spell1` = 66290, `AIName` = 'EventAI', `ScriptName` = '' WHERE `entry` = 23989;
DELETE FROM `creature_model_info` WHERE (`modelid`=21985);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (21985, 1.15, 1.5, 0, 21986, 0);
DELETE FROM `creature_model_info` WHERE (`modelid`=21986);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (21986, 1.15, 1.5, 0, 21985, 0);
-- ACID
DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=23989);
INSERT INTO creature_ai_scripts VALUES
(2398900,23989,0,0,100,1,1000,1000,7000,7000,11,66290,1,0,0,0,0,0,0,0,0,0,'Gjalerbron Sleep Watcher - Cast Sleep');

-- ------------------------------
-- Gjalerbron Rune-Caster:ID 23990 -
-- ------------------------------

-- Template update (23990)
UPDATE `creature_template` SET `AIName` = 'EventAI', `ScriptName` = '' WHERE `entry` = 23990;
DELETE FROM `creature_model_info` WHERE (`modelid`=21983);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (21983, 1.15, 1.5, 0, 21984, 0);
DELETE FROM `creature_model_info` WHERE (`modelid`=21984);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (21984, 1.15, 1.5, 0, 21983, 0);
-- Text
DELETE FROM creature_ai_texts WHERE entry IN (-239901,-239902);
INSERT INTO creature_ai_texts VALUES
(-239901,'You tiny creatures disgust me.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,0,0,0,'Gjalerbron Rune-Caster Say1'),
(-239902,'There will be no everlasting life for you.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,0,0,0,'Gjalerbron Rune-Caster Say2');
-- ACID
DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=23990);
INSERT INTO creature_ai_scripts VALUES
(2399000,23990,4,0,100,0,0,0,0,0,11,34787,1,0,23,1,0,0,1,-239901,-239902,0,'Gjalerbron Rune-Caster - Cast Freezing Circle and Say on Aggro'),
(2399001,23990,0,0,100,1,1000,1000,5000,5000,11,9672,1,0,0,0,0,0,0,0,0,0,'Gjalerbron Rune-Caster - Cast Frostbolt'),
(2399002,23990,0,0,100,1,4000,4000,15000,15000,11,43453,1,0,0,0,0,0,0,0,0,0,'Gjalerbron Rune-Caster - Cast Rune Ward');

-- ------------------------------
-- Gjalerbron Warrior :ID 23991 -
-- ------------------------------

-- template update(23991)
UPDATE `creature_template` SET `AIName` = 'EventAI', `ScriptName` = '' WHERE `entry` = 23991;
-- Text
DELETE FROM creature_ai_texts WHERE entry=-239911;
INSERT INTO creature_ai_texts VALUES
(-239911,'Look what has come to play.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,0,0,0,'Gjalerbron Warrior Say1');
-- ACID
DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=23991);
INSERT INTO creature_ai_scripts VALUES
(2399100,23991,4,0,100,0,0,0,0,0,11,13730,1,0,23,1,0,0,1,-239911,0,0,'Gjalerbron Warrior - Cast Demoralizing Shout and Say on Aggro'),
(2399101,23991,0,0,100,1,1000,1000,10000,10000,11,10966,1,0,0,0,0,0,0,0,0,0,'Gjalerbron Warrior - Cast Uppercut');
DELETE FROM `creature_model_info` WHERE (`modelid`=21961);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (21961, 1.15, 1.8, 0, 21987, 0);
DELETE FROM `creature_model_info` WHERE (`modelid`=21987);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (21987, 1.15, 1.8, 0, 21961, 0);

-- ------------------------------
-- Sepulchral Overseer :ID 23993 -
-- ------------------------------
-- Template updateSepulchral Overseer (23993)
UPDATE `creature_template` SET `modelid_2` = 17444, `AIName` = 'EventAI', `ScriptName` = '' WHERE `entry` = 23993;
DELETE FROM `creature_model_info` WHERE (`modelid`=17444);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (17444, 3.5, 4.25, 0, 0, 0);
-- EventAi
DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=23993);
INSERT INTO creature_ai_scripts VALUES
(2399300,23993,4,0,100,0,0,0,0,0,11,43556,1,0,23,1,0,0,1,-239901,-239902,0,'Sepulchral Overseer - Cast Curse of the Sepulcher on Aggro'),
(2399301,23993,0,0,100,1,1000,1000,5000,5000,11,12737,1,0,0,0,0,0,0,0,0,0,'Sepulchral Overseerr - Cast Frostbolt'),
(2399302,23993,0,0,100,1,4000,4000,10000,10000,11,22744,1,0,0,0,0,0,0,0,0,0,'Sepulchral Overseer - Cast Chains of Ice');

-- -------------------------
-- Necrolord :ID 24014     -
-- -------------------------

-- Template Updates (24014)
UPDATE `creature_template` SET `AIName` = 'EventAI', `ScriptName` = '' WHERE `entry` = 24014;
UPDATE `creature_template` SET `modelid_2` = 21988, `AIName` = 'EventAI', `ScriptName` = '' WHERE `entry` = 24014;
-- ACID Text
DELETE FROM creature_ai_texts WHERE entry IN (-240141,-240142);
INSERT INTO creature_ai_texts VALUES
(-240141,'More ingredients to fuel our rituals here.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,0,0,0,'Necrolord Say1'),
(-240142,'You too will serve the Lich King.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,0,0,0,'Necrolord Say2');
-- ACID
DELETE FROM creature_ai_scripts WHERE id IN (2401400,2401401,2401402);
INSERT INTO creature_ai_scripts VALUES
(2401400,24014,4,0,100,0,0,0,0,0,11,18267,1,0,23,1,0,0,1,-240141,-240142,0,'Necrolord - Cast Curse of Weakness and Say on Aggro'),
(2401401,24014,0,0,100,1,1000,1000,10000,10000,11,9613,1,0,0,0,0,0,0,0,0,0,'Necrolord - Cast Shadowbolt '),
(2401402,24014,0,0,100,1,4000,4000,10000,10000,11,17173,1,0,0,0,0,0,0,0,0,0,'Necrolord - Cast Drain Life');

DELETE FROM `creature_model_info` WHERE (`modelid`=21988);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (21988, 2, 2.625, 0, 0, 0);

-- --------------------------------------
--  Tundra Wolf :ID 25675  -
-- --------------------------------------
UPDATE `creature_template` SET `modelid_2` = 22044, `speed_run` = 1.4285 WHERE `entry` = 25675;

-- --------------------------------------
--  Oil-stained Wolf :ID 25791  -
-- --------------------------------------
UPDATE `creature_template` SET `speed_walk` = 1, `AIName` = '' WHERE `entry` = 25791;
DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=25791);

-- --------------------------------------
--  Bloodthirsty Tundra Wolf :ID 26672  -
-- --------------------------------------
UPDATE `creature_template` SET `speed_walk` = 1.2, `speed_run` = 1.4285 WHERE `entry` = 26672;

-- --------------------------------------
--  Sinewy Wolf :ID 31233  -
-- --------------------------------------
UPDATE `creature_template` SET `speed_run` = 1.4285 WHERE `entry` = 31233;


