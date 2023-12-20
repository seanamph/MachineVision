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
        public IntPtr m_Obj = NObjectDLL.CreateNObject();
        public IntPtr m_Gauge = NGaugeDLL.CreateNGauge();

        public IntPtr m_Mask_Img;
        public IntPtr m_Otsu_Img;
        public IntPtr m_Erosion_Img;
        public IntPtr m_Dilation_Img;

        public int wid, hei;

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
                    wid = NImageDLL.GetWidth(m_Img);
                    hei = NImageDLL.GetHeight(m_Img);

                    NImageDLL.DestroyNImage(m_Mask_Img);
                    NImageDLL.DestroyNImage(m_Otsu_Img);
                    NImageDLL.DestroyNImage(m_Dilation_Img);
                    NImageDLL.DestroyNImage(m_Erosion_Img);

                    m_Mask_Img = NImageDLL.CreateNImageEx(wid, hei);
                    m_Otsu_Img = NImageDLL.CreateNImageEx(wid, hei);
                    m_Erosion_Img = NImageDLL.CreateNImageEx(wid, hei);
                    m_Dilation_Img = NImageDLL.CreateNImageEx(wid, hei);

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
            NImageDLL.DestroyNImage(m_Mask_Img);
            NImageDLL.DestroyNImage(m_Otsu_Img);
            NImageDLL.DestroyNImage(m_Dilation_Img);
            NImageDLL.DestroyNImage(m_Erosion_Img);

            NImgProcessDLL.DestroyNImgProcess(m_ImgPro);

            NObjectDLL.DestroyNObject(m_Obj);

            NGaugeDLL.DestroyNGauge(m_Gauge);
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
            NImgProcessDLL.OtsuThresholding(m_Img, m_Otsu_Img, m_ImgPro);

            hbitmap = NImageDLL.GetBitmap(m_Otsu_Img);

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

            NImgProcessDLL.Subtract(m_Dilation_Img, m_Erosion_Img, m_ImgPro);

            sw.Stop();

            hbitmap = NImageDLL.GetBitmap(m_Dilation_Img);

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

            NImgProcessDLL.BitwiseXOR(m_Img, m_Img_SIMD, m_ImgPro);

            sw.Stop();

            hbitmap = NImageDLL.GetBitmap(m_Img);

            if (pictureBox1.Image != null)
                pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
            pictureBox1.Refresh();

            label1.Text = String.Format("Time: {0} us", sw.ElapsedTicks * 1000000F / Stopwatch.Frequency);
        }

        private void button12_Click(object sender, EventArgs e)
        {
            NImgProcessDLL.OtsuThresholding(m_Img, m_Otsu_Img, m_ImgPro);

            sw.Reset();
            sw.Start();

            int blob_count = NObjectDLL.Blob_Labelling(m_Otsu_Img, m_Obj);

            sw.Stop();


            // Contour Tracing and Drawing
            Font drawFont = new Font("Time New Roman", 12);
            SolidBrush drawBrush = new SolidBrush(Color.LightSkyBlue);
            Graphics g = pictureBox1.CreateGraphics();
            int[] ct_x = new int[1000];
            int[] ct_y = new int[1000];
            int chain_count = 0;
            int i, j, blob_area;
            for (i = 0; i < blob_count; i++)
            {
                chain_count = NObjectDLL.Contour_Tracing(m_Otsu_Img, m_Obj, i, ref ct_x[0], ref ct_y[0]);

                blob_area = NObjectDLL.Area(m_Obj, i);

                g.DrawString(blob_area.ToString(), drawFont, drawBrush, ct_x[0], ct_y[0]);
                for (j = 0; j < chain_count - 1 ; j++)
                {
                    g.DrawLine(Pens.Red, ct_x[j], ct_y[j], ct_x[j+1], ct_y[j+1]);
                }
            }


            label1.Text = String.Format("Time: {0} us", sw.ElapsedTicks * 1000000F / Stopwatch.Frequency);
            label2.Text = String.Format("Blob_Count: {0} ", blob_count);
        }

        private void button13_Click(object sender, EventArgs e)
        {
            sw.Reset();
            sw.Start();

            NImgProcessDLL.OtsuThresholding(m_Img, m_Otsu_Img, m_ImgPro);
            NImgProcessDLL.Dilation3x3(m_Otsu_Img, m_Dilation_Img, m_ImgPro);

            sw.Stop();

            hbitmap = NImageDLL.GetBitmap(m_Dilation_Img);

            if (pictureBox1.Image != null)
                pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
            pictureBox1.Refresh();

            label1.Text = String.Format("Time: {0} us", sw.ElapsedTicks * 1000000F / Stopwatch.Frequency);
        }

        private void button15_Click(object sender, EventArgs e)
        {
            if (NObjectDLL.CreateMaskFromObject(m_Mask_Img, m_Obj, 15))
            {
                hbitmap = NImageDLL.GetBitmap(m_Mask_Img);

                if (pictureBox1.Image != null)
                    pictureBox1.Image.Dispose();
                pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
                pictureBox1.Refresh();
            }

             
        }

        private void button16_Click(object sender, EventArgs e)
        {
            // 產生邊緣運算遮罩
            NImgProcessDLL.OtsuThresholding(m_Img, m_Otsu_Img, m_ImgPro);
            NImgProcessDLL.Dilation3x3(m_Otsu_Img, m_Dilation_Img, m_ImgPro);
            NImgProcessDLL.Erosion3x3(m_Otsu_Img, m_Erosion_Img, m_ImgPro);
            NImgProcessDLL.Subtract(m_Dilation_Img, m_Erosion_Img, m_ImgPro);

            // 對邊緣遮罩進行連結體編碼
            int blob_count = NObjectDLL.Blob_Labelling(m_Dilation_Img, m_Obj);

            // Subpixel Edge Detection, Circle Fitting and Drawing
            Font drawFont = new Font("Time New Roman", 12);
            SolidBrush drawBrush = new SolidBrush(Color.LightSkyBlue);
            Graphics g = pictureBox1.CreateGraphics();
            int[] ct_x = new int[10000];
            int[] ct_y = new int[10000];
            double[] sub_x = new double[10000];
            double[] sub_y = new double[10000];
            int edge_count = 0;

            double result_x =0, result_y=0, result_r=0;

            for (int i = 0; i < blob_count; i++)
            {
                // 從 Object 產生二值化遮罩
                if (NObjectDLL.CreateMaskFromObject(m_Mask_Img, m_Obj,i))
                {
                    // 使用遮罩做次像素邊緣偵測
                    edge_count = NGaugeDLL.SubPixel_EdgeDetector(m_Img, m_Mask_Img, m_Obj, ref sub_x[0], ref sub_y[0]);

                    // 擬合
                    NGaugeDLL.CircleFitByKasa(m_Gauge, ref sub_x[0], ref sub_y[0], edge_count, ref result_x, ref result_y, ref result_r);

                    // 畫圓
                    g.DrawEllipse(Pens.Red, Convert.ToInt32(result_x - result_r),
                                  Convert.ToInt32(result_y - result_r),
                                  Convert.ToInt32(result_r * 2), Convert.ToInt32(result_r * 2));
                    // 畫中心線
                    g.DrawLine(Pens.YellowGreen, Convert.ToInt32(result_x - 5), Convert.ToInt32(result_y),
                               Convert.ToInt32(result_x + 5), Convert.ToInt32(result_y));
                    g.DrawLine(Pens.YellowGreen, Convert.ToInt32(result_x), Convert.ToInt32(result_y - 5),
                                Convert.ToInt32(result_x), Convert.ToInt32(result_y + 5));

                }
                
            }

            label1.Text = String.Format("Time: {0} us", sw.ElapsedTicks * 1000000F / Stopwatch.Frequency);
            label2.Text = String.Format("Blob_Count: {0} ", blob_count);
        }

        private void button17_Click(object sender, EventArgs e)
        {
            NImgProcessDLL.OtsuThresholding(m_Img, m_Otsu_Img, m_ImgPro);

            sw.Reset();
            sw.Start();

            int blob_count = NObjectDLL.Blob_Labelling(m_Otsu_Img, m_Obj);

            sw.Stop();


            // Contour Tracing, Fitting and Drawing
            Font drawFont = new Font("Time New Roman", 12);
            SolidBrush drawBrush = new SolidBrush(Color.LightSkyBlue);
            Graphics g = pictureBox1.CreateGraphics();
            int[] ct_x = new int[10000];
            int[] ct_y = new int[10000];
            double[] sub_x = new double[10000];
            double[] sub_y = new double[10000];

            int chain_count = 0;
            int i, j;

            double result_x = 0, result_y = 0, result_r = 0;

            for (i = 0; i < blob_count; i++)
            {
                // 輪廓追蹤
                chain_count = NObjectDLL.Contour_Tracing(m_Otsu_Img, m_Obj, i, ref ct_x[0], ref ct_y[0]);

                for (j= 0; j< chain_count;j++)
                {
                    sub_x[j] = ct_x[j];
                    sub_y[j] = ct_y[j];
                }

                // 擬合
                NGaugeDLL.CircleFitByKasa(m_Gauge, ref sub_x[0], ref sub_y[0], chain_count, ref result_x, ref result_y, ref result_r);

                // 畫圓
                g.DrawEllipse(Pens.Blue, Convert.ToInt32(result_x - result_r),
                              Convert.ToInt32(result_y - result_r),
                              Convert.ToInt32(result_r * 2), Convert.ToInt32(result_r * 2));
                // 畫中心線
                g.DrawLine(Pens.Purple, Convert.ToInt32(result_x - 5), Convert.ToInt32(result_y),
                           Convert.ToInt32(result_x + 5), Convert.ToInt32(result_y));
                g.DrawLine(Pens.Purple, Convert.ToInt32(result_x), Convert.ToInt32(result_y - 5),
                            Convert.ToInt32(result_x), Convert.ToInt32(result_y + 5));
            }


            label1.Text = String.Format("Time: {0} us", sw.ElapsedTicks * 1000000F / Stopwatch.Frequency);
            label2.Text = String.Format("Blob_Count: {0} ", blob_count);
        }

        private void button14_Click(object sender, EventArgs e)
        {
            sw.Reset();
            sw.Start();

            NImgProcessDLL.OtsuThresholding(m_Img, m_Otsu_Img, m_ImgPro);
            NImgProcessDLL.Erosion3x3(m_Otsu_Img, m_Erosion_Img, m_ImgPro);

            sw.Stop();

            hbitmap = NImageDLL.GetBitmap(m_Erosion_Img);

            if (pictureBox1.Image != null)
                pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
            pictureBox1.Refresh();

            label1.Text = String.Format("Time: {0} us", sw.ElapsedTicks * 1000000F / Stopwatch.Frequency);
        }
    }
}
