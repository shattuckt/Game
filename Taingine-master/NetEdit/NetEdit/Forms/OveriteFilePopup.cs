using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NetEdit.Forms
{
    public partial class OveriteFilePopup : PopupForm
    {
        public OveriteFilePopup()
        {
            InitializeComponent();
            MainLabelText = "File already exists. Do you want to overite it?";
            this.DialogResult = DialogResult.Cancel;
        }


        private void OveriteFilePopup_Yes_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Yes;
            this.Close();
        }
    }
}
