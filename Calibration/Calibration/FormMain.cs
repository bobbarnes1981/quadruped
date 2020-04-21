﻿using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Ports;
using System.Windows.Forms;

namespace Calibration
{
    public partial class FormMain : Form
    {
        private string[] ports;

        private SerialPort port;

        public FormMain()
        {
            InitializeComponent();

            ports = SerialPort.GetPortNames();

            comboBoxPort.DataSource = ports;
            comboBoxServo.DataSource = new[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
        }

        private string[] readLines()
        {
            List<string> lines = new List<string>();
            System.Threading.Thread.Sleep(500);
            while (port.BytesToRead > 0)
            {
                string line = port.ReadLine();
                lines.Add(line);
                appendLine(line);
                System.Threading.Thread.Sleep(100);
            }
            return lines.ToArray();
        }

        private void appendLine(string text)
        {
            textBoxOutput.AppendText(text);
            textBoxOutput.AppendText("\r\n");
        }

        private void readInfo()
        {
            port.WriteLine("i");
            string[] lines = readLines();
            foreach (var line in lines)
            {
                string[] parts = line.Split(':');
                switch (parts[0])
                {
                    case "servo":
                        comboBoxServo.SelectedItem = int.Parse(parts[1].Trim());
                        break;
                    case "min":
                        numericUpDownMin.Value = decimal.Parse(parts[1]);
                        break;
                    case "max":
                        numericUpDownMax.Value = decimal.Parse(parts[1]);
                        break;
                    default:
                        MessageBox.Show(line);
                        break;
                }
            }
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            if (port == null)
            {
                port = new SerialPort((string)comboBoxPort.SelectedValue);
                try
                {
                    port.Open();
                    readLines();

                    readInfo();

                    buttonClose.Enabled = true;
                    buttonConnect.Enabled = false;
                }
                catch (IOException exception)
                {
                    MessageBox.Show(exception.Message);
                }
            }
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            if (port != null && port.IsOpen)
            {
                port.Close();
                port = null;
                buttonClose.Enabled = false;
                buttonConnect.Enabled = true;
            }
        }

        private void numericUpDownMin_ValueChanged(object sender, EventArgs e)
        {
            port.WriteLine($"n{(int)(numericUpDownMin.Value * 1000000)}");
            readLines();
        }

        private void numericUpDownMax_ValueChanged(object sender, EventArgs e)
        {
            port.WriteLine($"x{(int)(numericUpDownMax.Value * 1000000)}");
            readLines();
        }

        private void buttonGo_Click(object sender, EventArgs e)
        {
            port.WriteLine($"g{int.Parse(textBoxAngle.Text)}");
            readLines();
        }

        private void buttonTest_Click(object sender, EventArgs e)
        {
            port.WriteLine("t");
            readLines();
        }

        private void comboBoxServo_SelectedValueChanged(object sender, EventArgs e)
        {
            if (port != null)
            {
                port.WriteLine($"s{(int)comboBoxServo.SelectedValue}");
                readLines();
            }
        }
    }
}