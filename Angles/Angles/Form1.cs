using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Angles
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private double degToRad(double deg)
        {
            return deg * (Math.PI / 180);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            double scale = 3.6;

            int startx = 10;
            int starty = pictureBox1.Height / 2;
            int ty = -38;
            int tx = 150;

            double angle1 = 32.4;
            double h1 = 59;
            double a1 = Math.Cos(degToRad(angle1)) * h1;
            double b1 = Math.Sin(degToRad(angle1)) * h1;

            double z = Math.Sqrt(Math.Pow(a1, 2) + Math.Pow(b1, 2));

            float ax = startx;
            float ay = starty;

            float bx = (float)(startx + (a1 * scale));
            float by = (float)(starty - (b1 * scale));

            double angle2 = 112.8;
            double h2 = 122;

            double angle3 = 180 - (angle1 + angle2);
            double a2 = Math.Cos(degToRad(angle3)) * h2;
            double b2 = Math.Sin(degToRad(angle3)) * h2;

            float cx = (float)(bx + (a2 * scale));
            float cy = (float)(by + (b2 * scale));

            Bitmap bmp = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            using (Graphics g = Graphics.FromImage(bmp))
            {
                g.DrawLine(new Pen(Color.Gray),
                    startx, starty,
                    startx, starty - (float)(ty * scale));
                g.DrawLine(new Pen(Color.Black),
                    startx, starty - (float)(ty * scale),
                    startx + (float)(tx * scale), starty - (float)(ty * scale));

                g.DrawLine(new Pen(Color.Red),
                    ax, ay,
                    bx, by);
                g.DrawLine(new Pen(Color.Green),
                    bx, by,
                    cx, cy);
            }
            pictureBox1.Image = bmp;
        }
    }
}
