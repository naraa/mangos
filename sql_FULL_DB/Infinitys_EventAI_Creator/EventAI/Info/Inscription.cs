using System.Windows.Forms;
using System.Drawing;

namespace EventAI
{
    public class Inscription
    {
        public static void ShowActionParametr(ComboBox combobox, ComboBox cb1, ComboBox cb2, ComboBox cb3, Label l1, Label l2, Label l3)
        {
            ((GroupBox)combobox.Parent).Reset();
            
            switch ((ActionType)combobox.SelectedValue.ToUInt32())
            {
                case ActionType.TEXT:
                    l1.Text = "ID Text 1";
                    //new ButtonHandler(cb1, BType.TEXT);
                    l2.Text = "ID Text 2";
                    l3.Text = "ID Text 3";
                    break;
                case ActionType.SET_FACTION:
                    l1.Text = "FactionID";
                    cb1.SetDbcData(DBC.Faction, null);
                    break;
                case ActionType.MORPH_TO_ENTRY_OR_MODEL:
                    l1.Text = "CreatureID";
                    new ButtonHandler(cb1, BType.CREATURE, null, 0);
                    l2.Text = "ModelID";
                    break;
                case ActionType.SOUND:
                    l1.Text = "ID sound";
                    break;
                case ActionType.EMOTE:
                    l1.Text = "EmoteID";
                    cb1.SetDbcData(DBC.Emotes, null);
                    break;
                case ActionType.CAST:
                    l1.Text = "SpellId";
                    new ButtonHandler(cb1, BType.SPELL, null, 0);
                    l2.Text = "Target";
                    cb2.SetEnumValues<CastTarget>("", "", true);
                    l3.Text = "CastFlags";
                    new ButtonHandler(cb3, typeof(CastFlags), null, 0);
                    break;
                case ActionType.TEMP_SUMMON:
                    l1.Text = "CreatureID";
                    new ButtonHandler(cb1, BType.CREATURE, null , 0);
                    l2.Text = "Target";
                    l3.Text = "Duration (ms)";
                    cb2.SetEnumValues<CastTarget>("", "", true);
                    break;
                case ActionType.THREAT_SINGLE_PCT:
                    l1.Text = "Threat %";
                    l2.Text = "Target";
                    cb2.SetEnumValues<CastTarget>("", "", true);
                    break;
                case ActionType.THREAT_ALL_PCT:
                    l1.Text = "Threat %";
                    break;
                case ActionType.QUEST_EVENT:
                    l1.Text = "QuestID";
                    new ButtonHandler(cb1, BType.QUEST, null, 0);
                    l2.Text = "Target";
                    cb2.SetEnumValues<CastTarget>("", "", true);
                    break;
                case ActionType.CASTCREATUREGO:
                    l1.Text = "CreatureID";
                    new ButtonHandler(cb1, BType.CREATURE, null , 0);
                    l2.Text = "SpellID";
                    new ButtonHandler(cb2, BType.SPELL, null , 0);
                    l3.Text = "Target";
                    cb3.SetEnumValues<CastTarget>("", "", true);
                    break;
                case ActionType.SET_UNIT_FIELD:
                    l1.Text = "Field_Number";
                    cb1.SetEnumValues<EUnitFields>("", "UNIT_FIELD_", true);
                    l2.Text = "Value";
                    l3.Text = "Target";
                    cb3.SetEnumValues<CastTarget>("", "", true);
                    break;
                case ActionType.SET_UNIT_FLAG:
                    l1.Text = "Flag being";
                    new ButtonHandler(cb1, typeof(UnitFlags), null, 0);
                    l2.Text = "Target";
                    cb2.SetEnumValues<CastTarget>("", "", true);
                    break;
                case ActionType.REMOVE_UNIT_FLAG:
                    l1.Text = "Flag being";
                    new ButtonHandler(cb1, typeof(UnitFlags), null, 0);
                    l2.Text = "Target";
                    cb2.SetEnumValues<CastTarget>("", "", true);
                    break;
                case ActionType.AUTO_ATTACK:
                    l1.Text = "AllowAutoAttack";
                    cb1.SetEnumValues<YesNO>("", "", true);
                    break;
                case ActionType.COMBAT_MOVEMENT:
                    l1.Text = "Allow movement in battle";
                    l2.Text = "Stop, start combat mode";
                    cb1.SetEnumValues<YesNO>("", "", true);
                    cb2.SetEnumValues<YesNO>("", "", true);
                    break;
                case ActionType.SET_PHASE:
                    l1.Text = "Phase";
                    new ButtonHandler(cb1, typeof(Phase), null, 0);
                     break;
                case ActionType.INC_PHASE:
                     l1.Text = "Value";
                    break;
                case ActionType.QUEST_EVENT_ALL:
                    l1.Text = "QuestId";
                    new ButtonHandler(cb1, BType.QUEST, null, 0);
                    break;
                case ActionType.CASTCREATUREGO_ALL:
                    l1.Text = "QuestId";
                    new ButtonHandler(cb1, BType.QUEST, null, 0);
                    l2.Text = "SpellId";
                    new ButtonHandler(cb2, BType.SPELL, null, 0);
                    break;
                case ActionType.REMOVEAURASFROMSPELL:
                    l1.Text = "Target";
                    cb1.SetEnumValues<CastTarget>("", "" , true);
                    l2.Text = "SpellId";
                    new ButtonHandler(cb2, BType.SPELL, null, 0);
                    break;
                case ActionType.RANGED_MOVEMENT:
                    l1.Text = "Distance";
                    l2.Text = "Angle";
                    break;
                case ActionType.RANDOM_PHASE:
                    l1.Text = "PhaseID 1";
                    new ButtonHandler(cb1, typeof(Phase), null, 0);
                    l2.Text = "PhaseID 2";
                    new ButtonHandler(cb2, typeof(Phase), null, 0);
                    l3.Text = "PhaseID 3";
                    new ButtonHandler(cb3, typeof(Phase), null, 0);
                    break;
                case ActionType.RANDOM_PHASE_RANGE:
                    l1.Text = "The minimum number of phases";
                    new ButtonHandler(cb1, typeof(Phase), null, 0);
                    l2.Text = "The maximum number of phases";
                    new ButtonHandler(cb2, typeof(Phase), null, 0);
                    break;
                case ActionType.SUMMON:
                    l1.Text = "CreatureID";
                    new ButtonHandler(cb1, BType.CREATURE, null, 0);
                    l2.Text = "Target";
                    cb2.SetEnumValues<CastTarget>("", "", true);
                    l3.Text = "ID for creature_ai_summons";
                    break;
                case ActionType.KILLED_MONSTER:
                    l1.Text = "CreatureID ";
                    new ButtonHandler(cb1, BType.CREATURE, null, 0);
                    l2.Text = "Target";
                    cb2.SetEnumValues<CastTarget>("", "", true);
                    break;
                case ActionType.SET_INST_DATA:
                    l1.Text = "Field";
                    l2.Text = "Data";
                    cb2.SetEnumValues<instanceData>("", "", true);
                    break;
                case ActionType.SET_INST_DATA64:
                    l1.Text = "Field";
                    l2.Text = "Target";
                    cb2.SetEnumValues<CastTarget>("", "", true);
                    break;
                case ActionType.UPDATE_TEMPLATE:
                    l1.Text = "TemplateId";
                    new ButtonHandler(cb1, BType.CREATURE, null, 0);
                    l2.Text = "Team:";
                    cb2.SetEnumValues<Team>("", "", true);
                    break;
                case ActionType.CALL_FOR_HELP:
                    l1.Text = "Radius:";
                    break;
                case ActionType.SET_SHEATH:
                    l1.Text = "Set Sheath State";
                    cb1.SetEnumValues<SheathState>("", "", true);
                     break;
                case ActionType.FORCE_DESPAWN:
                     l1.Text = "Delay (мs)";
                    break;
                case ActionType.SET_INVINCIBILITY_HP_LEVEL:
                    l1.Text = "Minimum Health";
                    l2.Text = "If the value of life";
                    cb1.SetEnumValues<ValueType>("", "", true);
                    break;
                case ActionType.MOUNT_TO_ENTRY_OR_MODEL:
                    l1.Text = "Entry";
                    l2.Text = "Model";
                    new ButtonHandler(cb1, BType.CREATURE, null, 0);
                    break;
            }

            cb1.Visible = l1.Text != string.Empty;
            cb2.Visible = l2.Text != string.Empty;
            cb3.Visible = l3.Text != string.Empty;
         }

