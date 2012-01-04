using System;
using System.Linq;
using System.Windows.Forms;
using System.Drawing;
using System.Text;
using System.IO;

namespace EventAI
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
             // 1 page
            _cbEventType.SetEnumValues<EventType>("", "", true);
            _cbActionType1.SetEnumValues<ActionType>("", "", true);
            _cbActionType2.SetEnumValues<ActionType>("", "", true);
            _cbActionType3.SetEnumValues<ActionType>("", "", true);

            _cbFilteEventType.SetEnumValues<EventType>("EventType", "", false);
            _cbFilteActionType.SetEnumValues<ActionType>("ActionType", "", false);
             // 2 page
            _cbMessageType.SetEnumValues<MessageType>("", "", true);
            _cbLenguage.SetEnumValues<Lenguage>("", "", true);
            _cbLocale.DataSource = Enum.GetValues(typeof(Locales));
             // 4 page
            _cbGossipCondtion_1.SetEnumValues<Gossip_Conditions>("", "", true);
            _cbGossipCondtion_2.SetEnumValues<Gossip_Conditions>("", "", true);
            // 5 page
            _cbGossipOptionCondtion_1.SetEnumValues<Gossip_Conditions>("", "", true);
            _cbGossipOptionCondtion_2.SetEnumValues<Gossip_Conditions>("", "", true);
            _cbGossipOptionCondtion_3.SetEnumValues<Gossip_Conditions>("", "", true);
            _cbGossipOptionIcon.SetEnumValues<OptionIcon>("", "", true);
            _cbGossipOptionID.SetEnumValues<OptionID>("", "", true);
            _cbGossipOptionNpcFlag.SetEnumValues<Option_NPC_Flag>("", "", true);
            // 6 page
            _cbNpc_textLang0.SetEnumValues<Lenguage>("", "", true);
            _cbNpc_textLang1.SetEnumValues<Lenguage>("", "", true);
            _cbNpc_textLang2.SetEnumValues<Lenguage>("", "", true);
            _cbNpc_textLang3.SetEnumValues<Lenguage>("", "", true);
            _cbNpc_textLang4.SetEnumValues<Lenguage>("", "", true);
            _cbNpc_textLang5.SetEnumValues<Lenguage>("", "", true);
            _cbNpc_textLang6.SetEnumValues<Lenguage>("", "", true);
            _cbNpc_textLang7.SetEnumValues<Lenguage>("", "", true);
             // def
            _cbEventType.SelectedValue = 1;
            FillListView();
        }

        private bool err = false;

        private void AboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new FormAboutBox().ShowDialog();
        }

        private void ComboBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (((ComboBox)sender).Text.Contains('-'))
            {
                if (!((Char.IsDigit(e.KeyChar) && ((ComboBox)sender).SelectionStart > 0) || e.KeyChar == (char)Keys.Back))
                    e.Handled = true;
            }
            else
                if (!(Char.IsDigit(e.KeyChar) || e.KeyChar == (char)Keys.Back || (e.KeyChar == '-' && ((ComboBox)sender).SelectionStart == 0)))
                    e.Handled = true;
        }

        private void NumberScripts_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (((TextBox)sender).Text.Contains('-'))
            {
                if (!((Char.IsDigit(e.KeyChar) && ((TextBox)sender).SelectionStart > 0) || e.KeyChar == (char)Keys.Back))
                    e.Handled = true;
            }
            else
                if (!(Char.IsDigit(e.KeyChar) || e.KeyChar == (char)Keys.Back || (e.KeyChar == '-' && ((TextBox)sender).SelectionStart == 0)))
                    e.Handled = true;
        }

        private void EventType_SelectedIndexChanged(object sender, EventArgs e)
        {
            Inscription.ShowEventType(_cbEventType, _cbEventParametr1, _cbEventParametr2, _cbEventParametr3, _cbEventParametr4, lEventType1, lEventType2, lEventType3, lEventType4);
        }

        private void ActionType_SelectedIndexChanged_1(object sender, EventArgs e)
        {
            Inscription.ShowActionParametr(_cbActionType1, _cbActionParam1_1, _cbActionParam1_2, _cbActionParam1_3, lActionParam1_1, lActionParam1_2, lActionParam1_3);
        }

        private void ActionType_SelectedIndexChanged_2(object sender, EventArgs e)
        {
            Inscription.ShowActionParametr(_cbActionType2, _cbActionParam2_1, _cbActionParam2_2, _cbActionParam2_3, lActionParam2_1, lActionParam2_2, lActionParam2_3);
        }

        private void ActionType_SelectedIndexChanged_3(object sender, EventArgs e)
        {
            Inscription.ShowActionParametr(_cbActionType3, _cbActionParam3_1, _cbActionParam3_2, _cbActionParam3_3, lActionParam3_1, lActionParam3_2, lActionParam3_3);
        }

        private void ActionTyteCondition_SelectedIndexChanged(object sender, EventArgs e)
        {
            Inscription.ShowActionTyteCondition(_cbEventType, _cbEventParametr2, _cbEventParametr3, _cbEventParametr4, lEventType3, lEventType4);
        }

        private void _tbFilterNum_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
                CreateQuery();
        }

        private void _cbFilteEventType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (((ComboBox)sender).SelectedIndex > 0)
                CreateQuery();
        }

        private void _bFind_Click(object sender, EventArgs e)
        {
            CreateQuery();
        }

        private void _lvScripts_RetrieveVirtualItem(object sender, RetrieveVirtualItemEventArgs e)
        {
            e.Item = new ListViewItem(MySQLConnenct.AIScript[e.ItemIndex].ToArray());
        }

        private void LogOut(string text, params object[] arg)
        {
            rtbScriptOut.ForeColor = Color.Red;
            rtbScriptOut.AppendFormatLine(text, arg);
            rtbScriptOut.ForeColor = rtbScriptOut.ForeColor;
            err = true;
        }

        private void _clbPhase_SelectedValueChanged(object sender, EventArgs e)
        {
            _gbPhase.Text = "phase " + ((CheckedListBox)sender).GetFlagsValue();
        }

        private void _clbEventFlag_SelectedValueChanged(object sender, EventArgs e)
        {
            _gbEventFlag.Text = "EventFlags " + ((CheckedListBox)sender).GetFlagsValue();
        }

        private void clbEventFlag_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (_clbEventFlag.SelectedIndex == 6)
            {
                _clbEventFlag.SetItemChecked(6, false);
                MessageBox.Show("You can not use this flag!");
            }
        }

        private void ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FormPropertis form = new FormPropertis();
            form.ShowDialog(this);
        }

        private void _lvScripts_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (_lvScripts.SelectedIndices.Count > 0)
                ParseScriptsData(MySQLConnenct.AIScript[_lvScripts.SelectedIndices[0]]);
        }

        private void CreateAIScript_Click(object sender, EventArgs e)
        {
            err = false;
            rtbScriptOut.Clear();
            rtbScriptOut.ForeColor = Color.Blue;

            ScriptAI script             = new ScriptAI();
            script.ID                   = _tbScriptID.Text.ToInt32();
            script.NpcEntry             = _tbEntryNpc.Text.ToInt32();
            script.EventType            = _cbEventType.GetIntValue();
            script.Phase                = _clbPhase.GetFlagsValue();
            script.Chance               = _tbShance.Text.ToInt32();
            script.Flags                = _clbEventFlag.GetFlagsValue();

            script.EventParam[0]        = _cbEventParametr1.GetIntValue();
            script.EventParam[1]        = _cbEventParametr2.GetIntValue();
            script.EventParam[2]        = _cbEventParametr3.GetIntValue();
            script.EventParam[3]        = _cbEventParametr4.GetIntValue();

            script.ActionType[0]        = _cbActionType1.GetIntValue();
            script.ActionParam[0, 0]    = _cbActionParam1_1.GetIntValue();
            script.ActionParam[0, 1]    = _cbActionParam1_2.GetIntValue();
            script.ActionParam[0, 2]    = _cbActionParam1_3.GetIntValue();

            script.ActionType[1]        = _cbActionType2.GetIntValue();
            script.ActionParam[1, 0]    = _cbActionParam2_1.GetIntValue();
            script.ActionParam[1, 1]    = _cbActionParam2_2.GetIntValue();
            script.ActionParam[1, 2]    = _cbActionParam2_3.GetIntValue();

            script.ActionType[2]        = _cbActionType3.GetIntValue();
            script.ActionParam[2, 0]    = _cbActionParam3_1.GetIntValue();
            script.ActionParam[2, 1]    = _cbActionParam3_2.GetIntValue();
            script.ActionParam[2, 2]    = _cbActionParam3_3.GetIntValue();

            script.Comment              = _tbComment.Text;

            #region Check

            if (script.ID < 1)
                LogOut("Script must have value greater than 0!");

            if (script.Chance == 0 || script.Chance > 100)
                LogOut("Proc must be 0 or greater than 100%!");

            switch ((EventType)script.EventType)
            {
                case EventType.TIMER:
                case EventType.TIMER_OOC:
                    if (script.EventParam[0] > script.EventParam[1])
                        LogOut("Minimum time can not be greater than the maximum!");
                    if (script.EventParam[2] > script.EventParam[3])
                        LogOut("Minimum time to repeat can not be greater than the maximum!");
                    break;
                case EventType.HP:
                case EventType.MANA:
                case EventType.TARGET_HP:
                case EventType.TARGET_MANA:
                    if (script.EventParam[0] > 100 || script.EventParam[1] > 100)
                        LogOut("Option 1 or 2 can not be greater 100%!");
                    if (script.EventParam[1] > script.EventParam[0])
                        LogOut("The minimum value of life (MP) can not be greater than the maximum!");
                    if (script.EventParam[2] > script.EventParam[3])
                        LogOut("Minimum time to repeat can not be greater than the maximum!");
                    break;
                case EventType.KILL:
                    if (script.EventParam[0] > script.EventParam[1])
                        LogOut("Minimum time to repeat can not be greater than the maximum!");
                    break;
                case EventType.SPELLHIT:
                    if (script.EventParam[2] > script.EventParam[3])
                        LogOut("Minimum time to repeat can not be greater than the maximum!");
                    if (script.EventParam[0] > 0 && script.EventParam[1] > -1)
                        LogOut(@"If set to \ ID Spells \, then the value of \ School \ must be (-1), otherwise \ id spell \ must be (0)");
                    break;
                case EventType.RANGE:
                    if (script.EventParam[0] > script.EventParam[1])
                        LogOut("The minimum distance to the target can not be greater than the maximum");
                    if (script.EventParam[2] > script.EventParam[3])
                        LogOut("Minimum time to repeat can not be greater than the maximum!");
                    break;
                case EventType.OOC_LOS:
                    if (script.EventParam[2] > script.EventParam[3])
                        LogOut("Minimum time to repeat can not be greater than the maximum!");
                    break;
                case EventType.TARGET_CASTING:
                    if (script.EventParam[0] > script.EventParam[1])
                        LogOut("Minimum time to repeat can not be greater than the maximum!");
                    break;
            }

            if (err)
            {
                _bWriteFiles.Enabled = false;
                return;
            }

            #endregion

            StringBuilder sb = new StringBuilder();
            sb.AppendFormatLine("UPDATE `creature_template` SET `AIName` = 'EventAI', `ScriptName` = '' WHERE `entry` = '{0}';", script.NpcEntry);
            sb.AppendFormatLine("DELETE FROM `creature_ai_scripts` WHERE (`id`='{0}');", script.ID);
            sb.AppendFormatLine("INSERT INTO `creature_ai_scripts` VALUES ('{0}', '{1}', '{2}', '{3}', '{4}', '{5}', '{6}', '{7}', '{8}', '{9}', '{10}', '{11}', '{12}', '{13}', '{14}', '{15}', '{16}', '{17}', '{18}', '{19}', '{20}', '{21}', '{22}');",
                script.ID, script.NpcEntry, script.EventType, script.Phase, script.Chance, script.Flags,
                script.EventParam[0], script.EventParam[1], script.EventParam[2], script.EventParam[3],
                script.ActionType[0], script.ActionParam[0, 0], script.ActionParam[0, 1], script.ActionParam[0, 2],
                script.ActionType[1], script.ActionParam[1, 0], script.ActionParam[1, 1], script.ActionParam[1, 2],
                script.ActionType[2], script.ActionParam[2, 0], script.ActionParam[2, 1], script.ActionParam[2, 2],
                script.Comment.RemExc());

            rtbScriptOut.Text = sb.ToString();
            _bWriteFiles.Enabled = true;
        }

        private void CreateTextQuery_Click(object sender, EventArgs e)
        {
            rtbTextOut.Clear();
            rtbTextOut.ForeColor = Color.Blue;

            int entry;
            if ((entry = _tbTextID.Text.ToInt32()) > -1)
            {
                MessageBox.Show("TextID must be negative!");
                return;
            }

            string[] loc = new string[_cbLocale.Items.Count];
            if (_cbLocale.SelectedIndex > 0)
                loc[_cbLocale.SelectedIndex] = _tbTextContentLocales.Text.RemExc();

            StringBuilder sb = new StringBuilder();
            sb.AppendFormatLine("DELETE FROM `creature_ai_texts` WHERE entry IN ('{0}');", entry);
            sb.AppendFormatLine("INSERT INTO `creature_ai_texts` VALUES ('{0}', '{1}', '{2}', '{3}', '{4}', '{5}', '{6}', '{7}', '{8}', '{9}', '{10}', '{11}', '{12}', '{13}', '{14}');",
                entry,
                _tbTextContentDefault.Text.RemExc(),
                loc[1], loc[2], loc[3], loc[4], loc[5], loc[6], loc[7], loc[8],
                _cbSoundEntry.GetIntValue(),
                _cbMessageType.GetIntValue(),
                _cbLenguage.GetIntValue(),
                _cbTextEmote.GetIntValue(),
                _tbCommentAITexts.Text.RemExc());

            rtbTextOut.Text = sb.ToString();
        }

        private void ParseScriptsData(ScriptAI script)
        {
            _tbScriptID.Text = script.ID.ToString();
            _tbEntryNpc.Text = script.NpcEntry.ToString();
            _tbShance.Text = script.Chance.ToString();

            _clbEventFlag.SetCheckedItemFromFlag((uint)script.Flags);
            _clbPhase.SetCheckedItemFromFlag((uint)script.Phase);
            
            _cbEventType.SelectedValue = script.EventType;
            _cbEventParametr1.SetValue(script.EventParam[0]);
            _cbEventParametr2.SetValue(script.EventParam[1]);
            _cbEventParametr3.SetValue(script.EventParam[2]);
            _cbEventParametr4.SetValue(script.EventParam[3]);

            _cbActionType1.SetValue(script.ActionType[0]);
            _cbActionParam1_1.SetValue(script.ActionParam[0, 0]);
            _cbActionParam1_2.SetValue(script.ActionParam[0, 1]);
            _cbActionParam1_3.SetValue(script.ActionParam[0, 2]);

            _cbActionType2.SetValue(script.ActionType[1]);
            _cbActionParam2_1.SetValue(script.ActionParam[1, 0]);
            _cbActionParam2_2.SetValue(script.ActionParam[1, 1]);
            _cbActionParam2_3.SetValue(script.ActionParam[1, 2]);

            _cbActionType3.SetValue(script.ActionType[2]);
            _cbActionParam3_1.SetValue(script.ActionParam[2, 0]);
            _cbActionParam3_2.SetValue(script.ActionParam[2, 1]);
            _cbActionParam3_3.SetValue(script.ActionParam[2, 2]);

            _tbComment.Text = script.Comment;
        }

        private void Revert1_Click(object sender, EventArgs e)
        {
            switch (((ToolStripItem)sender).Name)
            {
                case "UnselectALL1":
                    for (int i = 0; i < _clbEventFlag.Items.Count; i++)
                        if (i != 6 && i != 5)
                            _clbEventFlag.SetItemChecked(i, false);
                    break;
                case "SelectAll1":
                    for (int i = 0; i < _clbEventFlag.Items.Count; i++)
                        if (i != 6 && i != 5)
                            _clbEventFlag.SetItemChecked(i, true);
                    break;
                case "Revert1":
                    for (int i = 0; i < _clbEventFlag.Items.Count; i++)
                        if (i != 6 && i != 5)
                            _clbEventFlag.SetItemChecked(i, !_clbEventFlag.GetItemChecked(i));
                    break;
            }
        }

        private void UnselectALL_Click(object sender, EventArgs e)
        {
            switch (((ToolStripItem)sender).Name)
            {
                case "UnselectALL":
                    for (int i = 0; i < _clbPhase.Items.Count; i++)
                        _clbPhase.SetItemChecked(i, false);
                    break;
                case "SelectAll":
                    for (int i = 0; i < _clbPhase.Items.Count; i++)
                        _clbPhase.SetItemChecked(i, true);
                    break;
                case "Revert":
                    for (int i = 0; i < _clbPhase.Items.Count; i++)
                        _clbPhase.SetItemChecked(i, !_clbPhase.GetItemChecked(i));
                    break;
            }
        }

        private void CreateQuery()
        {
            int id = _tbFilterNum.GetIntValue();
            int creature = _tbFilterCreat.GetIntValue();
            int etype = _cbFilteEventType.GetIntValue();
            int atype = _cbFilteActionType.GetIntValue();

            string fquery = "SELECT * FROM `creature_ai_scripts` WHERE ";
            string squery = "";
            squery += (id > 0) ? String.Format("id = {0} || ", id) : "";
            squery += (creature > 0) ? String.Format("creature_id = {0} || ", creature) : "";
            squery += (etype > -1) ? String.Format("event_type = {0} || ", etype) : "";
            squery += (atype > -1) ? String.Format("action1_type = {0} || action2_type = {0} || action3_type = {0} || ", atype) : "";

            string q = (squery.Length == 0) ? fquery.Remove(fquery.Length - 6) : fquery + squery.Remove(squery.Length - 3);

            MySQLConnenct.SelectAIScript(q);
            _lvScripts.VirtualListSize = MySQLConnenct.AIScript.Count;
            _lvScripts.Refresh();
        }

        private void WriteFiles_Click(object sender, EventArgs e)
        {
            using (StreamWriter sw = new StreamWriter("NEW_EVENTAI_SQL.sql", true, Encoding.UTF8))
                sw.WriteLine(rtbScriptOut.Text);
            MySQLConnenct.Insert(rtbScriptOut.Text);
        }

        private void _lvText_RetrieveVirtualItem(object sender, RetrieveVirtualItemEventArgs e)
        {
            e.Item = new ListViewItem(MySQLConnenct.AIText[e.ItemIndex].ToArray());
        }

        private void _bTextSearch_Click(object sender, EventArgs e)
        {
            MySQLConnenct.SelectAIText();
            _lvText.VirtualListSize = MySQLConnenct.AIText.Count;
            _lvText.Refresh();
        }

        private void _lvText_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (_lvText.SelectedIndices.Count > 0)
            {
                TextAI text = MySQLConnenct.AIText[_lvText.SelectedIndices[0]];
                int loc = _cbLocale.SelectedIndex == 0 ? 0 : _cbLocale.SelectedIndex - 1;

                _tbTextID.Text = text.ID.ToString();
                _tbTextContentDefault.Text = text.ContentDefault;
                _tbTextContentLocales.Text = text.ContentLocale[loc];
                _cbSoundEntry.SetValue(text.Sound);
                _cbMessageType.SetValue(text.Type);
                _cbLenguage.SetValue(text.Lenguage);
                _cbTextEmote.SetValue(text.Emote);
                _tbCommentAITexts.Text = text.Comment;
            }
        }

        private void _lvSummon_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (_lvSummon.SelectedIndices.Count > 0)
            {
                SummonAI summon = MySQLConnenct.AISummon[_lvSummon.SelectedIndices[0]];

                _tbSummonID.Text        = summon.ID.ToString();
                _tbSummonX.Text         = summon.PositionX.ToString();
                _tbSummonY.Text         = summon.PositionY.ToString();
                _tbSummonZ.Text         = summon.PositionZ.ToString();
                _tbSummonO.Text         = summon.Orientation.ToString();
                _tbSummonSps.Text       = summon.SpawnTimeSecs.ToString();
                _tbSummonComment.Text   = summon.Comment;
            }
        }

        private void _lvSummon_RetrieveVirtualItem(object sender, RetrieveVirtualItemEventArgs e)
        {
            e.Item = new ListViewItem(MySQLConnenct.AISummon[e.ItemIndex].ToArray());
        }

        private void _bSummonSearch_Click(object sender, EventArgs e)
        {
            MySQLConnenct.SelectAISummon();
            _lvSummon.VirtualListSize = MySQLConnenct.AISummon.Count;
            _lvSummon.Refresh();
        }

        private void _tPanel_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(((TabControl)sender).SelectedIndex == 1)
                _cbTextEmote.SetDbcData<EmotesEntry>(DBC.Emotes, null);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            using (StreamWriter sw = new StreamWriter("NEW_EVENTAI_SQL.sql", true, Encoding.UTF8))
                sw.WriteLine(rtbTextOut.Text);
            MySQLConnenct.Insert(rtbTextOut.Text);
        }

        private void _bGossipSearch_Click(object sender, EventArgs e)
        {
            if (_rbTextID.Checked)
            {
                if (_tbFilterGossip.Text.Length > 0)
                {
                    MySQLConnenct.SelectNpcText(_tbFilterGossip.Text.ToInt32());
                }
                else
                {
                    MySQLConnenct.SelectNpcText(0);
                }
                _lvNpc_text.VirtualListSize = MySQLConnenct.npc_text.Count;
                _lvNpc_text.Refresh();
            }
            else if (_rbGossip.Checked)
            {
                if (_tbFilterGossip.Text.Length > 0)
                {
                    MySQLConnenct.SelectGossip(_tbFilterGossip.Text.ToInt32());
                }
                else
                {
                    MySQLConnenct.SelectGossip(0);
                }
                _lvGossip_menu.VirtualListSize = MySQLConnenct.GossipMenu.Count;
                _lvGossip_menu.Refresh();
            }
            else
            {
                if (_tbFilterGossip.Text.Length > 0)
                {
                    MySQLConnenct.SelectGossipCrearture(0,_tbFilterGossip.Text.ToInt32());
                }
                else
                {
                    MySQLConnenct.SelectGossipCrearture(0,0);
                }
                _lvGossip_Creature.VirtualListSize = MySQLConnenct.GossipMenuCreature.Count;
                _lvGossip_Creature.Refresh();
            }
        }

        private void _lvGossip_menu_RetrieveVirtualItem(object sender, RetrieveVirtualItemEventArgs e)
        {
            e.Item = new ListViewItem(MySQLConnenct.GossipMenu[e.ItemIndex].ToArray());
        }

        private void _lvGossip_Creature_RetrieveVirtualItem(object sender, RetrieveVirtualItemEventArgs e)
        {
            e.Item = new ListViewItem(MySQLConnenct.GossipMenuCreature[e.ItemIndex].ToArray());
        }

        private void _lvGossip_Option_RetrieveVirtualItem(object sender, RetrieveVirtualItemEventArgs e)
        {
            e.Item = new ListViewItem(MySQLConnenct.GossipMenuOption[e.ItemIndex].ToArray());
        }

        private void _lvNpc_text_RetrieveVirtualItem(object sender, RetrieveVirtualItemEventArgs e)
        {
            e.Item = new ListViewItem(MySQLConnenct.npc_text[e.ItemIndex].ToArray());
        }

        private void _lvGossip_Option_RetrieveVirtualItem_1(object sender, RetrieveVirtualItemEventArgs e)
        {
            e.Item = new ListViewItem(MySQLConnenct.GossipMenuOption[e.ItemIndex].ToArray());
        }

        private void _lvNpcText_RetrieveVirtualItem(object sender, RetrieveVirtualItemEventArgs e)
        {
            e.Item = new ListViewItem(MySQLConnenct.npc_text[e.ItemIndex].ToArray());
        }

        private void _lvGossip_menu_SelectedIndexChanged(object sender, EventArgs e)
        {
            _tbCreatureGossip.Clear();
            if (_lvGossip_menu.SelectedIndices.Count > 0)
            {
                GossipMenu GossipCreature = MySQLConnenct.GossipMenu[_lvGossip_menu.SelectedIndices[0]];
                MySQLConnenct.SelectGossipCrearture(GossipCreature.Entry, 0);

                if (MySQLConnenct.GossipMenuCreature.Count > 0)
                {
                    _lvGossip_Creature.Visible = true;
                    _lblnpctext.Visible = false;
                    _lvGossip_Creature.VirtualListSize = MySQLConnenct.GossipMenuCreature.Count;
                    _lvGossip_Creature.Refresh();
                    StringBuilder sb = new StringBuilder();

                    for (int i = 0; i < _lvGossip_Creature.VirtualListSize; i++)
                    {
                        if (i > -1)
                            if (i != (_lvGossip_Creature.VirtualListSize))
                            {
                                sb.Append(",");
                                sb.Append(_lvGossip_Creature.Items[i].Text);
                            }
                        else
                            sb.Append(_lvGossip_Creature.Items[i].Text);
                    }
                    sb.Remove(0, 1);
                    _tbCreatureGossip.Text = sb.ToString();
                }
                else
                {
                    _lvGossip_Creature.Visible = false;
                    _lblnpctext.Visible = true;
                }


                _tbGossipEntry.Text = GossipCreature.Entry.ToString();
                _GossipTextID.Text = GossipCreature.TextID.ToString();
                _cbGossipCondtion_1.SelectedValue = GossipCreature.cond_1;
                _cbCondtion1Value_1.SetValue(GossipCreature.cond_1_val_1);
                _cbCondtion1Value_2.SetValue(GossipCreature.cond_1_val_2);
                _cbGossipCondtion_2.SelectedValue = GossipCreature.cond_2;
                _cbCondtion2Value_1.SetValue(GossipCreature.cond_2_val_1);
                _cbCondtion2Value_2.SetValue(GossipCreature.cond_2_val_2);

                MySQLConnenct.SelectNpcText(GossipCreature.TextID);
                _lvNpc_text.VirtualListSize = MySQLConnenct.npc_text.Count;
                _lvNpc_text.Refresh();
            }
        }

        private void _cbGossipCondtion_1_SelectedIndexChanged(object sender, EventArgs e)
        {
            Inscription.ShowGossipCondition(_cbGossipCondtion_1, _cbCondtion1Value_1, _cbCondtion1Value_2, lCondition1Val1, lCondition1Val2);
        }

        private void _cbGossipCondtion_2_SelectedIndexChanged(object sender, EventArgs e)
        {
            Inscription.ShowGossipCondition(_cbGossipCondtion_2, _cbCondtion2Value_1, _cbCondtion2Value_2, lCondition2Val1, lCondition2Val2);
        }

        private void _bCreateGossip_Click(object sender, EventArgs e)
        {
            string creatureID = "";
            rtbGossipMenuOut.Clear();
            rtbGossipMenuOut.ForeColor = Color.Blue;

            GossipMenu gossip = new GossipMenu();
            gossip.Entry = _tbGossipEntry.Text.ToInt32();
            gossip.TextID = _GossipTextID.Text.ToInt32();
            gossip.cond_1 = _cbGossipCondtion_1.GetIntValue();
            gossip.cond_1_val_1 = _cbCondtion1Value_1.GetIntValue();
            gossip.cond_1_val_2 = _cbCondtion1Value_2.GetIntValue();
            gossip.cond_2 = _cbGossipCondtion_2.GetIntValue();
            gossip.cond_2_val_1 = _cbCondtion2Value_1.GetIntValue();
            gossip.cond_2_val_2 = _cbCondtion2Value_2.GetIntValue();


            if (_tbCreatureGossip.Text.Contains(","))
                creatureID = "IN[" + _tbCreatureGossip.Text + "]";
            else
                creatureID = " = " + _tbCreatureGossip.Text;

            StringBuilder sb = new StringBuilder();
            if (_tbCreatureGossip.Text.Length > 0)
                sb.AppendFormatLine("UPDATE `creature_template` SET `gossip_menu_id`='{0}' WHERE `entry`{1};", gossip.Entry, creatureID);

            sb.AppendFormatLine("DELETE FROM `gossip_menu` WHERE (`entry`='{0}') AND (`textid` = '{1}');", gossip.Entry, gossip.TextID);
            sb.AppendFormatLine("INSERT INTO `gossip_menu` VALUES ('{0}', '{1}', '{2}', '{3}', '{4}', '{5}', '{6}', '{7}');",
                gossip.Entry, gossip.TextID, gossip.cond_1, gossip.cond_1_val_1, gossip.cond_1_val_2, gossip.cond_2, gossip.cond_2_val_1, gossip.cond_2_val_2);

            rtbGossipMenuOut.Text = sb.ToString();
            _bWriteFilesGossip.Enabled = true;
        }

        private void _bWriteFilesGossip_Click(object sender, EventArgs e)
        {
            using (StreamWriter sw = new StreamWriter("NEW_GOSSIP_SQL.sql", true, Encoding.UTF8))
                sw.WriteLine(rtbGossipMenuOut.Text);
            MySQLConnenct.Insert(rtbGossipMenuOut.Text);
        }

        private void _lvNpc_text_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (_lvNpc_text.SelectedIndices.Count > 0)
            {
                NPC_TEXT npc_text = MySQLConnenct.npc_text[_lvNpc_text.SelectedIndices[0]];
                _GossipTextID.Text = npc_text.ID.ToString();
            }
        }

        private void _bCreateSummon_Click(object sender, EventArgs e)
        {
            _rtbSummon.Clear();
            _rtbSummon.ForeColor = Color.Blue;

            StringBuilder sb = new StringBuilder();
            sb.AppendFormatLine("DELETE FROM `creature_ai_summons` WHERE id ='{0}';", _tbSummonID.Text);
            sb.AppendFormatLine("INSERT INTO `creature_ai_summons` VALUES ('{0}', '{1}', '{2}', '{3}', '{4}', '{5}', '{6}');",
            _tbSummonID.Text, _tbSummonX.Text, _tbSummonY.Text, _tbSummonZ.Text, _tbSummonO.Text, _tbSummonSps.Text, _tbSummonComment.Text);
            _rtbSummon.Text = sb.ToString();
        }

        private void _bWriteSummon_Click(object sender, EventArgs e)
        {
            using (StreamWriter sw = new StreamWriter("NEW_EVENTAI_SQL.sql", true, Encoding.UTF8))
                sw.WriteLine(_rtbSummon.Text);
            MySQLConnenct.Insert(_rtbSummon.Text);
        }

        private void _bFilterMenuOption_Click(object sender, EventArgs e)
        {
            if (_rbGossipMenuOption.Checked)
            {
                if (_tbfilterGossipMenu.Text.Length > 0)
                    MySQLConnenct.SelectGossipOption(_tbfilterGossipMenu.Text.ToInt32());
                else
                    MySQLConnenct.SelectGossipOption(0);
                _lvGossip_Option.VirtualListSize = MySQLConnenct.GossipMenuOption.Count;
                _lvGossip_Option.Refresh();
            }
        }

        private void _lvGossip_Option_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (_lvGossip_Option.SelectedIndices.Count > 0)
                ParseGossipOptionData(MySQLConnenct.GossipMenuOption[_lvGossip_Option.SelectedIndices[0]]);
        }

        private void ParseGossipOptionData(GossipMenuOption GossipMenu)
        {
            _tbGossipMenuID.Text = GossipMenu.menu_id.ToString();
            _tbGossipID.Text = GossipMenu.id.ToString();
            _tbGossipOptionText.Text = GossipMenu.option_text;
            _tbGossipNpcMenu.Text = GossipMenu.npc_menu_id.ToString();
            _tbGossipPOI_id.Text = GossipMenu.action_poi_id.ToString();
            _tbGossipAction.Text = GossipMenu.action_script_id.ToString();
            _tbGossipBoxCoded.Text = GossipMenu.box_coded.ToString();
            _tbGossipBoxMoney.Text = GossipMenu.box_money.ToString();
            _tbGossipBoxText.Text = GossipMenu.box_text;

            _cbGossipOptionIcon.SelectedValue = GossipMenu.option_icon;
            _cbGossipOptionID.SelectedValue = GossipMenu.option_id;
            _cbGossipOptionNpcFlag.SelectedValue = GossipMenu.npc_option_npcflag;

            _cbGossipOptionCondtion_1.SelectedValue = GossipMenu.cond[0];
            _cbOptionCondtion1Value_1.SetValue(GossipMenu.cond_val[0, 0]);
            _cbOptionCondtion1Value_2.SetValue(GossipMenu.cond_val[0, 1]);
            _cbGossipOptionCondtion_2.SelectedValue = GossipMenu.cond[1];
            _cbOptionCondtion2Value_1.SetValue(GossipMenu.cond_val[1, 0]);
            _cbOptionCondtion2Value_2.SetValue(GossipMenu.cond_val[1, 1]);
            _cbGossipOptionCondtion_3.SelectedValue = GossipMenu.cond[2];
            _cbOptionCondtion3Value_1.SetValue(GossipMenu.cond_val[2, 0]);
            _cbOptionCondtion3Value_2.SetValue(GossipMenu.cond_val[2, 1]);
        }

        private void _cbGossipOptionCondtion_1_SelectedIndexChanged(object sender, EventArgs e)
        {
            Inscription.ShowGossipCondition(_cbGossipOptionCondtion_1,_cbOptionCondtion1Value_1, 
                _cbOptionCondtion1Value_2, lGossipOptionCondtion1Val1, lGossipOptionCondtion1Val2);
        }

        private void _cbGossipOptionCondtion_2_SelectedIndexChanged(object sender, EventArgs e)
        {
            Inscription.ShowGossipCondition(_cbGossipOptionCondtion_2, _cbOptionCondtion2Value_1,
                _cbOptionCondtion2Value_2, lGossipOptionCondtion2Val1, lGossipOptionCondtion2Val2);
        }

        private void _cbGossipOptionCondtion_3_SelectedIndexChanged(object sender, EventArgs e)
        {
            Inscription.ShowGossipCondition(_cbGossipOptionCondtion_3, _cbOptionCondtion3Value_1,
                _cbOptionCondtion3Value_2, lGossipOptionCondtion3Val1, lGossipOptionCondtion3Val2);
        }

        private void _bGossipOptionCreate_Click(object sender, EventArgs e)
        {
            rtbGossipOptionMenuOut.Clear();
            rtbGossipOptionMenuOut.ForeColor = Color.Blue;

            GossipMenuOption gossip = new GossipMenuOption();
            gossip.menu_id  = _tbGossipMenuID.Text.ToInt32();
            gossip.id = _tbGossipID.Text.ToInt32();
            gossip.option_text = _tbGossipOptionText.Text;
            gossip.npc_menu_id = _tbGossipNpcMenu.Text.ToInt32();
            gossip.action_poi_id = _tbGossipPOI_id.Text.ToInt32();
            gossip.action_script_id = _tbGossipAction.Text.ToInt32();
            gossip.box_coded = _tbGossipBoxCoded.Text.ToInt32();
            gossip.box_money = _tbGossipBoxMoney.Text.ToInt32();
            gossip.box_text = _tbGossipBoxText.Text;
            gossip.option_icon = _cbGossipOptionIcon.GetIntValue();
            gossip.option_id = _cbGossipOptionID.GetIntValue();
            gossip.npc_option_npcflag = _cbGossipOptionNpcFlag.GetIntValue();
            gossip.cond[0] = _cbGossipOptionCondtion_1.GetIntValue();
            gossip.cond_val[0, 0] = _cbGossipOptionCondtion_1.GetIntValue();
            gossip.cond_val[0, 1] = _cbOptionCondtion1Value_2.GetIntValue();
            gossip.cond[1] = _cbGossipOptionCondtion_2.GetIntValue();
            gossip.cond_val[1, 0] = _cbOptionCondtion2Value_1.GetIntValue();
            gossip.cond_val[1, 1] = _cbOptionCondtion2Value_2.GetIntValue();
            gossip.cond[2] = _cbGossipOptionCondtion_3.GetIntValue();
            gossip.cond_val[2, 0] = _cbOptionCondtion3Value_1.GetIntValue();
            gossip.cond_val[2, 1] = _cbOptionCondtion3Value_2.GetIntValue();

            StringBuilder sb = new StringBuilder();
            sb.AppendFormatLine("DELETE FROM `gossip_menu_option` WHERE `entry`='{0}' AND `id`='{1}';", gossip.menu_id, gossip.id);
            sb.AppendFormatLine("INSERT INTO `gossip_menu_option` VALUES ('{0}', '{1}', '{2}', '{3}', '{4}', '{5}', '{6}', '{7}', '{8}'," +
                "'{9}', '{10}', '{11}', '{12}', '{13}', '{15}', '{16}', '{17}', '{18}', '{19}', '{20}');"
                , gossip.menu_id, gossip.id, gossip.option_icon, gossip.option_text.RemExc(), gossip.option_id, gossip.npc_option_npcflag, gossip.npc_menu_id
                , gossip.action_poi_id, gossip.action_script_id, gossip.box_coded, gossip.box_money, gossip.box_text, gossip.cond[0], gossip.cond_val[0, 0]
                , gossip.cond_val[0, 1], gossip.cond[1], gossip.cond_val[1, 0], gossip.cond_val[1, 1], gossip.cond[2], gossip.cond_val[2, 0], gossip.cond_val[2, 1]);

            rtbGossipOptionMenuOut.Text = sb.ToString();
        }

        private void _bGossipOptionRecord_Click(object sender, EventArgs e)
        {
            using (StreamWriter sw = new StreamWriter("NEW_GOSSIP_SQL.sql", true, Encoding.UTF8))
                sw.WriteLine(rtbGossipOptionMenuOut.Text);
            MySQLConnenct.Insert(rtbGossipOptionMenuOut.Text);
        }

        private void _bFilterNpcText_Click(object sender, EventArgs e)
        {
            MySQLConnenct.SelectNpcText(_tbFilterNpcText.Text.ToInt32());
            _lvNpcText.VirtualListSize = MySQLConnenct.npc_text.Count;
            _lvNpcText.Refresh();
        }

        private void _lvNpcText_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (_lvNpcText.SelectedIndices.Count > 0)
                ParseNpcTextData(MySQLConnenct.npc_text[_lvNpcText.SelectedIndices[0]]);
        }

        private void ParseNpcTextData(NPC_TEXT npc_text)
        {
            NPCTextHandler.DisplayValues(_gpText, npc_text);
        }

        private void bNpcTextRecord_Click(object sender, EventArgs e)
        {
            using (StreamWriter sw = new StreamWriter("NEW_NPC_TEXT_SQL.sql", true, Encoding.UTF8))
                sw.WriteLine(_gpText.Text);
            MySQLConnenct.Insert(_gpText.Text);
        }

        private void bNpcTextCreate_Click(object sender, EventArgs e)
        {
            rtbNpcTextOut.Clear();
            rtbNpcTextOut.ForeColor = Color.Blue;

            NPC_TEXT npc_text;
            npc_text = NPCTextHandler.LoadValues(_gpText);

            for (int x = 0; x < 8; x++)
            {
                npc_text.text0[x] = npc_text.text0[x].RemExc();
                npc_text.text1[x] = npc_text.text1[x].RemExc();
            }

            StringBuilder sb = new StringBuilder();
            sb.AppendFormatLine("DELETE FROM `npc_text` WHERE `ID`='{0}';", npc_text.ID);
            sb.AppendLine("INSERT INTO `npc_text` VALUES (" + npc_text.ToArrayString() + ");");

            rtbNpcTextOut.Text = sb.ToString();
        }

        public void FillListView()
        {
            _lvGossip_Option.FillColumnsFromDatabase("gossip_menu_option");
            _lvScripts.FillColumnsFromDatabase("creature_ai_scripts");
            _lvText.FillColumnsFromDatabase("creature_ai_texts");
            _lvGossip_menu.FillColumnsFromDatabase("gossip_menu");
            _lvNpc_text.FillColumnsFromDatabase("npc_text");
            _lvNpcText.FillColumnsFromDatabase("npc_text");
        }
    }
}