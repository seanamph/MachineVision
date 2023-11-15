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


        public IntPtr hbitmap;

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
            NObjectDLL.DestroyNObject(m_Obj);
        }


        private void button12_Click(object sender, EventArgs e)
        {
            NImgProcessDLL.OtsuThresholding(m_Img, m_ImgPro);
			
			// Lab_12 Blob_Labelling
            int blob_count = NObjectDLL.Blob_Labelling(m_Img, m_Obj);

            Font drawFont = new Font("Time New Roman", 12);
            SolidBrush drawBrush = new SolidBrush(Color.LightSkyBlue);
            Graphics g = pictureBox1.CreateGraphics();
			
            int[] ct_x = new int[10000];
            int[] ct_y = new int[10000];
            int chain_count = 0;
            int i, j, blob_area;
            for (i = 0; i < blob_count; i++)
            {
                // Lab_12 Contour Tracing and Drawing
				chain_count = NObjectDLL.Contour_Tracing(m_Img, m_Obj, i, ref ct_x[0], ref ct_y[0]);
				
				for (j = 0; j < chain_count - 1 ; j++)
                {
                    g.DrawLine(Pens.Red, ct_x[j], ct_y[j], ct_x[j+1], ct_y[j+1]);
                }

				// Lab_12 Getting Area and Drawing
                blob_area = NObjectDLL.Area(m_Obj, i);
                g.DrawString(blob_area.ToString(), drawFont, drawBrush, ct_x[0], ct_y[0]);
                
            }

            label2.Text = String.Format("Blob_Count: {0} ", blob_count);
        }
    }
}
