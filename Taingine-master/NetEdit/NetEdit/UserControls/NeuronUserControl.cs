using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using NetEdit.Forms;

namespace NetEdit
{
    public partial class NeuronUserControl : UserControl
    {

        #region Private Members

        private string _tag;
        private int _arrPosition;
        private NeuronType _neuronType;
        private GraphicsPath path = new GraphicsPath();

        #endregion


        #region Exposed Members
        public string NeuronTag
        {
            get => _tag;
            set => _tag = value;
        }

        public int ArrPosition
        {
            get => _arrPosition;
            set => _arrPosition = value;
        }

        public NeuronType NeuronType
        {
            get => _neuronType;
            set => _neuronType = value;
        }

        #endregion

        public NeuronUserControl()
        {
            InitializeComponent();
            path.AddEllipse(0, 0, this.ClientSize.Width, this.ClientSize.Height);
            this.Region = new Region(path);

            this.BackColor = Color.FromArgb(139, 87, 92);
            //DrawInnerCircle();
        }

        private void DrawInnerCircle()
        {
            Pen pen = new Pen(Color.FromArgb(69, 73, 85));
            Graphics formGraphics = this.CreateGraphics();
            formGraphics.DrawEllipse(pen, new Rectangle(5, 5, 20, 20));

            pen.Dispose();
            formGraphics.Dispose();
        }

        private void NeuronUserControl_Click(object sender, EventArgs e)
        {
            EditorHelper.ActiveNeuron = this;
            this.BackColor = Color.White;
        }

        private void NeuronUserControl_DoubleClick(object sender, EventArgs e)
        {
            using (var form = new SynapseEditForm())
            {
                form.ShowDialog();
            }
        }

        public void NeuronUserControl_ChangeColor()
        {
            this.BackColor = Color.FromArgb(139, 87, 92);
        }
    }
}
