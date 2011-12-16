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