        public static void ShowEventType(ComboBox combobox, ComboBox cb1, ComboBox cb2, ComboBox cb3, ComboBox cb4, Label l1, Label l2, Label l3, Label l4)
        {
            ((GroupBox)combobox.Parent).Reset();

            switch ((EventType)combobox.SelectedValue.ToUInt32())
            {
                case EventType.TIMER:
                case EventType.TIMER_OOC:
                    l1.Text = "InitialMin (мs)";
                    l2.Text = "InitialMax (мs)";
                    l3.Text = "RepeatMin (мs)";
                    l4.Text = "RepeatMax (мs)";
                    break;
                case EventType.HP:
                case EventType.TARGET_HP:
                    l1.Text = "HPMax%";
                    l2.Text = "HPMin%";
                    l3.Text = "RepeatMin (мs)";
                    l4.Text = "RepeatMax (мs)";
                    break;
                case EventType.MANA:
                case EventType.TARGET_MANA:
                    l1.Text = "ManaMax%";
                    l2.Text = "ManaMin%";
                    l3.Text = "RepeatMin (мs)";
                    l4.Text = "RepeatMax (мs)";
                    break;
                case EventType.KILL:
                case EventType.TARGET_CASTING:
                    l1.Text = "RepeatMin  (мs)";
                    l2.Text = "RepeatMax  (мs)";
                    break;
                case EventType.SPELLHIT:
                    l1.Text = "SpellID";
                    new ButtonHandler(cb1, BType.SPELL, cb2, -1);
                    l2.Text = "School";
                    new ButtonHandler(cb2, typeof(School), cb1, 0);
                    l3.Text = "RepeatMin (мs)";
                    l4.Text = "RepeatMax (мs)";
                    break;
                case EventType.RANGE:
                    l1.Text = "MinDist";
                    l2.Text = "MaxDist";
                    l3.Text = "RepeatMin (мs)";
                    l4.Text = "RepeatMax (мs)";
                    break;
                case EventType.OOC_LOS:
                    l1.Text = "Hostile-or-Not";
                    cb1.SetEnumValues<TargetFrends>("", "", true);
                    l2.Text = "MaxAllowedRange";
                    l3.Text = "RepeatMin (мs)";
                    l4.Text = "RepeatMax (мs)";
                    break;
                case EventType.FRIENDLY_HP:
                    l1.Text = "HPDeficit";
                    l2.Text = "Radius";
                    l3.Text = "RepeatMin (мs)";
                    l4.Text = "RepeatMax (мs)";
                    break;
                case EventType.FRIENDLY_IS_CC:
                    l1.Text = "DispelType";
                    cb1.SetEnumValues<DispelType>("", "DISPEL_", true);
                    l2.Text = "Radius";
                    l3.Text = "RepeatMin (мs)";
                    l4.Text = "RepeatMax (мs)";
                    break;
                case EventType.FRIENDLY_MISSING_BUFF:
                    l1.Text = "SpellId";
                    new ButtonHandler(cb1, BType.SPELL, null, 0);
                    l2.Text = "Radius";
                    l3.Text = "RepeatMin (мs)";
                    l4.Text = "RepeatMax (мs)";
                    break;
                case EventType.SUMMONED_UNIT:
                    l1.Text = "CreatureId";
                    new ButtonHandler(cb1, BType.CREATURE, null, 0);
                    l2.Text = "RepeatMin (ms)";
                    l3.Text = "RepeatMax (ms)";
                    break;
                case EventType.RECEIVE_EMOTE:
                    l1.Text = "EmoteID";
                    l2.Text = "condition";
                    cb1.SetDbcData(DBC.Emotes, null);
                    cb2.SetEnumValues<ConditionType>("", "", true);
                    break;
                case EventType.AURA:
                case EventType.TARGET_AURA:
                case EventType.MISSING_AURA:
                case EventType.TARGET_MISSING_AURA:
                    l1.Text = "SpellID";
                    new ButtonHandler(cb1, BType.SPELL, null, 0);
                    l2.Text = "Amount";
                    l3.Text = "RepeatMin (ms)";
                    l4.Text = "RepeatMax (ms)";
                    break;
                case EventType.SUMMONED_JUST_DIED:
                case EventType.SUMMONED_JUST_DESPAWN:
                    l1.Text = "CreatureId";
                    new ButtonHandler(cb1, BType.CREATURE, null, 0);
                    l2.Text = "RepeatMin (ms)";
                    l3.Text = "RepeatMax (ms)";
                    break;
            }

            cb1.Visible = l1.Text != string.Empty;
            cb2.Visible = l2.Text != string.Empty;
            cb3.Visible = l3.Text != string.Empty;
            cb4.Visible = l4.Text != string.Empty;
         }

