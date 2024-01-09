using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MyApp;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public IntPtr m_Img = Dll1.CreateNImage();
        public IntPtr hbitmap;
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //IntPtr calculatorInstance = Dll1.CreateCalculatorInstance();
            //int result = Dll1.Calculator_Add(calculatorInstance, 3, 4);
            //Dll1.DestroyCalculatorInstance(calculatorInstance);


            openFileDialog1.Filter = "BMP file |*.bmp";
            string path;

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                path = openFileDialog1.FileName;

                if (Dll1.LoadBMP(m_Img, path))
                {

                    hbitmap = Dll1.GetBitmap(m_Img);

                    if (pictureBox1.Image != null)
                        pictureBox1.Image.Dispose();
                    pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
                    pictureBox1.Refresh();
                }
                else
                    MessageBox.Show("Error", "Error");
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Dll1.DestroyNImage(m_Img);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string path;
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                path = saveFileDialog1.FileName;

                if (Dll1.SaveBMP(m_Img, path))
                {

                    hbitmap = Dll1.GetBitmap(m_Img);

                    if (pictureBox1.Image != null)
                        pictureBox1.Image.Dispose();
                    pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
                    pictureBox1.Refresh();
                }
                else
                    MessageBox.Show("Error", "Error");
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Dll1.MeanFilter3x3(m_Img);
            hbitmap = Dll1.GetBitmap(m_Img);

            if (pictureBox1.Image != null)
                pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
            pictureBox1.Refresh();

        }

        private void button4_Click(object sender, EventArgs e)
        {

            Dll1.SobelFilter(m_Img);
            hbitmap = Dll1.GetBitmap(m_Img);

            if (pictureBox1.Image != null)
                pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
            pictureBox1.Refresh();
        }

        private void button5_Click(object sender, EventArgs e)
        {

            Dll1.LaplacianFilter(m_Img);
            hbitmap = Dll1.GetBitmap(m_Img);

            if (pictureBox1.Image != null)
                pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
            pictureBox1.Refresh();

        }

        private void button6_Click(object sender, EventArgs e)
        {

            Dll1.Threshold(m_Img);
            hbitmap = Dll1.GetBitmap(m_Img);

            if (pictureBox1.Image != null)
                pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
            pictureBox1.Refresh();
        }

        private void button7_Click(object sender, EventArgs e)
        {

            Dll1.AdaptiveMeanThreshold(m_Img, int.Parse(textBox1.Text));
            hbitmap = Dll1.GetBitmap(m_Img);

            if (pictureBox1.Image != null)
                pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
            pictureBox1.Refresh();

        }

        private void button8_Click(object sender, EventArgs e)
        {

            Dll1.AdaptiveGaussianThreshold(m_Img, int.Parse(textBox1.Text));
            hbitmap = Dll1.GetBitmap(m_Img);

            if (pictureBox1.Image != null)
                pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
            pictureBox1.Refresh();
        }

        private void button9_Click(object sender, EventArgs e)
        {

            textBox1.Text =  Dll1.Blob_Labelling(m_Img).ToString();
            hbitmap = Dll1.GetBitmap(m_Img);

            if (pictureBox1.Image != null)
                pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
            pictureBox1.Refresh();
        }

        private void button10_Click(object sender, EventArgs e)
        {

            textBox1.Text = Dll1.Contour_Tracing(m_Img).ToString();
            hbitmap = Dll1.GetBitmap(m_Img);

            if (pictureBox1.Image != null)
                pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
            pictureBox1.Refresh();

        }

        private void button11_Click(object sender, EventArgs e)
        {

            textBox1.Text = Dll1.CalculateBlobArea(m_Img).ToString();
        }
    }
}
