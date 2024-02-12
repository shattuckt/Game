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
    public partial class PopupForm : MovableResizableForm
    {
        #region Exposed Members

        [Category("PopupForm")]
        [Description("The main message displayed.")]
        public string MainLabelText
        {
            get => mainLabel.Text;
            set => mainLabel.Text = value;
        }

        [Category("PopupForm")]
        [Description("The secondary message displayed.")]
        public string SecondaryLabelText
        {
            get => secondaryLabel.Text;
            set => secondaryLabel.Text = value;
        }

        [Category("PopupForm")]
        [Description("Wether or not the secondary label is visable.")]
        public bool SecondaryLabelVisable
        {
            get => secondaryLabel.Visible;
            set => secondaryLabel.Visible = value;
        }

        #endregion


        public PopupForm()
        {
            InitializeComponent();
            TitleBarText = "NetEdit";
        }


        private void PopupForm_Cancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }
    }
}
