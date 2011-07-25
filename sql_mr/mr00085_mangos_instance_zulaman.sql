-- Instance Zul'Aman

-- -----------------------------------------------------------------

-- double check trash loot
-- double check eventAI , creature template info/data

-- --------------
-- nalorakk fixes
-- --------------
-- should fix tanzar display and he shouldnt be on fire 8P
UPDATE `creature_template` SET `modelid_2` = 21767 WHERE `entry` = 23790;
DELETE FROM `creature_template_addon` WHERE (`entry`=23790);

-- -----------------------------------------------------------------------

-- --------------
-- Akil'zon fixes
-- --------------

-- need to double check akil'zon loot table

-- harkor in his right spot
UPDATE `creature` SET `position_x` = 409.204010, `position_y` = 1417.109985, `position_z` = 74.305199, `orientation` = 3.526491 WHERE `guid` = 23999;

-- respawn and remove eagle in harkor cage
DELETE FROM `creature` WHERE `id`=24159;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(127140, 24159, 568, 1, 1, 0, 0, 396.217, 1453.29, 76.3272, 4.10901, 604800, 0, 0, 4890, 0, 0, 0),
(127141, 24159, 568, 1, 1, 0, 0, 326.908, 1435.63, 74.1542, 3.44625, 604800, 0, 0, 4890, 0, 0, 0),
(127142, 24159, 568, 1, 1, 0, 0, 420.42, 1376.62, 74.2976, 2.48716, 604800, 0, 0, 4890, 0, 0, 0),
(127143, 24159, 568, 1, 1, 0, 0, 358.853, 1365.97, 74.3047, 3.41719, 604800, 0, 0, 4890, 0, 0, 0);

-- -----------------------------------------------------------------------------------------------------------------

-- ----------------
-- Jan'a'lai Fixes
-- ----------------

-- need to double check loot

-- kraz in the right place
UPDATE `creature` SET `position_x` = -73.1978, `position_y` = 1163.92, `position_z` = 5.1926, `orientation` = 3.517833 WHERE `guid` = 24024;

-- ------------------------------------------------------------------------------------

-- -------
-- Halazzi
-- -------

-- double check all

-- -----------------------------------------------------------------------------

-- ------
-- Zu'Jin
-- ------

UPDATE `creature_template` SET `ScriptName` = 'mob_zuljin_vortex' WHERE `entry` = 24136;