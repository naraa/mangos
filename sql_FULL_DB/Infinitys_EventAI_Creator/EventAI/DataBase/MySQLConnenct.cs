using System;
using System.Collections.Generic;
using System.Data;
using System.Windows.Forms;
using MySql.Data.MySqlClient;
using EventAI.Properties;
using System.Collections.Specialized;

namespace EventAI
{
    public static class MySQLConnenct
    {
        private static MySqlConnection _conn;
        private static MySqlCommand _command;

        private static List<ScriptAI> _AIScript = new List<ScriptAI>();
        private static List<TextAI>   _AIText   = new List<TextAI>();
        private static List<SummonAI> _AISummon = new List<SummonAI>();
        private static List<GossipMenu> _GossipMenu = new List<GossipMenu>();
        private static List<GossipMenuCreature> _GossipMenuCreature = new List<GossipMenuCreature>();
        private static List<GossipMenuOption> _GossipMenuOption = new List<GossipMenuOption>();
        private static List<NPC_TEXT> _NPC_TEXT = new List<NPC_TEXT>();

        public static StringCollection GetColumns(string Table)
        {
            string query = "SHOW COLUMNS FROM " + Table;
            StringCollection fldCol = new StringCollection();

            if (!IsConnected)
            {
                return fldCol = null;
            }

            try
            {
                using (_conn = new MySqlConnection(ConnectionString))
                {
                    _command = new MySqlCommand(query, _conn);
                    _conn.Open();

                    using (var reader = _command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            fldCol.Add(reader.GetValue(0).ToString());
                        }
                    }
                }
                return fldCol;
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message.ToString());
                return fldCol;
            }
        }

        public static void SelectAIScript(string query)
        {
            if (!IsConnected)
            {
                System.Windows.Forms.MessageBox.Show("No connection to database, please check settings", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            using (_conn = new MySqlConnection(ConnectionString))
            {
                _command = new MySqlCommand(query, _conn);
                _conn.Open();
                _AIScript.Clear();

                using (var reader = _command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        ScriptAI script = new ScriptAI();

                        script.ID                = reader[0].ToInt32();
                        script.NpcEntry          = reader[1].ToInt32();
                        script.EventType         = reader[2].ToInt32();
                        script.Phase             = reader[3].ToInt32();
                        script.Chance            = reader[4].ToInt32();
                        script.Flags             = reader[5].ToInt32();

                        script.EventParam[0]     = reader[6].ToInt32();
                        script.EventParam[1]     = reader[7].ToInt32();
                        script.EventParam[2]     = reader[8].ToInt32();
                        script.EventParam[3]     = reader[9].ToInt32();

                        script.ActionType[0]     = reader[10].ToInt32();
                        script.ActionParam[0, 0] = reader[11].ToInt32();
                        script.ActionParam[0, 1] = reader[12].ToInt32();
                        script.ActionParam[0, 2] = reader[13].ToInt32();

                        script.ActionType[1]     = reader[14].ToInt32();
                        script.ActionParam[1, 0] = reader[15].ToInt32();
                        script.ActionParam[1, 1] = reader[16].ToInt32();
                        script.ActionParam[1, 2] = reader[17].ToInt32();

                        script.ActionType[2]     = reader[18].ToInt32();
                        script.ActionParam[2, 0] = reader[19].ToInt32();
                        script.ActionParam[2, 1] = reader[20].ToInt32();
                        script.ActionParam[2, 2] = reader[21].ToInt32();

                        script.Comment           = reader[22].ToString();

                        _AIScript.Add(script);
                    }
                }

                _conn.Close();
            }
        }

        public static void SelectNpcText(int TextID)
        {
            if (!IsConnected)
            {
                System.Windows.Forms.MessageBox.Show("No connection to database, please check settings", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string query;
            int counter = 1;

            if (TextID != 0)
            {
                query = "SELECT * FROM npc_text WHERE ID=" + TextID;
            }
            else
            {
                query = "SELECT * FROM npc_text;";
            }

            using (_conn = new MySqlConnection(ConnectionString))
            {
                _command = new MySqlCommand(query, _conn);
                _conn.Open();
                _NPC_TEXT.Clear();

                using (var reader = _command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        NPC_TEXT npc_text = new NPC_TEXT();
                        npc_text.ID = reader[0].ToInt32();
                        for (int x = 0; x < 8; x++)
                        {
                            npc_text.text0[x]   = reader[counter].ToString(); counter++;
                            npc_text.text1[x]   = reader[counter].ToString(); counter++;
                            npc_text.lang[x]    = reader[counter].ToInt32(); counter++;
                            npc_text.prob[x]    = reader[counter].ToFloat(); counter++;
                            npc_text.em0[x]     = reader[counter].ToInt32(); counter++;
                            npc_text.em1[x]     = reader[counter].ToInt32(); counter++;
                            npc_text.em2[x]     = reader[counter].ToInt32(); counter++;
                            npc_text.em3[x]     = reader[counter].ToInt32(); counter++;
                            npc_text.em4[x]     = reader[counter].ToInt32(); counter++;
                            npc_text.em5[x]     = reader[counter].ToInt32(); counter++;
                        }
                        counter = 1;
                        _NPC_TEXT.Add(npc_text);
                    }
                }

                _conn.Close();
            }
        }

        public static void SelectGossipOption(int MenuID)
        {
            if (!IsConnected)
            {
                System.Windows.Forms.MessageBox.Show("No connection to database, please check settings", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string query;

            if (MenuID > 0)
            {
                query = "SELECT * FROM gossip_menu_option WHERE menu_id=" + MenuID;
            }
            else
            {
                query = "SELECT * FROM gossip_menu_option";
            }

            using (_conn = new MySqlConnection(ConnectionString))
            {
                _command = new MySqlCommand(query, _conn);
                _conn.Open();
                _GossipMenuOption.Clear();

                using (var reader = _command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        GossipMenuOption GossipOption = new GossipMenuOption();

                        GossipOption.menu_id            = reader[0].ToInt32();
                        GossipOption.id                 = reader[1].ToInt32();
                        GossipOption.option_icon        = reader[2].ToInt32();
                        GossipOption.option_text        = reader[3].ToString();
                        GossipOption.option_id          = reader[4].ToInt32();
                        GossipOption.npc_option_npcflag = reader[5].ToInt32();
                        GossipOption.npc_menu_id        = reader[6].ToInt32();
                        GossipOption.action_poi_id      = reader[7].ToInt32();
                        GossipOption.action_script_id   = reader[8].ToInt32();
                        GossipOption.box_coded          = reader[9].ToInt32();
                        GossipOption.box_money          = reader[10].ToInt32();
                        GossipOption.box_text           = reader[11].ToString();

                        GossipOption.cond[0]            = reader[12].ToInt32();
                        GossipOption.cond_val[0, 0]     = reader[13].ToInt32();
                        GossipOption.cond_val[0, 1]     = reader[14].ToInt32();

                        GossipOption.cond[1]            = reader[15].ToInt32();
                        GossipOption.cond_val[1, 0]     = reader[16].ToInt32();
                        GossipOption.cond_val[1, 1]     = reader[17].ToInt32();

                        GossipOption.cond[2]            = reader[18].ToInt32();
                        GossipOption.cond_val[2, 0]     = reader[19].ToInt32();
                        GossipOption.cond_val[2, 1]     = reader[20].ToInt32();

                        _GossipMenuOption.Add(GossipOption);
                    }
                }

                _conn.Close();
            }
        }

        public static void SelectGossipCrearture(int GossipID, int GossipCreature)
        {
            if (!IsConnected)
            {
                System.Windows.Forms.MessageBox.Show("No connection to database, please check settings", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string query;
            bool useCreature;

            if (GossipID > 0)
            {
                query = "SELECT entry, name FROM creature_template WHERE gossip_menu_id=" + GossipID;
                useCreature = false;
            }
            else if (GossipCreature > 0)
            {
                query = "SELECT entry, name, gossip_menu_id FROM creature_template WHERE entry=" + GossipCreature;
                useCreature = true;
            }
            else
            {
                query = "SELECT entry, name, gossip_menu_id FROM creature_template";
                useCreature = true;
            }

            using (_conn = new MySqlConnection(ConnectionString))
            {
                _command = new MySqlCommand(query, _conn);
                _conn.Open();
                _GossipMenuCreature.Clear();

                using (var reader = _command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        if (!useCreature)
                        {
                            GossipMenuCreature script;
                            script.Entry = reader["entry"].ToString();
                            script.Name = reader["name"].ToString();
                            _GossipMenuCreature.Add(script);
                        }
                        else
                        {
                            SelectGossip(reader["gossip_menu_id"].ToInt32());
                        }
                    }
                }

                _conn.Close();
            }
        }

        public static void SelectGossip(int GossipID)
        {
            if (!IsConnected)
            {
                System.Windows.Forms.MessageBox.Show("No connection to database, please check settings", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string query;

            if (GossipID > 0)
            {
                query = "SELECT * FROM gossip_menu WHERE Entry=" + GossipID;
            }
            else
            {
                query = "SELECT * FROM gossip_menu;";
            }

            using (_conn = new MySqlConnection(ConnectionString))
            {
                _command = new MySqlCommand(query, _conn);
                _conn.Open();
                _GossipMenu.Clear();

                using (var reader = _command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        GossipMenu script;
                        script.Entry = reader[0].ToInt32();
                        script.TextID = reader[1].ToInt32();
                        script.cond_1 = reader[2].ToInt32();
                        script.cond_1_val_1 = reader[3].ToInt32();
                        script.cond_1_val_2 = reader[4].ToInt32();
                        script.cond_2 = reader[5].ToInt32();
                        script.cond_2_val_1 = reader[6].ToInt32();
                        script.cond_2_val_2 = reader[7].ToInt32();
                        _GossipMenu.Add(script);
                    }
                }

                _conn.Close();
            }
        }

        public static void SelectAIText()
        {
            if (!IsConnected)
            {
                System.Windows.Forms.MessageBox.Show("No connection to database, please check settings", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string query = "SELECT * FROM creature_ai_texts;";
            using (_conn = new MySqlConnection(ConnectionString))
            {
                _command = new MySqlCommand(query, _conn);
                _conn.Open();
                _AIText.Clear();

                using (var reader = _command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        TextAI script = new TextAI();

                        script.ID               = reader[0].ToInt32();
                        script.ContentDefault   = reader[1].ToString();

                        script.ContentLocale[0] = reader[2].ToString();
                        script.ContentLocale[1] = reader[3].ToString();
                        script.ContentLocale[2] = reader[4].ToString();
                        script.ContentLocale[3] = reader[5].ToString();
                        script.ContentLocale[4] = reader[6].ToString();
                        script.ContentLocale[5] = reader[7].ToString();
                        script.ContentLocale[6] = reader[8].ToString();
                        script.ContentLocale[7] = reader[9].ToString();

                        script.Sound            = reader[10].ToInt32();
                        script.Type             = reader[11].ToInt32();
                        script.Lenguage         = reader[12].ToInt32();
                        script.Emote            = reader[13].ToInt32();

                        script.Comment          = reader[14].ToString();

                        _AIText.Add(script);
                    }
                }

                _conn.Close();
            }
        }

        public static void SelectAISummon()
        {
            if (!IsConnected)
            {
                System.Windows.Forms.MessageBox.Show("No connection to database, please check settings", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string query = "SELECT * FROM creature_ai_summons;";
            using (_conn = new MySqlConnection(ConnectionString))
            {
                _command = new MySqlCommand(query, _conn);
                _conn.Open();
                _AISummon.Clear();

                using (var reader = _command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        SummonAI script;

                        script.ID               = reader[0].ToInt32();
                        script.PositionX        = reader.GetFloat(1);
                        script.PositionY        = reader.GetFloat(2);
                        script.PositionZ        = reader.GetFloat(3);
                        script.Orientation      = reader.GetFloat(4);
                        script.SpawnTimeSecs    = reader[5].ToInt32();
                        script.Comment          = reader[6].ToString();

                        _AISummon.Add(script);
                    }
                }

                _conn.Close();
            }
        }

        public static void Insert(string query)
        {
            if (!IsConnected)
            {
                System.Windows.Forms.MessageBox.Show("No connection to database, please check settings", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            try
            {
                _conn = new MySqlConnection(ConnectionString);
                _command = new MySqlCommand(query, _conn);
                _conn.Open();
                _command.ExecuteNonQuery();
                _command.Connection.Close();
            }
            catch (Exception ex)
            {
                System.Windows.Forms.MessageBox.Show("Data not recorded " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            finally
            {
                _conn.Close();
            }
        }

        #region Properties

        public static List<ScriptAI> AIScript
        {
            get { return _AIScript; }
        }

        public static List<TextAI> AIText
        {
            get { return _AIText; }
        }

        public static List<SummonAI> AISummon
        {
            get { return _AISummon; }
        }

        public static List<GossipMenu> GossipMenu
        {
            get { return _GossipMenu; }
        }

        public static List<GossipMenuCreature> GossipMenuCreature
        {
            get { return _GossipMenuCreature; }
        }

        public static List<GossipMenuOption> GossipMenuOption
        {
            get { return _GossipMenuOption; }
        }

        public static List<NPC_TEXT> npc_text
        {
            get { return _NPC_TEXT; }
        }

        private static String ConnectionString
        {
            get
            {
                return String.Format("Server={0};Port={1};Uid={2};Pwd={3};Database={4};character set=utf8;Connection Timeout=10",
                    Settings.Default.Host,
                    Settings.Default.Port,
                    Settings.Default.User,
                    Settings.Default.Pass,
                    Settings.Default.Db_mangos);
            }
        }

        public static bool IsConnected
        {
            get
            {
                if (!Settings.Default.UseDbConnect)
                    return false;

                try
                {
                    _conn = new MySqlConnection(ConnectionString);
                    _conn.Open();
                    _conn.Close();
                    return true;
                }
                catch
                {
                    return false;
                }
            }
        }

        #endregion
    }
}
