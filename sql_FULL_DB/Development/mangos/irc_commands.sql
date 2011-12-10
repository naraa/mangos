# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3968
# Date/time:                    2011-12-10 02:15:06
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table mangos.irc_commands
DROP TABLE IF EXISTS `irc_commands`;
CREATE TABLE IF NOT EXISTS `irc_commands` (
  `Command` varchar(10) NOT NULL default '',
  `Description` varchar(150) NOT NULL default '',
  `gmlevel` tinyint(3) unsigned NOT NULL default '0',
  PRIMARY KEY  (`Command`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='IRC Module System';

# Dumping data for table mangos.irc_commands: 31 rows
/*!40000 ALTER TABLE `irc_commands` DISABLE KEYS */;
INSERT IGNORE INTO `irc_commands` (`Command`, `Description`, `gmlevel`) VALUES
	('acct', '[acct <Player> <(un)lock/mail/pass/rename>] : Perform Action To <Player> Account.', 3),
	('ban', '[ban <Player/IP> <ip/acct/unban/reason>] : Ban/Unban <Player>', 3),
	('chan', '[chan <op/deop/voice/devoice> <*IRC Nick*>] : Set Mode On Yourself, If <IRC Nick> Is Specified Then Set mode On Nick.', 3),
	('char', '[char <Player> <mailcheat/taxicheat/maxskill/setskill>] : Perform Action To Character.', 3),
	('fun', '[fun <Player> <Sound/Say>] : Do Selected Fun Action To <Player>.', 3),
	('help', '[help Command] : Use No Paramaters For List Of Available Commands.', 0),
	('inchan', '[inchan <Channel>] : Display Users In Selected In Game <Channel>', 0),
	('info', '[info] : Display Server Info. (Number Of Players Online/Max Since Last Restart/Uptime)', 0),
	('item', '[item <Player> <add> <ItemID/[ItemName]> <Amount>] : Additem To <Player>, Use <ItemID> Or <[Exact Item Name]>.', 3),
	('jail', '[jail <Player> <release/Reason>] : Jail Selected <Player> For <Reason>. Using release As <Reason> Releases Player.', 3),
	('kick', '[kick <Player> <Reason>] : Kick <Player> For <Reason>.', 3),
	('kill', '[kill <Player> <Reason>] : Kill <Player> For <Reason>.', 3),
	('level', '[level <Player> <NewLevel>] : Level <Player> To <NewLevel>. *Can Be Done Offline*', 3),
	('lookup', '[lookup <acct/char/creature/faction/go/item/quest/skill/spell/tele> <ID/Name>] : ', 3),
	('login', '[login <UserName> <Password>] : Login To MangChat Admin Mode.  (Must Be Done In A PM)', 0),
	('logout', '[logout] : Logout Of MangChat Admin Mode.', 0),
	('money', '[money <Player> <(-)Money>] : Give Money To <Player>, Use - To Take Money. *Can Be Done Offline*', 3),
	('mute', '[mute <Player> <release/TimeInMins> <Reason>] : Mute Player For Reason, For <TimeInMins>. Using release As Time Releases Player. *Can Be Done Offline*', 3),
	('online', '[online] : Display All Users Logged In Game.', 0),
	('pm', '[pm <Player> <Message>] : Whisper <Player> In WoW <Message>.', 3),
	('reload', '[reload] : Reload MangChat Config Options And Security Level From DataBase.', 3),
	('restart', '[restart] : Restart MangChat, NOT MaNGOS World Server Itself. Forces Reconnection To IRC Server.', 3),
	('revive', '[revive <Player>] : Revive <Player>.', 3),
	('saveall', '[saveall] : Forces MaNGOS To Save All Players.', 3),
	('shutdown', '[shutdown <TimeInSeconds>] : Shuts The Server Down In <TimeInSeconds>, Use 0 For Immediate Shut Down', 3),
	('spell', '[spell <Player> <Cast/Learn/UnLearn> <SpellID>] : Make <Player> <Learn> Or <UnLearn> A Spell, Or <Cast> A Spell On A <Player>.', 3),
	('tele', '[tele <Player> <l/c/r/to> <Loc.Name/MAPID X Y Z/Recall/Player>] : Teleport Player To Location, Coords, Or Another Player. (l-Location)(c-Coords)', 3),
	('ticket', '[ticket <list/read/respond/delete> <limit/name/all> <message>] : Manage GM tickets, respond with message', 3),
	('top', '[top <accttime/chartime/money> <limit>] : Display top stats for given option. Only GM Higher Than Config Option Can Use Limit.', 3),
	('who', '[who] : Displays Users Currently Logged In To MangChat.', 1),
	('sysmsg', '[sysmsg <a/n/e> <Message>] : Broadcasts A System Message. (a-Broadcast System Message)(n-Broadcast Notify Message)(e-Event Message)', 3);
/*!40000 ALTER TABLE `irc_commands` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
