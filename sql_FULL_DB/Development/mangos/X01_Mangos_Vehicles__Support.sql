-- ---------------------------------------------------------------------------------------- --
-- -------------------------- __Vehicle__Support__ ---------------------------------------- --
-- ---------------------------------------------------------------------------------------- --

-- ------------------------------------
-- HavenShire Colt, Mare and Stallion -
-- ------------------------------------
UPDATE creature_template SET
    spell1 = 52264,
    spell2 = 52268,
    spell3 = 0,
    spell4 = 0,
    spell5 = 0,
    spell6 = 0,
    spell7 = 0,
    spell8 = 0,
    vehicle_id = 123
WHERE entry IN (28605, 28606, 28607);

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (28605, 28606, 28607);
INSERT INTO npc_spellclick_spells VALUES
(28605, 52263, 12680, 1, 12680, 1),
(28606, 52263, 12680, 1, 12680, 1),
(28607, 52263, 12680, 1, 12680, 1);
INSERT IGNORE INTO spell_script_target VALUES (52264, 1, 28653);

-- -----------------------
-- Valkyrion Harpoon Gun -
-- -----------------------
UPDATE creature_template SET
    spell1 = 55812,
    spell2 = 0,
    spell3 = 0,
    spell4 = 0,
    spell5 = 0,
    spell6 = 0,
    vehicle_id = 213
WHERE entry = 30066;

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (30066);
INSERT INTO npc_spellclick_spells VALUES
(30066, 44002, 12953, 1, 12953, 1);
-- INSERT IGNORE INTO spell_script_target VALUES (55812, 1, 30096); -- listed for TargetEntry 30096 does not have any implicit target TARGET_SCRIPT(38) or TARGET_SCRIPT_COORDINATES (46) or TARGET_FOCUS_OR_SCRIPTED_GAMEOBJECT (40).

-- ----------------------
-- 7th Legion Chain Gun -
-- ----------------------
UPDATE creature_template SET
    IconName = 'Gunner',
    spell1 = 49190,
    spell2 = 49550,
    spell3 = 0,
    spell4 = 0,
    spell5 = 0,
    spell6 = 0,
    vehicle_id = 68
WHERE entry = 27714;

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (27714);
INSERT INTO npc_spellclick_spells VALUES
(27714, 67373, 0, 0, 0, 1);

-- ----------------------
-- Broken-down Shredder -
-- ----------------------
UPDATE creature_template SET
    IconName = 'vehichleCursor',
    spell1 = 48558,
    spell2 = 48604,
    spell3 = 48548,
    spell4 = 0,
    spell5 = 48610,
    spell6 = 0,
    vehicle_id = 49
WHERE entry = 27354;

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (27354);
INSERT INTO npc_spellclick_spells VALUES
(27354, 67373, 0, 0, 0, 1);
INSERT IGNORE INTO spell_script_target VALUES (48610, 1, 27396);

-- --------------------------
-- Forsaken Blight Spreader -
-- --------------------------
UPDATE creature_template SET
    IconName = 'vehichleCursor',
    spell1 = 48211,
    spell2 = 0,
    spell3 = 0,
    spell4 = 0,
    spell5 = 0,
    spell6 = 0,
    vehicle_id = 36
WHERE entry = 26523;

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (26523);
INSERT INTO npc_spellclick_spells VALUES
(26523, 47961, 0, 0, 0, 1);

-- --------------------------
-- Argent Tournament Mount -
-- --------------------------
UPDATE creature_template SET
    spell1 = 62544,
    spell2 = 62575,
    spell3 = 63010,
    spell4 = 62552,
    spell5 = 64077,
    spell6 = 62863,
    speed_run = '1.5',
    unit_flags = 8,
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

-- ---------
-- IceFang -
-- ---------
-- Quest vehicles Support: Going Bearback (12851)
UPDATE creature_template SET
    spell1 = 54897,
    spell2 = 54907,
    spell3 = 0,
    spell4 = 0,
    spell5 = 0,
    spell6 = 0,
    vehicle_id = 308
WHERE entry = 29598;

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (29598);
INSERT INTO npc_spellclick_spells VALUES
(29598, 54908, 12851, 1, 12851, 1);

-- INSERT IGNORE INTO spell_script_target VALUES (54897, 1, 29358); --listed for TargetEntry 29358 does not have any implicit target TARGET_SCRIPT(38) or TARGET_SCRIPT_COORDINATES (46) or TARGET_FOCUS_OR_SCRIPTED_GAMEOBJECT (40).

