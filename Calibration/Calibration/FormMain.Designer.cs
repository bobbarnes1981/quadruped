namespace Calibration
{
    partial class FormMain
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
            this.comboBoxServo = new System.Windows.Forms.ComboBox();
            this.numericUpDownMin = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownMax = new System.Windows.Forms.NumericUpDown();
            this.comboBoxPort = new System.Windows.Forms.ComboBox();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.buttonClose = new System.Windows.Forms.Button();
            this.buttonGo = new System.Windows.Forms.Button();
            this.textBoxAngle = new System.Windows.Forms.TextBox();
            this.groupBoxConnection = new System.Windows.Forms.GroupBox();
            this.groupBoxCalibration = new System.Windows.Forms.GroupBox();
            this.trackBarPulse = new System.Windows.Forms.TrackBar();
            this.labelPulse = new System.Windows.Forms.Label();
            this.textBoxPulse = new System.Windows.Forms.TextBox();
            this.buttonGoPulse = new System.Windows.Forms.Button();
            this.labelAngle = new System.Windows.Forms.Label();
            this.labelMaxPulse = new System.Windows.Forms.Label();
            this.labelMinPulse = new System.Windows.Forms.Label();
            this.labelServo = new System.Windows.Forms.Label();
            this.textBoxOutput = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMin)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMax)).BeginInit();
            this.groupBoxConnection.SuspendLayout();
            this.groupBoxCalibration.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarPulse)).BeginInit();
            this.SuspendLayout();
            // 
            // comboBoxServo
            // 
            this.comboBoxServo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxServo.FormattingEnabled = true;
            this.comboBoxServo.Location = new System.Drawing.Point(87, 19);
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
            this.numericUpDownMin.Location = new System.Drawing.Point(88, 46);
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
            this.numericUpDownMax.Location = new System.Drawing.Point(88, 72);
            this.numericUpDownMax.Name = "numericUpDownMax";
            this.numericUpDownMax.Size = new System.Drawing.Size(120, 20);
            this.numericUpDownMax.TabIndex = 3;
            this.numericUpDownMax.ValueChanged += new System.EventHandler(this.numericUpDownMax_ValueChanged);
            // 
            // comboBoxPort
            // 
            this.comboBoxPort.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxPort.FormattingEnabled = true;
            this.comboBoxPort.Location = new System.Drawing.Point(6, 21);
            this.comboBoxPort.Name = "comboBoxPort";
            this.comboBoxPort.Size = new System.Drawing.Size(121, 21);
            this.comboBoxPort.TabIndex = 4;
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(133, 19);
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
            this.buttonClose.Location = new System.Drawing.Point(214, 19);
            this.buttonClose.Name = "buttonClose";
            this.buttonClose.Size = new System.Drawing.Size(75, 23);
            this.buttonClose.TabIndex = 6;
            this.buttonClose.Text = "Close";
            this.buttonClose.UseVisualStyleBackColor = true;
            this.buttonClose.Click += new System.EventHandler(this.buttonClose_Click);
            // 
            // buttonGo
            // 
            this.buttonGo.Location = new System.Drawing.Point(214, 96);
            this.buttonGo.Name = "buttonGo";
            this.buttonGo.Size = new System.Drawing.Size(75, 23);
            this.buttonGo.TabIndex = 7;
            this.buttonGo.Text = "Go";
            this.buttonGo.UseVisualStyleBackColor = true;
            this.buttonGo.Click += new System.EventHandler(this.buttonGo_Click);
            // 
            // textBoxAngle
            // 
            this.textBoxAngle.Location = new System.Drawing.Point(88, 98);
            this.textBoxAngle.Name = "textBoxAngle";
            this.textBoxAngle.Size = new System.Drawing.Size(120, 20);
            this.textBoxAngle.TabIndex = 8;
            // 
            // groupBoxConnection
            // 
            this.groupBoxConnection.Controls.Add(this.comboBoxPort);
            this.groupBoxConnection.Controls.Add(this.buttonConnect);
            this.groupBoxConnection.Controls.Add(this.buttonClose);
            this.groupBoxConnection.Location = new System.Drawing.Point(12, 12);
            this.groupBoxConnection.Name = "groupBoxConnection";
            this.groupBoxConnection.Size = new System.Drawing.Size(296, 55);
            this.groupBoxConnection.TabIndex = 10;
            this.groupBoxConnection.TabStop = false;
            this.groupBoxConnection.Text = "Connection";
            // 
            // groupBoxCalibration
            // 
            this.groupBoxCalibration.Controls.Add(this.trackBarPulse);
            this.groupBoxCalibration.Controls.Add(this.labelPulse);
            this.groupBoxCalibration.Controls.Add(this.textBoxPulse);
            this.groupBoxCalibration.Controls.Add(this.buttonGoPulse);
            this.groupBoxCalibration.Controls.Add(this.labelAngle);
            this.groupBoxCalibration.Controls.Add(this.labelMaxPulse);
            this.groupBoxCalibration.Controls.Add(this.labelMinPulse);
            this.groupBoxCalibration.Controls.Add(this.labelServo);
            this.groupBoxCalibration.Controls.Add(this.buttonGo);
            this.groupBoxCalibration.Controls.Add(this.textBoxAngle);
            this.groupBoxCalibration.Controls.Add(this.comboBoxServo);
            this.groupBoxCalibration.Controls.Add(this.numericUpDownMin);
            this.groupBoxCalibration.Controls.Add(this.numericUpDownMax);
            this.groupBoxCalibration.Location = new System.Drawing.Point(12, 73);
            this.groupBoxCalibration.Name = "groupBoxCalibration";
            this.groupBoxCalibration.Size = new System.Drawing.Size(296, 232);
            this.groupBoxCalibration.TabIndex = 11;
            this.groupBoxCalibration.TabStop = false;
            this.groupBoxCalibration.Text = "groupBoxCalibration";
            // 
            // trackBarPulse
            // 
            this.trackBarPulse.Location = new System.Drawing.Point(6, 167);
            this.trackBarPulse.Maximum = 250;
            this.trackBarPulse.Minimum = 50;
            this.trackBarPulse.Name = "trackBarPulse";
            this.trackBarPulse.Size = new System.Drawing.Size(283, 45);
            this.trackBarPulse.TabIndex = 13;
            this.trackBarPulse.TickFrequency = 10;
            this.trackBarPulse.Value = 150;
            this.trackBarPulse.ValueChanged += new System.EventHandler(this.trackBarPulse_ValueChanged);
            // 
            // labelPulse
            // 
            this.labelPulse.AutoSize = true;
            this.labelPulse.Location = new System.Drawing.Point(6, 130);
            this.labelPulse.Name = "labelPulse";
            this.labelPulse.Size = new System.Drawing.Size(33, 13);
            this.labelPulse.TabIndex = 12;
            this.labelPulse.Text = "Pulse";
            // 
            // textBoxPulse
            // 
            this.textBoxPulse.Location = new System.Drawing.Point(88, 127);
            this.textBoxPulse.Name = "textBoxPulse";
            this.textBoxPulse.Size = new System.Drawing.Size(120, 20);
            this.textBoxPulse.TabIndex = 11;
            // 
            // buttonGoPulse
            // 
            this.buttonGoPulse.Location = new System.Drawing.Point(214, 125);
            this.buttonGoPulse.Name = "buttonGoPulse";
            this.buttonGoPulse.Size = new System.Drawing.Size(75, 23);
            this.buttonGoPulse.TabIndex = 10;
            this.buttonGoPulse.Text = "Go";
            this.buttonGoPulse.UseVisualStyleBackColor = true;
            this.buttonGoPulse.Click += new System.EventHandler(this.buttonGoPulse_Click);
            // 
            // labelAngle
            // 
            this.labelAngle.AutoSize = true;
            this.labelAngle.Location = new System.Drawing.Point(6, 101);
            this.labelAngle.Name = "labelAngle";
            this.labelAngle.Size = new System.Drawing.Size(34, 13);
            this.labelAngle.TabIndex = 9;
            this.labelAngle.Text = "Angle";
            // 
            // labelMaxPulse
            // 
            this.labelMaxPulse.AutoSize = true;
            this.labelMaxPulse.Location = new System.Drawing.Point(6, 74);
            this.labelMaxPulse.Name = "labelMaxPulse";
            this.labelMaxPulse.Size = new System.Drawing.Size(56, 13);
            this.labelMaxPulse.TabIndex = 4;
            this.labelMaxPulse.Text = "Max Pulse";
            // 
            // labelMinPulse
            // 
            this.labelMinPulse.AutoSize = true;
            this.labelMinPulse.Location = new System.Drawing.Point(6, 48);
            this.labelMinPulse.Name = "labelMinPulse";
            this.labelMinPulse.Size = new System.Drawing.Size(53, 13);
            this.labelMinPulse.TabIndex = 3;
            this.labelMinPulse.Text = "Min Pulse";
            // 
            // labelServo
            // 
            this.labelServo.AutoSize = true;
            this.labelServo.Location = new System.Drawing.Point(6, 22);
            this.labelServo.Name = "labelServo";
            this.labelServo.Size = new System.Drawing.Size(35, 13);
            this.labelServo.TabIndex = 2;
            this.labelServo.Text = "Servo";
            // 
            // textBoxOutput
            // 
            this.textBoxOutput.Location = new System.Drawing.Point(12, 311);
            this.textBoxOutput.Multiline = true;
            this.textBoxOutput.Name = "textBoxOutput";
            this.textBoxOutput.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBoxOutput.Size = new System.Drawing.Size(295, 160);
            this.textBoxOutput.TabIndex = 12;
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(322, 483);
            this.Controls.Add(this.textBoxOutput);
            this.Controls.Add(this.groupBoxCalibration);
            this.Controls.Add(this.groupBoxConnection);
            this.Name = "FormMain";
            this.Text = "Calibration";
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMin)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMax)).EndInit();
            this.groupBoxConnection.ResumeLayout(false);
            this.groupBoxCalibration.ResumeLayout(false);
            this.groupBoxCalibration.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarPulse)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ComboBox comboBoxServo;
        private System.Windows.Forms.NumericUpDown numericUpDownMin;
        private System.Windows.Forms.NumericUpDown numericUpDownMax;
        private System.Windows.Forms.ComboBox comboBoxPort;
        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.Button buttonClose;
        private System.Windows.Forms.Button buttonGo;
        private System.Windows.Forms.TextBox textBoxAngle;
        private System.Windows.Forms.GroupBox groupBoxConnection;
        private System.Windows.Forms.GroupBox groupBoxCalibration;
        private System.Windows.Forms.Label labelAngle;
        private System.Windows.Forms.Label labelMaxPulse;
        private System.Windows.Forms.Label labelMinPulse;
        private System.Windows.Forms.Label labelServo;
        private System.Windows.Forms.TextBox textBoxOutput;
        private System.Windows.Forms.Label labelPulse;
        private System.Windows.Forms.TextBox textBoxPulse;
        private System.Windows.Forms.Button buttonGoPulse;
        private System.Windows.Forms.TrackBar trackBarPulse;
    }
}

