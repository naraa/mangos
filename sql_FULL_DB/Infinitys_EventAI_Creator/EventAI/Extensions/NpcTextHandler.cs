using System;
using System.Windows.Forms;

namespace EventAI
{
    public static class NPCTextHandler
    {
        public static NPC_TEXT LoadValues(GroupBox gb)
        {
            NPC_TEXT npc_text = new NPC_TEXT();
            foreach (var ctrl in gb.Controls)
            {
                if (ctrl is TextBox)
                {
                    TextBox tb = (TextBox)ctrl;
                    if (tb.Name.Contains("ID"))         npc_text.ID = tb.Text.ToInt32();
                    if (tb.Name.Contains("text0_0"))    npc_text.text0[0] = tb.Text;
                    if (tb.Name.Contains("text0_1"))    npc_text.text1[0] = tb.Text;
                    if (tb.Name.Contains("Prob0"))      npc_text.prob[0] = tb.Text.ToFloat();
                    if (tb.Name.Contains("Em0_0"))      npc_text.em0[0] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em0_1"))      npc_text.em1[0] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em0_2"))      npc_text.em2[0] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em0_3"))      npc_text.em3[0] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em0_4"))      npc_text.em4[0] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em0_5"))      npc_text.em5[0] = tb.Text.ToInt32();
                    
