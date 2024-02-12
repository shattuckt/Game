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
    public partial class AddSyanpseForm : MovableResizableForm
    {
        public AddSyanpseForm()
        {
            InitializeComponent();
        }

        private void AddButton_Click(object sender, EventArgs e)
        {
            AddSynapseEventArgs args = new AddSynapseEventArgs { Start = (int)startNumeric.Value, Target = (int)targetNumeric.Value, Weight = Double.Parse(weightTextBox.Text)};
            EventHub.OnAddSynapse(this, args);
        }
    }
}