-- -----------------------
-- Frostbrood Vanquisher -
-- -----------------------
UPDATE creature_template SET
    spell1 = 53114,
    spell2 = 53110,
    spell3 = 0,
    spell4 = 0,
    spell5 = 0,
    spell6 = 0,
    maxhealth = 133525,
    minhealth = 133525,
    maxmana = 51360,
    minmana = 51360,
    InhabitType = 3,
    vehicle_id = 156
WHERE entry = 28670;

REPLACE INTO creature_template_addon (entry, mount, bytes1, b2_0_sheath, emote, moveflags, auras) VALUES
(28670, 0, 50331648, 1, 0, 1024, '53112');

-- ---------------
-- Infected Kodo -
-- ---------------
-- fix quest (11690)
UPDATE creature_template SET
    spell1 = 45901,
    spell2 = 45877,
    spell3 = 0,
    spell4 = 0,
    spell5 = 0,
    spell6 = 0,
    KillCredit1 = 25596,
    vehicle_id = 29
WHERE entry = 25596;

INSERT IGNORE INTO spell_script_target VALUES (45877, 1, 25698);

-- ------------------
-- Horde Siege Tank -
-- ------------------
UPDATE creature_template SET
    spell1 = 50672,
    spell2 = 45750,
    spell3 = 50677,
    spell4 = 47849,
    spell5 = 47962,
    spell6 = 0,
    vehicle_id = 26
WHERE entry = 25334;

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (25334, 27107);
INSERT INTO npc_spellclick_spells VALUES
(25334, 47917, 11652, 1, 11652, 1);
REPLACE INTO spell_area (spell, AREA, quest_start, quest_start_active, quest_end, aura_spell, racemask, gender, autocast)
VALUES ('47917','4027','11652','1','11652','0','0','2','0'), ('47917','4130','11652','1','11652','0','0','2','0');
-- REPLACE INTO spell_script_target VALUES (47962, 1, 27107); -- listed for TargetEntry 27107 does not have any implicit target TARGET_SCRIPT(38) or TARGET_SCRIPT_COORDINATES (46) or TARGET_FOCUS_OR_SCRIPTED_GAMEOBJECT (40).

-- -----------------------
-- Refurbished Shredder  -
-- -----------------------
-- (quest 12050)
UPDATE creature_template SET
    spell1 = 47939,
    spell2 = 47921,
    spell3 = 47966,
    spell4 = 47938,
    spell5 = 0,
    spell6 = 0,
    vehicle_id = 300
WHERE entry = 27061;

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (27061);
INSERT INTO npc_spellclick_spells VALUES (27061, 47920, 0, 0, 0, 1);
REPLACE INTO spell_script_target VALUES (47939, 0, 188539);

-- ----------------
-- Argent Cannon  -
-- ----------------
-- (quest 13086)
UPDATE creature_template SET
    spell1 = 57485,
    spell2 = 57412,
    spell3 = 0,
    spell4 = 0,
    spell5 = 0,
    spell6 = 0,
    vehicle_id = 244
WHERE entry = 30236;

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (30236);
INSERT INTO npc_spellclick_spells VALUES
(30236, 57573, 13086, 1, 13086, 1);

-- ---------------------
-- Wyrmrest Vanquisher -
-- ---------------------
-- (quest 12498)
UPDATE creature_template SET
    spell1 = 55987,
    spell2 = 50348,
    spell3 = 50430,
    spell4 = 0,
    spell5 = 0,
    spell6 = 0,
    vehicle_id = 99
WHERE entry = 27996;

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (27996);
INSERT INTO npc_spellclick_spells VALUES
(27996, 50343, 12498, 1, 12498, 1);

REPLACE INTO creature_template_addon (entry, auras) VALUES (27996, '53112');

-- ---------------
-- The Etymidian -
-- ---------------
-- Quest Reclamation (12546)
UPDATE creature_template SET
    spell1 = 50978,
    spell2 = 50980,
    spell3 = 50983,
    spell4 = 50985,
    vehicle_id = 111
WHERE entry = 28222;

-- -------------------
-- Warbear Matriarch -
-- -------------------
-- Quest 12996
UPDATE creature_template SET
    spell1 = 54459,
    spell2 = 54458,
    spell3 = 54460,
    vehicle_id = 208
WHERE entry = 29918;

