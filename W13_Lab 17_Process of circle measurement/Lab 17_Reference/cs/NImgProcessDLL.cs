using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace MyApp
{
    public class NImgProcessDLL
    {
        [DllImport("NImgProcessDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "CreateNImgProcess")]
        public extern static IntPtr CreateNImgProcess();

        [DllImport("NImgProcessDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "DestroyNImgProcess")]
        public extern static bool DestroyNImgProcess(IntPtr m_ImgPro);

        [DllImport("NImgProcessDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Inverse")]
        public extern static bool Inverse(IntPtr m_Img, IntPtr m_ImgPro);

        [DllImport("NImgProcessDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "SingleThresholding")]
        public extern static IntPtr SingleThresholding(IntPtr m_Img, IntPtr m_ImgPro, int threshold);

        [DllImport("NImgProcessDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "OtsuThresholding")]
        public extern static IntPtr OtsuThresholding(IntPtr m_Img, IntPtr m_Img2, IntPtr m_ImgPro);

        [DllImport("NImgProcessDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Sobel")]
        public extern static IntPtr Sobel(IntPtr m_Img, IntPtr m_ImgPro);

        [DllImport("NImgProcessDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Laplacian")]
        public extern static IntPtr Laplacian(IntPtr m_Img, IntPtr m_ImgPro);

        [DllImport("NImgProcessDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Mean")]
        public extern static IntPtr Mean(IntPtr m_Img, IntPtr m_ImgPro);

        [DllImport("NImgProcessDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Inverse_SIMD")]
        public extern static bool Inverse_SIMD(IntPtr m_Img, IntPtr m_ImgPro);

        [DllImport("NImgProcessDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "SingleThresholding_SIMD")]
        public extern static bool SingleThresholding_SIMD(IntPtr m_Img, IntPtr m_ImgPro, int threshold);

        [DllImport("NImgProcessDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Subtract")]
        public extern static bool Subtract(IntPtr m_SrcImg, IntPtr m_RefImg, IntPtr m_ImgPro);

        [DllImport("NImgProcessDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "BitwiseXOR")]
        public extern static bool BitwiseXOR(IntPtr m_SrcImg, IntPtr m_RefImg, IntPtr m_ImgPro);

        [DllImport("NImgProcessDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Dilation3x3")]
        public extern static bool Dilation3x3(IntPtr m_Img, IntPtr m_Img2, IntPtr m_ImgPro);

        [DllImport("NImgProcessDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Erosion3x3")]
        public extern static bool Erosion3x3(IntPtr m_Img, IntPtr m_Img2, IntPtr m_ImgPro);

    }
}
