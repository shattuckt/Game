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
    public partial class MainForm : MovableResizableForm
    {
        #region Private Members

        #endregion

        public MainForm()
        {
            InitializeComponent();
            this.FormClosing += MainForm_FormClosing;
            this.Resize += MainForm_Resize;
            EventHub.AddNeuron += AddNeuronToTray;
            EventHub.LoadNeuronView += MainForm_LoadNeuronView;
            Network.InitilizeEvents();
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if(FileHelper.CheckFileStatus() == DialogResult.Cancel)
                e.Cancel = true;
        }


        public void AddNeuronToTray(object sender, AddNeuronEventArgs eventArgs)
        {
            //NeuronUserControl neuron = new NeuronUserControl();
            switch (eventArgs.NeuronType)
            {
                case NeuronType.Input:
                    //neuron.NeuronTag = eventArgs.Name;
                    //inputNeuronTray.AddNeuron(neuron);
                    inputNeuronTray.AddNeuron(eventArgs.Name, eventArgs.NeuronType);
                    break;
                case NeuronType.Hiden:
                    hiddenNeuronTray.AddNeuron(eventArgs.Name, eventArgs.NeuronType);
                    break;
                case NeuronType.Output:
                    //neuron.NeuronTag = eventArgs.Name;
                    //outputNeuronTray.AddNeuron(neuron);
                    outputNeuronTray.AddNeuron(eventArgs.Name, eventArgs.NeuronType);
                    break;
            }

            this.Invalidate();
        }

        protected override void DoneResizing()
        {
            inputNeuronTray.RedrawNeurons();
            outputNeuronTray.RedrawNeurons();
        }

        private void MainForm_Paint(object sender, PaintEventArgs e)
        {
            var inputNeruonList = inputNeuronTray.NeuronList;
            var outputNeruonList = outputNeuronTray.NeuronList;
            Pen pen = new Pen(Brushes.White);
            pen.Width = 6f;

            foreach(var inNeuron in inputNeruonList)
            {
                foreach(var outNeuron in outputNeruonList)
                {

                    Point p1 = new Point(inNeuron.Right, inNeuron.Location.Y + 55);

                    Point p2 = new Point(outNeuron.Left + (outputNeuronTray.Location.X + outputNeuronTray.Width / 2), outNeuron.Location.Y + 55);

                    e.Graphics.DrawLine(pen, p1, p2);
                }
            }
            pen.Dispose();
        }

        private void MainForm_Resize(object sender, EventArgs e)
        {
            this.Invalidate();
        }


        private void MainForm_LoadNeuronView(object sender, EventArgs e)
        {
            inputNeuronTray.RemoveNeurons();
            outputNeuronTray.RemoveNeurons();
            EditorHelper.Reset();

            foreach(var inName in Network.InputTags.ToList())
            {
                inputNeuronTray.AddNeuronDescrete(inName, NeuronType.Input);
            }

            foreach (var outName in Network.OutputTags.ToList())
            {
                outputNeuronTray.AddNeuronDescrete(outName, NeuronType.Output);
            }

            this.Invalidate();
        }
    }
}
