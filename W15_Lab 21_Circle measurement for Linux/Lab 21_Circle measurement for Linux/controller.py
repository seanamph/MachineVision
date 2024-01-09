import numpy as np
from ctypes import * 
from PyQt5 import QtWidgets, QtCore
from PyQt5.QtGui import QImage, QPixmap
from PyQt5.QtGui import QPainter, QPen
from PyQt5.QtCore import QRect, Qt

from UI import Ui_MainWindow
from NImage import ImageClass
from NImgProcess import ImgProcessClass
from NObject import ObjectClass
from NGauge import GaugeClass

class MainWindow_controller(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__() # in python3, super(Class, self).xxx = super().xxx
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.setup_control()

    def setup_control(self):
        # TODO
        self.img_path = '6.bmp'
        self.display_img()

    def display_img(self):
        NImg = ImageClass()
        NImgPro = ImgProcessClass()
        NOtsuImg = ImageClass()
        NObj = ObjectClass()
        NGauge = GaugeClass()
		
		
        self.array = NImg.LoadBMP(self.img_path)
        height, width = self.array.shape
        bytesPerline = width
		
        self.qimg = QImage(self.array.data, width, height, bytesPerline, QImage.Format_Grayscale8)
        self.ui.label.setPixmap(QPixmap.fromImage(self.qimg))
        self.ui.label.adjustSize()
        
        
        self.array2 = NOtsuImg.ReSize(NImg.GetWidth(), NImg.GetHeight())
		
        
        ct_x = np.arange(0, 10000, 1, c_int)
        ct_y = np.arange(0, 10000, 1, c_int)
        sub_x = np.arange(0, 10000, 1, c_double)
        sub_y = np.arange(0, 10000, 1, c_double)

        chain_count = 0
        result_x = np.arange(0, 1, 1, c_double)
        result_y = np.arange(0, 1, 1, c_double)
        result_r = np.arange(0, 1, 1, c_double)
        
        
        self.qimg2 = QImage(self.array2.data, width, height, bytesPerline, QImage.Format_Grayscale8)
        
        painter = QPainter(self.qimg2)
        painter.setPen(QPen(Qt.green, 2, Qt.SolidLine))
       
        
        if (NImgPro.OtsuThresholding(NImg.GetHandle(), NOtsuImg.GetHandle())): 
            blob_count = NObj.Blob_Labelling(NOtsuImg.GetHandle())
        
        for i in range(blob_count):
            chain_count = NObj.Contour_Tracing(NOtsuImg.GetHandle(), i, ct_x.ctypes.data_as(POINTER(c_int)), ct_y.ctypes.data_as(POINTER(c_int)))
            for j in range(chain_count):
                sub_x[j] = ct_x[j]
                sub_y[j] = ct_y[j]
	
            if (NGauge.CircleFitByKasa(sub_x.ctypes.data_as(POINTER(c_double)), sub_y.ctypes.data_as(POINTER(c_double)), chain_count, result_x.ctypes.data_as(POINTER(c_double)), result_y.ctypes.data_as(POINTER(c_double)), result_r.ctypes.data_as(POINTER(c_double)))):
                
                Sx = int(result_x[0]-result_r[0])
                Sy = int(result_y[0]-result_r[0])
                Sr = int(result_r[0]*2)
                painter.drawEllipse(Sx,Sy,Sr,Sr)
                
        painter.end()
        
        self.ui.label_2.setPixmap(QPixmap.fromImage(self.qimg2))
        self.ui.label_2.adjustSize()
