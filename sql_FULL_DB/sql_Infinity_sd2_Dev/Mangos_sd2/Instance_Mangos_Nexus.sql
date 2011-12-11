-- ----------------
-- Instance Nexus -
-- ----------------

UPDATE `creature_template` SET `ScriptName` = 'npc_crystal_spike' WHERE `entry` = '27099';
UPDATE `creature_template` SET `ScriptName` = 'npc_crystalline_tangler' WHERE `entry` = '32665';
UPDATE `creature_template` SET `ScriptName` = 'npc_chaotic_rift' WHERE `entry` = '26918';
UPDATE `creature_template` SET `ScriptName` = 'boss_commander_kolurg' WHERE `entry` = '26798';
UPDATE `creature_template` SET `ScriptName` = 'boss_commander_stoutbeard' WHERE `entry` = '26796';

-- set Breath Casters to flying (dummy NPCs near Keristrasza)
UPDATE creature_template SET InhabitType = 4 WHERE entry = 27048;


