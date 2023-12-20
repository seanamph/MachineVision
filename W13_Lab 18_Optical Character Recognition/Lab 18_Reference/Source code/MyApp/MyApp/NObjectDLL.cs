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

        [DllImport("NObjectDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Blob_Labelling")]
        public extern static int Blob_Labelling(IntPtr m_Img, IntPtr m_Obj);

        [DllImport("NObjectDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Contour_Tracing")]
        public extern static int Contour_Tracing(IntPtr m_Img, IntPtr m_Obj, int blob_num, ref int ct_x, ref int ct_y);

        [DllImport("NObjectDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Area")]
        public extern static int Area(IntPtr m_Obj, int blob_num);

        [DllImport("NObjectDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Blob_Count")]
        public extern static int Blob_Count(IntPtr m_Obj);

        [DllImport("NObjectDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "Rect")]
        public extern static bool Rect(IntPtr m_Obj, int blob_num, ref int start_x, ref int start_y, ref int rect_w, ref int rect_h);

        [DllImport("NObjectDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "CreateMaskFromObject")]
        public extern static bool CreateMaskFromObject(IntPtr m_Mask_Img, IntPtr m_Obj, int blob_num);
    }
}
