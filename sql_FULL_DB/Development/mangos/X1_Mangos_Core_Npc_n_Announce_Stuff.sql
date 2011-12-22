
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
