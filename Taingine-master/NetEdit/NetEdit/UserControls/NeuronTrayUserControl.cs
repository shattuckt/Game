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
    public partial class NeuronTrayUserControl : UserControl
    {
        private int X;


        #region Private Members

        private int panSign = 1;
        private Point offset;
        private bool moveing = false;
        private List<NeuronUserControl> neuronList = new List<NeuronUserControl>();

        #endregion

        #region Exposed Members

        [Category("ResizeBar Dock Style")]
        [Description("Where the ResizeBar docks")]
        public DockStyle ResizeBarDockStyle
        {
            get => resizeBar.Dock;
            set
            {
                resizeBar.Dock = value;
                if (value == DockStyle.Left) panSign = -1;
                else panSign = 1;
            }
        }

        
        public List<NeuronUserControl> NeuronList
        {
            get => neuronList;
            //set => neuronList = value;
        }

        #endregion


        public NeuronTrayUserControl()
        {
            InitializeComponent();
            X = ((Width - 8) / 2) - 25;
            neuronList = new List<NeuronUserControl>();
        }

        #region ResizeBar Controls

        public void NeuronTray_ResizeBar_MouseEnter(object sender, EventArgs e)
        {
            this.Cursor = Cursors.SizeWE;
        }


        public void NeuronTray_ResizeBar_MouseLeave(object sender, EventArgs e)
        {
            this.Cursor = Cursors.Default;
        }


        private void NeuronTray_ResizeBar_MouseDown(object sender, MouseEventArgs e)
        {
            offset = new Point(e.X, e.Y);
            moveing = true;
        }


        private void NeuronTray_ResizeBar_MouseMove(object sender, MouseEventArgs e)
        {
            if (moveing)
            {
                int newWidth = this.Width;
                newWidth += (e.X - offset.X) * panSign;
                this.Width = newWidth;
            }
        }


        private void NeuronTray_ResizeBar_MouseUp(object sender, MouseEventArgs e)
        {
            if (moveing) moveing = false;
        }

        #endregion

        public void AddNeuron(string name, NeuronType type)
        {
            var neuron = AddNeuronDescrete(name, type);

            EditorHelper.ActiveNeuron = neuron;
        }


        public NeuronUserControl AddNeuronDescrete(string name, NeuronType type)
        {
            NeuronUserControl neuron = new NeuronUserControl();
            neuron.NeuronTag = name;
            neuron.ArrPosition = neuronList.Count;
            neuron.NeuronType = type;
            neuronList.Add(neuron);

            RedrawNeurons();

            Controls.Add(neuron);
            return neuron;
        }


        public void RedrawNeurons()
        {
            int drawableHeight = this.Height - 50;
            double positionChange = 1 / (double)(neuronList.Count + 1);
            for (int i = 0; i < neuronList.Count; i++)
            {
                int y = (int)((double)Height * positionChange * (i + 1)) - 25;
                neuronList[i].Location = new Point(X, y);
            }
        }


        public void RemoveNeurons()
        {
            foreach(var neuron in neuronList)
            {
                Controls.Remove(neuron);
            }
            neuronList = new List<NeuronUserControl>();
        }
    }
}
