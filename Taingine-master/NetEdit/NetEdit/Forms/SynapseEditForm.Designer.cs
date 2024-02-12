namespace NetEdit.Forms
{
    partial class SynapseEditForm
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
            this.synapseSelectionComboBox = new System.Windows.Forms.ComboBox();
            this.weightLabel = new System.Windows.Forms.Label();
            this.changeButton = new System.Windows.Forms.Button();
            this.newValueTextBox = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // synapseSelectionComboBox
            // 
            this.synapseSelectionComboBox.FormattingEnabled = true;
            this.synapseSelectionComboBox.Location = new System.Drawing.Point(12, 26);
            this.synapseSelectionComboBox.Name = "synapseSelectionComboBox";
            this.synapseSelectionComboBox.Size = new System.Drawing.Size(121, 21);
            this.synapseSelectionComboBox.TabIndex = 6;
            this.synapseSelectionComboBox.SelectedIndexChanged += new System.EventHandler(this.SynapseSelectionComboBox_SelectedIndexChanged);
            // 
            // weightLabel
            // 
            this.weightLabel.AutoSize = true;
            this.weightLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.weightLabel.ForeColor = System.Drawing.SystemColors.Control;
            this.weightLabel.Location = new System.Drawing.Point(139, 26);
            this.weightLabel.Name = "weightLabel";
            this.weightLabel.Size = new System.Drawing.Size(46, 18);
            this.weightLabel.TabIndex = 7;
            this.weightLabel.Text = "label2";
            // 
            // changeButton
            // 
            this.changeButton.Location = new System.Drawing.Point(313, 63);
            this.changeButton.Name = "changeButton";
            this.changeButton.Size = new System.Drawing.Size(75, 23);
            this.changeButton.TabIndex = 8;
            this.changeButton.Text = "Change";
            this.changeButton.UseVisualStyleBackColor = true;
            this.changeButton.Click += new System.EventHandler(this.ChangeButton_Click);
            // 
            // newValueTextBox
            // 
            this.newValueTextBox.Location = new System.Drawing.Point(12, 66);
            this.newValueTextBox.Name = "newValueTextBox";
            this.newValueTextBox.Size = new System.Drawing.Size(222, 20);
            this.newValueTextBox.TabIndex = 9;
            // 
            // SynapseEditForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(28)))), ((int)(((byte)(29)))), ((int)(((byte)(33)))));
            this.ClientSize = new System.Drawing.Size(400, 300);
            this.Controls.Add(this.newValueTextBox);
            this.Controls.Add(this.changeButton);
            this.Controls.Add(this.weightLabel);
            this.Controls.Add(this.synapseSelectionComboBox);
            this.InformationBarColor = System.Drawing.Color.White;
            this.Name = "SynapseEditForm";
            this.Text = "SynapseEditForm";
            this.TitleBarTextVisable = true;
            this.Controls.SetChildIndex(this.synapseSelectionComboBox, 0);
            this.Controls.SetChildIndex(this.weightLabel, 0);
            this.Controls.SetChildIndex(this.changeButton, 0);
            this.Controls.SetChildIndex(this.newValueTextBox, 0);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox synapseSelectionComboBox;
        private System.Windows.Forms.Label weightLabel;
        private System.Windows.Forms.Button changeButton;
        private System.Windows.Forms.TextBox newValueTextBox;
    }
}