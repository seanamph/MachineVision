using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace MyApp
{
    public class NObjectDLL
    {
        [DllImport("NObjectDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "CreateNObject")]
        public extern static IntPtr CreateNObject();

        [DllImport("NObjectDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "DestroyNObject")]
        public extern static bool DestroyNObject(IntPtr m_Obj);

		// Lab_12 Blob_Labelling
        [DllImport("NObjectDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Blob_Labelling")]
        public extern static int Blob_Labelling(IntPtr m_Img, IntPtr m_Obj);

		// Lab_12 Contour Tracing
        [DllImport("NObjectDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Contour_Tracing")]
        public extern static int Contour_Tracing(IntPtr m_Img, IntPtr m_Obj, int blob_num, ref int ct_x, ref int ct_y);

		// Lab_12 Getting Area
        [DllImport("NObjectDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Area")]
        public extern static int Area(IntPtr m_Obj, int blob_num);
    }
}
