using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace MyApp
{
    class NGaugeDLL
    {
        [DllImport("NGaugeDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "CreateNGauge")]
        public extern static IntPtr CreateNGauge();

        [DllImport("NGaugeDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "DestroyNGauge")]
        public extern static bool DestroyNGauge(IntPtr m_Gauge);

        [DllImport("NGaugeDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "SubPixel_EdgeDetector")]
        public extern static int SubPixel_EdgeDetector(IntPtr m_Img, IntPtr m_MaskImg, IntPtr m_Gauge, ref double sub_x, ref double sub_y);

        [DllImport("NGaugeDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "CircleFitByKasa")]
        public extern static bool CircleFitByKasa(IntPtr m_Gauge, ref double edgelist_x, ref double edgelist_y, int edge_num,
                                                  ref double result_x, ref double result_y, ref double result_r);
    }
}
