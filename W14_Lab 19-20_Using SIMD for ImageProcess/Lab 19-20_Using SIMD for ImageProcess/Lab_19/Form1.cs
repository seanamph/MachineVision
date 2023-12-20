using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;

namespace MyApp
{
    public partial class Form1 : Form
    {
        public IntPtr m_Img = NImageDLL.CreateNImage();
        public IntPtr m_Img_SIMD = NImageDLL.CreateNImage();
        public IntPtr m_ImgPro = NImgProcessDLL.CreateNImgProcess();
        

        public IntPtr hbitmap;

        Stopwatch sw = new Stopwatch();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "BMP file |*.bmp";
            string path;

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                path = openFileDialog1.FileName;

                if (NImageDLL.LoadBMP(m_Img, path))
                {

                    hbitmap = NImageDLL.GetBitmap(m_Img);

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
            NImageDLL.DestroyNImage(m_Img);
            NImageDLL.DestroyNImage(m_Img_SIMD);
            NImgProcessDLL.DestroyNImgProcess(m_ImgPro);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            sw.Reset();
            sw.Start();

            NImgProcessDLL.Inverse(m_Img, m_ImgPro);

            sw.Stop();


            hbitmap = NImageDLL.GetBitmap(m_Img);

            if (pictureBox1.Image != null)
                pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
            pictureBox1.Refresh();

            label1.Text = String.Format("Time: {0} us", sw.ElapsedTicks * 1000000F / Stopwatch.Frequency);

        }

        private void button3_Click(object sender, EventArgs e)
        {
            sw.Reset();
            sw.Restart();

            NImgProcessDLL.SingleThresholding(m_Img, m_ImgPro, 100);

            sw.Stop();

            hbitmap = NImageDLL.GetBitmap(m_Img);

            if (pictureBox1.Image != null)
                pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
            pictureBox1.Refresh();

            label1.Text = String.Format("Time: {0} us", sw.ElapsedTicks * 1000000F / Stopwatch.Frequency);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            NImgProcessDLL.OtsuThresholding(m_Img, m_ImgPro);

            hbitmap = NImageDLL.GetBitmap(m_Img);

            if (pictureBox1.Image != null)
                pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
            pictureBox1.Refresh();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            NImgProcessDLL.Sobel(m_Img, m_ImgPro);

            hbitmap = NImageDLL.GetBitmap(m_Img);

            if (pictureBox1.Image != null)
                pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
            pictureBox1.Refresh();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            NImgProcessDLL.Laplacian(m_Img, m_ImgPro);

            hbitmap = NImageDLL.GetBitmap(m_Img);

            if (pictureBox1.Image != null)
                pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
            pictureBox1.Refresh();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            NImgProcessDLL.Mean(m_Img, m_ImgPro);

            hbitmap = NImageDLL.GetBitmap(m_Img);

            if (pictureBox1.Image != null)
                pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
            pictureBox1.Refresh();
        }

        private void button8_Click(object sender, EventArgs e)
        {
            string  path = openFileDialog1.FileName;

            if (NImageDLL.LoadBMP(m_Img_SIMD, path))
            {
                sw.Reset();
                sw.Start();

				// Lab_16 Using SIMD for Inverse
                NImgProcessDLL.Inverse_SIMD(m_Img_SIMD, m_ImgPro);

                sw.Stop();

                hbitmap = NImageDLL.GetBitmap(m_Img_SIMD);

                if (pictureBox1.Image != null)
                    pictureBox1.Image.Dispose();
                pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
                pictureBox1.Refresh();

                label1.Text = String.Format("Time: {0} us", sw.ElapsedTicks * 1000000F / Stopwatch.Frequency);
            }
            else
                MessageBox.Show("Error", "Error");

        }

        private void button9_Click(object sender, EventArgs e)
        {
            string path = openFileDialog1.FileName;

            if (NImageDLL.LoadBMP(m_Img_SIMD, path))
            {
                sw.Reset();
                sw.Start();

				// Lab_16 Using SIMD for Thresholding
                NImgProcessDLL.SingleThresholding_SIMD(m_Img_SIMD, m_ImgPro, 100);

                sw.Stop();

                hbitmap = NImageDLL.GetBitmap(m_Img_SIMD);

                if (pictureBox1.Image != null)
                    pictureBox1.Image.Dispose();
                pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
                pictureBox1.Refresh();

                label1.Text = String.Format("Time: {0} us", sw.ElapsedTicks * 1000000F / Stopwatch.Frequency);
            }
            else
                MessageBox.Show("Error", "Error");
        }

        private void button10_Click(object sender, EventArgs e)
        {
            sw.Reset();
            sw.Start();

			// Lab_17 Please Using SIMD for Subtracting
            NImgProcessDLL.Subtract(m_Img, m_Img_SIMD, m_ImgPro);

            sw.Stop();

            hbitmap = NImageDLL.GetBitmap(m_Img);

            if (pictureBox1.Image != null)
                pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
            pictureBox1.Refresh();

            label1.Text = String.Format("Time: {0} us", sw.ElapsedTicks * 1000000F / Stopwatch.Frequency);
        }

        private void button11_Click(object sender, EventArgs e)
        {
            sw.Reset();
            sw.Start();

			// Lab_17 Please Using SIMD for BitwiseXOR
            NImgProcessDLL.BitwiseXOR(m_Img, m_Img_SIMD, m_ImgPro);

            sw.Stop();

            hbitmap = NImageDLL.GetBitmap(m_Img);

            if (pictureBox1.Image != null)
                pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
            pictureBox1.Refresh();

            label1.Text = String.Format("Time: {0} us", sw.ElapsedTicks * 1000000F / Stopwatch.Frequency);
        }
    }
}
