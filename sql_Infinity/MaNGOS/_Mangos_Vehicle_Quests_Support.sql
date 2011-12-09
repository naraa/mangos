-- ---------------------------------------------------------------------------------------- --
-- ----------------------- Vehicles Quests Support ---------------------------------------- --
-- ---------------------------------------------------------------------------------------- --

UPDATE creature_template SET
    spell1 = 52264,
    spell2 = 52268,
    spell3 = 0,
    spell4 = 0,
    spell5 = 0,
    spell6 = 0,
    vehicle_id = 123
WHERE entry IN (28605, 28606, 28607);

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (28605, 28606, 28607);
INSERT INTO npc_spellclick_spells VALUES
(28605, 52263, 12680, 1, 12680, 1),
(28606, 52263, 12680, 1, 12680, 1),
(28607, 52263, 12680, 1, 12680, 1);
INSERT IGNORE INTO spell_script_target VALUES (52264, 1, 28653);

-- -------------
-- Quest 12953 -
-- -------------

UPDATE creature_template SET
    spell1 = 55812,
    spell2 = 0,
    spell3 = 0,
    spell4 = 0,
    spell5 = 0,
    spell6 = 0,
    vehicle_id = 213
WHERE entry IN (30066);

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (30066);
INSERT INTO npc_spellclick_spells VALUES
(30066, 44002, 12953, 1, 12953, 1);
-- INSERT IGNORE INTO spell_script_target VALUES (55812, 1, 30096); -- listed for TargetEntry 30096 does not have any implicit target TARGET_SCRIPT(38) or TARGET_SCRIPT_COORDINATES (46) or TARGET_FOCUS_OR_SCRIPTED_GAMEOBJECT (40).

-- ----------------------
-- 7th Legion Chain Gun -
-- -------------------- -

UPDATE creature_template SET
    IconName = 'Gunner',
    spell1 = 49190,
    spell2 = 49550,
    spell3 = 0,
    spell4 = 0,
    spell5 = 0,
    spell6 = 0,
    vehicle_id = 68
WHERE entry IN (27714);

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (27714);
INSERT INTO npc_spellclick_spells VALUES
(27714, 67373, 0, 0, 0, 1);

/* Broken-down Shredder */
UPDATE creature_template SET
    IconName = 'vehichleCursor',
    spell1 = 48558,
    spell2 = 48604,
    spell3 = 48548,
    spell4 = 0,
    spell5 = 48610,
    spell6 = 0,
    vehicle_id = 49
WHERE entry IN (27354);

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (27354);
INSERT INTO npc_spellclick_spells VALUES
(27354, 67373, 0, 0, 0, 1);
INSERT IGNORE INTO spell_script_target VALUES (48610, 1, 27396);

/* Forsaken Blight Spreader */
UPDATE creature_template SET
    IconName = 'vehichleCursor',
    spell1 = 48211,
    spell2 = 0,
    spell3 = 0,
    spell4 = 0,
    spell5 = 0,
    spell6 = 0,
    vehicle_id = 36
WHERE entry IN (26523);

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (26523);
INSERT INTO npc_spellclick_spells VALUES
(26523, 47961, 0, 0, 0, 1);

/* Argent Tournament mount */
UPDATE creature_template SET
    spell1 = 62544,
    spell2 = 62575,
    spell3 = 63010,
    spell4 = 62552,
    spell5 = 64077,
    spell6 = 62863,
    vehicle_id = 349
WHERE entry IN (33844, 33845);
UPDATE creature_template SET KillCredit1 = 33340 WHERE entry IN (33272);
UPDATE creature_template SET KillCredit1 = 33339 WHERE entry IN (33243);

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (33842, 33843);
INSERT INTO npc_spellclick_spells VALUES
(33842, 63791, 13829, 1, 0, 3),
(33842, 63791, 13839, 1, 0, 3),
(33842, 63791, 13838, 1, 0, 3),
(33843, 63792, 13828, 1, 0, 3),
(33843, 63792, 13837, 1, 0, 3),
(33843, 63792, 13835, 1, 0, 3);

DELETE FROM creature WHERE id IN (33844,33845);
UPDATE creature_template SET speed_run = '1.5', unit_flags = 8 WHERE entry IN (33844,33845);

-- Quest vehicles Support: Going Bearback (12851)
UPDATE creature_template SET
    spell1 = 54897,
    spell2 = 54907,
    spell3 = 0,
    spell4 = 0,
    spell5 = 0,
    spell6 = 0,
    vehicle_id = 308
WHERE entry IN (29598);

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (29598);
INSERT INTO npc_spellclick_spells VALUES
(29598, 54908, 12851, 1, 12851, 1);

-- INSERT IGNORE INTO spell_script_target VALUES (54897, 1, 29358); --listed for TargetEntry 29358 does not have any implicit target TARGET_SCRIPT(38) or TARGET_SCRIPT_COORDINATES (46) or TARGET_FOCUS_OR_SCRIPTED_GAMEOBJECT (40).

