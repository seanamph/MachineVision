from PyQt5 import QtWidgets, QtCore
from PyQt5.QtGui import QImage, QPixmap

from UI import Ui_MainWindow
from NImage import ImageClass
#from NImgProcess import ImgProcessClass

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
        self.img = NImg.LoadBMP(self.img_path)
        height, width = self.img.shape

        bytesPerline = width
        self.qimg = QImage(self.img.data, width, height, bytesPerline, QImage.Format_Grayscale8)
        self.ui.label.setPixmap(QPixmap.fromImage(self.qimg))
        self.ui.label.adjustSize()

