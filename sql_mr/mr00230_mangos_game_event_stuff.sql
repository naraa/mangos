-- ------------------------------
-- Game Events && Holiday Stuff -
-- ------------------------------

-- --------------------------
-- Hallow Ends
-- --------------------------

-- Fixed Correct spell on bobbing apples ( Hallow Ends Event )  // DBC still showing wrong description in-game but effect works like it should
UPDATE `item_template` SET `spellid_1` = 24707 WHERE `entry` = 20516;

-- ------------------------------------------
-- Boss Headless Horseman fight in scarlet monastry
-- ------------------------------------------

-- Scriptname assignment

UPDATE creature_template SET ScriptName = 'boss_headless_horseman' WHERE entry = 23682;
UPDATE creature_template SET ScriptName = 'npc_horsemans_head' WHERE entry = 23775;
UPDATE creature_template SET ScriptName = 'mob_pulsing_pumpkin' WHERE entry = 23694;

-- Pumkin fiend template fixes
UPDATE `creature_template` SET `modelid_2` = 21822, `faction_A` = 14, `faction_H` = 14 WHERE `entry` = 23545;

-- Pulsing pumkin template fixes
UPDATE `creature_template` SET `modelid_2` = 24720, `faction_A` = 14, `faction_H` = 14, `type` = 6, `mechanic_immune_mask` = 8388624, `flags_extra` = 0 WHERE `entry` = 23694;

-- head of the horseman fixes
UPDATE `creature_template` SET `modelid_2` = 21908, `faction_A` = 7, `faction_H` = 7, `mechanic_immune_mask` = 787202047 WHERE `entry` = 23775;

-- Fixes to his template ( smart to wiped clean and replaced data)
-- Headless Horseman fixes and ect
DELETE FROM `creature_template` WHERE (`entry`=23682);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `unk16`, `unk17`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `vehicle_id`, `equipment_id`, `trainer_id`, `vendor_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES (23682, 0, 0, 0, 0, 0, 22351, 0, 0, 0, 'Headless Horseman', '', '', 0, 80, 80, 126000, 126000, 3994, 3994, 9929, 14, 14, 0, 1, 1.14286, 1, 3, 405, 609, 0, 152, 17.2, 2000, 2000, 2, 0, 0, 0, 0, 0, 0, 0, 324, 487, 122, 6, 1024, 23682, 0, 0, 0, 0, 0, 0, 0, 0, 42587, 42380, 42394, 0, 0, 0, 0, '', 0, 3, 10, 1, 0, 33277, 0, 0, 0, 0, 0, 167, 1, 0, 10400, 0, 0, 646659039, 0, 'boss_headless_horseman');
 
-- Fix quest script to correct horseman summon location
DELETE FROM `quest_end_scripts` WHERE `id`=11405;
INSERT INTO `quest_end_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `datalong3`, `datalong4`, `data_flags`,`dataint`,`dataint2`,`dataint3`,`dataint4`, `x`, `y`, `z`, `o`,`comments`) VALUES 
(11405, 0, 10, 23682, 1200000, 0, 0, 0, '0', '0', '0', '0', 1766.798, 1349.538, 18.6855, 6.2786, '');

DELETE FROM `quest_end_scripts` WHERE `id`=11404;
INSERT INTO `quest_end_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `datalong3`, `datalong4`, `data_flags`,`dataint`,`dataint2`,`dataint3`,`dataint4`, `x`, `y`, `z`, `o`,`comments`) VALUES 
(11404, 0, 10, 23682, 1200000, 0, 0, 0, '0', '0', '0', '0', 1766.798, 1349.538, 18.6855, 6.2786, '');

DELETE FROM `quest_end_scripts` WHERE `id`=11401;
INSERT INTO `quest_end_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `datalong3`, `datalong4`, `data_flags`,`dataint`,`dataint2`,`dataint3`,`dataint4`, `x`, `y`, `z`, `o`,`comments`) VALUES 
(11401, 0, 10, 23682, 1200000, 0, 0, 0, '0', '0', '0', '0', 1766.798, 1349.538, 18.6855, 6.2786, '');

