using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using NetEdit.Forms;

namespace NetEdit
{
    public partial class ResizableForm : Form
    {
        #region Constants

        private const int MINIMUM_WINDOW_HEIGHT = 40;
        private const int MINIMUM_WINDOW_WIDTH = 130;

        #endregion

        #region Private Members

        private bool resizing = false;
        private Point resizeOffset;

        #endregion

        #region Exposed Members

        [Category("ResizableForm")]
        [Description("Image that the resize region displays.")]
        public Image ResizeRegionImage
        {
            get => resizeRegionPictureBox.Image;
            set => resizeRegionPictureBox.Image = value;
        }


        [Category("ResizableForm")]
        [Description("Wether or not the resize region is visable.")]
        public bool ResizeRegionVisable
        {
            get => resizeRegionPictureBox.Visible;
            set => resizeRegionPictureBox.Visible = value;
        }


        [Category("ResizableForm")]
        [Description("The background color of the Information Bar.")]
        public Color InformationBarColor
        {
            get => informationBarPannel.BackColor;
            set => informationBarPannel.BackColor = value;
        }


        [Category("ResizableForm")]
        [Description("Wether or not the informationBar is visable.")]
        public bool InformationBarVisable
        {
            get => informationBarPannel.Visible;
            set
            {
                informationBarPannel.Visible = value;
                editPannel.Visible = value;
                editPaddingPanel.Visible = value;
            }
        }


        protected Label SynapseNumberLabel
        {
            get => synapseNumberLabel;
            set => synapseNumberLabel = value;
        }


        public Label NeuronNumberLabel
        {
            get => neuronNumberLabel;
            set => neuronNumberLabel = value;
        }

        #endregion


        public ResizableForm()
        {
            InitializeComponent();
            EventHub.ChangeText += ResizableForm_ChangeText;
        }

        #region Resize Control

        public void MovableResize_ResizeWinRegion_MouseEnter(object sender, EventArgs e)
        {
            this.Cursor = Cursors.SizeNWSE;
        }


        public void MovableResize_ResizeWinRegion_MouseLeave(object sender, EventArgs e)
        {
            this.Cursor = Cursors.Default;
        }


        private void MovableResize_ResizeWinRegion_MouseDown(object sender, MouseEventArgs e)
        {
            resizeOffset = new Point(e.X, e.Y);
            resizing = true;
        }


        private void MovableResize_ResizeWinRegion_MouseMove(object sender, MouseEventArgs e)
        {
            if (resizing)
            {
                if (this.Width + (e.X - resizeOffset.X) > MINIMUM_WINDOW_WIDTH)
                    this.Width += e.X - resizeOffset.X;
                else
                    this.Width = MINIMUM_WINDOW_WIDTH;

                if (this.Height + (e.X - resizeOffset.X) > MINIMUM_WINDOW_HEIGHT)
                    this.Height += e.Y - resizeOffset.Y;
                else
                    this.Height = MINIMUM_WINDOW_HEIGHT;
            }
        }


        private void MovableResize_ResizeWinRegion_MouseUp(object sender, MouseEventArgs e)
        {
            if (resizing)
            {
                resizing = false;
                DoneResizing();
            }
        }

        #endregion

        #region Neuron Creation
        private void ResizableForm_AddInput_Click(object sender, EventArgs e)
        {
            AddNeuronEventArgs eventArgs = new AddNeuronEventArgs();
            eventArgs.NeuronType = NeuronType.Input;
            eventArgs.Name = "temp";

            EventHub.OnAddNeuron(this, eventArgs);
        }

        private void ResizableForm_AddHiden_Click(object sender, EventArgs e)
        {
            AddNeuronEventArgs eventArgs = new AddNeuronEventArgs();
            eventArgs.NeuronType = NeuronType.Hiden;
            eventArgs.Name = "temp";

            EventHub.OnAddNeuron(this, eventArgs);
        }

        private void ResizableForm_AddOutput_Click(object sender, EventArgs e)
        {
            AddNeuronEventArgs eventArgs = new AddNeuronEventArgs();
            eventArgs.NeuronType = NeuronType.Output;
            eventArgs.Name = "temp";

            EventHub.OnAddNeuron(this, eventArgs);
        }

        #endregion

        private void ResizableForm_ChangeText(object sender, AddNeuronEventArgs e)
        {
            neuronTagEditBox.Text = e.Name;
        }

        private void NeuronTagEditBox_TextChanged(object sender, EventArgs e)
        {
            EditorHelper.ActiveNeuronTag = neuronTagEditBox.Text;
        }

        protected virtual void DoneResizing()
        {

        }

        private void AddSyanpseButton_Click(object sender, EventArgs e)
        {
            using(var form = new AddSyanpseForm())
            {
                form.ShowDialog();
            }
        }
    }
}
