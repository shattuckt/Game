namespace NetEdit
{
    partial class NeuronTrayUserControl
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.resizeBar = new System.Windows.Forms.Panel();
            this.SuspendLayout();
            // 
            // resizeBar
            // 
            this.resizeBar.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(69)))), ((int)(((byte)(73)))), ((int)(((byte)(85)))));
            this.resizeBar.Dock = System.Windows.Forms.DockStyle.Right;
            this.resizeBar.Location = new System.Drawing.Point(135, 0);
            this.resizeBar.Name = "resizeBar";
            this.resizeBar.Size = new System.Drawing.Size(8, 482);
            this.resizeBar.TabIndex = 0;
            this.resizeBar.MouseDown += new System.Windows.Forms.MouseEventHandler(this.NeuronTray_ResizeBar_MouseDown);
            this.resizeBar.MouseEnter += new System.EventHandler(this.NeuronTray_ResizeBar_MouseEnter);
            this.resizeBar.MouseLeave += new System.EventHandler(this.NeuronTray_ResizeBar_MouseLeave);
            this.resizeBar.MouseMove += new System.Windows.Forms.MouseEventHandler(this.NeuronTray_ResizeBar_MouseMove);
            this.resizeBar.MouseUp += new System.Windows.Forms.MouseEventHandler(this.NeuronTray_ResizeBar_MouseUp);
            // 
            // NeuronTrayUserControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(37)))), ((int)(((byte)(38)))));
            this.Controls.Add(this.resizeBar);
            this.Name = "NeuronTrayUserControl";
            this.Size = new System.Drawing.Size(143, 482);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel resizeBar;
    }
}
