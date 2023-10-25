using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MyApp;

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
    }
}
