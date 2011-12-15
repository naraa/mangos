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

