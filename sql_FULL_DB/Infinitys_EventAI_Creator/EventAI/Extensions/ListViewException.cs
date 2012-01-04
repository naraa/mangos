using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Reflection;
using System.Collections.Specialized;

namespace EventAI
{
    public static class ListViewException
    {
        public static void SetColumns<T>(this ListView lv)
        {
            lv.Columns.Clear();
            lv.View = View.Details;

            foreach (FieldInfo element in typeof(T).GetFields())
            {
                ColumnHeader ch = new ColumnHeader();
                ch.Width = element.FieldType.FullName == "System.String" ? 300 : 80;
                ch.Name = typeof(T).Name + "_" + element.Name;
                ch.Text = element.Name;

                lv.Columns.Add(ch);
            }
        }

        public static void FillColumnsFromDatabase(this ListView lv, string sTable)
        {
            lv.Columns.Clear();
            lv.View = View.Details;

            StringCollection fldCol = new StringCollection();
            fldCol = MySQLConnenct.GetColumns(sTable);

            if (fldCol == null)
                return;

            foreach (string Column in fldCol)
            {
                ColumnHeader ch = new ColumnHeader();
                ch.Text = Column;
                lv.Columns.Add(ch);
            }
        }
    }
}
