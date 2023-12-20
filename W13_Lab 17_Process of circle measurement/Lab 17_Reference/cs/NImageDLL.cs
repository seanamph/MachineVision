﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace MyApp
{
    public class NImageDLL
    {
        [DllImport("NImageDll.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "CreateNImage")]
        public extern static IntPtr CreateNImage();

        [DllImport("NImageDll.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "CreateNImageEx")]
        public extern static IntPtr CreateNImageEx(int wid, int hei);

        [DllImport("NImageDll.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "DestroyNImage")]
        public extern static bool DestroyNImage(IntPtr m_Img);

        [DllImport("NImageDll.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "LoadBMP")]
        public extern static bool LoadBMP(IntPtr m_Img, string filename);

        [DllImport("NImageDll.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "GetBitmap")]
        public extern static IntPtr GetBitmap(IntPtr m_Img);

        [DllImport("NImageDll.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "GetWidth")]
        public extern static int GetWidth(IntPtr m_Img);

        [DllImport("NImageDll.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "GetHeight")]
        public extern static int GetHeight(IntPtr m_Img);
    }
}
