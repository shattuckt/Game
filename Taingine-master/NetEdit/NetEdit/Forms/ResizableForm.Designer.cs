namespace NetEdit
{
    partial class ResizableForm
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
            this.resizeRegionPictureBox = new System.Windows.Forms.PictureBox();
            this.informationBarPannel = new System.Windows.Forms.Panel();
            this.synapseNumberLabel = new System.Windows.Forms.Label();
            this.neuronNumberLabel = new System.Windows.Forms.Label();
            this.addOutputButton = new System.Windows.Forms.Button();
            this.editPannel = new System.Windows.Forms.Panel();
            this.addSyanpseButton = new System.Windows.Forms.Button();
            this.neuronTagEditBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.addInputButton = new System.Windows.Forms.Button();
            this.addHidenButton = new System.Windows.Forms.Button();
            this.editPaddingPanel = new System.Windows.Forms.Panel();
            ((System.ComponentModel.ISupportInitialize)(this.resizeRegionPictureBox)).BeginInit();
            this.informationBarPannel.SuspendLayout();
            this.editPannel.SuspendLayout();
            this.SuspendLayout();
            // 
            // resizeRegionPictureBox
            // 
            this.resizeRegionPictureBox.Dock = System.Windows.Forms.DockStyle.Right;
            this.resizeRegionPictureBox.Image = global::NetEdit.Properties.Resources.ResizeImage;
            this.resizeRegionPictureBox.InitialImage = null;
            this.resizeRegionPictureBox.Location = new System.Drawing.Point(780, 0);
            this.resizeRegionPictureBox.Name = "resizeRegionPictureBox";
            this.resizeRegionPictureBox.Size = new System.Drawing.Size(20, 20);
            this.resizeRegionPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.resizeRegionPictureBox.TabIndex = 0;
            this.resizeRegionPictureBox.TabStop = false;
            this.resizeRegionPictureBox.MouseDown += new System.Windows.Forms.MouseEventHandler(this.MovableResize_ResizeWinRegion_MouseDown);
            this.resizeRegionPictureBox.MouseEnter += new System.EventHandler(this.MovableResize_ResizeWinRegion_MouseEnter);
            this.resizeRegionPictureBox.MouseLeave += new System.EventHandler(this.MovableResize_ResizeWinRegion_MouseLeave);
            this.resizeRegionPictureBox.MouseMove += new System.Windows.Forms.MouseEventHandler(this.MovableResize_ResizeWinRegion_MouseMove);
            this.resizeRegionPictureBox.MouseUp += new System.Windows.Forms.MouseEventHandler(this.MovableResize_ResizeWinRegion_MouseUp);
            // 
            // informationBarPannel
            // 
            this.informationBarPannel.Controls.Add(this.synapseNumberLabel);
            this.informationBarPannel.Controls.Add(this.neuronNumberLabel);
            this.informationBarPannel.Controls.Add(this.resizeRegionPictureBox);
            this.informationBarPannel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.informationBarPannel.Location = new System.Drawing.Point(0, 430);
            this.informationBarPannel.Name = "informationBarPannel";
            this.informationBarPannel.Size = new System.Drawing.Size(800, 20);
            this.informationBarPannel.TabIndex = 2;
            // 
            // synapseNumberLabel
            // 
            this.synapseNumberLabel.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.synapseNumberLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(243)))), ((int)(((byte)(239)))), ((int)(((byte)(245)))));
            this.synapseNumberLabel.Location = new System.Drawing.Point(650, 0);
            this.synapseNumberLabel.Name = "synapseNumberLabel";
            this.synapseNumberLabel.Size = new System.Drawing.Size(70, 20);
            this.synapseNumberLabel.TabIndex = 2;
            this.synapseNumberLabel.Text = "label2";
            // 
            // neuronNumberLabel
            // 
            this.neuronNumberLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(243)))), ((int)(((byte)(239)))), ((int)(((byte)(245)))));
            this.neuronNumberLabel.Location = new System.Drawing.Point(520, 0);
            this.neuronNumberLabel.Name = "neuronNumberLabel";
            this.neuronNumberLabel.Size = new System.Drawing.Size(70, 20);
            this.neuronNumberLabel.TabIndex = 1;
            this.neuronNumberLabel.Text = "label1";
            // 
            // addOutputButton
            // 
            this.addOutputButton.Dock = System.Windows.Forms.DockStyle.Right;
            this.addOutputButton.FlatAppearance.BorderSize = 0;
            this.addOutputButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.addOutputButton.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(243)))), ((int)(((byte)(239)))), ((int)(((byte)(245)))));
            this.addOutputButton.Location = new System.Drawing.Point(750, 0);
            this.addOutputButton.Name = "addOutputButton";
            this.addOutputButton.Size = new System.Drawing.Size(50, 20);
            this.addOutputButton.TabIndex = 3;
            this.addOutputButton.Text = "Output";
            this.addOutputButton.UseVisualStyleBackColor = true;
            this.addOutputButton.Click += new System.EventHandler(this.ResizableForm_AddOutput_Click);
            // 
            // editPannel
            // 
            this.editPannel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(69)))), ((int)(((byte)(73)))), ((int)(((byte)(85)))));
            this.editPannel.Controls.Add(this.addSyanpseButton);
            this.editPannel.Controls.Add(this.neuronTagEditBox);
            this.editPannel.Controls.Add(this.label1);
            this.editPannel.Controls.Add(this.addInputButton);
            this.editPannel.Controls.Add(this.addHidenButton);
            this.editPannel.Controls.Add(this.addOutputButton);
            this.editPannel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.editPannel.Location = new System.Drawing.Point(0, 410);
            this.editPannel.Name = "editPannel";
            this.editPannel.Size = new System.Drawing.Size(800, 20);
            this.editPannel.TabIndex = 4;
            // 
            // addSyanpseButton
            // 
            this.addSyanpseButton.Dock = System.Windows.Forms.DockStyle.Right;
            this.addSyanpseButton.FlatAppearance.BorderSize = 0;
            this.addSyanpseButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.addSyanpseButton.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(243)))), ((int)(((byte)(239)))), ((int)(((byte)(245)))));
            this.addSyanpseButton.Location = new System.Drawing.Point(600, 0);
            this.addSyanpseButton.Name = "addSyanpseButton";
            this.addSyanpseButton.Size = new System.Drawing.Size(50, 20);
            this.addSyanpseButton.TabIndex = 9;
            this.addSyanpseButton.Text = "Synapse";
            this.addSyanpseButton.UseVisualStyleBackColor = true;
            this.addSyanpseButton.Click += new System.EventHandler(this.AddSyanpseButton_Click);
            // 
            // neuronTagEditBox
            // 
            this.neuronTagEditBox.Dock = System.Windows.Forms.DockStyle.Left;
            this.neuronTagEditBox.Location = new System.Drawing.Point(35, 0);
            this.neuronTagEditBox.Name = "neuronTagEditBox";
            this.neuronTagEditBox.Size = new System.Drawing.Size(236, 20);
            this.neuronTagEditBox.TabIndex = 8;
            this.neuronTagEditBox.TextChanged += new System.EventHandler(this.NeuronTagEditBox_TextChanged);
            // 
            // label1
            // 
            this.label1.Dock = System.Windows.Forms.DockStyle.Left;
            this.label1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(243)))), ((int)(((byte)(239)))), ((int)(((byte)(245)))));
            this.label1.Location = new System.Drawing.Point(0, 0);
            this.label1.Name = "label1";
            this.label1.Padding = new System.Windows.Forms.Padding(0, 3, 0, 0);
            this.label1.Size = new System.Drawing.Size(35, 20);
            this.label1.TabIndex = 7;
            this.label1.Text = "Tag: ";
            // 
            // addInputButton
            // 
            this.addInputButton.Dock = System.Windows.Forms.DockStyle.Right;
            this.addInputButton.FlatAppearance.BorderSize = 0;
            this.addInputButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.addInputButton.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(243)))), ((int)(((byte)(239)))), ((int)(((byte)(245)))));
            this.addInputButton.Location = new System.Drawing.Point(650, 0);
            this.addInputButton.Name = "addInputButton";
            this.addInputButton.Size = new System.Drawing.Size(50, 20);
            this.addInputButton.TabIndex = 5;
            this.addInputButton.Text = "Input";
            this.addInputButton.UseVisualStyleBackColor = true;
            this.addInputButton.Click += new System.EventHandler(this.ResizableForm_AddInput_Click);
            // 
            // addHidenButton
            // 
            this.addHidenButton.Dock = System.Windows.Forms.DockStyle.Right;
            this.addHidenButton.FlatAppearance.BorderSize = 0;
            this.addHidenButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.addHidenButton.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(243)))), ((int)(((byte)(239)))), ((int)(((byte)(245)))));
            this.addHidenButton.Location = new System.Drawing.Point(700, 0);
            this.addHidenButton.Name = "addHidenButton";
            this.addHidenButton.Size = new System.Drawing.Size(50, 20);
            this.addHidenButton.TabIndex = 4;
            this.addHidenButton.Text = "Hiden";
            this.addHidenButton.UseVisualStyleBackColor = true;
            this.addHidenButton.Click += new System.EventHandler(this.ResizableForm_AddHiden_Click);
            // 
            // editPaddingPanel
            // 
            this.editPaddingPanel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(69)))), ((int)(((byte)(73)))), ((int)(((byte)(85)))));
            this.editPaddingPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.editPaddingPanel.Location = new System.Drawing.Point(0, 405);
            this.editPaddingPanel.Name = "editPaddingPanel";
            this.editPaddingPanel.Size = new System.Drawing.Size(800, 5);
            this.editPaddingPanel.TabIndex = 5;
            // 
            // ResizableForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.editPaddingPanel);
            this.Controls.Add(this.editPannel);
            this.Controls.Add(this.informationBarPannel);
            this.Name = "ResizableForm";
            this.Text = "MovableResizableForm";
            ((System.ComponentModel.ISupportInitialize)(this.resizeRegionPictureBox)).EndInit();
            this.informationBarPannel.ResumeLayout(false);
            this.editPannel.ResumeLayout(false);
            this.editPannel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox resizeRegionPictureBox;
        private System.Windows.Forms.Panel informationBarPannel;
        private System.Windows.Forms.Label synapseNumberLabel;
        private System.Windows.Forms.Label neuronNumberLabel;
        private System.Windows.Forms.Button addOutputButton;
        private System.Windows.Forms.Panel editPannel;
        private System.Windows.Forms.TextBox neuronTagEditBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button addInputButton;
        private System.Windows.Forms.Button addHidenButton;
        private System.Windows.Forms.Panel editPaddingPanel;
        private System.Windows.Forms.Button addSyanpseButton;
    }
}