/* Frostbrood Vanquisher */
UPDATE creature_template SET
    spell1 = 53114,
    spell2 = 53110,
    spell3 = 0,
    spell4 = 0,
    spell5 = 0,
    spell6 = 0,
    vehicle_id = 156
WHERE entry IN (28670);

UPDATE creature_template SET maxhealth = 133525, minhealth = 133525, maxmana = 51360, minmana = 51360, InhabitType = 3 WHERE entry = 28670;

REPLACE INTO creature_template_addon (entry, mount, bytes1, b2_0_sheath, emote, moveflags, auras) VALUES
(28670, 0, 50331648, 1, 0, 1024, '53112');

-- from lanc
-- Infected Kodo fix quest (11690)
UPDATE creature_template SET
spell1 = 45877,
spell2 = 0,
spell3 = 0,
spell4 = 0,
spell5 = 0,
spell6 = 0,
vehicle_id = 29
WHERE entry IN (25596);

INSERT IGNORE INTO spell_script_target VALUES (45877, 1, 25596);

-- Horde Siege Tank
UPDATE creature_template SET
spell1 = 50672,
spell2 = 45750,
spell3 = 50677,
spell4 = 47849,
spell5 = 47962,
spell6 = 0,
vehicle_id = 26
WHERE entry IN (25334);

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (25334, 27107);
INSERT INTO npc_spellclick_spells VALUES
(25334, 47917, 11652, 1, 11652, 1);

-- REPLACE INTO spell_script_target VALUES (47962, 1, 27107); -- listed for TargetEntry 27107 does not have any implicit target TARGET_SCRIPT(38) or TARGET_SCRIPT_COORDINATES (46) or TARGET_FOCUS_OR_SCRIPTED_GAMEOBJECT (40).

REPLACE INTO spell_area (spell, AREA, quest_start, quest_start_active, quest_end, aura_spell, racemask, gender, autocast) 
VALUES ('47917','4027','11652','1','11652','0','0','2','0'), ('47917','4130','11652','1','11652','0','0','2','0');

-- from lanc
-- Refurbished Shredder (quest 12050)
UPDATE creature_template SET
spell1 = 47939,
spell2 = 47921,
spell3 = 47966,
spell4 = 47938,
spell5 = 0,
spell6 = 0,
vehicle_id = 300
WHERE entry IN (27061);

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (27061);
INSERT INTO npc_spellclick_spells VALUES (27061, 47920, 0, 0, 0, 1);
REPLACE INTO spell_script_target VALUES (47939, 0, 188539);

-- Argent Cannon (quest 13086)
UPDATE creature_template SET
    spell1 = 57485,
    spell2 = 57412,
    spell3 = 0,
    spell4 = 0,
    spell5 = 0,
    spell6 = 0,
    vehicle_id = 244
WHERE entry IN (30236);

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (30236);
INSERT INTO npc_spellclick_spells VALUES
(30236, 57573, 13086, 1, 13086, 1);

-- Wyrmrest Vanquisher (quest 12498)
UPDATE creature_template SET
    spell1 = 55987,
    spell2 = 50348,
    spell3 = 50430,
    spell4 = 0,
    spell5 = 0,
    spell6 = 0,
    vehicle_id = 99
WHERE entry IN (27996);

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (27996);
INSERT INTO npc_spellclick_spells VALUES
(27996, 50343, 12498, 1, 12498, 1);

REPLACE INTO creature_template_addon (entry, auras) VALUES (27996, '53112');

-- from me
-- Quest Reclamation (12546)
UPDATE creature_template SET spell1 = 50978,spell2 = 50980,spell3 = 50983,spell4 = 50985,
vehicle_id = 111
WHERE  entry = 28222;

-- Quest 12996
UPDATE creature_template SET spell1 = 54459,spell2 = 54458,spell3 = 54460,vehicle_id = 208 WHERE  creature_template.entry = 29918;

-- Quest 13236 Gift of the Lich King
REPLACE INTO spell_script_target VALUES (58916,2,31254);
REPLACE INTO spell_script_target VALUES (58917,1,31276);

-- from traponinet
-- Quest: No Fly Zone (12815)
UPDATE creature_template SET spell1=48766, spell2=54469, spell3=54467, spell4=55214, InhabitType=3 WHERE entry=29414;
REPLACE INTO creature_template_addon (entry,auras) VALUES (29414,'57403');

