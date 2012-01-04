using System;
using System.Windows.Forms;
using System.Drawing;

namespace EventAI
{
    /// <summary>
    /// Creating buttons for pre-printed forms
    /// </summary>
    public class ButtonHandler
    {
        private ComboBox _combobox;
        private ComboBox _comboboxAdditional;
        private Button   _button;
        private Type     _type;
        private BType    _bType;
        private int      _additionalValue;

        private uint ComboboxValue
        {
            get { return (uint)_combobox.GetIntValue(); }
        }

        private Point ButtonLocation
        {
            get { return new Point(_combobox.Location.X + _combobox.Size.Width, _combobox.Location.Y - 1); }
        }

        private Size ButtonSize 
        { 
            get { return new Size(58, 23); } 
        }

        private Size ComboboxSize
        {
            get { return new Size(180, 21); }
        }

        private FormMain ParentForm
        {
            get { return (FormMain)_combobox.FindForm(); }
        }

        /// <summary>
        /// Creates a button to search for values in a collection
        /// </summary>
        /// <param name="combobox">Element around which to create a button</param>
        /// <param name="btype">Button type</param>
        public ButtonHandler(ComboBox combobox, BType btype, ComboBox combobox2, int combobox2Val)
        {
            _combobox           = combobox;
            _comboboxAdditional = combobox2;
            _additionalValue    = combobox2Val;
            _combobox.Size      = ComboboxSize;
            _bType              = btype;

            CreateButton("Search");
        }

        /// <summary>
        /// Creates a button to call the form of counting flags 
        /// </summary>
        /// <typeparam name="T">Type flag</typeparam>
        /// <param name="combobox">Yelement around which to create a button</param>
        public ButtonHandler(ComboBox combobox, Type type, ComboBox combobox2, int combobox2Val)
        {
            _type               = type;
            _combobox           = combobox;
            _comboboxAdditional = combobox2;
            _additionalValue    = combobox2Val;
            _combobox.Size      = ComboboxSize;
            _bType              = BType.FLAG;

            CreateButton("Flag");
        }

        private void CreateButton(string text)
        {
            _button             = new Button();
            _button.Size        = ButtonSize;
            _button.Location    = ButtonLocation;
            _button.Text        = text;
            _button.Click      += new System.EventHandler(ShowForm);
            _button.UseVisualStyleBackColor = true;

            ((GroupBox)_combobox.Parent).Controls.Add(_button);
        }

        private void ShowForm(object sender, EventArgs e)
        {
            switch (_bType)
            {
                case BType.SPELL:
                    {
                        FormSearchSpell _form = new FormSearchSpell(ComboboxValue);
                        _form.ShowDialog();
                        if(_form.DialogResult == DialogResult.OK)
                            _combobox.SetValue(_form.Spell.ID);
                        _form.Dispose();
                    }
                    break;
                case BType.FLAG:
                    {
                        FormCalculateFlags _form = new FormCalculateFlags(_type, ComboboxValue, String.Empty);
                        _form.ShowDialog();
                        if (_form.DialogResult == DialogResult.OK)
                            _combobox.SetValue(_form.Flags);
                        _form.Dispose();
                    }
                    break;
                case BType.TEXT:
                    {
                        MySQLConnenct.SelectAIText();
                        ParentForm._tPanel.SelectedIndex = 1;
                    }
                    break;
                case BType.SUMMON:
                    {
                        MySQLConnenct.SelectAIText();
                        ParentForm._tPanel.SelectedIndex = 2;
                    }
                    break;
                default:
                    {
                        FormDbSearch _form = new FormDbSearch(_bType, ComboboxValue);
                        _form.ShowDialog();
                        if (_form.DialogResult == DialogResult.OK)
                            _combobox.SetValue(_form.Value);
                        _form.Dispose();
                    }
                    break;
            }

            if (_comboboxAdditional != null)
                _comboboxAdditional.SetValue(_additionalValue);

        }

        ~ButtonHandler()
        {
            try
            {
                _button.Dispose();
            }
            catch 
            { 
            }
        }
    }

    /// <summary>
    /// Specifies the type caused by the form
    /// </summary>
    public enum BType
    {
        /// <summary>
        /// Search Form Spell
        /// </summary>
        SPELL,
        /// <summary>
        /// Search form beings 
        /// </summary>
        CREATURE,
        /// <summary>
        /// Search form objects 
        /// </summary>
        ITEM,
        /// <summary>
        /// Form Search Jobs 
        /// </summary>
        QUEST,
        /// <summary>
        /// Search form flag 
        /// </summary>
        FLAG,
        /// <summary>
        /// Opens a tab with lyrics 
        /// </summary>
        TEXT,
        /// <summary>
        /// 
        /// </summary>
        SUMMON,
    };
}
