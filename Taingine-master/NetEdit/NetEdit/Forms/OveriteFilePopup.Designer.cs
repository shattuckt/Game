namespace NetEdit.Forms
{
    partial class OveriteFilePopup
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
            this.overiteButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // overiteButton
            // 
            this.overiteButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.overiteButton.Location = new System.Drawing.Point(236, 165);
            this.overiteButton.Name = "overiteButton";
            this.overiteButton.Size = new System.Drawing.Size(59, 23);
            this.overiteButton.TabIndex = 6;
            this.overiteButton.Text = "Yes";
            this.overiteButton.UseVisualStyleBackColor = true;
            // 
            // OveriteFilePopup
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(400, 200);
            this.Controls.Add(this.overiteButton);
            this.Name = "OveriteFilePopup";
            this.Text = "OveriteFilePopup";
            this.TitleBarTextVisable = true;
            this.Controls.SetChildIndex(this.overiteButton, 0);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button overiteButton;
    }
}