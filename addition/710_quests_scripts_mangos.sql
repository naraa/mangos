-- quest 12801
UPDATE `creature_template` SET `AIName` = '', `ScriptName`='npc_highlord_darion_mograine' WHERE `entry`='29173';
UPDATE `creature_template` SET `AIName` = '', `ScriptName`='npc_the_lich_king_tirion_dawn' WHERE `entry` in (29183,29175);
UPDATE `creature_template` SET `AIName` = '', `ScriptName`='npc_minibosses_dawn_of_light' WHERE `entry` IN (29199,29204,29200);
UPDATE `creature_template` SET `AIName` = '', `ScriptName`='mob_acherus_ghoul' WHERE `entry`='29219';
UPDATE `creature_template` SET `AIName` = '', `ScriptName`='mob_warrior_of_the_frozen_wastes' WHERE `entry`='29206';
DELETE FROM `creature_ai_scripts` WHERE (`id`='2920601');

UPDATE `creature_template` SET `unit_flags`=0,`type_flags`=8 WHERE entry IN (29174,29182,29186,29190,29206,29176,29177,29181);
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'generic_creature' WHERE `entry` = 29178;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'generic_creature' WHERE `entry` = 29179;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'generic_creature' WHERE `entry` = 29180;

DELETE FROM `creature_ai_scripts` WHERE (`id`='2921901') OR (`id`='90076');

DELETE FROM `spell_script_target` WHERE `entry` in (53658, 53679, 53701, 53705, 53706, 53677, 53685);
INSERT INTO `spell_script_target` VALUES (53679, 1, 29183);
INSERT INTO `spell_script_target` VALUES (53701, 1, 29175);
INSERT INTO `spell_script_target` VALUES (53705, 1, 29183);
INSERT INTO `spell_script_target` VALUES (53706, 1, 29183);
INSERT INTO `spell_script_target` VALUES (53677, 1, 29227);
INSERT INTO `spell_script_target` VALUES (53685, 1, 29175);

-- YTDB cleanup
DELETE FROM `creature` WHERE `map` = 609 AND `guid` IN (116863);
DELETE FROM `creature` WHERE `map` = 609 AND `id` IN (29219,29206,29190);

-- quest 12701
DELETE FROM `spell_target_position` WHERE `id` = 52462;
INSERT INTO `spell_target_position` (id,target_map,target_position_x,target_position_y,target_position_z,target_orientation) VALUES (52462,609,2388.507568, -5900.213867, 108.645972, 3.797623);

-- Quest: Drake Hunt (11940/11919)
UPDATE `creature_template` SET ScriptName='npc_nexus_drake', AIName='' WHERE entry = 26127;

-- Quest: Merciful Freedom (11676)
UPDATE gameobject_template SET ScriptName='go_scourge_cage' WHERE entry IN (187854,187855,187856,187857,187858,187859,187860,187862,187863,187864,187865,187866,187867,187868,187870,187871,187872,187873,187874,187861,190803);

-- Quest The Gift That Keeps On Giving
-- item spell script targets (Scarlet Miners)
DELETE FROM spell_script_target WHERE entry = 52479;
INSERT INTO spell_script_target VALUES
(52479, 1, 28819),
(52479, 1, 28822),
(52479, 1, 28841);

UPDATE `creature_template` SET `AIName` = "EventAI" WHERE `entry` = 28846;
UPDATE `creature_template` SET `ScriptName` = "mob_scarlet_ghoul" WHERE `entry` = 28845;
 
DELETE FROM `creature_ai_texts` WHERE `entry` IN (-286102, -286101, -286100);
INSERT INTO `creature_ai_texts` VALUES
(-286100, "Die, Scourge filth!", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Scarlet Ghost SAY1"),
(-286101, "It won't be that easy, friend!", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Scarlet Ghost SAY2"),
(-286102, "I'll take you with me!", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Scarlet Ghost SAY3");
 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 28846;
INSERT INTO `creature_ai_scripts` VALUES
(2884601, 28846, 11, 0, 100, 0, 0, 0, 0, 0, 1, -286100, -286101, -286102, 0, 0, 0, 0, 0, 0, 0, 0, "Scarlet Ghost - Random say at spawn");

-- Quest: Abduction (11590)
UPDATE `creature_template` SET
minhealth=6387,
maxhealth=7185,
minlevel=64,
maxlevel=70,
minmana=7031,
maxmana=7196
WHERE entry=25474;

UPDATE `creature_template` SET
`ScriptName`='npc_beryl_sorcerer' , AIName=''
WHERE entry=25316;

-- Quest: Powering Our Defenses (8490)
UPDATE `creature_template` SET ScriptName='npc_infused_crystal' WHERE entry = 16364;

-- Enraged Wraith
DELETE FROM `creature` WHERE id = 17086;
UPDATE `creature_template` SET AIName='EventAI', flags_extra=flags_extra|64 WHERE entry=17086;

DELETE FROM `creature_ai_scripts` WHERE creature_id = 17086;
INSERT INTO `creature_ai_scripts` VALUES
(1708601,17086,2,0,100,0,25,0,0,0,11,8599,0,1,1,-106,0,0,0,0,0,0,'Enraged Wraith - Cast Enrage on 50% HP');
