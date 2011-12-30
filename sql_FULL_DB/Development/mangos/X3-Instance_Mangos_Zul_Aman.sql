-- ------------------------
-- Instance Zul Aman      -
-- ------------------------

-- ----------
-- Akil'zon -
-- ----------
UPDATE `creature_template` SET `modelid_2` = 21630, `flags_extra` = 1 WHERE `entry` = 23574;
DELETE FROM `creature_model_info` WHERE (`modelid`=21630);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (21630, 2, 2, 0, 0, 0);
UPDATE `creature_template` SET `KillCredit1` = 23574 WHERE `entry` = 23574;

UPDATE `creature_template` SET `modelid_2` = 22255 WHERE `entry` = 24858;
DELETE FROM `creature_model_info` WHERE (`modelid`=22255);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (22255, 1, 1, 2, 0, 0);