        public static void ShowActionTyteCondition(ComboBox combobox, ComboBox cb2, ComboBox cb3, ComboBox cb4, Label l3, Label l4)
        {
            if ((EventType)combobox.SelectedValue.ToInt32() == EventType.RECEIVE_EMOTE)
            {
                ((GroupBox)combobox.Parent).ResetButton();
                l3.Text = l4.Text = string.Empty;
                cb3.Reset();
                cb4.Reset();
                
                switch ((ConditionType)cb2.SelectedValue.ToUInt32())
                {
                    case ConditionType.AURA:
                        l3.Text = "SpellID";
                        new ButtonHandler(cb3, BType.SPELL, null, 0);
                        l4.Text = "Time to repeat (ms)";
                        break;
                    case ConditionType.ITEM:
                    case ConditionType.ITEM_EQUIPPED:
                        l3.Text = "ItemID";
                        new ButtonHandler(cb3, BType.ITEM, null, 0);
                        l4.Text = "count";
                        break;
                    case ConditionType.ZONEID:
                        l3.Text = "ZoneID";
                        cb3.SetDbcData(DBC.AreaTable, null);
                        break;
                    case ConditionType.REPUTATION_RANK:
                        l3.Text = "FactionID";
                        cb3.SetDbcData(DBC.Faction, null);
                        l4.Text = "Minimum Rank";
                        break;
                    case ConditionType.TEAM:
                        l3.Text = "Team";
                        cb3.SetEnumValues<ConditionTeam>("", "", true);
                        break;
                    case ConditionType.SKILL:
                        l3.Text = "SkillID";
                        cb3.SetDbcData(DBC.SkillLine, null);
                        l4.Text = "Minimum Skill Value";
                        break;
                    case ConditionType.QUESTREWARDED:
                    case ConditionType.QUESTTAKEN:
                        l3.Text = "QuestId";
                        new ButtonHandler(cb3, BType.QUEST, null, 0);
                        break;
                    case ConditionType.ACTIVE_EVENT:
                        l3.Text = "EventId";
                        cb3.SetDbcData(DBC.HolidayNames, null);
                        break;
                }

                cb3.Visible = l3.Text != string.Empty;
                cb4.Visible = l4.Text != string.Empty;
            }
        }

