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