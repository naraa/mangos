
-- Implement creature spells storage
-- DROP TABLE IF EXISTS `creature_spell`;
CREATE TABLE IF NOT EXISTS `creature_spell` (
    `guid`      int(11) unsigned NOT NULL COMMENT 'Unique entry from creature_template',
    `spell`     int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Spell id from DBC',
    `index`     tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT 'Spell index',
    `active`    tinyint(3) unsigned NOT NULL DEFAULT '0'COMMENT 'Active state for this spell',
    `disabled`  tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT 'Boolean state for spell',
    `flags`     int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Spell custom flags',
     PRIMARY KEY (`guid`,`index`,`active`)
) DEFAULT CHARSET=utf8 PACK_KEYS=0 COMMENT='Creature spells storage';

ALTER TABLE `creature_spell`
    DROP PRIMARY KEY,
    ADD PRIMARY KEY (`guid`,`index`,`active`);

-- creature table minor fix
ALTER TABLE `creature` CHANGE `spawndist` `spawndist` FLOAT DEFAULT '0' NOT NULL;

-- Playerbot

DELETE FROM `command` WHERE `name` = 'bot';
INSERT INTO `command`
    (`name`, `security`, `help`)
VALUES 
    ('bot',0,'Syntax:\r.bot add BOTNAME (add character to world)\r.bot remove BOTNAME (remove character from world)\r.bot co|combatorder BOTNAME COMBATORDER [TARGET]');

DELETE FROM `gossip_menu_option` WHERE `option_text` = 'GOSSIP_OPTION_BOT';

-- Item Convert

REPLACE INTO `item_convert`
    (`entry`, `item`)
VALUES
    (50337, 44136),
    (50335, 44133),
    (50370, 44152),
    (50367, 44149),
    (50368, 44159),
    (50369, 44150),
    (50372, 44701),
    (50373, 44702),
    (50336, 44134),
    (50338, 44135);

-- Raise Ally
-- Commit 8f022d171f3e383e2e77

UPDATE `creature_template` SET `PowerType`='3', `spell1`='62225', `spell2`='47480', `spell3`='47481', `spell4`='47482', `spell5`='47484', `spell6`='67886', `ScriptName`='npc_risen_ally' WHERE `entry`='30230';

-- Refer a friend

DELETE FROM `command` WHERE `name` IN ('account friend add','account friend delete', 'account friend list');

INSERT INTO `command`
    (`name`, `security`, `help`)
VALUES
    ('account friend add',3,'Syntax: .account friend add [#accountId|$accountName] [#friendaccountId|$friendaccountName]\r\n\r\nSet friend account.'),
    ('account friend delete',3,'Syntax: .account friend delete [#accountId|$accountName] [#friendaccountId|$friendaccountName]\r\n\r\nDelete friend account.'),
    ('account friend list',3,'Syntax: .account friend list [#accountId|$accountName]\r\n\r\nList friends for account.');

DELETE FROM `mangos_string` WHERE `entry` IN (11133,11134);
INSERT INTO `mangos_string`
    (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`)
VALUES
    (11133,'RAF system ok.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
    (11134,'RAF system error.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);

-- SET Diminishing Returns for taunt
UPDATE creature_template SET flags_extra = flags_extra|8192 WHERE rank = 3;

-- Not Diminishing Returns for taunt
UPDATE creature_template SET flags_extra = flags_extra&~8192 WHERE entry IN (
-- Instructor Razuvious
16061, 29940,
-- Toravon the Ice Watcher
38433, 38462,
-- Gormok the Impaler
34796, 35438, 35439, 35440,
-- Lady Deathwhisper
36855, 38106, 38296, 38297
);

-- had typo in off mangos strings

DELETE FROM `command` WHERE `name` IN ('cast','cast back','cast self','cast target');

INSERT INTO `command` (`name`,`security`,`help`) VALUES
('cast',3,'Syntax: .cast #spellid [triggered]\r\n  Cast #spellid to selected target. If no target selected cast to self. If \'triggered\' or part provided then spell casted with triggered flag.'),
('cast back',3,'Syntax: .cast back #spellid [triggered]\r\n  Selected target will cast #spellid to your character. If \'triggered\' or part provided then spell casted with triggered flag.'),
('cast self',3,'Syntax: .cast self #spellid [triggered]\r\nCast #spellid by target at target itself. If \'triggered\' or part provided then spell casted with triggered flag.'),
('cast target',3,'Syntax: .cast target #spellid [triggered]\r\n  Selected target will cast #spellid to his victim. If \'triggered\' or part provided then spell casted with triggered flag.');


DELETE IGNORE FROM `command` WHERE `name` = 'cast dist';
INSERT IGNORE INTO `command` (`name`,`security`,`help`) VALUES
('cast dist',3,'Syntax: .cast dist #spellid [#dist [triggered]]\r\n  You will cast spell to pint at distance #dist. If \'triggered\' or part provided then spell casted with triggered flag. Not all spells can be casted as area spells.');




-- Chat spy
DELETE FROM `mangos_string` WHERE `entry` IN (11600, 11601, 11602, 11603, 11604, 11605, 11606, 11607, 11608);
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES
(11600, 'ChatSpy appended to player |cffff0000%s|r(%u)', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'ChatSpy ??????????? ? ?????? |cffff0000%s|r(%u)'),
(11601, 'ChatSpy for player |cffff0000%s|r(%u) cancelled by massive ChatSpy cancel.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'ChatSpy ??? ?????? |cffff0000%s|r(%u) ??????? ???????? ??????? ??????? ChatSpy.'),
(11602, 'All ChatSpys reset.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'ChatSpy ??? ???? ??????? ???????.'),
(11603, 'Player %s(%u) has no ChatSpy.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '? ?????? %s(%u) ?? ?????????? ChatSpy.'),
(11604, 'You were ChatSpying player, cancelled.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'ChatSpying ???? ? ??????.'),
(11605, '%s(%u) was ChatSpying player, cancelled.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '%s(%u) ????????? ChatSpy ?? ??????, ????????.'),
(11606, 'List of ChatSpys appended', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '?????? ????????????? ChatSpy'),
(11607, 'Total: %u', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '?????: %u'),
(11608, '%s(%u) spys |cffff0000%s|r(%u)', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '%s(%u) ?????? ?? |cffff0000%s|r(%u)');

DELETE FROM `command` WHERE `name` IN ('chatspy set', 'chatspy reset', 'chatspy status', 'chatspy cancel');
INSERT INTO `command` VALUES
('chatspy set',    3, 'Syntax: .chatspy set $PlayerName\r\n  Append ChatSpy on $player.'),
('chatspy reset',  3, 'Syntax: .chatspy reset\r\n  Reset all ChatSpys.'),
('chatspy status', 3, 'Syntax: .chatspy status $PlayerName\r\n  Show ChatSpy status for $player.'),
('chatspy cancel', 3, 'Syntax: .chatspy cancel $PlayerName\r\n  Reset ChatSpy for $player.');

-- chat disbale by level
DELETE FROM mangos_string WHERE `entry` IN (50000,50001,50002,50003,50004,50005,50006,50007);
INSERT INTO mangos_string
   (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`)