        public static void ShowGossipCondition(ComboBox combobox, ComboBox cb1, ComboBox cb2, Label l1, Label l2)
        {
            ((GroupBox)combobox.Parent).Reset();

            switch ((Gossip_Conditions)combobox.SelectedValue.ToUInt32())
            {
                case Gossip_Conditions.AURA:
                case Gossip_Conditions.NO_AURA:
                    l1.Text = "SpellID";
                    l2.Text = "EffIndex";
                    break;
                case Gossip_Conditions.ITEM:
                case Gossip_Conditions.NO_ITEM:
                case Gossip_Conditions.ITEM_WITH_BANK:
                case Gossip_Conditions.NOITEM_WITH_BANK:
                    l1.Text = "ItemID";
                    l2.Text = "Count";
                    break;
                case Gossip_Conditions.ITEM_EQUIPPED:
                    l1.Text = "ItemID";
                    break;
                case Gossip_Conditions.AREAID:
                    l1.Text = "Area_id";
                    l2.Text = "Sub or Not";
                    cb1.SetDbcData(DBC.AreaTable, null);
                    cb2.SetEnumValues<SubArea>("", "", true);
                    break;
                case Gossip_Conditions.REPUTATION_RANK:
                    l1.Text = "Faction_id";
                    l2.Text = "minimum rank";
                    cb1.SetDbcData(DBC.Faction, null);
                    break;
                case Gossip_Conditions.TEAM:
                    l1.Text = "Player Team";
                    cb1.SetEnumValues<ConditionTeam>("", "", true);
                    break;
                case Gossip_Conditions.SKILL:
                    l1.Text = "Skill ID";
                    l2.Text = "Value";
                    cb1.SetDbcData(DBC.SkillLine, null);
                    break;
                case Gossip_Conditions.QUEST_REWARDED:
                case Gossip_Conditions.QUEST_TAKEN:
                case Gossip_Conditions.QUEST_AVAILBLE:
                case Gossip_Conditions.QUEST_NONE:
                    l1.Text = "Quest ID";
                    break;
                case Gossip_Conditions.ACTIVE_EVENT:
                case Gossip_Conditions.NOT_ACTIVE_GAME_EVENT:
                    l1.Text = "Event ID";
                    cb1.SetDbcData(DBC.HolidayNames, null);
                    break;
                case Gossip_Conditions.AREA_FLAG:
                    l1.Text = "Flag";
                    l2.Text = "Not Flag";
                    break;
                case Gossip_Conditions.RACE_CLASS:
                    l1.Text = "Race";
                    l2.Text = "Class";
                    cb1.SetEnumValues<Race>("", "", true);
                    cb2.SetEnumValues<Class>("", "", true);
                    break;
                case Gossip_Conditions.LEVEL:
                    l1.Text = "Player level";
                    l2.Text = "status";
                    cb2.SetEnumValues<PlayerLevel>("", "", true);
                    break;
                case Gossip_Conditions.SPELL:
                    l1.Text = "Spell ID";
                    l2.Text = "status";
                    cb2.SetEnumValues<HasOrNot>("", "", true);
                    break;
                case Gossip_Conditions.INSTANCE_SCRIPT:
                    l1.Text = "Map ID";
                    l2.Text = "Instance Condition";
                    cb1.SetDbcData(DBC.Map, null);
                    cb2.SetEnumValues<instanceData>("", "", true);
                    break;
                case Gossip_Conditions.ACHIEVEMENT:
                    l1.Text = "Achievemnt ID";
                    l2.Text = "status";
                    cb1.SetDbcData(DBC.Achievement, null);
                    cb2.SetEnumValues<HasOrNot>("", "", true);
                    break;
                case Gossip_Conditions.ACHIEVEMENTREALM:
                    l1.Text = "Achievemnt ID";
                    l2.Text = "status";
                    cb1.SetDbcData(DBC.Achievement, null);
                    cb2.SetEnumValues<HasOrNot>("", "", true);
                    break;
                case Gossip_Conditions.ACTIVE_HOLIDAY:
                case Gossip_Conditions.NOT_ACTIVE_HOLIDAY:
                    l1.Text = "Holiday ID";
                    cb1.SetDbcData(DBC.HolidayNames, null);
                    break;
            }

            cb1.Visible = l1.Text != string.Empty;
            cb2.Visible = l2.Text != string.Empty;
        }
    }
}
