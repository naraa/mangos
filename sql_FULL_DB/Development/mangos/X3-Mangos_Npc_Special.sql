-- ---------------
-- Special NPCS  -
-- ---------------

-- -----------
-- Snakes trap
-- -----------
UPDATE `creature_template` SET `ScriptName`='npc_snake_trap_serpents' WHERE `entry` IN (19921, 19833);

-- ------------ -
-- Mirror Immage
-- -------------
UPDATE `creature_template` SET `speed_walk` = 2.5, `modelid_1` = 11686, `modelid_3` = 11686, `minlevel` = 80, `maxlevel` = 80, `AIName` = '', `ScriptName`='npc_mirror_image' WHERE `entry` = 31216;

-- ----------
-- Rune blade
-- ----------
UPDATE `creature_template` SET  `modelid_1` = 11686, `modelid_3` = 11686,`AIName` = '', `ScriptName`='npc_runeblade' WHERE `entry` = 27893;

-- -----------
-- DK Gargoyle
-- -----------
UPDATE `creature_template` SET `ScriptName` = 'npc_death_knight_gargoyle' WHERE `entry` = '27829';

-- ---------------
-- Explosive decoy
-- ---------------
UPDATE `creature_template` SET `ScriptName` = 'npc_explosive_decoy' WHERE `entry` = '29134';

-- --------------
-- Eye of Kilrogg
-- --------------
UPDATE `creature_template` SET `ScriptName` = 'npc_eye_of_kilrogg' WHERE `entry` = '4277';

-- ----------------------
-- Greater fire elemental
-- ----------------------
UPDATE `creature_template` SET `ScriptName` = 'pet_greater_fire_elemental' WHERE `entry` = '15438';

-- -----------------------
-- Greater earth elemental
-- -----------------------
UPDATE `creature_template` SET `ScriptName` = 'pet_greater_earth_elemental' WHERE `entry` = '15352';

-- ------------------------
-- npc arena-honor exchange
-- ------------------------
DELETE FROM `creature_template` WHERE `entry` = 7;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `PowerType`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `vehicle_id`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `unk16`, `unk17`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(7, 0, 0, 0, 0, 0, 17858, 0, 17858, 0, 'Besdoban Durnoye', 'Arena-Honor Exchange', NULL, 0, 59, 61, 6700, 24000, 0, 5598, 5875, 4009, 35, 35, 1, 1.48, 1.14286, 1, 0, 91, 137, 0, 34, 1.4, 1400, 1400, 2, 0, 0, 0, 0, 0, 0, 0, 73, 110, 27, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 1, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 'npc_arena_honor');

-- ----------------
-- Tracking_Hound -
-- ----------------

UPDATE `creature_template` SET `modelid_2` = 2709, `minlevel` = 31, `maxlevel` = 33, `minhealth` = 4228, `maxhealth` = 4228 WHERE `entry` = 6867;

-- ---------------
-- off sd2 fixes -
-- ---------------

UPDATE gameobject_template SET ScriptName='' where entry=179552;
UPDATE gameobject_template SET ScriptName='' WHERE entry=179879;
UPDATE creature_template SET ScriptName='' WHERE entry=12144;
UPDATE creature_template SET ScriptName='' WHERE entry=14387;
UPDATE creature_template SET ScriptName='' WHERE entry IN (918, 3328, 4163, 4583, 5165, 5167, 13283, 16684);
UPDATE creature_template SET ScriptName='spell_dummy_npc' WHERE entry=23678;
UPDATE creature_template SET ScriptName='' WHERE entry=8436;

-- -----------
-- NeatElves -
-- -----------

-- Orb of Command
DELETE FROM gossip_menu WHERE entry=6001;
INSERT INTO `gossip_menu` (`entry`, `text_id`, `cond_1`, `cond_1_val_1`, `cond_1_val_2`, `cond_2`, `cond_2_val_1`, `cond_2_val_2`) VALUES
(6001, 7154, 0, 0, 0, 0, 0, 0),
(6001, 7155, 8, 7761, 0, 0, 0, 0);
DELETE FROM gossip_menu_option WHERE menu_id=6001;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `action_script_id`, `box_coded`, `box_money`, `box_text`, `cond_1`, `cond_1_val_1`, `cond_1_val_2`, `cond_2`, `cond_2_val_1`, `cond_2_val_2`, `cond_3`, `cond_3_val_1`, `cond_3_val_2`) VALUES
(6001, 0, 0, '<Put your hand on the sphere.>', 1, 1, -1, 0, 6001, 0, 0, NULL, 8, 7761, 0, 0, 0, 0, 0, 0, 0);
DELETE FROM gossip_scripts WHERE id=6001;
INSERT INTO `gossip_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `datalong3`, `datalong4`, `data_flags`, `dataint`, `dataint2`, `dataint3`, `dataint4`, `x`, `y`, `z`, `o`, `comments`) VALUES
(6001, 0, 15, 23460, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
-- Lunaclaw Spirit
DELETE FROM gossip_scripts WHERE id IN (386201, 386202);
INSERT INTO gossip_scripts (`id`, `delay`, `command`, `datalong`, `datalong2`, `datalong3`, `datalong4`, `data_flags`, `dataint`, `dataint2`, `dataint3`, `dataint4`, `x`, `y`, `z`, `o`, `comments`) VALUES
(386201, 0, 7, 6001, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Spirit of Lunaclaw - Questcredit (Alliance)'),
(386202, 0, 7, 6002, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Spirit of Lunaclaw - Questcredit (Horde)');
DELETE FROM gossip_menu_option WHERE menu_id=3862;
INSERT INTO gossip_menu_option VALUES
('3862', '0', '0', 'You have fought well, spirit.  I ask you to grant me the strength of your body and the strength of your heart.', '1', '1', '3863', '0', '386201', '0', '0', '', 9, 6001, 1, '0', '0', '0', '0', '0', '0'),
('3862', '1', '0', 'You have fought well, spirit.  I ask you to grant me the strength of your body and the strength of your heart.', '1', '1', '3863', '0', '386202', '0', '0', '', 9, 6002, 1, '0', '0', '0', '0', '0', '0');
-- Q3377 & npc_zamael_lunthistle
UPDATE gossip_menu_option SET cond_1=9,cond_1_val_1=3377, cond_1_val_2=1 WHERE menu_id=1285 AND id=0;
UPDATE gossip_menu_option SET action_menu_id= -1, action_script_id=1286 WHERE menu_id=1286 AND id=0;
DELETE FROM gossip_scripts WHERE id=1286;
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, comments) VALUES
(1286, 0, 7, 3377, 5, 'Zamael Lunthistle - Questcredit (3377');