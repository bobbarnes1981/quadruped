namespace Calibration
{
    partial class Form1
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
            this.button1 = new System.Windows.Forms.Button();
            this.comboBoxServo = new System.Windows.Forms.ComboBox();
            this.numericUpDownMin = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownMax = new System.Windows.Forms.NumericUpDown();
            this.comboBoxPort = new System.Windows.Forms.ComboBox();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.buttonClose = new System.Windows.Forms.Button();
            this.buttonGo = new System.Windows.Forms.Button();
            this.textBoxAngle = new System.Windows.Forms.TextBox();
            this.buttonTest = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMin)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMax)).BeginInit();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(428, 256);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // comboBoxServo
            // 
            this.comboBoxServo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxServo.FormattingEnabled = true;
            this.comboBoxServo.Location = new System.Drawing.Point(13, 88);
            this.comboBoxServo.Name = "comboBoxServo";
            this.comboBoxServo.Size = new System.Drawing.Size(121, 21);
            this.comboBoxServo.TabIndex = 1;
            this.comboBoxServo.SelectedValueChanged += new System.EventHandler(this.comboBoxServo_SelectedValueChanged);
            // 
            // numericUpDownMin
            // 
            this.numericUpDownMin.DecimalPlaces = 6;
            this.numericUpDownMin.Increment = new decimal(new int[] {
            1,
            0,
            0,
            327680});
            this.numericUpDownMin.Location = new System.Drawing.Point(13, 130);
            this.numericUpDownMin.Name = "numericUpDownMin";
            this.numericUpDownMin.Size = new System.Drawing.Size(120, 20);
            this.numericUpDownMin.TabIndex = 2;
            this.numericUpDownMin.ValueChanged += new System.EventHandler(this.numericUpDownMin_ValueChanged);
            // 
            // numericUpDownMax
            // 
            this.numericUpDownMax.DecimalPlaces = 6;
            this.numericUpDownMax.Increment = new decimal(new int[] {
            1,
            0,
            0,
            327680});
            this.numericUpDownMax.Location = new System.Drawing.Point(13, 167);
            this.numericUpDownMax.Name = "numericUpDownMax";
            this.numericUpDownMax.Size = new System.Drawing.Size(120, 20);
            this.numericUpDownMax.TabIndex = 3;
            this.numericUpDownMax.ValueChanged += new System.EventHandler(this.numericUpDownMax_ValueChanged);
            // 
            // comboBoxPort
            // 
            this.comboBoxPort.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxPort.FormattingEnabled = true;
            this.comboBoxPort.Location = new System.Drawing.Point(13, 13);
            this.comboBoxPort.Name = "comboBoxPort";
            this.comboBoxPort.Size = new System.Drawing.Size(121, 21);
            this.comboBoxPort.TabIndex = 4;
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(140, 11);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(75, 23);
            this.buttonConnect.TabIndex = 5;
            this.buttonConnect.Text = "Connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // buttonClose
            // 
            this.buttonClose.Enabled = false;
            this.buttonClose.Location = new System.Drawing.Point(221, 11);
            this.buttonClose.Name = "buttonClose";
            this.buttonClose.Size = new System.Drawing.Size(75, 23);
            this.buttonClose.TabIndex = 6;
            this.buttonClose.Text = "Close";
            this.buttonClose.UseVisualStyleBackColor = true;
            this.buttonClose.Click += new System.EventHandler(this.buttonClose_Click);
            // 
            // buttonGo
            // 
            this.buttonGo.Location = new System.Drawing.Point(140, 200);
            this.buttonGo.Name = "buttonGo";
            this.buttonGo.Size = new System.Drawing.Size(75, 23);
            this.buttonGo.TabIndex = 7;
            this.buttonGo.Text = "Go";
            this.buttonGo.UseVisualStyleBackColor = true;
            this.buttonGo.Click += new System.EventHandler(this.buttonGo_Click);
            // 
            // textBoxAngle
            // 
            this.textBoxAngle.Location = new System.Drawing.Point(13, 202);
            this.textBoxAngle.Name = "textBoxAngle";
            this.textBoxAngle.Size = new System.Drawing.Size(100, 20);
            this.textBoxAngle.TabIndex = 8;
            // 
            // buttonTest
            // 
            this.buttonTest.Location = new System.Drawing.Point(37, 239);
            this.buttonTest.Name = "buttonTest";
            this.buttonTest.Size = new System.Drawing.Size(75, 23);
            this.buttonTest.TabIndex = 9;
            this.buttonTest.Text = "Test";
            this.buttonTest.UseVisualStyleBackColor = true;
            this.buttonTest.Click += new System.EventHandler(this.buttonTest_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.buttonTest);
            this.Controls.Add(this.textBoxAngle);
            this.Controls.Add(this.buttonGo);
            this.Controls.Add(this.buttonClose);
            this.Controls.Add(this.buttonConnect);
            this.Controls.Add(this.comboBoxPort);
            this.Controls.Add(this.numericUpDownMax);
            this.Controls.Add(this.numericUpDownMin);
            this.Controls.Add(this.comboBoxServo);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMin)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMax)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ComboBox comboBoxServo;
        private System.Windows.Forms.NumericUpDown numericUpDownMin;
        private System.Windows.Forms.NumericUpDown numericUpDownMax;
        private System.Windows.Forms.ComboBox comboBoxPort;
        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.Button buttonClose;
        private System.Windows.Forms.Button buttonGo;
        private System.Windows.Forms.TextBox textBoxAngle;
        private System.Windows.Forms.Button buttonTest;
    }
}

