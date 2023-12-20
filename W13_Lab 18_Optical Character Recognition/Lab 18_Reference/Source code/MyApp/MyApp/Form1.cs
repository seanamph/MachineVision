using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using Perceptron;

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
        public IntPtr m_Split_Img;
        public IntPtr m_OCR_Img = NImageDLL.CreateNImageEx(10,15);

        public int wid, hei;

        public IntPtr hbitmap;
        public IntPtr hbitmap2;

        bool bmp_load = false;

        Stopwatch sw = new Stopwatch();

        MLP mlp = new MLP();

        public int OCR_Jog_index = 0;

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
                    NImageDLL.DestroyNImage(m_Split_Img);

                    m_Mask_Img = NImageDLL.CreateNImageEx(wid, hei);
                    m_Otsu_Img = NImageDLL.CreateNImageEx(wid, hei);
                    m_Erosion_Img = NImageDLL.CreateNImageEx(wid, hei);
                    m_Dilation_Img = NImageDLL.CreateNImageEx(wid, hei);
                    m_Split_Img = NImageDLL.CreateNImage();

                    if (pictureBox1.Image != null)
                        pictureBox1.Image.Dispose();
                    pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
                    pictureBox1.Refresh();

                    bmp_load = true;
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
            NImageDLL.DestroyNImage(m_Split_Img);
            NImageDLL.DestroyNImage(m_OCR_Img);

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

        private void button18_Click(object sender, EventArgs e)
        {
            if (!bmp_load) return;

			// Otsu 二值化
            NImgProcessDLL.OtsuThresholding(m_Img, m_Otsu_Img, m_ImgPro);
            
			// 影像反向 (SIMD 加速)
			NImgProcessDLL.Inverse_SIMD(m_Otsu_Img, m_ImgPro);

            int blob_count = NObjectDLL.Blob_Labelling(m_Otsu_Img, m_Obj);

            // Char Segmentation
            int start_x = 0, start_y = 0, rect_w = 0, rect_h = 0;

            Byte[] vector = new Byte[150];
            Graphics g = pictureBox1.CreateGraphics();
            pictureBox1.Refresh();
            for (int i = 0; i < blob_count; i++)
            {
                if (NObjectDLL.Rect(m_Obj, i, ref start_x, ref start_y, ref rect_w, ref rect_h))
				{
					g.DrawLine(Pens.Purple, Convert.ToInt32(start_x), Convert.ToInt32(start_y),
                               Convert.ToInt32(start_x + rect_w), Convert.ToInt32(start_y));
					g.DrawLine(Pens.Purple, Convert.ToInt32(start_x + rect_w), Convert.ToInt32(start_y),
								Convert.ToInt32(start_x + rect_w), Convert.ToInt32(start_y + rect_h));
					g.DrawLine(Pens.Purple, Convert.ToInt32(start_x + rect_w), Convert.ToInt32(start_y + rect_h),
								Convert.ToInt32(start_x), Convert.ToInt32(start_y + rect_h));
					g.DrawLine(Pens.Purple, Convert.ToInt32(start_x), Convert.ToInt32(start_y + rect_h),
								Convert.ToInt32(start_x), Convert.ToInt32(start_y));
				}
            }
        }

        private void button19_Click(object sender, EventArgs e)
        {
            if (!bmp_load) return;

			// 影像前處理：Otsu 二值化  Lab 5_Using PInvoke for NImgProcess
            NImgProcessDLL.OtsuThresholding(m_Img, m_Otsu_Img, m_ImgPro);

			// 影像前處理：影像反向 Lab 5_Using PInvoke for NImgProcess
            NImgProcessDLL.Inverse(m_Otsu_Img, m_ImgPro);

			// 影像分割：Connected component labelling  Lab 12_Using PInvoke in C# for Object Detection
            int blob_count = NObjectDLL.Blob_Labelling(m_Otsu_Img, m_Obj);

            // Char Segmentation
            int start_x = 0, start_y = 0, rect_w = 0, rect_h = 0;

			// Input feature vector = 10*15 = 150
            Byte[,] samples = new Byte[150, blob_count];
            Byte[] vector = new Byte[150];
            for (int i = 0; i < blob_count; i++)
            {
                // 影像分割：取得字元外接矩形  Lab 18_Optical Character Recognition
				if (NObjectDLL.Rect(m_Obj, i, ref start_x, ref start_y, ref rect_w, ref rect_h))
                {
                    //影像分割：寬高比過大，為避免大寫 I 的誤判問題，延伸外框
					if ((double)rect_h / rect_w > 3.0)
                    {
                        start_x -= 5;
                        rect_w += 10;
                    }

					//影像分割：切割字元影像 Lab 18_Optical Character Recognition
                    if (NImgProcessDLL.Split_Image(m_Otsu_Img, start_x, start_y, rect_w, rect_h, m_Split_Img, m_ImgPro))
                    {
                        //特徵擷取：Resize image to 10*15  Lab 18_Optical Character Recognition
						if (NImgProcessDLL.Small_Transform(m_Split_Img, m_OCR_Img, m_ImgPro))
                        {
                            //特徵擷取：Transfer to 1-D feature vector Lab 18_Optical Character Recognition
							NImgProcessDLL.FromImageToVector(m_OCR_Img, ref vector[0], 150, m_ImgPro);

                            for (int j = 0; j < 150; j++)
                                samples[j, i] = vector[j];
                        }
                    }
                }
            }

            string line = "", trainer_string = "";
            int number_of_input_sets = 0;
            openFileDialog1.Filter = "Character Trainer Set (*.cts)|*.cts";
            System.IO.StreamReader character_trainer_set_file_stream;
			
			//樣式分類：讀取字元影像學習匹配的字串
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                character_trainer_set_file_stream = new System.IO.StreamReader(openFileDialog1.FileName);
                trainer_string = "";
                while ((line = character_trainer_set_file_stream.ReadLine()) != null)
                    trainer_string = trainer_string + line;

                number_of_input_sets = trainer_string.Length;

                character_trainer_set_file_stream.Close();
            }

            label3.Text = trainer_string;
			
			//樣式分類：MLP 訓練 Lab 18_Optical Character Recognition
			//samples 為輸入學習字元組的影像特徵
			//trainer_string 為每組學習影像特徵對應的字串(後續需轉為 16 bits 的 Unicode 當成輸出值)
			//字串及物體個數需匹配才能開始學習
            if (number_of_input_sets == blob_count)
                mlp.Training(samples, trainer_string, blob_count);
        }

        private void button20_Click(object sender, EventArgs e)
        {
            if (!bmp_load) return;

            if (NObjectDLL.Blob_Count(m_Obj) == 0) NObjectDLL.Blob_Labelling(m_Otsu_Img, m_Obj);
            else if (OCR_Jog_index >= NObjectDLL.Blob_Count(m_Obj)) OCR_Jog_index = 0;

            Byte[] sample = new Byte[150];
            int start_x = 0, start_y = 0, rect_w = 0, rect_h = 0;

            if (NObjectDLL.Rect(m_Obj, OCR_Jog_index, ref start_x, ref start_y, ref rect_w, ref rect_h))
            {
                if ((double) rect_h / rect_w > 3.0)
                {
                    start_x -= 5;
                    rect_w += 10;
                }

                if (NImgProcessDLL.Split_Image(m_Otsu_Img, start_x, start_y, rect_w, rect_h, m_Split_Img, m_ImgPro))
                {
                    if (NImgProcessDLL.Small_Transform(m_Split_Img, m_OCR_Img, m_ImgPro))
                    {
                        NImgProcessDLL.FromImageToVector(m_OCR_Img, ref sample[0], 150, m_ImgPro);

                        hbitmap2 = NImageDLL.GetBitmap(m_OCR_Img);

                        if (pictureBox2.Image != null)
                            pictureBox2.Image.Dispose();
                        pictureBox2.Image = System.Drawing.Image.FromHbitmap(hbitmap2);
                        pictureBox2.Refresh();
                    }
                }  
            }
               
            OCR_Jog_index++;

            pictureBox1.Refresh();
            Graphics g = pictureBox1.CreateGraphics();
            g.DrawLine(Pens.Purple, Convert.ToInt32(start_x), Convert.ToInt32(start_y),
                           Convert.ToInt32(start_x + rect_w), Convert.ToInt32(start_y));
            g.DrawLine(Pens.Purple, Convert.ToInt32(start_x + rect_w), Convert.ToInt32(start_y),
                        Convert.ToInt32(start_x + rect_w), Convert.ToInt32(start_y+ rect_h));
            g.DrawLine(Pens.Purple, Convert.ToInt32(start_x + rect_w), Convert.ToInt32(start_y + rect_h),
                        Convert.ToInt32(start_x), Convert.ToInt32(start_y + rect_h));
            g.DrawLine(Pens.Purple, Convert.ToInt32(start_x), Convert.ToInt32(start_y + rect_h),
                        Convert.ToInt32(start_x), Convert.ToInt32(start_y));

			//樣式分類：MLP 推論或分類 Lab 18_Optical Character Recognition
			//samples 為輸入字元的影像特徵
            string result = mlp.Classify(sample);

            g.DrawString(result, new Font("Time New Roman", 12), new SolidBrush(Color.OrangeRed), start_x - 10, start_y - 10);
            label3.Text = result;
        }

        private void button21_Click(object sender, EventArgs e)
        {
            if (!bmp_load) return;

            int blob_count;

            if (NObjectDLL.Blob_Count(m_Obj) == 0)
            {
                NImgProcessDLL.OtsuThresholding(m_Img, m_Otsu_Img, m_ImgPro);
                NImgProcessDLL.Inverse_SIMD(m_Otsu_Img, m_ImgPro);

                blob_count = NObjectDLL.Blob_Labelling(m_Otsu_Img, m_Obj);
            }
            else blob_count = NObjectDLL.Blob_Count(m_Obj);


            Byte[] sample = new Byte[150];
            int start_x = 0, start_y = 0, rect_w = 0, rect_h = 0;
            string result;

            Graphics g = pictureBox1.CreateGraphics();
            pictureBox1.Refresh();
            for (int i = 0; i < blob_count; i++)
            {
                if (NObjectDLL.Rect(m_Obj, i, ref start_x, ref start_y, ref rect_w, ref rect_h))
                {
                    if ((double)rect_h / rect_w > 3.0)
                    {
                        start_x -= 5;
                        rect_w += 10;
                    }

                    if (NImgProcessDLL.Split_Image(m_Otsu_Img, start_x, start_y, rect_w, rect_h, m_Split_Img, m_ImgPro))
                    {
                        if (NImgProcessDLL.Small_Transform(m_Split_Img, m_OCR_Img, m_ImgPro))
                            NImgProcessDLL.FromImageToVector(m_OCR_Img, ref sample[0], 150, m_ImgPro);
                    }
                }

                g.DrawLine(Pens.Purple, Convert.ToInt32(start_x), Convert.ToInt32(start_y),
                               Convert.ToInt32(start_x + rect_w), Convert.ToInt32(start_y));
                g.DrawLine(Pens.Purple, Convert.ToInt32(start_x + rect_w), Convert.ToInt32(start_y),
                            Convert.ToInt32(start_x + rect_w), Convert.ToInt32(start_y + rect_h));
                g.DrawLine(Pens.Purple, Convert.ToInt32(start_x + rect_w), Convert.ToInt32(start_y + rect_h),
                            Convert.ToInt32(start_x), Convert.ToInt32(start_y + rect_h));
                g.DrawLine(Pens.Purple, Convert.ToInt32(start_x), Convert.ToInt32(start_y + rect_h),
                            Convert.ToInt32(start_x), Convert.ToInt32(start_y));

                result = mlp.Classify(sample);

                g.DrawString(result, new Font("Time New Roman", 12), new SolidBrush(Color.OrangeRed), start_x-10, start_y-10);

            }         
        }

        private void button22_Click(object sender, EventArgs e)
        {
            
			//樣式分類：儲存訓練後的 MLP 參數 Lab 18_Optical Character Recognition
			saveFileDialog1.Filter = "MultiLayer Perceptron Files (*.mlp)|*.mlp";
            System.IO.StreamWriter network_save_file_stream;
            if ((saveFileDialog1.ShowDialog() == DialogResult.OK))
            {
                if (saveFileDialog1.FileName != "")
                {
                    network_save_file_stream =  new StreamWriter(saveFileDialog1.FileName);
					
					//樣式分類：儲存訓練後的 MLP 參數 Lab 18_Optical Character Recognition
                    mlp.Save_Network(network_save_file_stream);

                    network_save_file_stream.Close();
                }
            }
        }

        private void button23_Click(object sender, EventArgs e)
        {
            //樣式分類：讀取訓練後的 MLP 參數 Lab 18_Optical Character Recognition
			openFileDialog1.Filter = "MultiLayer Perceptron Files (*.mlp)|*.mlp";
            System.IO.StreamReader network_load_file_stream;
            if ((openFileDialog1.ShowDialog() == DialogResult.OK))
            {
                if (openFileDialog1.FileName != "")
                {
                    network_load_file_stream = new StreamReader(openFileDialog1.FileName);
					
					//樣式分類：讀取訓練後的 MLP 參數 Lab 18_Optical Character Recognition
                    mlp.Load_Network(network_load_file_stream);

                    network_load_file_stream.Close();
                }
            }
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
