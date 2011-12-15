UPDATE `creature_template` SET `ScriptName`='boss_king_magni_bronzebreard' WHERE `entry` = 2784;
UPDATE `creature_template` SET `ScriptName`='boss_high_tinker_mekkatorque' WHERE `entry` = 7937;
UPDATE `creature_template` SET `ScriptName`='boss_lorthemar_theron' WHERE `entry` = 16802;
UPDATE `creature_template` SET `ScriptName`='boss_king_varian_wrynn' WHERE `entry` = 29611;
UPDATE `creature_template` SET `ScriptName`='boss_lady_jaina_proudmoore' WHERE `entry` = 4968;
UPDATE `creature_template` SET `ScriptName`='boss_prophet_velen' WHERE `entry` = 17468;
UPDATE `creature_template` SET `ScriptName`='boss_voljin' WHERE `entry` = 10540;
UPDATE `creature_template` SET `ScriptName`='boss_tyrande_whisperwind' WHERE `entry` = 7999;
UPDATE `creature_template` SET `ScriptName`='boss_fandral_staghelm' WHERE `entry` = 3516;
UPDATE `creature_template` SET `ScriptName`='generic_creature' WHERE `entry` in (16801, 34986, 1748);
REPLACE INTO spell_target_position VALUES
(20682, 1, -3992.637, -4717.926, 11.006, 0.7);

UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` = 3122;
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` = 3127;

-- --------------------------
-- Guards around the worlds -
-- --------------------------

-- NEEDS MORE RESEARCH

-- Cenarion hold infantry
  -- adding attack spells to creature template
UPDATE `creature_template` SET `spell1` = 18328, `spell2` = 19643, `spell3` = 15618, `flags_extra` = 0 WHERE `entry` = 15184;

-- Bluff watcher ( thunderbluff )
  -- correcting guard spells
UPDATE `creature_template` SET `spell1` = 40505, `spell2` = 12024, `spell3` = 23337, `flags_extra` = 0 WHERE `entry` = 3084;

-- orc guards
UPDATE `creature_template` SET `spell1` = 8599, `spell2` = 40505, `flags_extra` = 0 WHERE `entry` = 3296;

-- Darn Guards
UPDATE `creature_template` SET `spell1` = 40505, `spell2` = 8599, `flags_extra` = 0 WHERE `entry` = 4262;

-- stormwind guards Guards
UPDATE `creature_template` SET `spell1` = 40505, `spell2` = 8599, `flags_extra` = 0 WHERE `entry` = 68;

-- Undercity Guards
UPDATE `creature_template` SET `spell1` = 59395, `spell2` = 7160, `flags_extra` = 0 WHERE `entry` = 5624;
