namespace NetEdit
{
    partial class TabBarUserControl
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
            this.components = new System.ComponentModel.Container();
            this.fileButton = new System.Windows.Forms.Button();
            this.editButton = new System.Windows.Forms.Button();
            this.fileMenueStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.newFile = new System.Windows.Forms.ToolStripMenuItem();
            this.openFile = new System.Windows.Forms.ToolStripMenuItem();
            this.saveFile = new System.Windows.Forms.ToolStripMenuItem();
            this.saveFileAs = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.exit = new System.Windows.Forms.ToolStripMenuItem();
            this.editMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.addNeuron = new System.Windows.Forms.ToolStripMenuItem();
            this.addInput = new System.Windows.Forms.ToolStripMenuItem();
            this.addHidden = new System.Windows.Forms.ToolStripMenuItem();
            this.addOutput = new System.Windows.Forms.ToolStripMenuItem();
            this.addSynapse = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.fileMenueStrip.SuspendLayout();
            this.editMenuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // fileButton
            // 
            this.fileButton.Dock = System.Windows.Forms.DockStyle.Left;
            this.fileButton.FlatAppearance.BorderSize = 0;
            this.fileButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.fileButton.Font = new System.Drawing.Font("Verdana", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.fileButton.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(243)))), ((int)(((byte)(239)))), ((int)(((byte)(245)))));
            this.fileButton.Location = new System.Drawing.Point(0, 0);
            this.fileButton.Name = "fileButton";
            this.fileButton.Size = new System.Drawing.Size(55, 35);
            this.fileButton.TabIndex = 0;
            this.fileButton.Text = "File";
            this.fileButton.UseVisualStyleBackColor = true;
            this.fileButton.Click += new System.EventHandler(this.TabBar_FileButtonClicked);
            // 
            // editButton
            // 
            this.editButton.Dock = System.Windows.Forms.DockStyle.Left;
            this.editButton.FlatAppearance.BorderSize = 0;
            this.editButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.editButton.Font = new System.Drawing.Font("Verdana", 8F);
            this.editButton.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(243)))), ((int)(((byte)(239)))), ((int)(((byte)(245)))));
            this.editButton.Location = new System.Drawing.Point(55, 0);
            this.editButton.Name = "editButton";
            this.editButton.Size = new System.Drawing.Size(55, 35);
            this.editButton.TabIndex = 1;
            this.editButton.Text = "Edit";
            this.editButton.UseVisualStyleBackColor = true;
            this.editButton.Click += new System.EventHandler(this.TabBar_EditButtonClicked);
            // 
            // fileMenueStrip
            // 
            this.fileMenueStrip.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(28)))), ((int)(((byte)(29)))), ((int)(((byte)(33)))));
            this.fileMenueStrip.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.fileMenueStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newFile,
            this.openFile,
            this.saveFile,
            this.saveFileAs,
            this.toolStripSeparator1,
            this.exit});
            this.fileMenueStrip.Name = "contextMenuStrip1";
            this.fileMenueStrip.ShowImageMargin = false;
            this.fileMenueStrip.Size = new System.Drawing.Size(122, 118);
            // 
            // newFile
            // 
            this.newFile.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.newFile.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.newFile.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(243)))), ((int)(((byte)(239)))), ((int)(((byte)(245)))));
            this.newFile.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.newFile.ImageTransparentColor = System.Drawing.Color.FromArgb(((int)(((byte)(28)))), ((int)(((byte)(29)))), ((int)(((byte)(33)))));
            this.newFile.Margin = new System.Windows.Forms.Padding(0, 0, 100, 0);
            this.newFile.Name = "newFile";
            this.newFile.Padding = new System.Windows.Forms.Padding(0);
            this.newFile.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.newFile.Size = new System.Drawing.Size(121, 20);
            this.newFile.Text = "New";
            this.newFile.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.newFile.Click += new System.EventHandler(this.TabBar_NewMenuItem_Click);
            // 
            // openFile
            // 
            this.openFile.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.openFile.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(243)))), ((int)(((byte)(239)))), ((int)(((byte)(245)))));
            this.openFile.Name = "openFile";
            this.openFile.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.openFile.Size = new System.Drawing.Size(121, 22);
            this.openFile.Text = "Open";
            this.openFile.Click += new System.EventHandler(this.TabBar_OpenMenuItem_Click);
            // 
            // saveFile
            // 
            this.saveFile.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.saveFile.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(243)))), ((int)(((byte)(239)))), ((int)(((byte)(245)))));
            this.saveFile.Name = "saveFile";
            this.saveFile.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.saveFile.Size = new System.Drawing.Size(121, 22);
            this.saveFile.Text = "Save";
            this.saveFile.TextImageRelation = System.Windows.Forms.TextImageRelation.Overlay;
            this.saveFile.Click += new System.EventHandler(this.TabBar_SaveMenuItem_Click);
            // 
            // saveFileAs
            // 
            this.saveFileAs.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(243)))), ((int)(((byte)(239)))), ((int)(((byte)(245)))));
            this.saveFileAs.Name = "saveFileAs";
            this.saveFileAs.Size = new System.Drawing.Size(121, 22);
            this.saveFileAs.Text = "Save As";
            this.saveFileAs.Click += new System.EventHandler(this.TabBar_SaveMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(118, 6);
            // 
            // exit
            // 
            this.exit.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(243)))), ((int)(((byte)(239)))), ((int)(((byte)(245)))));
            this.exit.Name = "exit";
            this.exit.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.F4)));
            this.exit.Size = new System.Drawing.Size(121, 22);
            this.exit.Text = "Exit";
            this.exit.Click += new System.EventHandler(this.TabBar_ExitMenuItem_Click);
            // 
            // editMenuStrip
            // 
            this.editMenuStrip.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(28)))), ((int)(((byte)(29)))), ((int)(((byte)(33)))));
            this.editMenuStrip.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.editMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addNeuron,
            this.addSynapse});
            this.editMenuStrip.Name = "contextMenuStrip1";
            this.editMenuStrip.ShowImageMargin = false;
            this.editMenuStrip.Size = new System.Drawing.Size(156, 68);
            // 
            // addNeuron
            // 
            this.addNeuron.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.addNeuron.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.addNeuron.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addInput,
            this.addHidden,
            this.addOutput});
            this.addNeuron.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(243)))), ((int)(((byte)(239)))), ((int)(((byte)(245)))));
            this.addNeuron.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.addNeuron.ImageTransparentColor = System.Drawing.Color.FromArgb(((int)(((byte)(28)))), ((int)(((byte)(29)))), ((int)(((byte)(33)))));
            this.addNeuron.Margin = new System.Windows.Forms.Padding(0, 0, 100, 0);
            this.addNeuron.Name = "addNeuron";
            this.addNeuron.Padding = new System.Windows.Forms.Padding(0);
            this.addNeuron.Size = new System.Drawing.Size(155, 20);
            this.addNeuron.Text = "Add Neuron";
            this.addNeuron.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.addNeuron.Click += new System.EventHandler(this.TabBar_AddNeuronMenuItem_Click);
            // 
            // addInput
            // 
            this.addInput.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(28)))), ((int)(((byte)(29)))), ((int)(((byte)(33)))));
            this.addInput.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(243)))), ((int)(((byte)(239)))), ((int)(((byte)(245)))));
            this.addInput.Name = "addInput";
            this.addInput.Size = new System.Drawing.Size(180, 22);
            this.addInput.Text = "Input";
            this.addInput.Click += new System.EventHandler(this.TabBar_AddInputNeuronMenuItem_Click);
            // 
            // addHidden
            // 
            this.addHidden.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(28)))), ((int)(((byte)(29)))), ((int)(((byte)(33)))));
            this.addHidden.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(243)))), ((int)(((byte)(239)))), ((int)(((byte)(245)))));
            this.addHidden.Name = "addHidden";
            this.addHidden.Size = new System.Drawing.Size(180, 22);
            this.addHidden.Text = "Hidden";
            this.addHidden.Click += new System.EventHandler(this.TabBar_AddHidenNeuronMenuItem_Click);
            // 
            // addOutput
            // 
            this.addOutput.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(28)))), ((int)(((byte)(29)))), ((int)(((byte)(33)))));
            this.addOutput.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(243)))), ((int)(((byte)(239)))), ((int)(((byte)(245)))));
            this.addOutput.Name = "addOutput";
            this.addOutput.Size = new System.Drawing.Size(180, 22);
            this.addOutput.Text = "Ouput";
            this.addOutput.Click += new System.EventHandler(this.TabBar_AddOutputNeuronMenuItem_Click);
            // 
            // addSynapse
            // 
            this.addSynapse.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.addSynapse.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(243)))), ((int)(((byte)(239)))), ((int)(((byte)(245)))));
            this.addSynapse.Name = "addSynapse";
            this.addSynapse.Size = new System.Drawing.Size(155, 22);
            this.addSynapse.Text = "Add Synapse";
            this.addSynapse.Click += new System.EventHandler(this.TabBar_AddSynapseMenuItem_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.Filter = "Network Files|*.nn";
            // 
            // saveFileDialog
            // 
            this.saveFileDialog.Filter = "Network Files|*.nn";
            // 
            // TabBarUserControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(69)))), ((int)(((byte)(73)))), ((int)(((byte)(85)))));
            this.Controls.Add(this.editButton);
            this.Controls.Add(this.fileButton);
            this.Name = "TabBarUserControl";
            this.Size = new System.Drawing.Size(952, 35);
            this.fileMenueStrip.ResumeLayout(false);
            this.editMenuStrip.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button fileButton;
        private System.Windows.Forms.Button editButton;
        private System.Windows.Forms.ContextMenuStrip fileMenueStrip;
        private System.Windows.Forms.ToolStripMenuItem newFile;
        private System.Windows.Forms.ToolStripMenuItem openFile;
        private System.Windows.Forms.ToolStripMenuItem saveFile;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem exit;
        private System.Windows.Forms.ContextMenuStrip editMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem addNeuron;
        private System.Windows.Forms.ToolStripMenuItem addSynapse;
        private System.Windows.Forms.ToolStripMenuItem saveFileAs;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.SaveFileDialog saveFileDialog;
        private System.Windows.Forms.ToolStripMenuItem addInput;
        private System.Windows.Forms.ToolStripMenuItem addHidden;
        private System.Windows.Forms.ToolStripMenuItem addOutput;
    }
}
