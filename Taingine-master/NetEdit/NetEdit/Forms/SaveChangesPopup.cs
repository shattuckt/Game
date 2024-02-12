using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NetEdit
{
    public partial class SaveChangesPopup : PopupForm
    {
        public SaveChangesPopup()
        {
            InitializeComponent();
            MainLabelText = "Do you wish to save your changes before closing?";
            this.DialogResult = DialogResult.Cancel;
            InformationBarVisable = false;
            SecondaryLabelVisable = false;
            TitleBarBackgroundColor = Color.FromArgb(158, 158, 158);
        }


        private void DiscardChangesPopup_Yes_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Yes;
            this.Close();
        }


        private void DiscardChangesPopup_No_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.No;
            this.Close();
        }
    }
}
