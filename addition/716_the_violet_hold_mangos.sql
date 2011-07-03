/* VIOLET HOLD */
UPDATE `instance_template` SET `ScriptName`='instance_violet_hold' WHERE `map`=608;
UPDATE `creature_template` SET `ScriptName`='boss_erekem' WHERE entry=29315;
UPDATE `creature_template` SET `ScriptName`='mob_erekem_guard' WHERE entry=29395;
DELETE FROM `creature_ai_scripts` WHERE (`id`='2939503') OR (`id`='2939502') OR (`id`='2939501');
UPDATE `creature_template` SET `ScriptName`='boss_moragg' WHERE entry=29316;
UPDATE `creature_template` SET `ScriptName`='boss_ichoron' WHERE entry=29313;
UPDATE `creature_template` SET `ScriptName`='mob_ichor_globule' WHERE entry=29321;
UPDATE `creature_template` SET `ScriptName`='boss_xevozz' WHERE entry=29266;
UPDATE `creature_template` SET `ScriptName`='mob_ethereal_sphere' WHERE entry=29271;
UPDATE `creature_template` SET `ScriptName`='boss_lavanthor' WHERE entry=29312;
UPDATE `creature_template` SET `ScriptName`='boss_zuramat'WHERE entry=29314;
UPDATE `creature_template` SET `ScriptName`='mob_zuramat_sentry' WHERE entry=29364;
UPDATE `creature_template` SET `ScriptName`='boss_cyanigosa' WHERE entry=31134;
UPDATE `creature_template` SET `ScriptName`='npc_azure_saboteur' WHERE entry=31079;
UPDATE `creature_template` SET `ScriptName`='mob_vh_dragons', AIName='' WHERE entry IN (30666,30668,30667,32191,30660,30695,30663,30661,30664,30662);
DELETE FROM `creature_ai_scripts` WHERE (`id`='3066002') OR (`id`='3066001');
DELETE FROM `creature_ai_scripts` WHERE (`id`='3066401') OR (`id`='3066402') OR (`id`='3066314') OR (`id`='3066304') OR (`id`='3066309') OR (`id`='3066301') OR (`id`='3066307') OR (`id`='3066305') OR (`id`='3066311') OR (`id`='3066302') OR (`id`='3066313') OR (`id`='3066312') OR (`id`='3066308') OR (`id`='3066310') OR (`id`='3066306') OR (`id`='3066303') OR (`id`='3066203') OR (`id`='3066201') OR (`id`='3066202') OR (`id`='3066204') OR (`id`='3066104') OR (`id`='3066102') OR (`id`='3066101') OR (`id`='3066103');
DELETE FROM `creature_ai_scripts` WHERE (`id`='3066802') OR (`id`='3066803') OR (`id`='3066801') OR (`id`='3066711') OR (`id`='3066712') OR (`id`='3066706') OR (`id`='3066714') OR (`id`='3066704') OR (`id`='3066705') OR (`id`='3066708') OR (`id`='3066703') OR (`id`='3066709') OR (`id`='3066713') OR (`id`='3066701') OR (`id`='3066707') OR (`id`='3066702') OR (`id`='3066710') OR (`id`='3066602') OR (`id`='3066601') OR (`id`='3066603');
DELETE FROM `creature_ai_scripts` WHERE (`id`='3069508') OR (`id`='3069509') OR (`id`='3069501') OR (`id`='3069512') OR (`id`='3069514') OR (`id`='3069513') OR (`id`='3069510') OR (`id`='3069502') OR (`id`='3069511') OR (`id`='3069506') OR (`id`='3069505') OR (`id`='3069507') OR (`id`='3069504') OR (`id`='3069503');
DELETE FROM `creature_ai_scripts` WHERE (`id`='3107901');
DELETE FROM `creature_ai_scripts` WHERE (`id`='3219102') OR (`id`='3219103') OR (`id`='3219101') ;


UPDATE `creature_template` SET `ScriptName`='npc_sinclari', `npcflag`=1 WHERE entry=30658;
UPDATE `creature_template` SET `ScriptName`='npc_violet_portal' WHERE entry=31011;
UPDATE creature_template SET ScriptName='' WHERE entry IN (30679,32174); -- sd2 clean-up
UPDATE gameobject_template SET ScriptName='' WHERE entry=193611; -- sd2 clean-up
UPDATE `creature_template` SET `ScriptName`='npc_door_seal_vh' WHERE entry=30896;

-- Lieuntenant Sinclari (30658)
UPDATE `creature` SET `Spawntimesecs`=180 WHERE id=30658;


-- void sentry template (29364)

UPDATE `creature_template` SET faction_A=16, faction_H=16, minlevel=77, maxlevel=77, maxhealth=500, minhealth=500 WHERE entry=29364;
UPDATE `creature_template` SET `faction_A`=16,`faction_H`=16 WHERE `entry`=31518;
UPDATE `creature_template` SET `AIName`='' WHERE entry IN (31011,30695,31079,30666,30668,30667,32191,30660,30695,30663,30661,30664,30662,31118,29395,31513);

-- triggers
UPDATE `creature_template` SET flags_extra=flags_extra|128  WHERE entry IN (30857,30883,29326,30896);

DELETE FROM `creature` WHERE id=31011;

DELETE FROM `spell_script_target` WHERE `entry` =54160;
INSERT INTO `spell_script_target` VALUES (54160, 1, 29266);
DELETE FROM `spell_script_target` WHERE `entry`=59474;
INSERT INTO `spell_script_target` VALUES
(59474,1,29266),
(59474,1,31511);

-- immune masks (charm, fear, root, silence, sleep, snare, stun, freeze, knockout, polymorph, banish, shackle, horror, sapped)

UPDATE `creature_template` SET mechanic_immune_mask=mechanic_immune_mask|1|16|64|256|512|1024|2048|4096|8192|65536|131072|524288|8388608|536870912
WHERE `entry` IN (29315,29395,29316,29313,29321,29266,29271,29312,29314,31134,31511,31514,31509,31508,31512,31507,31510,31515,31513,31506);