-- --------------
-- Bone Gryphon -
-- --------------
-- Quest: No Fly Zone (12815)
UPDATE creature_template SET
    spell1=48766,
    spell2=54469,
    spell3=54467,
    spell4=55214,
    InhabitType=3
WHERE entry = 29414;
REPLACE INTO creature_template_addon (entry,auras) VALUES (29414,'57403');

-- -------------------
-- Wyrmrest Defender -
-- -------------------
-- Quest: Defending Wyrmrest Temple (12372)
UPDATE creature_template SET
    spell1=49161,
    spell2=49243,
    spell3=49263,
    spell4=49264,
    spell5=49367,
    unit_flags=0,
    InhabitType=3
WHERE entry=27629;

REPLACE INTO spell_script_target VALUES (49370,1,27698),(49367,1,27698);

-- ---------------------
-- Wintergarde Gryphon -
-- ---------------------
UPDATE creature_template SET
    spell1 = 48363,
    spell2 = 48397,
    spell3 = 54170
WHERE entry = 27258;
DELETE FROM npc_spellclick_spells WHERE npc_entry = 27258;
INSERT INTO npc_spellclick_spells VALUES
(27258, 48365, 12237, 1, 12237, 1),
(27258, 48365, 12237, 1, 12237, 3);

-- -----------------------
-- Geargrinder's Jumpbot -
-- -----------------------
-- Quest King of the Mountain (13280)
UPDATE creature_template SET
    spell1 = 4338,
    spell2 = 4342,
    spell3 = 4336,
    vehicle_id = 282
WHERE entry = 31784;
DELETE FROM npc_spellclick_spells WHERE npc_entry = 31736;
INSERT INTO npc_spellclick_spells VALUES (31736, 59592, 13280, 1, 0, 3);

-- ----------------------
-- Njorndar Proto-Drake -
-- ----------------------
UPDATE creature_template SET
    spell1 = 57493,
    spell2 = 7769,
    vehicle_id = 228
WHERE entry = 30272;
DELETE FROM npc_spellclick_spells WHERE npc_entry = 30272;
INSERT INTO npc_spellclick_spells VALUES (30272, 57401, 13071, 1, 13071, 1);

-- ---------
-- Chopper -
-- ---------
UPDATE creature_template SET
    IconName = 'vehichleCursor',
    PowerType = 3,
    spell1 = 62974,
    spell2 = 62286,
    spell3 = 62299,
    spell4 = 64660,
    AIName = 'NullAI'
WHERE entry = 33062;

DELETE FROM npc_spellclick_spells WHERE npc_entry = 33062;
INSERT INTO npc_spellclick_spells VALUES
(33062, 65030, 0, 0, 0, 1);

-- -----------------------
-- Salvaged Siege Engine -
-- -----------------------
UPDATE creature_template SET
    IconName = 'Gunner',
    PowerType = 3,
    spell1 = 62345,
    spell2 = 62522,
    spell3 = 62346,
    AIName = 'NullAI'
WHERE entry IN (33060);

DELETE FROM npc_spellclick_spells WHERE npc_entry = 33060;
INSERT INTO npc_spellclick_spells VALUES
(33060, 65031, 0, 0, 0, 1);

-- -----------------------
-- Salvaged Siege Turret -
-- -----------------------
UPDATE creature_template SET
    PowerType=3,
    spell1=62358,
    spell2=62359,
    spell3=64677,
    spell4=0,
    spell5=0,
    spell6=0
WHERE entry=33067;

-- ---------------------
-- Salvaged Demolisher -
-- ---------------------
UPDATE creature_template SET
    IconName = 'vehichleCursor',
    PowerType = 3,
    spell1 = 62306,
    spell2 = 62490,
    spell3 = 62308,
    spell4 = 62324,
    AIName = 'NullAI'
WHERE entry = 33109;

DELETE FROM npc_spellclick_spells WHERE npc_entry = 33109;
INSERT INTO npc_spellclick_spells VALUES
(33109, 62309, 0, 0, 0, 1);

-- -----------------------------------
-- Salvaged Demolisher Mechanic Seat -
-- -----------------------------------
UPDATE creature_template SET
    PowerType=3,
    spell1=62634,
    spell2=64979,
    spell3=62479,
    spell4=62471,
    spell5=0,
    spell6=62428
WHERE entry=33167;

-- ------------------------------------------------------
-- All Support Vehicles for mount The Argent Tournament -
-- ------------------------------------------------------
UPDATE `creature_template` SET
    spell1 = 62544,
    spell2 = 64342,
    spell3 = 63010,
    spell4 = 62552,
    spell5 = 64077,
    spell6 = 62863,
    spell7 = 63034,
    vehicle_id = 349
