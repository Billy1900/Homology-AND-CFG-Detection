import os
import sys
import bufferoverflowDetection
import CFG
import Formatstring
import HomologyDetection
import IntegerOverflow
import IntegerWidth
import Multi
import nullpointerdetection
import stackoverflow


from UI import Ui_Dialog
from PyQt5 import QtWidgets, QtCore, QtGui
from PyQt5.QtWidgets import QApplication,QMainWindow,QWidget,QMessageBox


class window(QWidget, Ui_Dialog):
    def __init__(self):
        super(window, self).__init__()
        self.setupUi(self)

    def set_homology(self):
        res = HomologyDetection.homologyDetection() #res is a str
        self.textBrowser.setText("Homology similarity:"+str(res)+"%")

    def set_CFG(self):
        res = CFG.CFG() #res is a str
        self.textBrowser.setText("CFG similarity:"+str(res)+"%")

    def set_Buffer(self):
        res = bufferoverflowDetection.buffer() #res is a dic
        self.textBrowser.setText("Buffer Over Flow (ALERT):" + str(res))


    def set_Format(self):
        res = Formatstring.FormatString() #res is a str
        self.textBrowser.setText("Dangerous lines that format string may occur:" + str(res))


    def set_Integer(self):
        res = IntegerOverflow.IntegerOver() # res is a str
        self.textBrowser.setText("Dangerous lines that Integer overflow may occur:" + str(res))

    def set_width(self):
        res = IntegerWidth.width() # res is a str
        self.textBrowser.setText("Dangerous lines that integer width may occur:" + str(res))

    def set_Muti(self):
        res = Multi.multiprocess() # res is a list
        self.textBrowser.setText("Homology Similarity:"+str(res[0])+"%"+"\n"+ "CFG Similarity:" + str(res[1]) + "%")

    def set_Null(self):
        res = nullpointerdetection.nullpointer()
        self.textBrowser.setText("Dangerous lines that null pointers may occur:" + str(res))

    def set_stackover(self):
        res = stackoverflow.stackover()
        self.textBrowser.setText("Dangerous lines that stack over flow may occur:" + str(res))


if __name__=='__main__':
    app = QApplication(sys.argv)
    w = window()
    w.setWindowTitle('Software Security')
    w.show()
    w.pushButton.clicked.connect(w.set_homology)
    w.pushButton_2.clicked.connect(w.set_CFG)
    w.pushButton_3.clicked.connect(w.set_Buffer)
    w.pushButton_4.clicked.connect(w.set_Format)
    w.pushButton_5.clicked.connect(w.set_Integer)
    w.pushButton_6.clicked.connect(w.set_width)
    w.pushButton_7.clicked.connect(w.set_Muti)
    w.pushButton_8.clicked.connect(w.set_Null)
    w.pushButton_9.clicked.connect(w.set_stackover)

    sys.exit(app.exec_())