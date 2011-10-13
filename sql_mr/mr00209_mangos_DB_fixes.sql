-- from ytdb 608_288 to current 608_2311
UPDATE creature_template SET ScriptName='npc_keeper_remulos' WHERE entry=11832;
UPDATE creature_template SET ScriptName='boss_eranikus' WHERE entry=15491;
UPDATE gameobject_template SET ScriptName='' WHERE entry=101833;
UPDATE creature_template SET ScriptName='npc_ranshalla' WHERE entry=10300;
UPDATE gameobject_template SET ScriptName='go_elune_fire' WHERE entry IN (177417, 177404);

-- spot for official sd2 sql clean up
DELETE FROM scripted_event_id WHERE id = 9735;