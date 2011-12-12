# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-11 23:56:17
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table scriptdev2.gossip_texts
DROP TABLE IF EXISTS `gossip_texts`;
CREATE TABLE IF NOT EXISTS `gossip_texts` (
  `entry` mediumint(8) NOT NULL,
  `content_default` text NOT NULL,
  `content_loc1` text,
  `content_loc2` text,
  `content_loc3` text,
  `content_loc4` text,
  `content_loc5` text,
  `content_loc6` text,
  `content_loc7` text,
  `content_loc8` text,
  `comment` text,
  PRIMARY KEY  (`entry`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Gossip Texts';

# Dumping data for table scriptdev2.gossip_texts: 67 rows
/*!40000 ALTER TABLE `gossip_texts` DISABLE KEYS */;
INSERT IGNORE INTO `gossip_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `comment`) VALUES
	(-3000000, '[PH] SD2 unknown text', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'GOSSIP_ID_UNKNOWN_TEXT'),
	(-3000101, 'Taruk send me to collect what you owe.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'silvermoon harry GOSSIP_ITEM_GAMBLING_DEBT'),
	(-3000102, 'Pay up, Harry!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'silvermoon harry GOSSIP_ITEM_PAYING'),
	(-3000103, 'I am ready to travel to you village now.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'rainspeaker GOSSIP_ITEM_READY'),
	(-3000104, '<Check for pulse...>', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'mosswalker victim GOSSIP_ITEM_PULSE'),
	(-3000105, 'Ezekiel said that you might have a certain book...', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'dirty larry GOSSIP_ITEM_BOOK'),
	(-3000106, 'Show me where I can fly.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'greer orehammer GOSSIP_ITEM_TAXI'),
	(-3000107, '[PH] Get Presicion Bombs', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'greer orehammer GOSSIP_ITEM_GET_BOMBS'),
	(-3000108, '[PH] Start bombing mission', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'greer orehammer GOSSIP_ITEM_FLIGHT'),
	(-3033000, 'Please unlock the courtyard door.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'deathstalker adamant/ sorcerer ashcrombe - GOSSIP_ITEM_DOOR'),
	(-3043000, 'Let the event begin!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Disciple of Naralex - GOSSIP_ITEM_BEGIN'),
	(-3090000, 'I am ready to begin.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'emi shortfuse GOSSIP_ITEM_START'),
	(-3409000, 'Tell me more.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'majordomo_executus GOSSIP_ITEM_SUMMON_1'),
	(-3409001, 'What else do you have to say?', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'majordomo_executus GOSSIP_ITEM_SUMMON_2'),
	(-3409002, 'You challenged us and we have come. Where is this master you speak of?', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'majordomo_executus GOSSIP_ITEM_SUMMON_3'),
	(-3469000, 'I\'ve made no mistakes.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'victor_nefarius GOSSIP_ITEM_NEFARIUS_1'),
	(-3469001, 'You have lost your mind, Nefarius. You speak in riddles.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'victor_nefarius GOSSIP_ITEM_NEFARIUS_2'),
	(-3469002, 'Please do.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'victor_nefarius GOSSIP_ITEM_NEFARIUS_3'),
	(-3469003, 'I cannot, Vaelastrasz! Surely something can be done to heal you!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'vaelastrasz GOSSIP_ITEM_VAEL_1'),
	(-3469004, 'Vaelastrasz, no!!!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'vaelastrasz GOSSIP_ITEM_VAEL_2'),
	(-3560000, 'I am ready to go to Durnholde Keep.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'brazen GOSSIP_ITEM_READY'),
	(-3560001, 'I need a pack of Incendiary Bombs.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'erozion GOSSIP_ITEM_NEED_BOMBS'),
	(-3560002, 'Taretha cannot see you, Thrall.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'thrall GOSSIP_ITEM_SKARLOC1'),
	(-3560003, 'The situation is rather complicated, Thrall. It would be best for you to head into the mountains now, before more of Blackmoore\'s men show up. We\'ll make sure Taretha is safe.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'thrall GOSSIP_ITEM_SKARLOC2'),
	(-3560004, 'We\'re ready, Thrall.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'thrall GOSSIP_ITEM_TARREN'),
	(-3560005, 'Strange wizard?', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'taretha GOSSIP_ITEM_EPOCH1'),
	(-3560006, 'We\'ll get you out. Taretha. Don\'t worry. I doubt the wizard would wander too far away.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'taretha GOSSIP_ITEM_EPOCH2'),
	(-3631600, 'Light\'s Hammer', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Молот света', 'IceCrown citadel teleporter text 1'),
	(-3631601, 'Oratory of the Damned', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Молельня проклятых', 'IceCrown citadel teleporter text 2'),
	(-3631602, 'Rampart of Skulls', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Черепной вал', 'IceCrown citadel teleporter text 3'),
	(-3631603, 'Deathbringer\'s Rise', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Подъем Смертоносного', 'IceCrown citadel teleporter text 4'),
	(-3603000, 'Teleport to the Expedition Base Camp.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'GOSSIP_ITEM_TELE_BASE_CAMP'),
	(-3603001, 'Teleport to the Formation Grounds.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'GOSSIP_ITEM_TELE_FORMATION_GROUNDS'),
	(-3603002, 'Teleport to the Colossal Forge.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'GOSSIP_ITEM_TELE_COLOSSAR_FORGE'),
	(-3603003, 'Teleport to the Scrapyard.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'GOSSIP_ITEM_TELE_SCRAPYARD'),
	(-3603004, 'Teleport to the Antechamber of Ulduar.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'GOSSIP_ITEM_TELE_ANTECHAMBER'),
	(-3603005, 'Teleport to the Shattered Walkway.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'GOSSIP_ITEM_TELE_WALKWAY'),
	(-3603006, 'Teleport to the Conservatory of Life.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'GOSSIP_ITEM_TELE_CONSERVATORY'),
	(-3603007, 'Teleport to the Spark of Imagination.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'GOSSIP_ITEM_TELE_SPARK_IMAGINATION'),
	(-3603008, 'Teleport to the Prison of Yogg-Saron.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'GOSSIP_ITEM_TELE_YOGG_SARON'),
	(-3608000, 'Activate the crystals when we get in trouble, right?', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'sinclari GOSSIP_ITEM_INTRO'),
	(-3608001, 'Get your people to safety, we\'ll keep the Blue Dragonflight\'s forces at bay.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'sinclari GOSSIP_ITEM_START'),
	(-3649000, 'Yes. We are prepared for the challenges ahead of us.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'barrett GOSSIP_ITEM_BEAST_INIT'),
	(-3649001, 'Bring forth the first challenge!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'barrett GOSSIP_ITEM_BEAST_START'),
	(-3649002, 'We want another shot at those beasts!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'barrett GOSSIP_ITEM_BEAST_WIPE_INIT'),
	(-3649003, 'What new challenge awaits us?', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'barrett GOSSIP_ITEM_JARAXXUS_INIT'),
	(-3649004, 'We\'re ready to fight the sorceror again.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'barrett GOSSIP_ITEM_JARAXXUS_WIPE_INIT'),
	(-3649005, 'Of course!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'barrett GOSSIP_ITEM_PVP_INIT'),
	(-3649006, 'Give the signal! We\'re ready to go!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'barrett GOSSIP_ITEM_PVP_START'),
	(-3649007, 'That tough, huh?', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'barrett GOSSIP_ITEM_TWINS_INIT'),
	(-3649008, 'Val\'kyr? We\'re ready for them', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'barrett GOSSIP_ITEM_TWINS_START'),
	(-3649009, 'Your words of praise are appreciated, Coliseum Master.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'barrett GOSSIP_ITEM_ANUB_INIT'),
	(-3649010, 'That is strange...', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'barrett GOSSIP_ITEM_ANUB_START'),
	(-3631604, 'Icecrown Citadel', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Цитадель Ледяной Короны', 'IceCrown citadel teleporter text 5'),
	(-3631605, 'The Sanctum of Blood', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Святилище крови', 'IceCrown citadel teleporter text 6'),
	(-3631606, 'Frost Queen\'s Lair', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Логово Королевы льда', 'IceCrown citadel teleporter text 7'),
	(-3631607, 'Frozen Throne', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Ледяной трон', 'IceCrown citadel teleporter text 8'),
	(-3631608, 'We are ready, Tirion!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Всегда готовы, дедуля!', 'IceCrown citadel Tirion gossip'),
	(-3594536, 'Lady Jaina, we are ready for next mission!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Джайна, мы готовы!', ''),
	(-3594537, 'Lady Jaina, Let\'s go!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Давай быстрее!', ''),
	(-3594538, 'Lady Sylvanas, we are ready for next mission!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Сильвана, мы готовы!', ''),
	(-3594539, 'Lady Sylvanas, Let\'s go!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Поехали!', ''),
	(-3594540, 'Let\'s go!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Побежали!', ''),
	(-3000770, 'Exchange 100 ArenaPoints to 2000 HonorPoints', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Обменять 100 АренаПойнтов на 2000 ХонорПойнтов', 'npc_arena_honor gossip 1'),
	(-3000771, 'Exchange 1000 ArenaPoints to 20000 HonorPoints', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Обменять 1000 АренаПойнтов на 20000 ХонорПойнтов', 'npc_arena_honor gossip 2'),
	(-3000772, 'Exchange 1000 HonorPoints to 50 ArenaPoints', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Обменять 1000 ХонорПойнтов на 50 АренаПойнтов', 'npc_arena_honor gossip 3'),
	(-3000773, 'Exchange 10000 HonorPoints to 500 ArenaPoints', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Обменять 10000 ХонорПойнтов на 500 АренаПойнтов', 'npc_arena_honor gossip 4');
/*!40000 ALTER TABLE `gossip_texts` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
