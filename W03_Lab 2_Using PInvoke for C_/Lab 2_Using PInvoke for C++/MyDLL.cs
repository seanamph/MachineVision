using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace MyApp
{
    public class MyDLL
    {
        [DllImport("MyDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "CreateMathTool")]
        public extern static IntPtr CreateMathTool();

        [DllImport("MyDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "DestroyMathTool")]
        public extern static bool  DestroyMathTool(IntPtr m_Math);

        [DllImport("MyDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Add")]
        public extern static int Add(IntPtr m_Math, int a, int b);

    }
}
