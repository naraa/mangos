-- ------------------------------------------------------------------------------------------------------------
-- World Creatures Template Spell Data && General Fixes ( all instance trash will be handled in instance sql) -
-- ------------------------------------------------------------------------------------------------------------

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
