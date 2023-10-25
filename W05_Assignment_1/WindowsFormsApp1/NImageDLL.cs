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

        [DllImport("Dll1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "GetBitmap")]
        public extern static IntPtr GetBitmap(IntPtr m_Img);

    }
}
