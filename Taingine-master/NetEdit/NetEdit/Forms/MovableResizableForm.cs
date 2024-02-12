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
    public partial class MovableResizableForm : ResizableForm
    {
        #region Private Members

        private bool isMaximized = false;
        private bool moving = false;
        private Point moveOffset;

        #endregion

        #region Exposed Members

        [Category("MovableForm")]
        [Description("Image that the exit button displays.")]
        public Image ExitButtonImage
        {
            get => exitButton.Image;
            set => exitButton.Image = value;
        }


        [Category("MovableForm")]
        [Description("Image that the maximize button displays.")]
        public Image MaximizeButtonImage
        {
            get => maximizeButton.Image;
            set => maximizeButton.Image = value;
        }


        [Category("MovableForm")]
        [Description("Image that the minimize button displays.")]
        public Image MinimizeButtonImage
        {
            get => minimizeButton.Image;
            set => minimizeButton.Image = value;
        }


        [Category("MovableForm")]
        [Description("Backround color of the title bar.")]
        public Color TitleBarBackgroundColor
        {
            get => titleBarPanel.BackColor;
            set => titleBarPanel.BackColor = value;
        }


        [Category("MovableForm")]
        [Description("Text displayed on the title bar.")]
        public string TitleBarText
        {
            get => titleLabel.Text;
            set => titleLabel.Text = value;
        }


        [Category("MovableForm")]
        [Description("Wether or not the title bar label is visable.")]
        public bool TitleBarTextVisable
        {
            get => titleLabel.Visible;
            set => titleLabel.Visible = value;
        }

        #endregion


        public MovableResizableForm()
        {
            InitializeComponent();
        }


        #region Form Contorl
        private void MovableForm_TitleBar_DoubleClick(object sender, EventArgs e)
        {
            if (isMaximized)
            {
                MinimizeScreen();
            }
            else
            {
                MaximizeScreen();
                isMaximized = true;
            }
        }


        private void MovableForm_TitleBar_MouseDown(object sender, MouseEventArgs e)
        {
            moveOffset = new Point(e.X, e.Y);
            moving = true;
        }


        private void MovableForm_TitleBar_MouseMove(object sender, MouseEventArgs e)
        {
            if (moving)
            {
                if (isMaximized)
                {
                    MinimizeScreen();
                    Point newlocation = Cursor.Position;
                    newlocation.X += e.X - moveOffset.X - (this.Width / 2);
                    newlocation.Y += e.Y - moveOffset.Y;
                    this.Location = newlocation;
                    moveOffset = this.PointToClient(Cursor.Position);
                }
                else
                {
                    Point newlocation = this.Location;
                    newlocation.X += e.X - moveOffset.X;
                    newlocation.Y += e.Y - moveOffset.Y;
                    this.Location = newlocation;
                }
            }
        }


        private void MovableForm_TitleBar_MouseUp(object sender, MouseEventArgs e)
        {
            if (moving)
            {
                if (this.Location.Y < 5)
                {
                    MaximizeScreen();
                }
                moving = false;
            }
        }


        private void MovableForm_ExitButtonClicked(object sender, EventArgs e)
        {
            Close();
        }


        private void MovableForm_MaximizeButtonClicked(object sender, EventArgs e)
        {
            if (isMaximized)
            {
                MinimizeScreen();
            }
            else
            {
                MaximizeScreen();
            }
        }


        private void MovableForm_MinimizeButtonClicked(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }


        private void MinimizeScreen()
        {
            this.WindowState = FormWindowState.Normal;
            isMaximized = false;
            ResizeRegionVisable = true;
            DoneResizing();
        }

        private void MaximizeScreen()
        {
            Rectangle rectangle = Screen.FromControl(this).WorkingArea;
            rectangle.X = 0;
            this.MaximizedBounds = rectangle;
            this.WindowState = FormWindowState.Maximized;
            isMaximized = true;
            ResizeRegionVisable = false;
            DoneResizing();
        }
        #endregion

    }
}
