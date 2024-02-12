using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace NetEdit
{
    public partial class NeuronEditForm : MovableResizableForm
    {

        #region Private Members

        private string _neuronName;

        #endregion

        #region Public Members

        public string NeuronName
        {
            get => _neuronName;
            set => _neuronName = value;
        }

        #endregion

        GraphicsPath path = new GraphicsPath();

        public NeuronEditForm()
        {
            InitializeComponent();
            Point[] points = new Point[]
            {
                new Point(0,0),
                new Point(0,200),
                new Point(70,200),
                new Point(100,230),
                new Point(130,200),
                new Point(200,200),
                new Point(200,0),
                new Point(0,0)
            };

            path.AddLines(points);
            //path.AddEllipse(0, 0, this.ClientSize.Width, this.ClientSize.Height);
            this.Region = new Region(path);

            //this.BackColor = Color.FromArgb(139, 87, 92);
        }
    }
}