VALUES
   (50000, 'You cannot say until you are level %u.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

INSERT INTO mangos_string
   (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`)
VALUES
   (50001, 'You cannot yell until you are level %u.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

INSERT INTO mangos_string
   (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`)
VALUES
   (50002, 'You cannot whisper until you are level %u.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

INSERT INTO mangos_string
   (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`)
VALUES
   (50003, 'You cannot party chat until you are level %u.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

INSERT INTO mangos_string
   (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`)
VALUES
   (50004, 'You cannot guild chat until you are level %u.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

INSERT INTO mangos_string
   (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`)
VALUES
   (50005, 'You cannot raid chat until you are level %u.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

INSERT INTO mangos_string
   (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`)
VALUES
   (50006, 'You cannot battleground chat until you are level %u.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

INSERT INTO mangos_string
   (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`)
VALUES
   (50007, 'You cannot chat in channel until you are level %u.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);


-- Pvp Token 
INSERT INTO `mangos_string` VALUES ('11050', 'You have been awarded a token for slaying another player.', null, null, null, null, null, null, null, null); 

-- Anticheat

DELETE FROM `mangos_string` WHERE `entry`='11000';
INSERT INTO `mangos_string`
    (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`)
VALUES
    (11000, '|cffff0000[Anticheat]: Cheater detected. Nickname: %s. Cheat type: %s.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '|cffff0000[???????]: ????? ?????????. ???: %s. ??? ????: %s.|r');


-- Arena Announcer

DELETE FROM `mangos_string` WHERE `entry`='17898';
INSERT INTO `mangos_string`
    (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`)
VALUES
    (17898, '|cffff0000[Arena Queue Announcer]:|r %ux%u %s started!|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '|cffff0000[????? ?????]:|r %ux%u %s ??????????!|r');


-- Autobroadcast
-- Commit 991d1b3b6f4ab7bb129d

DELETE FROM `mangos_string` WHERE `entry`='1300';
INSERT INTO `mangos_string`
    (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`)
VALUES
    (1300, '|cffffcc00[Server]: |cff00ff00%s|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);


-- Pandora Trader

  -- Vendor
DELETE FROM `creature_template` WHERE `entry`='99321';
INSERT INTO `creature_template`
    (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `unk16`, `unk17`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`)
VALUES
    (99321, 0, 0, 0, 0, 0, 25811, 0, 25811, 0, 'Pandora receller', 'Moneychanger', '', 0, 80, 80, 22000, 22000, 0, 0, 9730, 2007, 2007, 128, 1, 1.14286, 1, 0, 420, 630, 0, 158, 1, 2000, 2000, 1, 33282, 0, 0, 0, 0, 0, 0, 336, 504, 126, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, '');

DELETE FROM `locales_creature` WHERE `entry`='99321';
INSERT INTO `locales_creature`
    (`entry`, `name_loc1`, `name_loc2`, `name_loc3`, `name_loc4`, `name_loc5`, `name_loc6`, `name_loc7`, `name_loc8`, `subname_loc1`, `subname_loc2`, `subname_loc3`, `subname_loc4`, `subname_loc5`, `subname_loc6`, `subname_loc7`, `subname_loc8`)
VALUES
    (99321, 'Pandora reseller', '', '', '', '', '', '', '?????????? ???????', 'Moneychanger', NULL, NULL, NULL, NULL, NULL, NULL, '??????');

DELETE FROM `creature` WHERE `guid`='99321';
INSERT INTO `creature`
    (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`,      `DeathState`, `MovementType`)
VALUES
    (99321, 99321, 571, 1, 1, 25811, 0, 5809.08, 623.377, 647.744, 2.0217, 600, 0, 0, 22000, 0, 0, 0);

  -- Items
DELETE FROM `npc_vendor` WHERE `entry`='99321';
INSERT INTO `npc_vendor`
    (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`)
VALUES
    (99321, 41596, 0, 0 ,2707),
    (99321, 47241, 0, 0 ,1909),
    (99321, 44990, 0, 0 ,2707),
    (99321, 43228, 0, 0 ,2707),
    (99321, 47241, 0, 0 ,2589),
    (99321, 47241, 0, 0 ,2637),
    (99321, 47241, 0, 0 ,2743),
    (99321, 49426, 0, 0 ,2723),
    (99321, 43589, 0, 0 ,2707),
    (99321, 49908, 0, 0 ,2723);
    -- (99321, ??, 0, 0 ,2707), //1 Emblem of Triumph
    -- (99321, ??, 0, 0 ,2723); //15 Emblem of Triumph

-- Creature template
-- Commit 91fff03866982767a654

UPDATE `creature_template` SET `spell1`='55328' WHERE `entry`='3579';
UPDATE `creature_template` SET `spell1`='55329' WHERE `entry`='3911';
UPDATE `creature_template` SET `spell1`='55330' WHERE `entry`='3912';
UPDATE `creature_template` SET `spell1`='55332' WHERE `entry`='3913';
UPDATE `creature_template` SET `spell1`='55333' WHERE `entry`='7398';
UPDATE `creature_template` SET `spell1`='55335' WHERE `entry`='7399';
UPDATE `creature_template` SET `spell1`='55278' WHERE `entry`='15478';
UPDATE `creature_template` SET `spell1`='58589' WHERE `entry`='31120';
UPDATE `creature_template` SET `spell1`='58590' WHERE `entry`='31121';
UPDATE `creature_template` SET `spell1`='58591' WHERE `entry`='31122';

DELETE FROM mangos_string WHERE entry BETWEEN 17890 AND 17896;

INSERT INTO mangos_string (entry, content_default, content_loc8) VALUES
(17890, 'Gamemaster %s banned account %s for %s. Reason: %s', '?????????? %s ??????? ??????? %s ?? %s. ???????: %s'),
(17891, 'Gamemaster %s banned account %s permanently. Reason: %s', '?????????? %s ??????? ??????? %s ???????????. ???????: %s'),
(17892, 'Gamemaster %s banned character %s for %s. Reason: %s', '?????????? %s ??????? ????????? %s ?? %s. ???????: %s'),
(17893, 'Gamemaster %s banned character %s permanently. Reason: %s', '?????????? %s ??????? ????????? %s ???????????. ???????: %s'),
(17894, 'Gamemaster %s banned IP address %s for %s. Reason: %s', '?????????? %s ??????? IP ????? %s ?? %s. ???????: %s'),
(17895, 'Gamemaster %s banned IP address %s permanently. Reason: %s', '?????????? %s ??????? IP ????? %s ???????????. ???????: %s'),
(17896, 'Gamemaster %s disabled %s\'s chat for %u minutes.', '?????????? %s ???????????? ??? %s ?? %u ?????.');

DELETE FROM mangos_string WHERE entry IN (548, 549);

INSERT INTO mangos_string (entry, content_default, content_loc1, content_loc2, content_loc3, content_loc4, content_loc5, content_loc6, content_loc7, content_loc8) VALUES
(548, 'Player%s %s (guid: %u) Account: %s (id: %u) E-mail: %s GMLevel: %u Last IP: %s Last login: %s Latency: %ums', NULL, NULL, NULL, NULL, NULL, NULL, NULL,'?????%s %s (GUID: %u) ???????: %s (id: %u) ?-????: %s ??????? ???????: %u ????????? IP: %s ????????? ????: %s ????????: %ums'),
(549, 'Race: %s Class: %s Played time: %s Level: %u Money: %ug%us%uc', NULL, NULL, NULL, NULL, NULL, NULL, NULL,'????: %s ?????: %s ????????? ?????: %s ???????: %u ?????????? ?????: %ug%us');

-- NPC on transport

DROP TABLE IF EXISTS `creature_transport`;
CREATE TABLE `creature_transport` (
   `guid` int(10) unsigned NOT NULL auto_increment,
   `npc_entry` mediumint(8) unsigned NOT NULL default 0,
   `transport_entry` mediumint(8) unsigned NOT NULL default 0,
   `TransOffsetX` float NOT NULL DEFAULT '0',
   `TransOffsetY` float NOT NULL DEFAULT '0',
   `TransOffsetZ` float NOT NULL DEFAULT '0',
   `TransOffsetO` float NOT NULL DEFAULT '0',
   `emote` mediumint(8) unsigned NOT NULL default 0,
   PRIMARY KEY (`guid`, `transport_entry`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='NPC on Transports';

INSERT INTO `creature_transport`
   (`npc_entry`, `transport_entry`, `TransOffsetX`, `TransOffsetY`, `TransOffsetZ`, `TransOffsetO`, `emote`)
VALUES
   (25075, 164871, 4.22547, -13.2054, -23.6771, 1.54314, 0),
   (25012, 176310, 18.1475, -7.41572, 6.09809, 1.88535, 0),
   (30753, 192241, -26.8391, -10.402, 35.5991, 1.29366, 432),
   (29795, 192241, 45.6197, 7.29317, 30.0955, 4.67642, 0),
   (30754, 192241, -54.639, -15.3254, 34.3972, 3.83128, 0),
   (25013, 176310, 0.194107, 9.84585, 6.09941, 3.08731, 0),
   (31790, 190536, 34.0851, 0.015993, 19.7141, 3.03935, 0),
   (30752, 192241, 7.30473, 24.2619, 34.9491, 4.43536, 0),
   (25010, 176310, 13.2057, -2.817, 6.09989, 3.88733, 0),
   (30755, 192241, 7.49121, 6.05275, 34.4239, 3.16615, 0),
   (25009, 176310, 25.2165, 6.9111, 16.1459, 3.94958, 0),
   (25015, 176310, 34.0669, 0.119702, 18.287, 3.17832, 0),
   (31792, 190536, -4.5113, -0.220224, 9.36188, 1.57535, 432),
   (31791, 190536, -11.4596, -8.43786, 9.52534, 4.77978, 432),
   (25014, 176310, -0.532552, -8.68575, 6.09815, 3.19019, 0),
   (25017, 176310, 6.22581, 9.13103, 11.4836, 1.53614, 0),
   (30755, 192241, 37.6428, -9.00797, 30.0954, 0.004917, 0),
   (30754, 192241, -18.9215, -26.8371, 89.9664, 0.087792, 0),
   (30866, 192241, -36.528, 23.9373, 33.9184, 1.89617, 0),
   (30755, 192241, -3.46042, 28.0231, 34.2784, 4.66548, 0),
   (31793, 190536, 16.8969, -3.34782, 9.82203, 5.62173, 432),
   (30754, 192241, -54.7182, 15.5861, 34.3897, 2.50086, 0),
   (31789, 190536, 28.0019, 6.04888, 19.2448, 3.26161, 0),
   (30866, 192241, -36.1494, -23.2606, 33.9568, 4.2232, 0),
   (30753, 192241, -26.9812, 10.5208, 35.5936, 4.74156, 432),
   (25016, 176310, -11.1276, 6.60326, 6.09852, 3.05167, 432),
   (30866, 192241, 15.9225, 26.2539, 35.4586, 1.60085, 0),
   (25018, 176310, 10.2474, 2.78122, 11.803, 3.46823, 432),
   (30755, 192241, 7.21494, -6.31021, 34.4191, 3.11118, 0),
   (32301, 192241, -3.37706, 0.007499, 34.0151, 4.65055, 0),
   (30752, 192241, 8.25547, -21.6199, 34.8875, 1.73515, 0),
   (30755, 192241, -5.59682, -28.2501, 34.1226, 1.55058, 0),
   (30866, 192241, 17.7216, -26.2695, 35.5686, 5.06367, 0),
   (30755, 192241, 37.6401, 8.9586, 30.0954, 0.012771, 0),
   (30755, 192241, 37.6428, -9.00797, 30.0954, 0.004917, 0),
   (30753, 192241, -7.63407, 0.007234, 86.0904, 6.2728, 0),
   (30827, 192241, 45.884, -8.99976, 30.0955, 1.52942, 0),
   (25011, 176310, 19.2178, -8.20848, 12.1102, 4.81518, 0),
   (30753, 192241, -34.939, -11.6484, 11.4697, 5.50858, 432),
   (30753, 192241, -34.785, 11.9312, 11.4869, 0.836243, 432),
   (30755, 192241, -26.188, -6.1712, 9.33333, 3.14217, 0),
   (30755, 192241, -26.1511, 6.90449, 9.405, 3.12647, 0),
   (30825, 192241, 38.4745, 0.038424, 10.1868, 3.15788, 0),
   (30753, 192241, 46.382, 7.89944, 10.4129, 3.96271, 0),
   (30753, 192241, 45.981, -6.55312, 10.3636, 2.23091, 0),
   (30755, 192241, 24.5852, 6.86575, 7.06382, 3.11055, 0),
   (30755, 192241, 24.3302, -6.97827, 7.08356, 3.34184, 0),
   (31243, 192241, 15.2483, -33.3678, 10.5837, 4.72649, 0),
   (31243, 192241, 1.91814, -32.9286, 10.0097, 4.6891, 0),
   (31243, 192241, -11.0915, -32.8872, 10.5819, 4.68507, 0),
   (31243, 192241, -11.2408, 33.2155, 10.5949, 1.58668, 0),
   (31243, 192241, 1.99373, 33.0756, 10.0105, 1.53853, 0),
   (31243, 192241, 15.239, 32.5832, 10.5826, 1.52441, 0),
   (30755, 192241, 8.85995, 18.8224, 8.7027, 4.69035, 0),
   (30755, 192241, -4.43012, 18.742, 8.62646, 4.66286, 0),
   (30755, 192241, -4.46811, -18.5567, 8.62604, 1.53698, 0),
   (30755, 192241, 9.06884, -18.7113, 8.70787, 1.56054, 0),
   (30753, 192241, 1.98831, -18.0873, 9.16057, 4.66993, 0),
   (30753, 192241, 2.15579, 17.0338, 9.16353, 1.54405, 0),
   (30752, 192241, 15.4321, 28.6642, 9.92277, 1.54012, 0),
   (30752, 192241, 2.01988, 28.7211, 9.33565, 1.58332, 0),
   (30752, 192241, -11.241, 28.5576, 9.91826, 1.5519, 0),
   (30826, 192241, 55.0542, -3.74557, 30.0955, 2.77577, 0),
   (30755, 192241, 29.8693, -29.5825, 89.7663, 3.05267, 0),
   (30824, 192241, 55.5028, 0.080449, 30.5268, 3.15669, 0),
   (30352, 192242, 48.8813, 8.78624, 40.0817, 3.1426, 433),
   (30352, 192242, 48.8649, -8.72834, 40.0818, 3.12642, 433),
   (30352, 192242, -17.337, 3.98796, 20.7652, 3.1541, 433),
   (30351, 192242, 39.976, 44.3876, 25.0331, 3.16019, 0),
   (30867, 192242, 36.8757, 45.226, 25.0331, 2.16509, 0),
   (30352, 192242, -17.2379, -3.94242, 20.7667, 3.1541, 433),
   (30867, 192242, 36.9277, -44.9241, 25.0318, 4.11052, 0),
   (32566, 192242, 34.6465, -41.7087, 25.0325, 3.20731, 0),
   (29799, 192242, 34.5332, -38.5618, 25.0323, 3.15234, 0),
   (30351, 192242, 2.42088, -23.0053, 22.5625, 0.046087, 432),
   (30867, 192242, -11.0475, -22.7053, 22.5096, 4.51265, 0),
   (30867, 192242, -32.9158, -22.1469, 22.5861, 4.59982, 0),
   (30394, 192242, -57.9337, 6.01148, 23.5029, 1.54855, 432),
   (30351, 192242, -36.4471, 6.81573, 20.4485, 4.73177, 432),
   (30351, 192242, -36.1811, -6.90251, 20.4501, 1.6483, 432),
   (30352, 192242, -49.1048, 0.044213, 20.6694, 0.029782, 433),
   (30351, 192242, 1.44228, 9.63379, 20.4566, 3.15096, 432),
   (30351, 192242, 1.29162, -9.37181, 20.458, 3.17295, 432),
   (30833, 192242, 6.18656, -0.008156, 20.5756, 6.28313, 0),
   (30352, 192242, 16.5684, 2.46962, 20.4252, 3.1329, 44),
   (30350, 192242, 16.4056, -2.2827, 20.4235, 3.11453, 0),
   (30392, 192242, 28.7566, 7.6217, 23.2872, 6.08285, 0),
   (30347, 192242, 28.6378, -7.55243, 23.2873, 0.157027, 0),
   (30344, 192242, 43.6738, 0.121325, 25.1341, 3.10227, 0),
   (32777, 192242, 42.9517, 4.20903, 25.1088, 3.47298, 0),
   (31259, 192242, 16.8761, -17.8635, 20.4597, 2.02864, 0),
   (30351, 192242, 0.773476, 22.5004, 22.5503, 3.2248, 432),
   (30867, 192242, -10.0824, 23.2226, 22.5129, 1.54405, 0),
   (30867, 192242, -33.4747, 22.2096, 22.5895, 1.56211, 0),
   (30346, 192242, 25.0778, -0.047958, 9.59893, 3.13291, 0),
   (30352, 192242, 36.4909, 6.11523, 9.60666, 3.01117, 433),
   (30352, 192242, 36.436, -6.06257, 9.60687, 3.09364, 433),
   (30380, 192242, 3.92454, 20.827, 9.67354, 1.30372, 0),
   (30380, 192242, -6.13984, 21.6533, 9.991, 1.48436, 0),
   (30380, 192242, -17.4619, 22.2092, 9.60018, 1.58254, 0),
   (30380, 192242, -30.2521, 21.9534, 9.5974, 1.54169, 0),
   (30380, 192242, -37.3836, 19.9617, 9.59771, 1.87549, 0),
   (30380, 192242, -37.1975, -20.2765, 9.65711, 4.32467, 0),
   (30380, 192242, -30.1731, -21.9358, 9.59686, 4.72914, 0),
   (30380, 192242, -18.0212, -22.0926, 9.60068, 4.66788, 0),
   (30380, 192242, -6.33308, -21.7722, 9.99575, 4.85167, 0),
   (30380, 192242, 3.99105, -21.2539, 9.67311, 4.9577, 0),
   (30394, 192242, -11.7295, -24.7904, 9.58663, 1.63703, 0),
   (30394, 192242, -11.9688, 25.5424, 9.58513, 4.66945, 0),
   (30352, 192242, -67.4841, 3.50927, 9.60209, 5.83577, 433),
   (30352, 192242, -67.1723, -3.73439, 9.60211, 0.318344, 433),
   (30394, 192242, -48.1449, -3.10366, -5.21617, 3.11436, 0),
   (30345, 192242, -48.0654, -0.185737, -4.98898, 3.11436, 0),
   (30352, 192242, -60.5592, 0.055898, -5.27774, 0.004184, 433),
   (30394, 192242, -14.1505, 23.0373, -5.24869, 0.027745, 0),
   (30380, 192242, -8.79147, 30.0334, -0.157799, 0.471494, 0),
   (30380, 192242, 1.92073, 28.7498, 0.101361, 0.232732, 0),
   (30394, 192242, -14.3898, -23.2398, -5.25039, 6.16013, 0),
   (30380, 192242, -7.54172, -30.0747, 0.101348, 4.17752, 0),
   (30380, 192242, 3.45962, -28.1289, 0.101388, 4.29376, 0),
   (30380, 192242, -24.7068, -29.9771, 0.101334, 3.66623, 0),
   (30380, 192242, -39.6946, -26.8419, 0.82802, 2.93659, 0),
   (30380, 192242, -41.0289, 25.7685, 1.20385, 1.49696, 0),
   (30380, 192242, -26.5726, 29.6008, -0.15773, 0.856857, 0),
   (30352, 192242, 43.7981, 13.0009, -2.07474, 4.61776, 433),
   (30753, 192241, 15.254, -0.009458, 86.0904, 3.14299, 0),
   (32302, 192242, 54.6648, -6.9431, 40.0874, 3.0302, 0),
   (32193, 192242, -21.6978, 0.127903, -18.1897, 3.12341, 0),
   (24935, 175080, 9.42351, -11.8801, -23.5908, 3.08558, 0),
   (24934, 175080, 9.56883, -3.62246, -23.5893, 3.07458, 0),
   (24924, 175080, -1.61694, -10.1641, -23.7649, 0.008681, 0),
   (24926, 175080, -5.41824, -2.06021, -17.7263, 1.97218, 0),
   (25080, 175080, -4.65078, -4.74596, -17.7144, 1.65016, 0),
   (25081, 175080, -5.03417, -10.8253, -17.689, 4.69751, 0),
   (24931, 175080, 7.15704, -3.89011, -17.7735, 5.15776, 432),
   (25083, 164871, -5.86083, -5.09646, -17.6306, 1.1754, 0),
   (25071, 164871, 6.71222, -4.1415, -17.794, 4.99008, 432),
   (25074, 164871, 4.49415, -7.97789, -17.8975, 0.065626, 432),
   (25072, 164871, 7.03763, -11.1073, -17.7946, 1.2987, 432),
   (25079, 164871, -5.00414, -10.5989, -17.6843, 4.66884, 0),
   (25070, 164871, -9.52824, -7.63628, -17.2095, 3.16716, 0),
   (25076, 164871, -1.27746, -7.88328, -23.7608, 3.14124, 432),
   (24934, 164871, -4.77478, -12.8175, -22.6773, 4.60522, 0),
   (24935, 164871, -6.29228, -12.7502, -22.6769, 4.66805, 0),
   (3084, 190549, -4.75387, -10.8675, -17.7074, 4.59518, 0),
   (3084, 190549, -5.13627, -4.61703, -17.6884, 1.65007, 0),
   (34715, 190549, -9.9527, -7.70295, -17.0973, 3.12662, 0),
   (34723, 190549, -17.7755, -5.62641, -14.9376, 3.69996, 0),
   (34717, 190549, -13.0353, -12.0914, -16.2584, 4.22853, 0),
   (34719, 190549, 7.35889, -11.108, -17.7826, 1.57997, 28),
   (34721, 190549, -0.488628, -5.93246, -23.7484, 3.81128, 0),
   (34730, 190549, -0.979586, -7.9528, -23.7559, 3.0456, 0),
   (24934, 190549, 9.49791, -3.56853, -23.5906, 6.28222, 0),
   (24935, 190549, 9.32634, -12.0478, -23.5942, 6.24295, 0),
   (34718, 190549, 13.5225, -5.26085, -24.1585, 0.03595, 207),
   (31725, 186238, 11.1323, -7.8428, -16.6839, 3.15041, 0),
   (31724, 186238, 5.72734, -3.28376, -17.8139, 1.55213, 0),
   (31727, 186238, -4.01569, -2.02455, -17.6298, 1.16964, 0),
   (31726, 186238, -3.59444, -13.8231, -17.678, 5.47991, 0),
   (31723, 186238, -11.0334, -12.5191, -16.8298, 4.64346, 0),
   (31720, 186238, -15.8872, -5.06557, -16.1287, 2.13411, 0),
   (25105, 176495, -9.54405, -7.94072, -17.2053, 3.17242, 0),
   (25106, 176495, -4.93938, -10.9634, -17.6988, 4.76285, 0),
   (25107, 176495, -4.98215, -4.67863, -17.696, 1.59455, 0),
   (25101, 176495, 7.56919, -4.02088, -17.7543, 4.77071, 0),
   (25103, 176495, 7.59398, -11.5166, -17.7745, 1.62204, 0),
   (25102, 176495, -11.0882, -3.47446, -16.7988, 2.00924, 0),
   (25075, 186238, 9.86442, -7.77519, -16.6839, 0.043302, 0),
   (25104, 176495, -0.898213, -7.76559, -23.7548, 3.11116, 0),
   (25100, 176495, -0.411733, -5.7239, -23.7457, 3.70414, 0),
   (24934, 176495, 9.63549, -3.67192, -23.588, 6.25904, 0),
   (24935, 176495, 9.79838, -11.8681, -23.5848, 6.25118, 0),
   (31706, 181689, -16.8964, -10.8497, -15.9745, 1.45699, 0),
   (31708, 181689, -2.74581, -1.47146, -17.7765, 4.67712, 0),
   (31708, 181689, -3.54276, -13.8752, -17.684, 1.53946, 0),
   (31705, 181689, 5.07824, -13.1188, -17.8135, 5.24182, 0),
   (31716, 181689, 11.5731, -7.65137, -16.6839, 3.20372, 0),
   (31704, 181689, 5.21605, -2.36685, -17.8223, 1.04622, 0),
   (31788, 190536, 26.1618, -2.95068, 19.2448, 2.72126, 0),
   (24996, 176244, -0.258897, -7.62734, 4.80823, 5.66423, 0),
   (24997, 176244, -0.416482, 4.39825, 4.79739, 5.10346, 0),
   (24993, 176244, 13.1874, 7.71381, 6.07001, 3.09834, 0),
   (24995, 176244, 13.3456, -7.63689, 6.09325, 3.06064, 0),
   (25007, 176244, 21.2462, 1.87803, 11.7334, 3.19572, 0),
   (24456, 176244, 29.5627, 0.150031, 16.6147, 3.18002, 0),
   (25052, 181646, 13.5093, 7.8287, 6.11039, 3.12838, 0),
   (25051, 181646, 13.4899, -7.71638, 6.11067, 3.11424, 0),
   (25056, 181646, 20.3045, 1.2971, 11.7088, 3.06319, 0),
   (25050, 181646, 29.8662, -0.374622, 16.6206, 3.09382, 0),
   (25054, 181646, -21.8863, -2.61623, 4.33103, 6.14509, 0),
   (25055, 181646, -21.4646, 2.87105, 4.31055, 6.26055, 0),
   (25097, 20808, -11.4014, 6.67999, 6.09785, 2.93715, 0),
   (25082, 20808, 15.6121, 1.09944, 6.09764, 2.52482, 0),
   (25089, 20808, 17.8437, -7.84575, 6.09877, 1.64493, 0),
   (25078, 20808, 34.095, 3.54049, 17.8892, 5.50987, 0),
   (25094, 20808, 34.0585, -0.04162, 18.2865, 3.17017, 0),
   (25095, 20808, 9.39981, 9.17899, 11.5941, 1.52083, 432),
   (25093, 20808, 15.8067, -5.80051, 11.9732, 1.86484, 0),
   (25111, 20808, 6.20811, 0.005208, 14.0554, 2.54813, 0),
   (30755, 192241, 8.83021, -4.6978, 84.7137, 2.34582, 0),
   (30755, 192241, 8.67689, 4.88796, 84.7137, 3.90012, 0),
   (30755, 192241, 29.4588, 29.8761, 89.7684, 3.15321, 0),
   (30754, 192241, -19.0109, 27.0177, 89.9667, 6.22411, 0),
   (25075, 164871, 10.6353, -12.1104, -23.5736, 3.01351, 0),
   (25075, 164871, 10.6391, -3.68298, -23.5737, 3.14703, 0),
   (25075, 164871, 4.53411, -2.57645, -23.6704, 4.7411, 0),
   (25075, 164871, -2.82445, -6.38118, -23.7807, 4.71631, 432),
   (25075, 164871, -3.59545, -7.90852, -23.7812, 6.26982, 0),
   (25075, 164871, -2.95326, -9.17582, -23.7804, 1.60848, 0),
   (25075, 175080, -3.59016, -7.79262, -23.7806, 6.27391, 0),
   (25075, 176495, -3.59133, -7.84061, -23.7802, 6.1969, 0),
   (25075, 190549, -3.59986, -8.08202, -23.7802, 0.039869, 0),
   (34935, 195276, -21.401, -31.343, 34.173, 4.62057, 0),
   (34935, 195276, -12.1064, -31.9697, 34.3807, 4.62057, 0),
   (34935, 195276, -2.4877, -31.9885, 34.8384, 4.62057, 0),
   (34935, 195276, 10.2664, -32.0713, 35.7357, 4.62057, 0),
   (34935, 195276, 19.4636, -30.794, 36.2254, 4.83106, 0),
   (34929, 195121, -41.7122, 23.1838, 22.5605, 1.60659, 0),
   (34929, 195121, -31.0354, 25.1286, 21.6921, 1.60659, 0),
   (34929, 195121, -21.4492, 25.8326, 21.6309, 1.60659, 0),
   (34929, 195121, -12.4734, 26.321, 21.6237, 1.60659, 0),
   (34929, 195121, -2.81125, 26.2077, 21.6566, 1.60659, 0),
   (24910, 187038, 34.6962, -0.27625, 20.9157, 3.44936, 0),
   (25026, 187038, 15.3122, 6.40496, 1.39596, 4.24673, 0),
   (25026, 187038, 14.4097, -6.40611, 1.39596, 1.86383, 0),
   (25026, 187038, 5.51407, -5.26758, 1.39596, 4.38889, 0),
   (25026, 187038, 5.50506, 5.17797, 1.39596, 1.53711, 0),
   (25026, 187038, -3.34169, -4.92735, 1.39595, 4.70933, 0),
   (25026, 187038, -2.64281, 5.46732, 1.39595, 0.520802, 0),
   (25026, 187038, 6.52141, 0.490373, 1.39693, 6.00288, 0),
   (25026, 187038, 23.0708, -2.7187, 1.39595, 5.37378, 0),
   (25026, 187038, 24.9381, 4.10155, 1.44058, 1.07922, 0),
   (24911, 187038, -1.47544, 9.97225, 8.72811, 1.47291, 0),
   (24911, 187038, 0.568386, 10.818, 8.68709, 1.24593, 0),
   (24911, 187038, -3.08712, 11.1947, 8.6042, 1.59543, 0),
   (24911, 187038, -3.00336, -1.39497, 8.72655, 0.455023, 0),
   (24911, 187038, -11.92, 6.82298, 8.72743, 2.64628, 0),
   (24911, 187038, 5.55254, 10.6903, 14.0795, 1.41713, 0),
   (24911, 187038, 19.1591, 9.74589, 14.7625, 1.55457, 0),
   (24911, 187038, -10.8992, 6.36276, 20.589, 1.29146, 0),
   (24911, 187038, -15.0531, 6.78103, 21.0344, 1.54279, 0),
   (24911, 187038, -16.544, 7.01147, 21.3668, 1.52708, 0),
   (24992, 187038, -13.669, 5.23144, 19.2894, 1.4721, 0),
   (24911, 187038, 29.079, 6.02911, 19.504, 1.29931, 0),
   (24911, 187038, 19.1465, -9.70741, 14.7601, 4.79434, 0),
   (24911, 187038, 5.53691, -10.9158, 14.0808, 4.59956, 0),
   (31261, 192242, -46.1663, 12.044, 13.2206, 1.43738, 0);

-- Lightwell Support
-- Commit 97e7463c82ad95cdc63f

DELETE FROM `creature_template_addon` WHERE `entry` IN (31897, 31896, 31895, 31894, 31893, 31883);
INSERT INTO `creature_template_addon`
    (`entry`, `auras`)
VALUES 
    (31897,59907),
    (31896,59907),
    (31895,59907),
    (31894,59907),
    (31893,59907),
    (31883,59907);

UPDATE `creature_template` SET `unit_flags`='4', `flags_extra`='2' WHERE `entry` IN (31897, 31896, 31895, 31894, 31893, 31883);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (31897, 31896, 31895, 31894, 31893, 31883);
INSERT INTO `npc_spellclick_spells`
    (`npc_entry`, `spell_id`, `quest_start`, `cast_flags`)
VALUES 
    (31897,60123,0,2),
    (31896,60123,0,2),
    (31895,60123,0,2),
    (31894,60123,0,2),
    (31893,60123,0,2),
    (31883,60123,0,2);

-- mailbox option to pet's menu fix
DELETE FROM gossip_menu_option WHERE menu_id = 10318;
DELETE FROM gossip_menu_option WHERE menu_id = 33239;

INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, action_poi_id, action_script_id, box_coded, box_money, box_text, cond_1, cond_1_val_1, cond_1_val_2, cond_2, cond_2_val_1, cond_2_val_2, cond_3, cond_3_val_1, cond_3_val_2) VALUES
	(10318,4,'0','Exodar Champion''s Pennant',1,'1',-1,'0','50130',0,'0','',20,'2761','0',0,'0','0',0,'0','0');
INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, action_poi_id, action_script_id, box_coded, box_money, box_text, cond_1, cond_1_val_1, cond_1_val_2, cond_2, cond_2_val_1, cond_2_val_2, cond_3, cond_3_val_1, cond_3_val_2) VALUES
	(10318,3,'0','Darnassus Champion''s Pennant',1,'1',-1,'0','50131',0,'0','',20,'2760','0',0,'0','0',0,'0','0');
INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, action_poi_id, action_script_id, box_coded, box_money, box_text, cond_1, cond_1_val_1, cond_1_val_2, cond_2, cond_2_val_1, cond_2_val_2, cond_3, cond_3_val_1, cond_3_val_2) VALUES
	(10318,2,'0','Visit a mailbox.',1,'1',-1,'0','0',0,'0','',11,'67334','0',20,'2817','0',0,'0','0');
INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, action_poi_id, action_script_id, box_coded, box_money, box_text, cond_1, cond_1_val_1, cond_1_val_2, cond_2, cond_2_val_1, cond_2_val_2, cond_3, cond_3_val_1, cond_3_val_2) VALUES
	(10318,1,'1','Visit a trader.',3,'128',-1,'0','0',0,'0','',11,'67334','0',20,'2817','0',0,'0','0');
INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, action_poi_id, action_script_id, box_coded, box_money, box_text, cond_1, cond_1_val_1, cond_1_val_2, cond_2, cond_2_val_1, cond_2_val_2, cond_3, cond_3_val_1, cond_3_val_2) VALUES
	(10318,0,'6','Visit a bank.',9,'131072',-1,'0','0',0,'0','',11,'67334','0',20,'2817','0',0,'0','0');
INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, action_poi_id, action_script_id, box_coded, box_money, box_text, cond_1, cond_1_val_1, cond_1_val_2, cond_2, cond_2_val_1, cond_2_val_2, cond_3, cond_3_val_1, cond_3_val_2) VALUES
	(33239,0,'6','Visit a bank.',9,'131072',-1,'0','0',0,'0','',11,'67401','0',20,'2816','0',0,'0','0');
INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, action_poi_id, action_script_id, box_coded, box_money, box_text, cond_1, cond_1_val_1, cond_1_val_2, cond_2, cond_2_val_1, cond_2_val_2, cond_3, cond_3_val_1, cond_3_val_2) VALUES
	(33239,1,'1','Visit a trader.',3,'128',-1,'0','0',0,'0','',11,'67401','0',20,'2816','0',0,'0','0');
INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, action_poi_id, action_script_id, box_coded, box_money, box_text, cond_1, cond_1_val_1, cond_1_val_2, cond_2, cond_2_val_1, cond_2_val_2, cond_3, cond_3_val_1, cond_3_val_2) VALUES
	(33239,2,'0','Visit a mailbox.',1,'1',-1,'0','0',0,'0','',11,'67401','0',20,'2816','0',0,'0','0');
INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, action_poi_id, action_script_id, box_coded, box_money, box_text, cond_1, cond_1_val_1, cond_1_val_2, cond_2, cond_2_val_1, cond_2_val_2, cond_3, cond_3_val_1, cond_3_val_2) VALUES
	(33239,3,'0','Orgrimmar Champion''s Pennant',1,'1',-1,'0','50132',0,'0',NULL,20,'2765','0',0,'0','0',0,'0','0');
INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, action_poi_id, action_script_id, box_coded, box_money, box_text, cond_1, cond_1_val_1, cond_1_val_2, cond_2, cond_2_val_1, cond_2_val_2, cond_3, cond_3_val_1, cond_3_val_2) VALUES
	(33239,4,'0','Sen''jin Champion''s Pennant',1,'1',-1,'0','50133',0,'0',NULL,20,'2766','0',0,'0','0',0,'0','0');
INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, action_poi_id, action_script_id, box_coded, box_money, box_text, cond_1, cond_1_val_1, cond_1_val_2, cond_2, cond_2_val_1, cond_2_val_2, cond_3, cond_3_val_1, cond_3_val_2) VALUES
	(10318,5,'0','Gnomeregan Champion''s Pennant',1,'1',-1,'0','50129',0,'0','',20,'2762','0',0,'0','0',0,'0','0');
INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, action_poi_id, action_script_id, box_coded, box_money, box_text, cond_1, cond_1_val_1, cond_1_val_2, cond_2, cond_2_val_1, cond_2_val_2, cond_3, cond_3_val_1, cond_3_val_2) VALUES
	(10318,6,'0','Ironforge Champion''s Pennant',1,'1',-1,'0','50128',0,'0','',20,'2763','0',0,'0','0',0,'0','0');
INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, action_poi_id, action_script_id, box_coded, box_money, box_text, cond_1, cond_1_val_1, cond_1_val_2, cond_2, cond_2_val_1, cond_2_val_2, cond_3, cond_3_val_1, cond_3_val_2) VALUES
	(10318,7,'0','Stormwind Champion''s Pennant',1,'1',-1,'0','50127',0,'0','',20,'2764','0',0,'0','0',0,'0','0');
INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, action_poi_id, action_script_id, box_coded, box_money, box_text, cond_1, cond_1_val_1, cond_1_val_2, cond_2, cond_2_val_1, cond_2_val_2, cond_3, cond_3_val_1, cond_3_val_2) VALUES
	(33239,5,'0','Silvermoon Champion''s Pennant',1,'1',-1,'0','50134',0,'0',NULL,20,'2767','0',0,'0','0',0,'0','0');
INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, action_poi_id, action_script_id, box_coded, box_money, box_text, cond_1, cond_1_val_1, cond_1_val_2, cond_2, cond_2_val_1, cond_2_val_2, cond_3, cond_3_val_1, cond_3_val_2) VALUES
	(33239,6,'0','Thunder Bluff Champion''s Pennant',1,'1',-1,'0','50135',0,'0',NULL,20,'2768','0',0,'0','0',0,'0','0');
INSERT INTO gossip_menu_option (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, action_poi_id, action_script_id, box_coded, box_money, box_text, cond_1, cond_1_val_1, cond_1_val_2, cond_2, cond_2_val_1, cond_2_val_2, cond_3, cond_3_val_1, cond_3_val_2) VALUES
	(33239,7,'0','Undercity Champion''s Pennant',1,'1',-1,'0','50136',0,'0',NULL,20,'2769','0',0,'0','0',0,'0','0');
