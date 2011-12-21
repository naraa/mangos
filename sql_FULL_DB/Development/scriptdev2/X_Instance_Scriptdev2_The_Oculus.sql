-- ------------
-- The Oculus -
-- ------------

-- -------------------------
-- Drakos the Interrogator -
-- -------------------------

DELETE FROM `script_texts` WHERE `entry` BETWEEN -1578011 AND -1578000;
INSERT INTO `script_texts` (entry, content_default, content_loc8, sound, type, language, emote, comment) VALUES
(-1578000,'The prisoners shall not go free. The word of Malygos is law!','Узники не вырвутся на волю. Слово Малигоса - закон!',13594,1,0,0,'SAY_AGGRO'),
(-1578001,'A fitting punishment!','Заслуженное наказание!',13602,1,0,0,'SAY_KILL_1'),
(-1578002,'Sentence: executed!','Приговор приведен в исполнение!',13603,1,0,0,'SAY_KILL_2'),
(-1578003,'Another casualty of war!','Еще одна жертва войны!',13604,1,0,0,'SAY_KILL_3'),
(-1578004,'The war... goes on.','Война... продолжается.',13605,1,0,0,'SAY_DEATH'),
(-1578005,'It is too late to run!','Поздно убегать!',13598,1,0,0,'SAY_PULL_1'),
(-1578006,'Gather \'round!','Станьте в круг!',13599,1,0,0,'SAY_PULL_2'),
(-1578007,'None shall escape!','Не кто не уйдет живым!',13600,1,0,0,'SAY_PULL_3'),
(-1578008,'I condemn you to death!','Я приговариваю вас к смерти!',13601,1,0,0,'SAY_PULL_4'),
(-1578009,'Tremble, worms!','Трепещите, черви!',13595,1,0,0,'SAY_STOMP_1'),
(-1578010,'I will crush you!','Я раздавлю вас!',13596,1,0,0,'SAY_STOMP_2'),
(-1578011,'Can you fly?','Вы умеете летать?',13597,1,0,0,'SAY_STOMP_3');

-- -------
-- Varos -
-- -------

DELETE FROM `script_texts` WHERE `entry` BETWEEN -1578029 AND -1578022;
INSERT INTO `script_texts` (entry, content_default, content_loc8, sound, type, language, emote, comment) VALUES
(-1578022,'There will be no mercy!','Пощады не будет!',13649,1,0,0,'SAY_AGGRO'),
(-1578023,'Oculus ours!','Окулус наш!',13654,1,0,0,'SAY_KILL_1'),
(-1578024,'I warned you!','Тебя предупреждали!',13653,1,0,0,'SAY_KILL_2'),
(-1578025,'They are... too strong! Underestimated their... fortitude.','Они... слишком сильны! Я недооценил... их мужество.',13655,1,0,0,'SAY_DEATH'),
(-1578026,'Blast them! Destroy them!','Взорвать их! Изничтожить!',13650,1,0,0,'SAY_STRIKE_1'),
(-1578027,'Take no prisoners! Attack!','Пленных не брать! В Атаку!',13651,1,0,0,'SAY_STRIKE_2'),
(-1578028,'Strike now! Obliterate them!','Нанесите удар! Уничтожте их!',13652,1,0,0,'SAY_STRIKE_3'),
(-1578029,'Intruders, your victory will be short-lived. I am Commander Varos Cloudstrider. My drakes control the skies and protest this conduit. I will see to it personally that the Oculus does not fall into your hands!','Чужаки, ваш триумф будет не долгим. Я командир Варос Заоблачный странник. Мои драконы обозревают небеса и защищают это место. Я позабочусь, чтобы Окулус не достался вам!',13648,1,0,0,'SAY_VAROS_SPAWN');

-- ------
-- urom -
-- ------

DELETE FROM `script_texts` WHERE `entry` BETWEEN -1578021 AND -1578012;
INSERT INTO `script_texts` (entry, content_default, content_loc8, sound, type, language, emote, comment) VALUES
(-1578012,'Poor blind fools!','Несчастные слепые глупцы!',13638,1,0,0,'SAY_AGGRO'),
(-1578013,'If only you understood!','Если бы вы только могли понять!',13641,1,0,0,'SAY_KILL_1'),
(-1578014,'Now do you see? Do you?!','Ну что, теперь тебе понятно? Или нет?!',13642,1,0,0,'SAY_KILL_2'),
(-1578015,'Unfortunate, but necessary.','Сожелею, это было необходимо.',13643,1,0,0,'SAY_KILL_3'),
(-1578016,'Everything I\'ve done... has been for Azeroth...','Все что я делал... было во имя Азерота...',13644,1,0,0,'SAY_DEATH'),
(-1578017,'A taste... just a small taste... of the Spell-Weaver\'s power!','Тень... лиш бледная тень... подленного могущества Хранителя магии!',13639,1,0,0,'SAY_EXPLOSION_1'),
(-1578018,'So much unstable energy... but worth the risk to destroy you!','Много неустойчивой энергии... но чтобы уничтожить вас, я готов рискнуть!',13640,1,0,0,'SAY_EXPLOSION_2'),
(-1578019,'What do we have here... those would defy the Spell-Weaver? Those without foresight or understanding. How could I make you see? Malygos is saving the world from itself! Bah! You are hardly worth my time!','Так, что у нас тут... ааа вы пришли сразится с Хранителем магии? Это вы то лишенные предвидиния и понимания. Как мне заставить вас прозреть? Малигос спасает мир от самого мира! Эх! На вас жаль тратить время!',13635,1,0,0,'SAY_SUMMON_1'),
(-1578020,'Clearly my pets failed. Perhaps another demonstration is in order.','Моих слуг постигла неудача. Возможно потребуется еще одно предупреждение.',13636,1,0,0,'SAY_SUMMON_2'),
(-1578021,'Still you fight. Still you cling to misguided principles. If you survive, you\'ll find me in the center ring.','Вы все еще сражаетесь. Все еще цепляетесь за свои ложные убеждения. Если выживите, встретимся в центральном кругу.',13637,1,0,0,'SAY_SUMMON_3'),
