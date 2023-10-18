using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MyApp
{
    public partial class Form1 : Form
    {
        public IntPtr m_Img = NImageDLL.CreateNImage();
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
        }
    }
}
