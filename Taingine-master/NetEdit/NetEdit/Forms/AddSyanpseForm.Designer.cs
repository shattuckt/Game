namespace NetEdit.Forms
{
    partial class AddSyanpseForm
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
            this.startNumeric = new System.Windows.Forms.NumericUpDown();
            this.targetNumeric = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.addButton = new System.Windows.Forms.Button();
            this.weightTextBox = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.startNumeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.targetNumeric)).BeginInit();
            this.SuspendLayout();
            // 
            // startNumeric
            // 
            this.startNumeric.Location = new System.Drawing.Point(74, 26);
            this.startNumeric.Name = "startNumeric";
            this.startNumeric.Size = new System.Drawing.Size(120, 20);
            this.startNumeric.TabIndex = 6;
            // 
            // targetNumeric
            // 
            this.targetNumeric.Location = new System.Drawing.Point(74, 64);
            this.targetNumeric.Name = "targetNumeric";
            this.targetNumeric.Size = new System.Drawing.Size(120, 20);
            this.targetNumeric.TabIndex = 7;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.White;
            this.label2.Location = new System.Drawing.Point(0, 30);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 16);
            this.label2.TabIndex = 8;
            this.label2.Text = "Start";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.ForeColor = System.Drawing.Color.White;
            this.label3.Location = new System.Drawing.Point(0, 68);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(48, 16);
            this.label3.TabIndex = 9;
            this.label3.Text = "Target";
            // 
            // addButton
            // 
            this.addButton.Location = new System.Drawing.Point(119, 142);
            this.addButton.Name = "addButton";
            this.addButton.Size = new System.Drawing.Size(75, 23);
            this.addButton.TabIndex = 11;
            this.addButton.Text = "Add";
            this.addButton.UseVisualStyleBackColor = true;
            this.addButton.Click += new System.EventHandler(this.AddButton_Click);
            // 
            // weightTextBox
            // 
            this.weightTextBox.Location = new System.Drawing.Point(74, 104);
            this.weightTextBox.Name = "weightTextBox";
            this.weightTextBox.Size = new System.Drawing.Size(120, 20);
            this.weightTextBox.TabIndex = 12;
            // 
            // AddSyanpseForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(28)))), ((int)(((byte)(29)))), ((int)(((byte)(33)))));
            this.ClientSize = new System.Drawing.Size(221, 177);
            this.Controls.Add(this.weightTextBox);
            this.Controls.Add(this.addButton);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.targetNumeric);
            this.Controls.Add(this.startNumeric);
            this.InformationBarColor = System.Drawing.Color.FromArgb(((int)(((byte)(28)))), ((int)(((byte)(29)))), ((int)(((byte)(33)))));
            this.Name = "AddSyanpseForm";
            this.Text = "AddSyanpseForm";
            this.TitleBarTextVisable = true;
            this.Controls.SetChildIndex(this.startNumeric, 0);
            this.Controls.SetChildIndex(this.targetNumeric, 0);
            this.Controls.SetChildIndex(this.label2, 0);
            this.Controls.SetChildIndex(this.label3, 0);
            this.Controls.SetChildIndex(this.addButton, 0);
            this.Controls.SetChildIndex(this.weightTextBox, 0);
            ((System.ComponentModel.ISupportInitialize)(this.startNumeric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.targetNumeric)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NumericUpDown startNumeric;
        private System.Windows.Forms.NumericUpDown targetNumeric;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button addButton;
        private System.Windows.Forms.TextBox weightTextBox;
    }
}