namespace NetEdit
{
    partial class MainForm
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tabBarUserControl1 = new NetEdit.TabBarUserControl();
            this.inputNeuronTray = new NetEdit.NeuronTrayUserControl();
            this.outputNeuronTray = new NetEdit.NeuronTrayUserControl();
            this.hiddenNeuronTray = new NetEdit.NeuronTrayUserControl();
            this.SuspendLayout();
            // 
            // tabBarUserControl1
            // 
            this.tabBarUserControl1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(69)))), ((int)(((byte)(73)))), ((int)(((byte)(85)))));
            this.tabBarUserControl1.Dock = System.Windows.Forms.DockStyle.Top;
            this.tabBarUserControl1.Location = new System.Drawing.Point(0, 20);
            this.tabBarUserControl1.Name = "tabBarUserControl1";
            this.tabBarUserControl1.Size = new System.Drawing.Size(800, 20);
            this.tabBarUserControl1.TabIndex = 4;
            // 
            // inputNeuronTray
            // 
            this.inputNeuronTray.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(37)))), ((int)(((byte)(38)))));
            this.inputNeuronTray.Dock = System.Windows.Forms.DockStyle.Left;
            this.inputNeuronTray.Location = new System.Drawing.Point(0, 40);
            this.inputNeuronTray.Name = "inputNeuronTray";
            this.inputNeuronTray.ResizeBarDockStyle = System.Windows.Forms.DockStyle.Right;
            this.inputNeuronTray.Size = new System.Drawing.Size(143, 365);
            this.inputNeuronTray.TabIndex = 5;
            // 
            // outputNeuronTray
            // 
            this.outputNeuronTray.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(37)))), ((int)(((byte)(38)))));
            this.outputNeuronTray.Dock = System.Windows.Forms.DockStyle.Right;
            this.outputNeuronTray.Location = new System.Drawing.Point(657, 40);
            this.outputNeuronTray.Name = "outputNeuronTray";
            this.outputNeuronTray.ResizeBarDockStyle = System.Windows.Forms.DockStyle.Left;
            this.outputNeuronTray.Size = new System.Drawing.Size(143, 365);
            this.outputNeuronTray.TabIndex = 6;
            // 
            // hiddenNeuronTray
            // 
            this.hiddenNeuronTray.BackColor = System.Drawing.Color.Transparent;
            this.hiddenNeuronTray.Dock = System.Windows.Forms.DockStyle.Fill;
            this.hiddenNeuronTray.Location = new System.Drawing.Point(143, 40);
            this.hiddenNeuronTray.Name = "hiddenNeuronTray";
            this.hiddenNeuronTray.ResizeBarDockStyle = System.Windows.Forms.DockStyle.Right;
            this.hiddenNeuronTray.Size = new System.Drawing.Size(514, 365);
            this.hiddenNeuronTray.TabIndex = 7;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(28)))), ((int)(((byte)(29)))), ((int)(((byte)(33)))));
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.hiddenNeuronTray);
            this.Controls.Add(this.outputNeuronTray);
            this.Controls.Add(this.inputNeuronTray);
            this.Controls.Add(this.tabBarUserControl1);
            this.InformationBarColor = System.Drawing.Color.FromArgb(((int)(((byte)(69)))), ((int)(((byte)(73)))), ((int)(((byte)(85)))));
            this.InformationBarVisable = true;
            this.Name = "MainForm";
            this.ResizeRegionVisable = true;
            this.Text = "Form1";
            this.TitleBarTextVisable = true;
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.MainForm_Paint);
            this.Controls.SetChildIndex(this.tabBarUserControl1, 0);
            this.Controls.SetChildIndex(this.inputNeuronTray, 0);
            this.Controls.SetChildIndex(this.outputNeuronTray, 0);
            this.Controls.SetChildIndex(this.hiddenNeuronTray, 0);
            this.ResumeLayout(false);

        }

        #endregion

        private TabBarUserControl tabBarUserControl1;
        private NeuronTrayUserControl inputNeuronTray;
        private NeuronTrayUserControl outputNeuronTray;
        private NeuronTrayUserControl hiddenNeuronTray;
    }
}

