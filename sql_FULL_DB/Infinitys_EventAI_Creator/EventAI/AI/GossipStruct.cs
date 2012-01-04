using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace EventAI
{
    public struct GossipMenu
    {
        public int Entry;
        public int TextID;
        public int cond_1;
        public int cond_1_val_1;
        public int cond_1_val_2;
        public int cond_2;
        public int cond_2_val_1;
        public int cond_2_val_2;

        public string[] ToArray()
        {
            return new[]
            {
                Entry.ToString(),
                TextID.ToString(),
                cond_1.ToString(),
                cond_1_val_1.ToString(),
                cond_1_val_2.ToString(),
                cond_2.ToString(),
                cond_2_val_1.ToString(),
                cond_2_val_2.ToString()
            };
        }
    };

    public class NPC_TEXT
    {
        private string[] FinaleArray = new string[81];
        public int ID;
        public string[] text0;
        public string[] text1;
        public int[] lang;
        public float[] prob;
        public int[] em0;
        public int[] em1;
        public int[] em2;
        public int[] em3;
        public int[] em4;
        public int[] em5;

        public NPC_TEXT()
        {
            text0   = new string[8];
            text1   = new string[8];
            lang    = new int[8];
            prob    = new float[8];
            em0 = new int[8];
            em1 = new int[8];
            em2 = new int[8];
            em3 = new int[8];
            em4 = new int[8];
            em5 = new int[8];
        }

        public string[] ToArray()
        {
            int counter = 1;
            FinaleArray[0] = ID.ToString();
            for (int x = 0; x < 8; x++)
            {
                BuildFinalArray(DataArray(x), counter);
                counter += 10;
            }

            return FinaleArray;
        }

        public string ToArrayString()
        {
            StringBuilder sb = new StringBuilder();
            foreach (string value in ToArray())
            {
                sb.Append("'" + value + "'");
                sb.Append(",");
            }
            sb.Remove(sb.Length-1,1);
            return sb.ToString();
        }

        private string[] BuildFinalArray(String[] arr1, int count)
        {
            arr1.CopyTo(FinaleArray, count);
            return FinaleArray;
        }

        private string[] DataArray(int count)
        {
            string[] _dataArray = new string[10];
            _dataArray[0] = text0[count];
            _dataArray[1] = text1[count];
            _dataArray[2] = lang[count].ToString();
            _dataArray[3] = prob[count].ToString();
            _dataArray[4] = em0[count].ToString();
            _dataArray[5] = em1[count].ToString();
            _dataArray[6] = em2[count].ToString();
            _dataArray[7] = em3[count].ToString();
            _dataArray[8] = em4[count].ToString();
            _dataArray[9] = em5[count].ToString();
            return _dataArray;
        }
    }

    public struct GossipMenuCreature
    {
        public string Entry;
        public string Name;

        public string[] ToArray()
        {
            return new[]
            {
                Entry,
                Name,
            };
        }
    };

    public class GossipMenuOption
    {
        public int menu_id;
        public int id;
        public int option_icon;
        public string option_text;
        public int option_id;
        public int npc_option_npcflag;
        public int npc_menu_id;
        public int action_poi_id;
        public int action_script_id;
        public int box_coded;
        public int box_money;
        public string box_text;
        public int[] cond;
        public int[,] cond_val;

        public GossipMenuOption()
        {
            cond = new int[3];
            cond_val = new int[3, 2];
        }

        public string[] ToArray()
        {
            return new[]
            {
                menu_id.ToString(),
                id.ToString(),
                option_icon.ToString(),
                option_text,
                option_id.ToString(),
                npc_option_npcflag.ToString(),
                npc_menu_id.ToString(),
                action_poi_id.ToString(),
                action_script_id.ToString(),
                box_coded.ToString(),
                box_money.ToString(),
                box_text,
                cond[0].ToString(),
                cond_val[0,0].ToString(),
                cond_val[0,1].ToString(),
                cond[1].ToString(),
                cond_val[1,0].ToString(),
                cond_val[1,1].ToString(),
                cond[2].ToString(),
                cond_val[2,0].ToString(),
                cond_val[2,1].ToString()
            };
        }
    };
}