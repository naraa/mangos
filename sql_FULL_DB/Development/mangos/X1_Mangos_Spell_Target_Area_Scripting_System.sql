-- Additions for spell_Area and Target_Postion

-- Spell Area Clean up
DELETE FROM `spell_area` WHERE `spell`='74411';
DELETE FROM `spell_area` WHERE `spell`='74410';

-- Frostmourne area spells
DELETE FROM spell_target_position WHERE id IN (70860, 72546, 73655);
INSERT INTO spell_target_position VALUES
    (70860, 631, 529.302, -2124.49, 1040.857, 3.1765),
    (72546, 631, 514.000, -2523.00, 1250.990, 3.1765),
    (73655, 631, 495.708, -2523.76, 1250.990, 3.1765);

DELETE FROM spell_area WHERE spell = 74276;
INSERT INTO spell_area (spell, area, autocast) VALUES (74276, 4910, 1);

-- Additions for spell_script_target
/* NOTICE: Targets, which need often a spell_script_target entry are:
    Target_Script - 38
    Target_AreaEffect_Instant
    maybe some more, but i think not
*/

-- Molten Fury - Sartharion encounter - target Lava Blazes only
DELETE FROM spell_script_target WHERE entry = 60430;
INSERT INTO spell_script_target VALUES
(60430, 1, 30643);

-- Berserk - Sartharion encounter - target dragon bosses only
DELETE FROM spell_script_target WHERE entry = 61632;
INSERT INTO spell_script_target VALUES
(61632, 1, 28860),
(61632, 1, 30452),
(61632, 1, 30451),
(61632, 1, 30449);

-- Devour humanoid ---- Quest and to all things (DK Area)
DELETE FROM spell_script_target WHERE entry = 53110;
INSERT INTO spell_script_target VALUES
(53110, 1, 29102),
(53110, 1, 29103);

DELETE FROM spell_script_target WHERE entry = 61920;
INSERT INTO spell_script_target VALUES 
(61920 ,1,32857),
(61920 ,1,32927),
(61920 ,1,32867);