WHERE entry IN (33324, 33323, 33322, 33321, 33320, 33319, 33318, 33317, 33316);

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
UPDATE `creature_template` SET
    spell1 = 62544,
    spell2 = 64342,
    spell3 = 63010,
    spell4 = 62552,
    spell5 = 64077,
    spell6 = 62863,
    spell7 = 63034,
    vehicle_id = 349
WHERE entry IN (33844, 33845);

  -- Argent warhorse
UPDATE `creature_template` SET
    `vehicle_id` = 529
WHERE `entry` = 33782;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = 33782;
INSERT INTO `npc_spellclick_spells` VALUES
(33782, 63151, 0, 0, 0, 1);

-- ---------
-- Enormos -
-- ---------
UPDATE `creature_template` SET
    `spell1` = 55982,
    `spell2` = 55980,
    `vehicle_id` = 30
WHERE `entry` = 30021;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = 30021;
INSERT INTO `npc_spellclick_spells` VALUES
(30021, 55785, 0, 0, 0, 3);

-- --------------------------
-- Skybreaker Recon Fighter -
-- --------------------------
UPDATE creature_template SET
    rangeattacktime = 2000,
    vehicle_id = 294
WHERE entry = 32189;

DELETE FROM npc_spellclick_spells WHERE npc_entry = 32189;
INSERT INTO npc_spellclick_spells VALUES
(32189, 46598, 0, 0, 0, 1);

DELETE FROM creature_template_addon WHERE entry = 32189;
INSERT INTO creature_template_addon (entry, mount, bytes1, b2_0_sheath, b2_1_pvp_state, emote, moveflags, auras) VALUES
(32189, 0, 50397184, 1, 0, 0, 0, '60464');

-- ---------------
-- Goblin Sapper -
-- ---------------
UPDATE creature_template SET
    rangeattacktime = 2000,
    vehicle_id = 168
WHERE entry = 29433;

UPDATE creature_template SET
    rangeattacktime = 2000,
    vehicle_id = 175
WHERE entry = 29555;

DELETE FROM npc_spellclick_spells WHERE npc_entry IN (29433, 29555);
INSERT INTO npc_spellclick_spells VALUES
(29555, 47020, 0, 0, 0, 1),
(29433, 47020, 0, 0, 0, 1);

DELETE FROM creature_template_addon WHERE entry = 29433;
INSERT INTO creature_template_addon (entry, mount, bytes1, b2_0_sheath, b2_1_pvp_state, emote, moveflags, auras) VALUES
(29433, 0, 0, 1, 0, 0, 0, NULL);

-- -----------------------
-- Hyldsmeet Proto-Drake -
-- -----------------------
DELETE FROM creature_template_addon WHERE entry = 29625;
INSERT INTO creature_template_addon (entry, mount, bytes1, b2_0_sheath, b2_1_pvp_state, emote, moveflags, auras) VALUES
(29625, 0, 50331648, 1, 0, 0, 0, NULL);

-- ------------------
-- Highland Mustang -
-- ------------------
DELETE FROM npc_spellclick_spells WHERE npc_entry = 26472;
INSERT INTO npc_spellclick_spells VALUES (26472, 67373, 0, 0, 0, 1);

-- --------------------
-- Kor Kron war Rider -
-- --------------------
DELETE FROM npc_spellclick_spells WHERE npc_entry = 26813;
INSERT INTO npc_spellclick_spells VALUES (26813, 47424, 0, 0, 0, 1);

-- ----------------------
-- Kor Kron war Rider 2 -
-- ----------------------
DELETE FROM npc_spellclick_spells WHERE npc_entry = 26572;
INSERT INTO npc_spellclick_spells VALUES (26572, 47424, 0, 0, 0, 1);

-- --------------------
-- Onslaught Warhorse -
-- --------------------
DELETE FROM npc_spellclick_spells WHERE npc_entry = 27213;
INSERT INTO npc_spellclick_spells VALUES (27213, 67373, 0, 0, 0, 1);

-- ----------------------------
-- Steel Gate Flying manchine -
-- ----------------------------
DELETE FROM npc_spellclick_spells WHERE npc_entry = 24418;
INSERT INTO npc_spellclick_spells VALUES (24418, 67373, 0, 0, 0, 1);

