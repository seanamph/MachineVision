using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace MyApp
{
    public class MyDLL
    {
        [DllImport("MyDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Add")]
        public extern static int Add(int a, int b);

    }
}
