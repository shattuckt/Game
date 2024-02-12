using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;
//using System.Drawing.Drawing2D;

namespace NetEdit
{
    class ContextMenueStripRenderer : ToolStripProfessionalRenderer
    {

        protected override void OnRenderMenuItemBackground(ToolStripItemRenderEventArgs e)
        {
            if (!e.Item.Selected) base.OnRenderMenuItemBackground(e);
            else
            {
                Rectangle rc = new Rectangle(Point.Empty, e.Item.Size);
                Brush brush = new SolidBrush(Color.FromArgb(69, 73, 85));
                e.Graphics.FillRectangle(brush, rc);
                e.Graphics.DrawRectangle(Pens.White, 1, 0, rc.Width - 2, rc.Height - 1);

                brush.Dispose();
            }
        }
    }
}
