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

-- quest 12801 -the light of dawn
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

-- quest 12701 --massacre at lights point
DELETE FROM `spell_target_position` WHERE `id` = 52462;
INSERT INTO `spell_target_position` (id,target_map,target_position_x,target_position_y,target_position_z,target_orientation) VALUES (52462,609,2388.507568, -5900.213867, 108.645972, 3.797623);

-- Quest Fix Noth Special Brew  (dk starting area quest fix 12716/12717
UPDATE `quest_template` SET `SpecialFlags` = 0 WHERE `entry` = 12717;

DELETE FROM `creature_questrelation` WHERE `quest` = 12716; 
DELETE FROM `gameobject_questrelation` WHERE `quest` = 12716; 
UPDATE `item_template` SET `StartQuest`=0 WHERE `StartQuest` = 12716; 
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES (28919, 12716); 
UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry` = 28919; 
DELETE FROM `creature_involvedrelation` WHERE `quest` = 12716; 
DELETE FROM `gameobject_involvedrelation` WHERE `quest` = 12716; 
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES (28919, 12716); 
UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry`=28919; 
UPDATE `quest_template` SET `ExclusiveGroup` = 12716 WHERE `entry` = 12716; 

-- Eye of acherus
UPDATE `creature_template` SET `InhabitType` = 3, `ScriptName` = 'npc_eye_of_acherus' WHERE `entry` = 28511;
REPLACE INTO `creature_template_addon` (`entry`,`moveflags`,`auras`) VALUES (28511,33562624,''),(28525,0,'64328'),(28542,0,'64328'),(28543,0,'64328'),(28544,0,'64328');
REPLACE INTO `spell_script_target` (`entry`,`type`,`targetEntry`) VALUES (51859,1,28525),(51859,1,28542),(51859,1,28543),(51859,1,28544);
DELETE FROM `creature_addon` WHERE `guid` IN (SELECT guid FROM `creature` WHERE `id` IN (28511,28525,28542,28543,28544));
UPDATE `npc_spellclick_spells` SET `quest_start` = 0, `quest_start_active` = 0 WHERE `npc_entry` = 29501;

-- hack fix paired with core commit for spell support to when this is reverted core support needs fixed
UPDATE `quest_template` SET `ReqSpellCast1` = 51858, `ReqSpellCast2` = 51858, `ReqSpellCast3` = 51858, `ReqSpellCast4` = 51858 WHERE `entry` = 12641;

-- vehicle info some needs fixed
-- from me
-- into realm of shadows
UPDATE creature_template SET IconName = 'vehichleCursor',
unit_flags = 0,
spell1 = 52362
WHERE entry =28782;

UPDATE quest_template SET 
SrcSpell = 52359,
SpecialFlags = 2,
ReqCreatureOrGOId1 = 28768,
ReqCreatureOrGOCount1 = 1,
ReqSpellCast1 = 0,
RewItemId1 = 39208,
RewItemCount1 = 1 WHERE entry = 12687;

DELETE FROM creature_involvedrelation WHERE quest IN (12687);
INSERT INTO creature_involvedrelation (id, quest) VALUES (28788, 12687);
UPDATE creature_template SET npcflag = 2 WHERE entry = 28788;

DELETE FROM spell_script_target WHERE entry = 52349;

UPDATE creature_ai_scripts SET 
action1_type   = '11',
action1_param1 = '52361',
action1_param2 = '6',
action1_param3 = '16',
action2_type   = '11',
action2_param1 = '52357',
action2_param2 = '6',
action2_param3 = '16',
action3_type   = '0'
WHERE id = 2876806;

DELETE FROM creature WHERE id = 28782;

DELETE FROM creature_template_addon WHERE entry = 28782;

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (28782);
INSERT INTO npc_spellclick_spells VALUES
(28782, 46598, 0, 0, 0, 1);

/* Scourge Gryphon */
UPDATE creature_template SET
    spell1 = 0,
    spell2 = 0,
    spell3 = 0,
    spell4 = 0,
    spell5 = 0,
    spell6 = 0,
    vehicle_id = 146
WHERE entry IN (28864);

-- From jahangames
-- Massacre at Light's point quest
UPDATE creature_template SET
spell1 = 52435,
spell2 = 52576,
spell3 = 0,
spell4 = 0,
spell5 = 52588,
spell6 = 0,
vehicle_id = 79
WHERE entry IN (28833);

UPDATE creature_template SET
spell1 = 52435,
spell2 = 52576,
spell3 = 0,
spell4 = 0,
spell5 = 52588,
spell6 = 0,
vehicle_id = 68
WHERE entry IN (28887);

INSERT INTO npc_spellclick_spells VALUES ('28833', '52447', '12701', '1', '12701', '1');
INSERT INTO npc_spellclick_spells VALUES ('28887', '52447', '12701', '1', '12701', '1');
UPDATE creature_template SET minhealth = 26140, maxhealth = 26140, dynamicflags = 0, minmana = 2117, maxmana = 2117, unit_flags = 772, minlevel = 55, maxlevel = 55, unk16 = 10, unk17 = 1, InhabitType = 3, scale = 1, mindmg = 685, maxdmg = 715, armor = 3232, attackpower = 214, unit_class = 2, TYPE = 10 WHERE entry = 28833;
UPDATE creature_template SET minhealth = 26140, maxhealth = 26140, dynamicflags = 0, minmana = 0, maxmana = 0, unit_flags = 772, minlevel = 55, maxlevel = 55, unk16 = 10, unk17 = 1, InhabitType = 3, scale = 1, mindmg = 685, maxdmg = 715, armor = 3232, attackpower = 214, unit_class = 2, TYPE = 10 WHERE entry = 28887;
INSERT IGNORE INTO spell_script_target VALUES (52576, 1, 28834);
INSERT IGNORE INTO spell_script_target VALUES (52576, 1, 28886);
INSERT IGNORE INTO spell_script_target VALUES (52576, 1, 28850);


