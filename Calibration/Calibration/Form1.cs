using System;
using System.IO;
using System.IO.Ports;
using System.Windows.Forms;

namespace Calibration
{
    public partial class Form1 : Form
    {
        private string[] ports;

        private SerialPort port;

        public Form1()
        {
            InitializeComponent();

            ports = SerialPort.GetPortNames();

            comboBoxPort.DataSource = ports;
            comboBoxServo.DataSource = new[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
        }

        private void button1_Click(object sender, EventArgs e)
        {
            SerialPort port = new SerialPort("COM3");
            //port.DataReceived += Port_DataReceived;
            port.Open();

            port.WriteLine("i");

            port.WriteLine("s0");
            port.WriteLine("n600");
            port.WriteLine("x2300");
            port.WriteLine("g90");
            System.Threading.Thread.Sleep(1000);
            port.WriteLine("t");
            port.Close();
        }

        private void Port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            System.Diagnostics.Debug.WriteLine(e);
        }

        private void readInfo()
        {
            port.WriteLine("i");
            System.Threading.Thread.Sleep(500);
            while(port.BytesToRead > 0)
            {
                string d = port.ReadLine();
                string[] parts = d.Split(':');
                switch (parts[0])
                {
                    case "servo":
                        comboBoxServo.SelectedItem = parts[1];
                        break;
                    case "min":
                        numericUpDownMin.Value = decimal.Parse(parts[1]);
                        break;
                    case "max":
                        numericUpDownMax.Value = decimal.Parse(parts[1]);
                        break;
                    default:
                        MessageBox.Show(d);
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
            System.Threading.Thread.Sleep(500);
            while (port.BytesToRead > 0)
            {
                MessageBox.Show(port.ReadLine());
            }
        }

        private void numericUpDownMax_ValueChanged(object sender, EventArgs e)
        {
            port.WriteLine($"x{(int)(numericUpDownMax.Value * 1000000)}");
            System.Threading.Thread.Sleep(500);
            while (port.BytesToRead > 0)
            {
                MessageBox.Show(port.ReadLine());
            }
        }

        private void buttonGo_Click(object sender, EventArgs e)
        {

        }

        private void buttonTest_Click(object sender, EventArgs e)
        {
            port.WriteLine("t");
        }

        private void comboBoxServo_SelectedValueChanged(object sender, EventArgs e)
        {
            if (port != null)
            {
                port.WriteLine($"s{(int)comboBoxServo.SelectedValue}");
            }
        }
    }
}