DELETE FROM `quest_end_scripts` WHERE `id`=11392;
INSERT INTO `quest_end_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `datalong3`, `datalong4`, `data_flags`,`dataint`,`dataint2`,`dataint3`,`dataint4`, `x`, `y`, `z`, `o`,`comments`) VALUES 
(11392, 0, 10, 23682, 1200000, 0, 0, 0, '0', '0', '0', '0', 1766.798, 1349.538, 18.6855, 6.2786, '');

-- -- Quest fix to get quest inside instance w/o having the others from the villages ( this is the daily neutral one )
UPDATE `quest_template` SET `PrevQuestId` = 0 WHERE `entry` = 11401;

-- built new equip_template for him
DELETE FROM `creature_equip_template` WHERE (`entry`=10400);
INSERT INTO `creature_equip_template` (`entry`, `equipentry1`, `equipentry2`, `equipentry3`) VALUES (10400, 38175, 0, 0);

-- fix no sword showing on regen/whirlwinding headless dude
UPDATE `creature_template` SET `equipment_id` = 10400 WHERE `entry` = 23800;

-- --------------------------------------------------------------------------------------------------------------------------------------------

-- -----------------------------
-- Headless horseman Quest Event
-- -----------------------------

-- Headless Horseman fire bunny
UPDATE creature_template SET unit_flags = 0, AIName = '', faction_a = 35, faction_h = 35, ScriptName = 'npc_horseman_fire_bunny' WHERE entry = 23686;
UPDATE creature_template SET InhabitType = 4, ScriptName = 'npc_shade_of_horseman' WHERE entry = 23543;

DELETE FROM game_event WHERE entry = 101;
INSERT INTO game_event (entry,start_time,end_time,occurence,LENGTH,description) VALUES
(101,'2012-11-02 18:45:00','2020-12-31 09:00:00','15','6','Hallows End - Horseman Village Attack');

DELETE FROM creature WHERE id IN (23543,23686);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
-- Elwynn Forest
-- Shade of Horseman
('300042','23543','0','1','1','0','1870','-9482.45','64.2219','76.6803','6.12238','900','0','0','2220','0','0','2'),
-- Fire Bunny
('300031','23686','0','1','1','0','0','-9452.44','43.7669','57.1428','5.22336','900','0','0','67000','7196','0','0'),
('300032','23686','0','1','1','0','0','-9452.64','80.2419','57.3832','1.73619','900','0','0','67000','7196','0','0'),
('300033','23686','0','1','1','0','0','-9468.36','80.5987','57.8556','0.0829242','900','0','0','67000','7196','0','0'),
('300034','23686','0','1','1','0','0','-9480.96','27.9996','57.6236','5.36473','900','0','0','67000','7196','0','0'),
('300035','23686','0','1','1','0','0','-9480.17','42.3062','56.8661','5.91844','900','0','0','67000','7196','0','0'),
('300036','23686','0','1','1','0','0','-9468.42','44.794','56.701','4.52043','900','0','0','67000','7196','0','0'),
('300037','23686','0','1','1','0','0','-9481.29','22.6125','56.6316','4.51144','900','0','0','67000','7196','0','0'),
('300038','23686','0','1','1','0','0','-9479.57','34.7349','56.7651','5.96836','900','0','0','67000','7196','0','0'),
('300039','23686','0','1','1','0','0','-9460.17','81.0493','57.8907','1.49396','900','0','0','67000','7196','0','0'),
('300040','23686','0','1','1','0','0','-9474.11','43.5743','56.591','4.30175','900','0','0','67000','7196','0','0'),
('300041','23686','0','1','1','0','0','-9458.88','45.7095','56.6641','4.82405','900','0','0','67000','7196','0','0'),
-- Durotar
-- Shade of Horseman
('300043','23543','1','1','1','0','1870','347.11','-4720.79','31.8356','1.29259','900','0','0','2220','0','0','2'),
-- Fire Bunny
('300044','23686','1','1','1','0','0','370.479','-4715.85','15.802','0.903043','900','0','0','67000','7196','0','0'),
('300045','23686','1','1','1','0','0','364.642','-4715.55','15.4561','3.05896','900','0','0','67000','7196','0','0'),
('300046','23686','1','1','1','0','0','365.273','-4708.58','16.1301','1.48424','900','0','0','67000','7196','0','0'),
('300047','23686','1','1','1','0','0','367.071','-4702.39','16.3041','1.28789','900','0','0','67000','7196','0','0'),
('300048','23686','1','1','1','0','0','345.526','-4709.85','16.792','3.59303','900','0','0','67000','7196','0','0'),
('300049','23686','1','1','1','0','0','351.231','-4704.78','16.6707','0.726327','900','0','0','67000','7196','0','0'),
('300050','23686','1','1','1','0','0','356.883','-4699.76','16.5437','0.726327','900','0','0','67000','7196','0','0'),
('300051','23686','1','1','1','0','0','361.915','-4694.9','16.4737','0.781305','900','0','0','67000','7196','0','0'),
('300052','23686','1','1','1','0','0','338.461','-4708.17','17.628','0.954092','900','0','0','67000','7196','0','0'),
('300053','23686','1','1','1','0','0','321.19','-4698.06','17.2701','1.70415','900','0','0','67000','7196','0','0'),
('300054','23686','1','1','1','0','0','316.608','-4694.7','16.6794','4.08375','900','0','0','67000','7196','0','0');

DELETE FROM game_event_creature WHERE guid IN (SELECT guid FROM creature WHERE id IN (23543,23686));
INSERT INTO game_event_creature (guid,EVENT) SELECT guid, 101 FROM creature WHERE id IN (23543,23686);