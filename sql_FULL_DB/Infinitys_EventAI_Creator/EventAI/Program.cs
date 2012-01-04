using System;
using System.Windows.Forms;
using System.Threading;
using System.IO;

namespace EventAI
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            if (!File.Exists("MySql.Data.dll"))
            {
                MessageBox.Show("Missing MySql.Data.dll, please make sure the file in the directory",
                "EventAI ERROR",
                MessageBoxButtons.OK,
                MessageBoxIcon.Error);
                Application.Exit();
                return;
            }
            
            if (!Directory.Exists(DBC.DBC_PATH))
            {
                MessageBox.Show("dbc directory does not exist",
                "EventAI ERROR",
                MessageBoxButtons.OK,
                MessageBoxIcon.Error);
                Application.Exit();
                return;
            }
            try
            {
                LoadDBC();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return;
            }
            Application.Run(new FormMain());            
        }

        private static void LoadDBC()
        {
            DBC.Spell               = DBCReader.ReadDBC<SpellEntry>(DBC._SpellStrings);
            DBC.SkillLine           = DBCReader.ReadDBC<SkillLineEntry>(DBC._SkillLineStrings);
            DBC.SpellRange          = DBCReader.ReadDBC<SpellRangeEntry>(DBC._SpellRangeStrings);
            DBC.Emotes              = DBCReader.ReadDBC<EmotesEntry>(DBC._EmotesStrings);
            DBC.Faction             = DBCReader.ReadDBC<FactionEntry>(DBC._FactionStrings);
            DBC.AreaTable           = DBCReader.ReadDBC<AreaTableEntry>(DBC._AreaTableStrings);
            DBC.HolidayNames        = DBCReader.ReadDBC<HolidayNamesEntry>(DBC._HolidayNamesStrings);
            DBC.CreatureFamily      = DBCReader.ReadDBC<CreatureFamilyEntry>(DBC._CreatureFamilyStrings);
            DBC.CreatureType        = DBCReader.ReadDBC<CreatureTypeEntry>(DBC._CreatureTypeStrings);
            DBC.QuestType           = DBCReader.ReadDBC<QuestInfoEntry>(DBC._QuestInfoStrings);
            DBC.SpellDuration       = DBCReader.ReadDBC<SpellDurationEntry>(null);
            DBC.SkillLineAbility    = DBCReader.ReadDBC<SkillLineAbilityEntry>(null);
            DBC.SpellRadius         = DBCReader.ReadDBC<SpellRadiusEntry>(null);
            DBC.SpellCastTimes      = DBCReader.ReadDBC<SpellCastTimesEntry>(null);
            DBC.Map                 = DBCReader.ReadDBC<MapEntry>(DBC._MapEntryStrings);
            DBC.Achievement         = DBCReader.ReadDBC<AchievementEntry>(DBC._AchievementStrings);

            DBC.Locale = DetectedLocale();
        }

        private static LocalesDBC DetectedLocale()
        {
            byte locale = 0;
            while (DBC.Spell[1].GetName(locale) == String.Empty)
            {
                ++locale;
                if (locale >= DBC.MAX_DBC_LOCALE)
                    throw new Exception("Detected unknown locale index " + locale);
            }
            return (LocalesDBC)locale;
        }
    }
}