-- Quest: Defending Wyrmrest Temple (12372)
DELETE FROM gossip_scripts WHERE id=9568;
REPLACE INTO gossip_scripts (id,command,datalong,datalong2,comments) VALUES (9568,15,49256,3,'');
REPLACE INTO gossip_menu_option VALUES (9568,0,0,'We need to get into the fight. Are you ready?',1,1,-1,0,9568,0,0,NULL,9,12372,0,0,0,0,0,0,0);
UPDATE creature_template SET spell1=49161,spell2=49243,spell3=49263,spell4=49264,spell5=49367,unit_flags=0,InhabitType=3 WHERE entry=27629;
REPLACE INTO creature_template_addon (entry,bytes1,b2_0_sheath,auras) VALUES (27629,33554432,1,'50069');
REPLACE INTO creature_ai_scripts VALUES (2769801,27698,8,0,100,0,49367,-1,0,0,33,27698,6,0,0,0,0,0,0,0,0,0,'q12372');
UPDATE creature_template SET AIName='EventAI' WHERE entry=27698;
REPLACE INTO spell_script_target VALUES (49370,1,27698),(49367,1,27698);

-- Wintergarde Gryphon
UPDATE creature_template SET spell1 = 48363, spell2 = 48397, spell3 = 54170 WHERE entry = 27258;
DELETE FROM npc_spellclick_spells WHERE npc_entry = 27258;
INSERT INTO npc_spellclick_spells VALUES 
(27258, 48365, 12237, 1, 12237, 1),
(27258, 48365, 12237, 1, 12237, 3);

-- Quest King of the Mountain (13280)
UPDATE creature_template SET spell1 = 4338, spell2 = 4342, spell3 = 4336, vehicle_id = 282 WHERE entry = 31784;
DELETE FROM npc_spellclick_spells WHERE npc_entry = 31736;
INSERT INTO npc_spellclick_spells VALUES (31736, 59592, 13280, 1, 0, 3);

-- Njorndar Proto-Drake
UPDATE creature_template SET spell1 = 57493, spell2 = 7769, vehicle_id = 228 WHERE entry = 30272;
DELETE FROM npc_spellclick_spells WHERE npc_entry = 30272;
INSERT INTO npc_spellclick_spells VALUES (30272, 57401, 13071, 1, 13071, 1);

-- Updates vehicles by lanc
UPDATE creature_template SET rangeattacktime = 2000, vehicle_id = 294 WHERE entry = 32189;
UPDATE creature_template SET rangeattacktime = 2000, vehicle_id = 168 WHERE entry = 29433;
UPDATE creature_template SET rangeattacktime = 2000, vehicle_id = 175 WHERE entry = 29555;
DELETE FROM npc_spellclick_spells WHERE npc_entry IN (32189, 29433, 29555);
INSERT INTO npc_spellclick_spells VALUES 
(32189, 46598, 0, 0, 0, 1),
(29433, 47020, 0, 0, 0, 1),
(29555, 47020, 0, 0, 0, 1);

DELETE FROM creature_template_addon WHERE entry IN (29625, 29433, 32189, 36558);
INSERT INTO creature_template_addon (entry, mount, bytes1, b2_0_sheath, b2_1_pvp_state, emote, moveflags, auras) VALUES 
(29625, 0, 50331648, 1, 0, 0, 0, NULL),
(29433, 0,        0, 1, 0, 0, 0, NULL),
(32189, 0, 50397184, 1, 0, 0, 0, '60464'),
(36558, 0,        0, 1, 0, 0, 0, '67865');

-- from lanc
-- All Support Vehicles for mount The Argent Tournament
UPDATE `creature_template` SET spell1 = 62544, spell2 = 64342, spell3 = 63010, spell4 = 62552, spell5 = 64077, spell6 = 62863, 
spell7 = 63034, vehicle_id = 349 WHERE entry IN (33324, 33323, 33322, 33321, 33320, 33319, 33318, 33317, 33316);

DELETE FROM `npc_spellclick_spells` WHERE npc_entry = 33870;
INSERT INTO `npc_spellclick_spells` VALUES
(33870, 63663, 13664, 1, 0, 3);

DELETE FROM `npc_spellclick_spells` WHERE npc_entry IN (33842, 33843);
INSERT INTO `npc_spellclick_spells` VALUES
(33842, 63791, 13829, 1, 0, 3),
(33842, 63791, 13839, 1, 0, 3),
(33842, 63791, 13838, 1, 0, 3),
(33843, 63792, 13828, 1, 0, 3),
(33843, 63792, 13837, 1, 0, 3),
(33843, 63792, 13835, 1, 0, 3);

-- Typo fix for Argent Mount
UPDATE `creature_template` SET spell1 = 62544, spell2 = 64342, spell3 = 63010, spell4 = 62552, spell5 = 64077, spell6 = 62863, spell7 = 63034, vehicle_id = 349 WHERE entry IN (33844, 33845);

UPDATE `creature_template` SET `spell1` = 55982, `spell2` = 55980, `vehicle_id` = 30 WHERE `entry` = 30021;
UPDATE `creature_template` SET `vehicle_id` = 529 WHERE `entry` = 33782;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (30021, 33782);
INSERT INTO `npc_spellclick_spells` VALUES
(30021, 55785, 0, 0, 0, 3),
(33782, 63151, 0, 0, 0, 1);