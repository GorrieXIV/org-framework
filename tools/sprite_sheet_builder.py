from PyQt5.QtWidgets import (
    QApplication,
    QMainWindow,
    QWidget,
    QFileDialog,
    QTextEdit,
    QPushButton,
    QLabel,
    QVBoxLayout,
)
from PyQt5.QtGui import QPixmap
from PyQt5.QtCore import QDir
import sys

class DialogApp(QWidget):
    def __init__(self):

        # Set window dimensions and title.
        super().__init__()
        self.resize(800, 600)
        self.setWindowTitle("ORG Engine Sprite Sheet Builder")

        self.button1 = QPushButton("Open Image File")
        self.button1.clicked.connect(self.get_image_file)

        self.button2 = QPushButton("Manually Edit Sprite Sheet JSON")
        self.button2.clicked.connect(self.get_text_file)

        self.labelImage = QLabel()
        self.textEditor = QTextEdit()

        layout = QVBoxLayout()
        layout.addWidget(self.button1)
        layout.addWidget(self.labelImage)
        layout.addWidget(self.button2)
        layout.addWidget(self.textEditor)

        self.setLayout(layout)

    def get_image_file(self):
        file_name, _ = QFileDialog.getOpenFileName(self, "Open Image File", "./", "Image files (*.jpg *.jpeg *.png *.gif)")
        self.labelImage.setPixmap(QPixmap(file_name))

    def get_text_file(self):
        dialog = QFileDialog()
        dialog.setFileMode(QFileDialog.AnyFile)
        dialog.setFilter(QDir.Files)

        if dialog.exec_():
            file_name = dialog.selectedFiles()
            if file_name[0].endswith('.json'):
                with open(file_name[0], 'r') as f:
                    data = f.read()
                    self.textEditor.setPlainText(data)
                    f.close()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    demo = DialogApp()
    demo.show()
    sys.exit(app.exec_())
