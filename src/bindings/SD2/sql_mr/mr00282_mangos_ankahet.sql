-- -------------------
-- Instance_Ahnkahet -
-- -------------------

-- -------------
-- Elder Nadox -
-- -------------

-- boss Elder Nadox Achievment
UPDATE `achievement_criteria_requirement` SET `type`='18' WHERE (`criteria_id`='7317') AND (`type`='11');

UPDATE `creature_template` SET `ScriptName` = 'boss_nadox', `AIName`='' WHERE `entry` = 29309;

UPDATE `creature_template` SET `AIName`='',`ScriptName`='mob_nadox_guardian' WHERE (`entry`='30176');
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 30176;
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` = 30176;

UPDATE `creature_template` SET `AIName` = 'EventAI', `ScriptName` = '' WHERE `entry` = 30178;
DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=30178);
INSERT INTO `creature_ai_scripts` VALUES 
(3017801, 30178, 0, 0, 100, 7, 0, 500, 25000, 40000, 11, 56354, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Ahn kahar Swarmer - Cast Sprint');

UPDATE `creature_template` SET `ScriptName` = '', `AIName`='' WHERE `entry` = 30172;
UPDATE `creature_template` SET `ScriptName` = '', `AIName`='' WHERE `entry` = 30173;