-- --------------------------
-- Wintergrasp tower cannon -
-- --------------------------
DELETE FROM npc_spellclick_spells WHERE npc_entry = 28366;
INSERT INTO npc_spellclick_spells VALUES (28366, 60968, 0, 0, 0, 1);

-- --------------------
-- Wintergrasp Bomber -
-- --------------------
DELETE FROM npc_spellclick_spells WHERE npc_entry = 27850;
INSERT INTO npc_spellclick_spells VALUES (27850, 60968, 0, 0, 0, 1);

-- ----------------------
-- Wintergrasp catapult -
-- ----------------------
DELETE FROM npc_spellclick_spells WHERE npc_entry = 27881;
INSERT INTO npc_spellclick_spells VALUES (27881, 60968, 0, 0, 0, 1);

-- ------------------------
-- Wintergrasp demolisher -
-- ------------------------
DELETE FROM npc_spellclick_spells WHERE npc_entry = 28094;
INSERT INTO npc_spellclick_spells VALUES (28094, 60968, 0, 0, 0, 1);

-- --------------------------
-- Wintergrasp Seige Engine -
-- --------------------------
DELETE FROM npc_spellclick_spells WHERE npc_entry = 28312;
INSERT INTO npc_spellclick_spells VALUES (28312, 60968, 0, 0, 0, 1);

DELETE FROM npc_spellclick_spells WHERE npc_entry = 32627;
INSERT INTO npc_spellclick_spells VALUES (32627, 60968, 0, 0, 0, 1);

-- --------------------------
-- Wintergrasp Seige Turret -
-- --------------------------
DELETE FROM npc_spellclick_spells WHERE npc_entry = 28319;
INSERT INTO npc_spellclick_spells VALUES (28319, 60968, 0, 0, 0, 1);

DELETE FROM npc_spellclick_spells WHERE npc_entry = 32629;
INSERT INTO npc_spellclick_spells VALUES (32629, 60968, 0, 0, 0, 1);

-- --------------------------
-- Frostbrood Vanquisher    -
-- --------------------------
DELETE FROM npc_spellclick_spells WHERE npc_entry = 28670;
INSERT INTO npc_spellclick_spells VALUES (28670, 52196, 0, 0, 0, 1);

-- --------------------
-- Wooly mammoth bull -
-- --------------------
DELETE FROM npc_spellclick_spells WHERE npc_entry = 25743;
INSERT INTO npc_spellclick_spells VALUES (25743, 43695, 0, 0, 0, 0);

-- -------------------
-- Wyrmrest skytalon -
-- -------------------
DELETE FROM npc_spellclick_spells WHERE npc_entry = 32535;
INSERT INTO npc_spellclick_spells VALUES (32535, 61245, 0, 0, 0, 1);


-- =====================================================================================
-- ---------------------
-- Multi-Seated Mounts -
-- ---------------------
-- Mechano-hog, Mekgineer's Chopper
UPDATE creature_template SET
    vehicle_id = 318,
    IconName = 'vehichleCursor'
WHERE entry IN (29929, 32286);
-- Traveler's Tundra Mammoth
-- Grand Ice Mammoth
-- Grand Black War Mammoth
-- Grand Caravan Mammoth
DELETE FROM creature_template_addon WHERE entry = 32638;
UPDATE creature_template SET
    vehicle_id = 312,
    IconName = 'vehichleCursor'
WHERE entry IN (32633, 32640, 31857, 31858, 31861, 31862, 32212, 32213);
-- X-53 Touring Rocket
UPDATE creature_template SET
    vehicle_id = 774,
    IconName = 'vehichleCursor'
WHERE entry = 40725;

-- ==================================================================================================
-- ====================== Misc ======================================================================

-- Quest 13236 Gift of the Lich King
REPLACE INTO spell_script_target VALUES (58916,2,31254);
REPLACE INTO spell_script_target VALUES (58917,1,31276);

-- Earthen Stoneshaper
UPDATE creature_template SET unit_flags=33587968 WHERE entry=33620;

-- Ymirjar Skycaller true fix (delete hack from YTDB)
DELETE FROM creature_template_addon WHERE entry IN (31260, 37643);

-- Raise Ally
-- Commit 8f022d171f3e383e2e77

UPDATE `creature_template` SET `PowerType`='3', `spell1`='62225', `spell2`='47480', `spell3`='47481', `spell4`='47482', `spell5`='47484', `spell6`='67886', `ScriptName`='npc_risen_ally' WHERE `entry`='30230';

