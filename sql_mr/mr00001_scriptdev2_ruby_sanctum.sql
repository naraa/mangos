-- sound / text
DELETE FROM `script_texts` WHERE `entry` BETWEEN -1724405 AND -1724000;

-- xerestrasza
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`) VALUES
('-1724000','Help! I am trapped within this tree! I require aid!','???????! ? ??? ???? ???????. ??? ????? ??????!','17490','6','0','0','SAY_XERESTRASZA_YELL_1'),
('-1724001','Thank you! I could have not held out for much longer. A terrible thing has happened here.','???????! ??? ??? ? ?? ????? ?? ????????????... ????? ????????? ???????? ???????...','17491','0','0','0','SAY_XERESTRASZA_YELL_2'),
('-1724002','We believed that the Sanctum was well fortified, but we were not prepareted for the nature of this assault.','????????? ????????? ????????????, ?? ?? ??? ??? ??? ?? ???????????? ?????? ??????...','17492','0','0','0','SAY_XERESTRASZA_SAY_1'),
('-1724003','The Black Dragonkin materialized from thin air, and set upon us before we could react.','?????? ??????? ??????? ?? ????????. ?? ???? ?? ?????? ?????? ??? ??????????...','17493','0','0','0','SAY_XERESTRASZA_SAY_2'),
('-1724004','We did not stand a chance. As my brethren perished around me, I managed to retreat hear and bar the entrance.','???? ???? ???????, ??? ?????? ????? ???? ?? ??????. ? ? ?????????? ????? ? ?????????? ????.','17494','0','0','0','SAY_XERESTRASZA_SAY_3'),
('-1724005','They slaughtered us with cold efficiency, but the true focus of their interest seemed to be the eggs kept here in the sanctum.','??? ??????? ? ??????????? ???????????, ?? ???????? ????? ????? ???? ?????? ??? ? ?????????.','17495','0','0','0','SAY_XERESTRASZA_SAY_4'),
('-1724006','The commander of the forces on the ground here is a cruel brute named Zarithrian. But I fear there are greater powers at work.',' ?????? ????????? ??????????? ?????????, ??, ?????, ??? ???????? ? ????? ?????????????? ???.','17496','0','0','0','SAY_XERESTRASZA_SAY_5'),
('-1724007','In their initial assault I caught a glimpse of their true leader, a fearsome full-grown Twilight Dragon.','? ????? ?????? ? ??????? ??????????? ?? ?????????? ?????? - ????????? ??????????? ???????.','17497','0','0','0','SAY_XERESTRASZA_SAY_6'),
('-1724008','I know not the extent of their plans heroes, but I know this: they cannot be allowed to succeed!','?????, ? ?? ???? ???? ?????????? ??? ??????????. ???? ? ???? ????? - ?? ????? ??????????!','17498','0','0','0','SAY_XERESTRASZA_SAY_7'),

-- Halion
('-1724100','Meddlesome insects, you\'re too late! The Ruby Sanctum is lost.','?????????? ???????! ?? ????????. ????????? ????????? ????!','17499','6','0','0','SAY_HALION_SPAWN'),
('-1724101','Your world teeters on the brink of annihilation. You will all bear witness to the coming of a new age of destruction!','???? ??? ???-??? ??????????? ? ??????. ??? ?????? ????? ?????? ?????? ??? ??????????!','17500','6','0','0','SAY_HALION_AGGRO'),
('-1724102','Another hero falls.','??????? ??? ????? ???????','17501','6','0','0','SAY_HALION_SLAY_1'),
('-1724103','Ha Ha Ha!','','17502','6','0','0','SAY_HALION_SLAY_2'),
('-1724104','Relish this victory mortals, for it will be your last. This world will burn with the Master\'s return!','??? ???? ????????? ??????. ??????????? ?????? ?? ??????. ??? ????? ???????? ??? ????????, ???? ??? ?????? ? ????!','17503','6','0','0','SAY_HALION_DEATH'),
('-1724105','Not good enough!','???????!','17504','6','0','0','SAY_HALION_BERSERK'),
('-1724106','The heavens burn!','?????? ? ????!','17505','6','0','0','SAY_HALION_SPECIAL_1'),
('-1724107','Beware the shadow!','','17506','6','0','0','SAY_HALION_SPECIAL_2'),
('-1724108','You will find only suffering within the realm of Twilight. Enter if you dare.','?? ??????? ?????? ???? ? ???? ???????. ???????, ???? ????????.','17507','6','0','0','SAY_HALION_PHASE_2'),
('-1724109','I am the light AND the darkness! Cower mortals before the Herald of Deathwing!','? ???? ???? ? ? ???? ????! ?????????, ?????????, ????? ??????????? ???????????!','17508','6','0','0','SAY_HALION_PHASE_3'),
('-1724110','The orbining spheres pulse with dark energy!','?? ??????????? ?????? ?????????? ?????? ???????!','0','3','0','0',''),
('-1724111','Your companions\' effort force Halion further into the physical realm!','???? ???????? ??????????? ??????? ?????? ? ?????????? ???!','0','3','0','0',''),
('-1724112','Your companions\' effort force Halion further into the twilight realm!','???? ???????? ??????????? ??????? ?????? ? ???????? ???!','0','3','0','0',''),
('-1724113','Being alone in one of the worlds, Halion restores vitality.','???????? ? ????? ? ????? ?? ?????, ?????? ??????????????? ????????? ????.','0','3','0','0',''),

-- Zarthrian
('-1724200','Alexstrasza has chosen capable allies. A pity that I must end you!','?????????? ??????? ????????? ?????????... ????, ??? ???????? ?????????? ???!','17512','6','0','0','SAY_ZARITHRIAN_AGGRO'),
('-1724201','You thought you stood a chance?','????? ???? ? ?????????!','17513','6','0','0','SAY_ZARITHRIAN_SLAY_1'),
('-1724202','It\'s for the best.','??? ?????? ? ???????!','17514','6','0','0','SAY_ZARITHRIAN_SLAY_2'),
('-1724203','Halion! I\'m...aah!','??????! ?...','17515','6','0','0','SAY_ZARITHRIAN_DEATH'),
('-1724204','Turn them to ash, minions!','?????! ???????? ?? ? ?????!','17516','6','0','0','SAY_ZARITHRIAN_SPECIAL_1'),

-- baltharus
('-1724300','Ah, the entertainment has arrived...','?-?-?, ???? ???????.','17520','6','0','0','SAY_BALTHARUS_AGGRO'),
('-1724301','Baltharus leaves no survivors!','?????? ?? ????????? ?????!','17521','6','0','0','SAY_BALTHARUS_SLAY_1'),
('-1724302','This world has enough heroes!','? ???? ??????? ?????? ? ??? ????...','17522','6','0','0','SAY_BALTHARUS_SLAY_2'),
('-1724303','I...didn\'t see that coming...','???… ??? ????? ??????????..','17523','1','0','0','SAY_BALTHARUS_DEATH'),
('-1724304','Twice the pain and half the fun!','????? ??????? ?????????.','17524','6','0','0','SAY_BALTHARUS_SPECIAL_1'),
('-1724305','Your power wanes, ancient one! Soon, you will join your friends!','???? ???? ?? ??????, ??????????! ????? ?? ?????????????? ? ????? ???????!','17525','6','0','0','SAY_BALTHARUS_YELL'),

-- saviana
('-1724400','You will suffer for this intrusion...','???-?-?? ???? ?-c????? ?????? ?? ??? ?????????!','17528','6','0','0','SAY_SAVIANA_AGGRO'),
('-1724401','As it should be!','??? ? ?????? ????!','17529','6','0','0','SAY_SAVIANA_SLAY_1'),
('-1724402','Halion will be pleased...','?????? ????? ???????!','17530','6','0','0','SAY_SAVIANA_SLAY_2'),
('-1724403','<screaming>','?...','17531','6','0','0','SAY_SAVIANA_DEATH'),
('-1724404','Burn in the master\'s flame!','?????? ? ???? ???????!','17532','6','0','0','SAY_SAVIANA_SPECIAL_1'),
('-1724405','falls into a trance!','|3-3(%s) ??????? ? ???????????!','0','3','0','0','');

-- Ruby sanctum spelltable
-- Boss Halion
DELETE FROM `boss_spell_table` WHERE `entry` = 39863;
INSERT INTO `boss_spell_table` (`entry`, `spellID_N10`, `spellID_N25`, `spellID_H10`, `spellID_H25`, `timerMin_N10`, `timerMin_N25`, `timerMin_H10`, `timerMin_H25`, `timerMax_N10`, `timerMax_N25`, `timerMax_H10`, `timerMax_H25`, `locData_x`, `locData_y`, `locData_z`, `CastType`, `isVisualEffect`, `isBugged`, `textEntry`) VALUES
(39863, 74637, 0, 0, 0, 30000, 0, 0, 0, 30000, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0),
(39863, 74525, 0, 0, 0, 10000, 0, 0, 0, 20000, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0),
(39863, 74562, 0, 0, 0, 30000, 0, 0, 0, 40000, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0),
(39863, 74809, 0, 0, 0, 15000, 0, 0, 0, 25000, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0),
(39863, 74808, 0, 0, 0, 15000, 0, 0, 0, 25000, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0),
(39863, 75063, 0, 0, 0, 15000, 0, 0, 0, 25000, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0),
(39863, 26663, 0, 0, 0, 600000, 0, 0, 0, 600000, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0),
(39863, 78243, 0, 0, 0, 15000, 0, 0, 0, 25000, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0);

-- Mob Meteor strike
DELETE FROM `boss_spell_table` WHERE `entry` = 40029;
INSERT INTO `boss_spell_table` (`entry`, `spellID_N10`, `spellID_N25`, `spellID_H10`, `spellID_H25`, `timerMin_N10`, `timerMin_N25`, `timerMin_H10`, `timerMin_H25`, `timerMax_N10`, `timerMax_N25`, `timerMax_H10`, `timerMax_H25`, `data1`, `data2`, `data3`, `data4`, `locData_x`, `locData_y`, `locData_z`, `CastType`, `isVisualEffect`, `isBugged`) VALUES
(40029, 40041, 0, 0, 0, 20000, 0, 0, 0, 20000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0),
(40029, 74641, 0, 0, 0, 500, 0, 0, 0, 500, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(40029, 74648, 0, 0, 0, 4500, 0, 0, 0, 4500, 0, 0, 0, 5, 7, 5, 7, 0, 0, 0, 1, 0, 0);

-- Mob Meteor flame
DELETE FROM `boss_spell_table` WHERE `entry` = 40041;
INSERT INTO `boss_spell_table` (`entry`, `spellID_N10`, `spellID_N25`, `spellID_H10`, `spellID_H25`, `timerMin_N10`, `timerMin_N25`, `timerMin_H10`, `timerMin_H25`, `timerMax_N10`, `timerMax_N25`, `timerMax_H10`, `timerMax_H25`, `data1`, `data2`, `data3`, `data4`, `locData_x`, `locData_y`, `locData_z`, `CastType`, `isVisualEffect`, `isBugged`) VALUES
(40041, 74718, 0, 0, 0, 2000, 0, 0, 0, 2000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);

-- Mob soul consumption
DELETE FROM `boss_spell_table` WHERE `entry` = 40135;
INSERT INTO `boss_spell_table` (`entry`, `spellID_N10`, `spellID_N25`, `spellID_H10`, `spellID_H25`, `timerMin_N10`, `timerMin_N25`, `timerMin_H10`, `timerMin_H25`, `timerMax_N10`, `timerMax_N25`, `timerMax_H10`, `timerMax_H25`, `data1`, `data2`, `data3`, `data4`, `locData_x`, `locData_y`, `locData_z`, `CastType`, `isVisualEffect`, `isBugged`) VALUES
(40135, 74803, 0, 0, 0, 60000, 0, 0, 0, 60000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(40135, 74807, 0, 0, 0, 2000, 0, 0, 0, 2000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);

-- Mob fiery combustion
DELETE FROM `boss_spell_table` WHERE `entry` = 40001;
INSERT INTO `boss_spell_table` (`entry`, `spellID_N10`, `spellID_N25`, `spellID_H10`, `spellID_H25`, `timerMin_N10`, `timerMin_N25`, `timerMin_H10`, `timerMin_H25`, `timerMax_N10`, `timerMax_N25`, `timerMax_H10`, `timerMax_H25`, `data1`, `data2`, `data3`, `data4`, `locData_x`, `locData_y`, `locData_z`, `CastType`, `isVisualEffect`, `isBugged`) VALUES
(40001, 74629, 0, 0, 0, 60000, 0, 0, 0, 60000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(40001, 74807, 0, 0, 0, 2000, 0, 0, 0, 2000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);

-- Twilight Halion
DELETE FROM `boss_spell_table` WHERE `entry` = 40142;
INSERT INTO `boss_spell_table` (`entry`, `spellID_N10`, `spellID_N25`, `spellID_H10`, `spellID_H25`, `timerMin_N10`, `timerMin_N25`, `timerMin_H10`, `timerMin_H25`, `timerMax_N10`, `timerMax_N25`, `timerMax_H10`, `timerMax_H25`, `locData_x`, `locData_y`, `locData_z`, `CastType`, `isVisualEffect`, `isBugged`, `textEntry`) VALUES
(40142, 74792, 0, 0, 0, 30000, 0, 0, 0, 40000, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0),
(40142, 74806, 0, 0, 0, 10000, 0, 0, 0, 20000, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0),
(40142, 78243, 0, 0, 0, 15000, 0, 0, 0, 25000, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0),
(40142, 74807, 0, 0, 0, 2000, 0, 0, 0, 2000, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0),
(40142, 26663, 0, 0, 0, 600000, 0, 0, 0, 600000, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0),
(40142, 75484, 0, 0, 0, 2000, 0, 0, 0, 2000, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0);

-- Mob orb carrier
DELETE FROM `boss_spell_table` WHERE `entry` = 40081;
INSERT INTO `boss_spell_table` (`entry`, `spellID_N10`, `spellID_N25`, `spellID_H10`, `spellID_H25`, `timerMin_N10`, `timerMin_N25`, `timerMin_H10`, `timerMin_H25`, `timerMax_N10`, `timerMax_N25`, `timerMax_H10`, `timerMax_H25`, `data1`, `data2`, `data3`, `data4`, `locData_x`, `locData_y`, `locData_z`, `CastType`, `isVisualEffect`, `isBugged`) VALUES
(40081, 77844, 0, 0, 0, 2000, 0, 0, 0, 2000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(40081, 74807, 0, 0, 0, 2000, 0, 0, 0, 2000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);

-- Mobs shadow orbs
DELETE FROM `boss_spell_table` WHERE `entry` = 40083;
INSERT INTO `boss_spell_table` (`entry`, `spellID_N10`, `spellID_N25`, `spellID_H10`, `spellID_H25`, `timerMin_N10`, `timerMin_N25`, `timerMin_H10`, `timerMin_H25`, `timerMax_N10`, `timerMax_N25`, `timerMax_H10`, `timerMax_H25`, `data1`, `data2`, `data3`, `data4`, `locData_x`, `locData_y`, `locData_z`, `CastType`, `isVisualEffect`, `isBugged`) VALUES
(40083, 77844, 0, 0, 0, 2000, 0, 0, 0, 2000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(40083, 74807, 0, 0, 0, 2000, 0, 0, 0, 2000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);
DELETE FROM `boss_spell_table` WHERE `entry` = 40100;
INSERT INTO `boss_spell_table` (`entry`, `spellID_N10`, `spellID_N25`, `spellID_H10`, `spellID_H25`, `timerMin_N10`, `timerMin_N25`, `timerMin_H10`, `timerMin_H25`, `timerMax_N10`, `timerMax_N25`, `timerMax_H10`, `timerMax_H25`, `data1`, `data2`, `data3`, `data4`, `locData_x`, `locData_y`, `locData_z`, `CastType`, `isVisualEffect`, `isBugged`) VALUES
(40100, 77844, 0, 0, 0, 2000, 0, 0, 0, 2000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
(40100, 74807, 0, 0, 0, 2000, 0, 0, 0, 2000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);

-- Mob Halion control
DELETE FROM `boss_spell_table` WHERE `entry` = 40146;
INSERT INTO `boss_spell_table` (`entry`, `spellID_N10`, `spellID_N25`, `spellID_H10`, `spellID_H25`, `timerMin_N10`, `timerMin_N25`, `timerMin_H10`, `timerMin_H25`, `timerMax_N10`, `timerMax_N25`, `timerMax_H10`, `timerMax_H25`, `data1`, `data2`, `data3`, `data4`, `locData_x`, `locData_y`, `locData_z`, `CastType`, `isVisualEffect`, `isBugged`) VALUES
(40146, 74826, 0, 0, 0, 5000, 0, 0, 0, 5000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 1),
(40146, 74827, 0, 0, 0, 5000, 0, 0, 0, 5000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 1),
(40146, 74828, 0, 0, 0, 5000, 0, 0, 0, 5000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 1),
(40146, 74829, 0, 0, 0, 5000, 0, 0, 0, 5000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 1),
(40146, 74830, 0, 0, 0, 5000, 0, 0, 0, 5000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 1),
(40146, 74831, 0, 0, 0, 5000, 0, 0, 0, 5000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 1),
(40146, 74832, 0, 0, 0, 5000, 0, 0, 0, 5000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 1),
(40146, 74833, 0, 0, 0, 5000, 0, 0, 0, 5000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 1),
(40146, 74834, 0, 0, 0, 5000, 0, 0, 0, 5000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 1),
(40146, 74835, 0, 0, 0, 5000, 0, 0, 0, 5000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 1),
(40146, 74836, 0, 0, 0, 5000, 0, 0, 0, 5000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 1);

/*
-- spelltable from notagain
-- Boss Halion
DELETE FROM `boss_spell_table` WHERE `entry` = 39863;
INSERT INTO `boss_spell_table` (`entry`, `spellID_N10`, `spellID_N25`, `timerMin_N10`, `timerMin_N25`, `timerMax_N10`, `timerMax_N25`, `data1`, `data2`, `data3`, `data4`, 
`locData_x`, `locData_y`, `locData_z`, `varData`, `StageMask_N`, `StageMask_H`, `CastType`, `isVisualEffect`, `isBugged`, `textEntry`, `comment`) VALUES
(39863, 78243, 0, 100, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, NULL),
(39863, 74562, 0, 20000, 0, 30000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, NULL),
(39863, 74792, 0, 20000, 0, 30000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, NULL),
(39863, 75877, 0, 100, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, NULL),
(39863, 74525, 74527, 8000, 8000, 12000, 12000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, NULL),
(39863, 74806, 0, 8000, 0, 12000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, NULL),
(39863, 75484, 75485, 1000, 1000, 1000, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, NULL);
*/

-- Boss Baltharus
DELETE FROM `boss_spell_table` WHERE `entry` = 39751;
INSERT INTO `boss_spell_table` (`entry`, `spellID_N10`, `spellID_N25`, `spellID_H10`, `spellID_H25`, `timerMin_N10`, `timerMin_N25`, `timerMin_H10`, `timerMin_H25`, `timerMax_N10`, `timerMax_N25`, `timerMax_H10`, `timerMax_H25`, `locData_x`, `locData_y`, `locData_z`, `CastType`, `isVisualEffect`, `isBugged`, `textEntry`) VALUES
(39751, 40504, 0, 0, 0, 10000, 0, 0, 0, 15000, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0),
(39751, 75125, 0, 0, 0, 22000, 0, 0, 0, 22000, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0),
(39751, 74502, 0, 0, 0, 10000, 0, 0, 0, 25000, 0, 0, 0, 40, 0, 0, 4, 0, 1, 0),
(39751, 74505, 0, 0, 0, 22000, 0, 0, 0, 22000, 0, 0, 0, 40, 0, 0, 1, 0, 0, 0),
(39751, 74509, 0, 0, 0, 15000, 0, 0, 0, 25000, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0),
(39751, 74511, 0, 0, 0, 20000, 0, 0, 0, 45000, 0, 0, 0, 0, 0, 0, 1, 0, 0, -1666304),
(39751, 76221, 0, 0, 0, 1000, 0, 0, 0, 1000, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0);
-- mob Baltharus Clone
DELETE FROM `boss_spell_table` WHERE `entry` = 39899;
INSERT INTO `boss_spell_table` (`entry`, `spellID_N10`, `spellID_N25`, `spellID_H10`, `spellID_H25`, `timerMin_N10`, `timerMin_N25`, `timerMin_H10`, `timerMin_H25`, `timerMax_N10`, `timerMax_N25`, `timerMax_H10`, `timerMax_H25`, `locData_x`, `locData_y`, `locData_z`, `CastType`, `isVisualEffect`, `isBugged`, `textEntry`) VALUES
(39899, 75125, 0, 0, 0, 22000, 0, 0, 0, 22000, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0),
(39899, 74502, 0, 0, 0, 10000, 0, 0, 0, 25000, 0, 0, 0, 40, 0, 0, 4, 0, 1, 0),
(39899, 40504, 0, 0, 0, 10000, 0, 0, 0, 15000, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0);

-- Boss Zarithian
DELETE FROM `boss_spell_table` WHERE `entry` = 39746;
INSERT INTO `boss_spell_table` (`entry`, `spellID_N10`, `spellID_N25`, `spellID_H10`, `spellID_H25`, `timerMin_N10`, `timerMin_N25`, `timerMin_H10`, `timerMin_H25`, `timerMax_N10`, `timerMax_N25`, `timerMax_H10`, `timerMax_H25`, `locData_x`, `locData_y`, `locData_z`, `CastType`, `isVisualEffect`, `isBugged`, `textEntry`) VALUES
(39746, 74367, 0, 0, 0, 10000, 0, 0, 0, 20000, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0),
(39746, 74384, 0, 0, 0, 15000, 0, 0, 0, 25000, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0),
(39746, 74398, 0, 0, 0, 45000, 0, 0, 0, 45000, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0),
(39746, 39814, 0, 0, 0, 15000, 0, 0, 0, 25000, 0, 0, 0, 40, 0, 0, 9, 0, 0, 0);
-- mob Onyx Falmecaller
DELETE FROM `boss_spell_table` WHERE `entry` = 39814;
INSERT INTO `boss_spell_table` (`entry`, `spellID_N10`, `spellID_N25`, `spellID_H10`, `spellID_H25`, `timerMin_N10`, `timerMin_N25`, `timerMin_H10`, `timerMin_H25`, `timerMax_N10`, `timerMax_N25`, `timerMax_H10`, `timerMax_H25`, `locData_x`, `locData_y`, `locData_z`, `CastType`, `isVisualEffect`, `isBugged`, `textEntry`) VALUES
(39814, 74392, 0, 0, 0, 10000, 0, 0, 0, 25000, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0),
(39814, 74394, 0, 0, 0, 10000, 0, 0, 0, 25000, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0);

-- Boss Saviana Ragefire
DELETE FROM `boss_spell_table` WHERE `entry` = 39747;
INSERT INTO `boss_spell_table` (`entry`, `spellID_N10`, `spellID_N25`, `spellID_H10`, `spellID_H25`, `timerMin_N10`, `timerMin_N25`, `timerMin_H10`, `timerMin_H25`, `timerMax_N10`, `timerMax_N25`, `timerMax_H10`, `timerMax_H25`,`data1`, `data2`, `data3`, `data4`, `locData_x`, `locData_y`, `locData_z`, `CastType`, `isVisualEffect`, `isBugged`, `textEntry`) VALUES
(39747, 78722, 0, 0, 0, 20000, 0, 0, 0, 40000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 ,-1666405),
(39747, 74404, 0, 0, 0, 5000, 0, 0, 0, 15000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0),
(39747, 74453, 0, 0, 0, 12000, 0, 0, 0, 22000, 0, 0, 0, 2, 5, 3, 5, 0, 0, 0, 6, 0, 0, 0),
(39747, 74452, 0, 0, 0, 15000, 0, 0, 0, 25000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0),
(39747, 74455, 0, 0, 0, 5000, 0, 0, 0, 5000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0),
(39747, 74456, 0, 0, 0, 15000, 0, 0, 0, 25000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0);

