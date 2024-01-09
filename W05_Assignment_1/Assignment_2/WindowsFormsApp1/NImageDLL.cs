using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace MyApp
{
    public class Dll1
    {
        [DllImport("Dll1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr CreateCalculatorInstance();

        [DllImport("Dll1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void DestroyCalculatorInstance(IntPtr instance);

        [DllImport("Dll1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Calculator_Add(IntPtr instance, int a, int b);


        [DllImport("Dll1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "CreateNImage")]
        public extern static IntPtr CreateNImage();

        [DllImport("Dll1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "DestroyNImage")]
        public extern static bool DestroyNImage(IntPtr m_Img);

        [DllImport("Dll1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "LoadBMP")]
        public extern static bool LoadBMP(IntPtr m_Img, string filename);

        [DllImport("Dll1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "SaveBMP")]
        public extern static bool SaveBMP(IntPtr m_Img, string filename);

        [DllImport("Dll1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "GetBitmap")]
        public extern static IntPtr GetBitmap(IntPtr m_Img);

        [DllImport("Dll1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "GetBitmap")]
        public extern static void MeanFilter3x3(IntPtr m_Img);

        [DllImport("Dll1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "SobelFilter")]
        public extern static void SobelFilter(IntPtr m_Img);

        [DllImport("Dll1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "LaplacianFilter")]
        public extern static void LaplacianFilter(IntPtr m_Img);

        [DllImport("Dll1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Threshold")]
        public extern static void Threshold(IntPtr m_Img);

        [DllImport("Dll1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "AdaptiveMeanThreshold")]
        public extern static void AdaptiveMeanThreshold(IntPtr m_Img, int blockSize);

        [DllImport("Dll1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "AdaptiveGaussianThreshold")]
        public extern static void AdaptiveGaussianThreshold(IntPtr m_Img, int blockSize);


        // Lab_12 Blob_Labelling
        [DllImport("Dll1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Blob_Labelling")]
        public extern static int Blob_Labelling(IntPtr m_Img);

        [DllImport("Dll1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Contour_Tracing")]
        public extern static int Contour_Tracing(IntPtr m_Img);

        [DllImport("Dll1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "CalculateBlobArea")]
        public extern static int CalculateBlobArea(IntPtr m_Img);


    }
}
