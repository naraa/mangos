-- Spell bonus data
-- Lifebloom
UPDATE `spell_bonus_data` SET `direct_bonus`= 0.8 WHERE `entry`= 33763;

DELETE FROM `spell_bonus_data` WHERE entry IN (30451, 51963, 52042, 52752, 54158, 56161, 58621, 64844, 64085);
INSERT INTO `spell_bonus_data`
    (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`)
VALUES
    -- Gargoyle Strike
    (51963, 0, 0, 0.33, 0,'Gargoyle Strike'),
    -- Healing Stream Totem
    (52042, 0, 0, 0, 0,'Healing Stream Totem'),
    -- Ancestral Awakening
    (52752, 0, 0, 0, 0,'Ancestral Awakening'),
    -- Judgement
    (54158, 0, 0, 0, 0,'Judgement'),
    -- Glyph of  Prayer of Healing
    (56161, 0, 0, 0, 0,'Glyph of Prayer of Healing'),
    -- Glyph of Chains of Ice (it's correct, but bonus value is simple)
    (58621, 0, 0, 0.08, 0, 'Glyph of Chains of Ice'),
    -- Priest - Divine Hymn
    (64844, 0.564, 0, 0, 0, 'Priest - Divine Hymn'),
    -- Priest - Vampiric Touch Dispel
    (64085, 2.4, 0, 0, 0, 'Priest - Vampiric Touch Dispel');

-- SPELL_AURA_DAMAGE_SHIELD by Warlord
DELETE FROM `spell_bonus_data` WHERE `entry` IN (7294, 467, 2947);
INSERT INTO `spell_bonus_data`(`entry`,`direct_bonus`,`dot_bonus`,`ap_bonus`,`ap_dot_bonus`,`comments`) VALUES
    ( 467, 0.033, 0, 0, 0,'Druid - Thorns'),
    (7294, 0.033, 0, 0, 0,'Paladin - Retribution Aura'),
    (2947, 0.033, 0, 0, 0,'Warlock - Fire Shield (Imp)');

-- Item's
DELETE FROM `spell_bonus_data` WHERE `entry` IN (16614, 45055, 60488);
INSERT INTO `spell_bonus_data`(`entry`,`direct_bonus`,`dot_bonus`,`ap_bonus`,`ap_dot_bonus`,`comments`) VALUES
(16614, 0, 0, 0, 0, 'Item - Storm Gauntlets - Lightning Strike'),
(45055, 0, 0, 0, 0, 'Item - Timbal''s Focusing Crystal'),
(60488, 0, 0, 0, 0, 'Item - Extract of Necromatic Power');

-- pet attack's by say1981
DELETE FROM `spell_bonus_data` WHERE `entry` IN (17253,16827,49966);
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES
    (17253, 0, 0, 0.08, 0, 'Bite (Rank 1) - Hunter pet'),
    (16827, 0, 0, 0.08, 0, 'Claw (Rank 1) - Hunter pet'),
    (49966, 0, 0, 0.08, 0, 'Smack (Rank 1) - Hunter pet');

-- Culling the Herd
DELETE FROM spell_chain WHERE spell_id IN (61680, 61681, 52858);
INSERT INTO spell_chain VALUES
(61680, 0, 61680, 1, 0),
(61681, 61680, 61680, 2, 0),
(52858, 61681, 61680, 3, 0);

-- Improved Spirit Tap
DELETE FROM spell_chain WHERE spell_id IN (15337, 15338);
INSERT INTO spell_chain VALUES
(15337, 0, 15337, 1, 0),
(15338, 15337, 15337, 2, 0);

-- Shaman Overload

-- Lightning Bolt
DELETE FROM spell_chain WHERE first_spell = 45284;
INSERT INTO spell_chain (spell_id, prev_spell, first_spell, rank) VALUES
(45284,     0, 45284,  1),
(45286, 45284, 45284,  2),
(45287, 45286, 45284,  3),
(45288, 45287, 45284,  4),
(45289, 45288, 45284,  5),
(45290, 45289, 45284,  6),
(45291, 45290, 45284,  7),
(45292, 45291, 45284,  8),
(45293, 45292, 45284,  9),
(45294, 45293, 45284, 10),
(45295, 45294, 45284, 11),
(45296, 45295, 45284, 12),
(49239, 45296, 45284, 13),
(49240, 49239, 45284, 14);

DELETE FROM spell_bonus_data WHERE entry = 45284;
INSERT INTO spell_bonus_data (entry, direct_bonus, comments) VALUES
(45284, 0.3572, 'Shaman - Lightning Bolt Overload Proc');

-- Chain Lightning
DELETE FROM spell_chain WHERE first_spell = 45297;
INSERT INTO spell_chain (spell_id, prev_spell, first_spell, rank) VALUES
(45297,     0, 45297, 1),
(45298, 45297, 45297, 2),
(45299, 45298, 45297, 3),
(45300, 45299, 45297, 4),
(45301, 45300, 45297, 5),
(45302, 45301, 45297, 6),
(49268, 45302, 45297, 7),
(49269, 49268, 45297, 8);

DELETE FROM spell_bonus_data WHERE entry = 45297;
INSERT INTO spell_bonus_data (entry, direct_bonus, comments) VALUES
(45297, 0.2857, 'Shaman - Chain Lightning Overload Proc');

-- missing passive aura for spell 22570
-- Commit 1dd5a80d385e2b35671c

DELETE FROM `playercreateinfo_spell` WHERE `Spell`='44835';
INSERT INTO `playercreateinfo_spell`
    (`race`, `class`, `Spell`, `Note`)
VALUES
    (4, 11, 44835, 'Maim Interrupt'),
    (6, 11, 44835, 'Maim Interrupt');