                    if (tb.Name.Contains("text1_0"))    npc_text.text0[1] = tb.Text;
                    if (tb.Name.Contains("text1_1"))    npc_text.text1[1] = tb.Text;
                    if (tb.Name.Contains("Prob1"))      npc_text.prob[1] = tb.Text.ToFloat();
                    if (tb.Name.Contains("Em1_0"))      npc_text.em0[1] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em1_1"))      npc_text.em1[1] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em1_2"))      npc_text.em2[1] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em1_3"))      npc_text.em3[1] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em1_4"))      npc_text.em4[1] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em1_5"))      npc_text.em5[1] = tb.Text.ToInt32();
                    
                    if (tb.Name.Contains("text2_0"))    npc_text.text0[2] = tb.Text;
                    if (tb.Name.Contains("text2_1"))    npc_text.text1[2] = tb.Text;
                    if (tb.Name.Contains("Prob2"))      npc_text.prob[2] = tb.Text.ToFloat();
                    if (tb.Name.Contains("Em2_0"))      npc_text.em0[2] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em2_1"))      npc_text.em1[2] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em2_2"))      npc_text.em2[2] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em2_3"))      npc_text.em3[2] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em2_4"))      npc_text.em4[2] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em2_5"))      npc_text.em5[2] = tb.Text.ToInt32();
                    
                    if (tb.Name.Contains("text3_0"))    npc_text.text0[3] = tb.Text;
                    if (tb.Name.Contains("text3_1"))    npc_text.text1[3] = tb.Text;
                    if (tb.Name.Contains("Prob3"))      npc_text.prob[3] = tb.Text.ToFloat();
                    if (tb.Name.Contains("Em3_0"))      npc_text.em0[3] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em3_1"))      npc_text.em1[3] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em3_2"))      npc_text.em2[3] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em3_3"))      npc_text.em3[3] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em3_4"))      npc_text.em4[3] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em3_5"))      npc_text.em5[3] = tb.Text.ToInt32();
                    
                    if (tb.Name.Contains("text4_0"))    npc_text.text0[4] = tb.Text;
                    if (tb.Name.Contains("text4_1"))    npc_text.text1[4] = tb.Text;
                    if (tb.Name.Contains("Prob4"))      npc_text.prob[4] = tb.Text.ToFloat();
                    if (tb.Name.Contains("Em4_0"))      npc_text.em0[4] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em4_1"))      npc_text.em1[4] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em4_2"))      npc_text.em2[4] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em4_3"))      npc_text.em3[4] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em4_4"))      npc_text.em4[4] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em4_5"))      npc_text.em5[4] = tb.Text.ToInt32();

                    if (tb.Name.Contains("text5_0"))    npc_text.text0[5] = tb.Text;
                    if (tb.Name.Contains("text5_1"))    npc_text.text1[5] = tb.Text;
                    if (tb.Name.Contains("Prob5"))      npc_text.prob[5] = tb.Text.ToFloat();
                    if (tb.Name.Contains("Em5_0"))      npc_text.em0[5] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em5_1"))      npc_text.em1[5] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em5_2"))      npc_text.em2[5] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em5_3"))      npc_text.em3[5] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em5_4"))      npc_text.em4[5] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em5_5"))      npc_text.em5[5] = tb.Text.ToInt32();

                    if (tb.Name.Contains("text6_0"))    npc_text.text0[6] = tb.Text;
                    if (tb.Name.Contains("text6_1"))    npc_text.text1[6] = tb.Text;
                    if (tb.Name.Contains("Prob6"))      npc_text.prob[6] = tb.Text.ToFloat();
                    if (tb.Name.Contains("Em6_0"))      npc_text.em0[6] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em6_1"))      npc_text.em1[6] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em6_2"))      npc_text.em2[6] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em6_3"))      npc_text.em3[6] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em6_4"))      npc_text.em4[6] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em6_5"))      npc_text.em5[6] = tb.Text.ToInt32();

                    if (tb.Name.Contains("text7_0"))    npc_text.text0[7] = tb.Text;
                    if (tb.Name.Contains("text7_1"))    npc_text.text1[7] = tb.Text;
                    if (tb.Name.Contains("Prob7"))      npc_text.prob[7] = tb.Text.ToFloat();
                    if (tb.Name.Contains("Em7_0"))      npc_text.em0[7] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em7_1"))      npc_text.em1[7] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em7_2"))      npc_text.em2[7] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em7_3"))      npc_text.em3[7] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em7_4"))      npc_text.em4[7] = tb.Text.ToInt32();
                    if (tb.Name.Contains("Em7_5"))      npc_text.em5[7] = tb.Text.ToInt32();
                }
                if (ctrl is ComboBox)
                {
                    ComboBox cb = (ComboBox)ctrl;
                    if (cb.Name.Contains("Lang0")) npc_text.lang[0] = cb.SelectedValue.ToInt32();
                    if (cb.Name.Contains("Lang1")) npc_text.lang[1] = cb.SelectedValue.ToInt32();
                    if (cb.Name.Contains("Lang2")) npc_text.lang[2] = cb.SelectedValue.ToInt32();
                    if (cb.Name.Contains("Lang3")) npc_text.lang[3] = cb.SelectedValue.ToInt32();
                    if (cb.Name.Contains("Lang4")) npc_text.lang[4] = cb.SelectedValue.ToInt32();
                    if (cb.Name.Contains("Lang5")) npc_text.lang[5] = cb.SelectedValue.ToInt32();
                    if (cb.Name.Contains("Lang6")) npc_text.lang[6] = cb.SelectedValue.ToInt32();
                    if (cb.Name.Contains("Lang7")) npc_text.lang[7] = cb.SelectedValue.ToInt32();
                }
            }

            return npc_text;
        }

        public static void DisplayValues(GroupBox gb, NPC_TEXT npc_text)
        {
            foreach (var ctrl in gb.Controls)
            {
                if (ctrl is TextBox)
                {
                    TextBox tb = (TextBox)ctrl;
                    if (tb.Name.Contains("ID"))         tb.Text = npc_text.ID.ToString();
                    if (tb.Name.Contains("text0_0"))    tb.Text = npc_text.text0[0];
                    if (tb.Name.Contains("text0_1"))    tb.Text = npc_text.text1[0];
                    if (tb.Name.Contains("Prob0"))      tb.Text = npc_text.prob[0].ToString();
                    if (tb.Name.Contains("Em0_0"))      tb.Text = npc_text.em0[0].ToString();
                    if (tb.Name.Contains("Em0_1"))      tb.Text = npc_text.em1[0].ToString();
                    if (tb.Name.Contains("Em0_2"))      tb.Text = npc_text.em2[0].ToString();
                    if (tb.Name.Contains("Em0_3"))      tb.Text = npc_text.em3[0].ToString();
                    if (tb.Name.Contains("Em0_4"))      tb.Text = npc_text.em4[0].ToString();
                    if (tb.Name.Contains("Em0_5"))      tb.Text = npc_text.em5[0].ToString();

                    if (tb.Name.Contains("text1_0")) tb.Text = npc_text.text0[1];
                    if (tb.Name.Contains("text1_1")) tb.Text = npc_text.text1[1];
                    if (tb.Name.Contains("Prob1")) tb.Text = npc_text.prob[1].ToString();
                    if (tb.Name.Contains("Em1_0")) tb.Text = npc_text.em0[1].ToString();
                    if (tb.Name.Contains("Em1_1")) tb.Text = npc_text.em1[1].ToString();
                    if (tb.Name.Contains("Em1_2")) tb.Text = npc_text.em2[1].ToString();
                    if (tb.Name.Contains("Em1_3")) tb.Text = npc_text.em3[1].ToString();
                    if (tb.Name.Contains("Em1_4")) tb.Text = npc_text.em4[1].ToString();
                    if (tb.Name.Contains("Em1_5")) tb.Text = npc_text.em5[1].ToString();

                    if (tb.Name.Contains("text2_0")) tb.Text = npc_text.text0[2];
                    if (tb.Name.Contains("text2_1")) tb.Text = npc_text.text1[2];
                    if (tb.Name.Contains("Prob2")) tb.Text = npc_text.prob[2].ToString();
                    if (tb.Name.Contains("Em2_0")) tb.Text = npc_text.em0[2].ToString();
                    if (tb.Name.Contains("Em2_1")) tb.Text = npc_text.em1[2].ToString();
                    if (tb.Name.Contains("Em2_2")) tb.Text = npc_text.em2[2].ToString();
                    if (tb.Name.Contains("Em2_3")) tb.Text = npc_text.em3[2].ToString();
                    if (tb.Name.Contains("Em2_4")) tb.Text = npc_text.em4[2].ToString();
                    if (tb.Name.Contains("Em2_5")) tb.Text = npc_text.em5[2].ToString();

                    if (tb.Name.Contains("text3_0")) tb.Text = npc_text.text0[3];
                    if (tb.Name.Contains("text3_1")) tb.Text = npc_text.text1[3];
                    if (tb.Name.Contains("Prob3")) tb.Text = npc_text.prob[3].ToString();
                    if (tb.Name.Contains("Em3_0")) tb.Text = npc_text.em0[3].ToString();
                    if (tb.Name.Contains("Em3_1")) tb.Text = npc_text.em1[3].ToString();
                    if (tb.Name.Contains("Em3_2")) tb.Text = npc_text.em2[3].ToString();
                    if (tb.Name.Contains("Em3_3")) tb.Text = npc_text.em3[3].ToString();
                    if (tb.Name.Contains("Em3_4")) tb.Text = npc_text.em4[3].ToString();
                    if (tb.Name.Contains("Em3_5")) tb.Text = npc_text.em5[3].ToString();

                    if (tb.Name.Contains("text4_0")) tb.Text = npc_text.text0[4];
                    if (tb.Name.Contains("text4_1")) tb.Text = npc_text.text1[4];
                    if (tb.Name.Contains("Prob4")) tb.Text = npc_text.prob[4].ToString();
                    if (tb.Name.Contains("Em4_0")) tb.Text = npc_text.em0[4].ToString();
                    if (tb.Name.Contains("Em4_1")) tb.Text = npc_text.em1[4].ToString();
                    if (tb.Name.Contains("Em4_2")) tb.Text = npc_text.em2[4].ToString();
                    if (tb.Name.Contains("Em4_3")) tb.Text = npc_text.em3[4].ToString();
                    if (tb.Name.Contains("Em4_4")) tb.Text = npc_text.em4[4].ToString();
                    if (tb.Name.Contains("Em4_5")) tb.Text = npc_text.em5[4].ToString();

                    if (tb.Name.Contains("text5_0")) tb.Text = npc_text.text0[5];
                    if (tb.Name.Contains("text5_1")) tb.Text = npc_text.text1[5];
                    if (tb.Name.Contains("Prob5")) tb.Text = npc_text.prob[5].ToString();
                    if (tb.Name.Contains("Em5_0")) tb.Text = npc_text.em0[5].ToString();
                    if (tb.Name.Contains("Em5_1")) tb.Text = npc_text.em1[5].ToString();
                    if (tb.Name.Contains("Em5_2")) tb.Text = npc_text.em2[5].ToString();
                    if (tb.Name.Contains("Em5_3")) tb.Text = npc_text.em3[5].ToString();
                    if (tb.Name.Contains("Em5_4")) tb.Text = npc_text.em4[5].ToString();
                    if (tb.Name.Contains("Em5_5")) tb.Text = npc_text.em5[5].ToString();

                    if (tb.Name.Contains("text6_0")) tb.Text = npc_text.text0[6];
                    if (tb.Name.Contains("text6_1")) tb.Text = npc_text.text1[6];
                    if (tb.Name.Contains("Prob6")) tb.Text = npc_text.prob[6].ToString();
                    if (tb.Name.Contains("Em6_0")) tb.Text = npc_text.em0[6].ToString();
                    if (tb.Name.Contains("Em6_1")) tb.Text = npc_text.em1[6].ToString();
                    if (tb.Name.Contains("Em6_2")) tb.Text = npc_text.em2[6].ToString();
                    if (tb.Name.Contains("Em6_3")) tb.Text = npc_text.em3[6].ToString();
                    if (tb.Name.Contains("Em6_4")) tb.Text = npc_text.em4[6].ToString();
                    if (tb.Name.Contains("Em6_5")) tb.Text = npc_text.em5[6].ToString();

                    if (tb.Name.Contains("text7_0")) tb.Text = npc_text.text0[7];
                    if (tb.Name.Contains("text7_1")) tb.Text = npc_text.text1[7];
                    if (tb.Name.Contains("Prob7")) tb.Text = npc_text.prob[7].ToString();
                    if (tb.Name.Contains("Em7_0")) tb.Text = npc_text.em0[7].ToString();
                    if (tb.Name.Contains("Em7_1")) tb.Text = npc_text.em1[7].ToString();
                    if (tb.Name.Contains("Em7_2")) tb.Text = npc_text.em2[7].ToString();
                    if (tb.Name.Contains("Em7_3")) tb.Text = npc_text.em3[7].ToString();
                    if (tb.Name.Contains("Em7_4")) tb.Text = npc_text.em4[7].ToString();
                    if (tb.Name.Contains("Em7_5")) tb.Text = npc_text.em5[7].ToString();
                }
                if (ctrl is ComboBox)
                {
                    ComboBox cb = (ComboBox)ctrl;
                    if (cb.Name.Contains("Lang0")) cb.SelectedValue = npc_text.lang[0];
                    if (cb.Name.Contains("Lang1")) cb.SelectedValue = npc_text.lang[1];
                    if (cb.Name.Contains("Lang2")) cb.SelectedValue = npc_text.lang[2];
                    if (cb.Name.Contains("Lang3")) cb.SelectedValue = npc_text.lang[3];
                    if (cb.Name.Contains("Lang4")) cb.SelectedValue = npc_text.lang[4];
                    if (cb.Name.Contains("Lang5")) cb.SelectedValue = npc_text.lang[5];
                    if (cb.Name.Contains("Lang6")) cb.SelectedValue = npc_text.lang[6];
                    if (cb.Name.Contains("Lang7")) cb.SelectedValue = npc_text.lang[7];
                }
            }
        }
    }
}