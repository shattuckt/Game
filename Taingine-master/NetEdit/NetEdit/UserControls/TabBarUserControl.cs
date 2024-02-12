using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NetEdit
{
    public partial class TabBarUserControl : UserControl
    {
        public TabBarUserControl()
        {
            InitializeComponent();
            fileMenueStrip.Renderer = new ContextMenueStripRenderer();
            editMenuStrip.Renderer = new ContextMenueStripRenderer();
        }

        #region TabBar Button Controls
        private void TabBar_FileButtonClicked(object sender, EventArgs e)
        {
            Button btnSender = (Button)sender;
            Point ptLowerLeft = new Point(0, btnSender.Height);
            ptLowerLeft = btnSender.PointToScreen(ptLowerLeft);
            fileMenueStrip.Show(ptLowerLeft);
        }


        private void TabBar_EditButtonClicked(object sender, EventArgs e)
        {
            Button btnSender = (Button)sender;
            Point ptLowerLeft = new Point(0, btnSender.Height);
            ptLowerLeft = btnSender.PointToScreen(ptLowerLeft);
            editMenuStrip.Show(ptLowerLeft);
        }
        #endregion

        #region TabBar FileMenue Controls

        private void TabBar_NewMenuItem_Click(object sender, EventArgs e)
        {
            FileHelper.CheckFileStatus();
        }


        private void TabBar_OpenMenuItem_Click(object sender, EventArgs e)
        {
            if (FileHelper.CheckFileStatus() == DialogResult.Cancel) return;

            DialogResult result = openFileDialog.ShowDialog();
            if (result == DialogResult.OK)
            {
                string fileLocation = openFileDialog.FileName;
                string fileName = openFileDialog.SafeFileName;

                if (String.IsNullOrEmpty(fileName) ||
                String.IsNullOrEmpty(fileLocation) ||
                !System.IO.File.Exists(fileLocation))
                {
                    return;
                }

                FileHelper.OpenFile(fileLocation);
                EventHub.OnLoadNeuronView(this, new EventArgs());
            }
        }


        private void TabBar_SaveMenuItem_Click(object sender, EventArgs e)
        {
            FileHelper.SaveFile();
        }


        private void TabBar_SaveAsMenuItem_Click(object sender, EventArgs e)
        {
            FileHelper.SaveFileAs();
        }


        private void TabBar_ExitMenuItem_Click(object sender, EventArgs e)
        {
            
        }

        #endregion

        #region TabBar EditMenue Controls

        private void TabBar_AddNeuronMenuItem_Click(object sender, EventArgs e)
        {

        }


        private void TabBar_AddInputNeuronMenuItem_Click(object sender, EventArgs e)
        {
            AddNeuronEventArgs eventArgs = new AddNeuronEventArgs();
            eventArgs.NeuronType = NeuronType.Input;
            eventArgs.Name = "temp";

            EventHub.OnAddNeuron(this, eventArgs);
        }


        private void TabBar_AddHidenNeuronMenuItem_Click(object sender, EventArgs e)
        {
            AddNeuronEventArgs eventArgs = new AddNeuronEventArgs();
            eventArgs.NeuronType = NeuronType.Hiden;
            eventArgs.Name = "temp";

            EventHub.OnAddNeuron(this, eventArgs);
        }


        private void TabBar_AddOutputNeuronMenuItem_Click(object sender, EventArgs e)
        {
            AddNeuronEventArgs eventArgs = new AddNeuronEventArgs();
            eventArgs.NeuronType = NeuronType.Output;
            eventArgs.Name = "temp";

            EventHub.OnAddNeuron(this, eventArgs);
        }


        private void TabBar_AddSynapseMenuItem_Click(object sender, EventArgs e)
        {

        }

        #endregion

        private void AddNeuron()
        {

        }

    }
}
