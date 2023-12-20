from PyQt5 import QtWidgets, QtCore
from PyQt5.QtGui import QImage, QPixmap

from UI import Ui_MainWindow
from NImage import ImageClass
from NImgProcess import ImgProcessClass

class MainWindow_controller(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__() # in python3, super(Class, self).xxx = super().xxx
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.setup_control()

    def setup_control(self):
        # TODO
        self.img_path = 'Pattern.bmp'
        self.display_img()

    def display_img(self):
        NImg = ImageClass()
        NImgPro = ImgProcessClass()
		
        self.img = NImg.LoadBMP(self.img_path)
        height, width = self.img.shape
        bytesPerline = width
		
        self.qimg = QImage(self.img.data, width, height, bytesPerline, QImage.Format_Grayscale8)
        self.ui.label.setPixmap(QPixmap.fromImage(self.qimg))
        self.ui.label.adjustSize()
		
        self.img2 = NImgPro.Inverse(self.img)
        self.qimg2 = QImage(self.img2.data, width, height, bytesPerline, QImage.Format_Grayscale8)
        self.ui.label_2.setPixmap(QPixmap.fromImage(self.qimg2))
        self.ui.label_2.adjustSize()
		
        self.img3 = NImgPro.SingleThresholding(self.img, 100)
        self.qimg3 = QImage(self.img3.data, width, height, bytesPerline, QImage.Format_Grayscale8)
        self.ui.label_3.setPixmap(QPixmap.fromImage(self.qimg3))
        self.ui.label_3.adjustSize()
		
        self.img4 = NImgPro.OtsuThresholding(self.img)
        self.qimg4 = QImage(self.img4.data, width, height, bytesPerline, QImage.Format_Grayscale8)
        self.ui.label_4.setPixmap(QPixmap.fromImage(self.qimg4))
        self.ui.label_4.adjustSize()
		
		

