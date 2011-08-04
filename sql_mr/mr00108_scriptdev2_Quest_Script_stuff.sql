-- ------------------------------------
-- Quest :: 12644, Quest :: 12645 texts
-- ------------------------------------

DELETE FROM script_texts WHERE entry BETWEEN -1999791 AND -1999783;
INSERT INTO script_texts VALUES
('-1999791','Aye, I\'ll try it.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','0','423','Hemet Nesingwary - Taste Test (1)'),
('-1999790','That\'s exactly what I needed!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','0','0','Hemet Nesingwary - Taste Test (2)'),
('-1999789','It\'s got my vote! That\'ll put hair on your chest like nothing else will.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','0','0','Hemet Nesingwary - Taste Test (3)'),
('-1999788','I\'m always up for something of Grimbooze\'s.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','0','423','Hadrius Harlowe - Taste Test (1)'),
('-1999787','Well, so far, it tastes like something my wife would drink...',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','0','0','Hadrius Harlowe - Taste Test (2)'),
('-1999786','Now, there\'s the kick I\'ve come to expect from Grimbooze\'s drinks! I like it!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','0','0','Hadrius Harlowe - Taste Test (3)'),
('-1999785','Sure!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','0','423','Tamara Wobblesprocket - Taste Test (1)'),
('-1999784','Oh my...',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','0','0','Tamara Wobblesprocket - Taste Test (2)'),
('-1999783','Tastes like I\'m drinking... engine degreaser!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','0','0','Tamara Wobblesprocket - Taste Test (3)');

DELETE from script_texts WHERE entry IN  (-1760000,-1760001,-1760002,-1760003,-1760004,-1760005,-1760006,-1760007,-1760008,-1760009,-1760010,-1760011);
INSERT into script_texts (entry,content_default,type,comment) VALUES
(-1760000,'Beginning the destillation in 5 seconds',0,'SAY_EVENT_STARTED'),
(-1760001,'Add bannanas',0,'SAY_ADD_BANNANAS'),
(-1760002,'Put a papaya in the still',0,'SAY_ADD_PAPAYA'),
(-1760003,'Good job! Keep your eyes open now',0,'SAY_GOOD_JOB_1'),
(-1760004,'The still needs heat! Light the brazier!',0,'SAY_BRAZIER'),
(-1760005,'Well done, be ready for anything!',0,'SAY_GOOD_JOB_2'),
(-1760006,'Pressuer\'s too high! Open the pressure valve!',0,'SAY_OPEN_VALVE'),
(-1760007,'That\'ll do. Never know what it\'ll need next ...',0,'SAY_GOOD_JOB_3'),
(-1760008,'Nicely handled! Stay on your toes',0,'SAY_GOOD_JOB_4'),
(-1760009,'We\'ve done it! Come get the cask',0,'SAY_EVENT_END'),
(-1760010,'Add orange, quickly !',0,'SAY_ADD_ORANGE'),
(-1760011,'You failed! You will have to begin new destillation process if you still want cask',0,'SAY_FAIL');

-- -----------
-- Quest 11466
-- -----------

DELETE FROM script_texts WHERE entry BETWEEN -1999818 AND -1999812;
INSERT INTO script_texts (`entry`,`content_default`,`type`,`comment`) VALUES
(-1999818,'Keep quiet, will you? If anyone catches on, we\'re both dead.',4,'Olga (0)'),
(-1999817,'All right, fellas! Who ordered the spiced rum? Was it you, Jackie boy?',0,'Olga (1)'),
(-1999816,'Sure thing, love. Put it on Harry\'s tab, will you? He owes me a drink!',0,'Jack Adams (2)'),
(-1999815,'It\'s ok sweetheart. This one is on the house',0,'Olga (3)'),
(-1999814,'Free rum? Why... that\'s me favourite kind!',0,'Jack Adams (4)'),
(-1999813,'Sweet Neptulon! That was... one drink... too many!',0,'Jack Adams (5)'),
(-1999812,'What are you lot looking at? Pour me another drink!',0,'Jack Adams (6)');

-- -----------------
-- Quest texts 14107
-- -----------------

DELETE FROM script_texts WHERE entry BETWEEN -1000598 AND -1000594;
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1000594,'At last... now I can rest.',0,0,0,0,'hero spirit SAY_BLESS_1'),
(-1000595,'I\'m so tired. Just let me rest for a moment.',0,0,0,0,'hero spirit SAY_BLESS_2'),
(-1000596,'I can\'t hear the screams anymore. Is this the end?',0,0,0,0,'hero spirit SAY_BLESS_3'),
(-1000597,'My nightmare, is it finally over?',0,0,0,0,'hero spirit SAY_BLESS_4'),
(-1000598,'It was awful... I dreamt I was fighting against my friends.',0,0,0,0,'hero spirit SAY_BLESS_5');
