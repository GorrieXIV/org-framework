from PyQt5.QtWidgets import (
    QApplication,
    QMainWindow,
    QWidget,
    QFileDialog,
    QTextEdit,
    QPushButton,
    QLabel,
    QGridLayout,
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

        self.openImageButton = QPushButton("Open Image File")
        self.openImageButton.clicked.connect(self.getImageFile)

        self.selectionButton = QPushButton("Selection Tool")
        self.selectionButton.clicked.connect(self.activateRectangleSelection)

        self.gridButton = QPushButton("Grid Tool")
        self.gridButton.clicked.connect(self.openGridToolDialog)

        self.openJsonButton = QPushButton("Manually Edit Sprite Sheet JSON")
        self.openJsonButton.clicked.connect(self.openJsonFile)

        self.labelImage = QLabel()
        self.textEditor = QTextEdit()

        layout = QGridLayout()

        # Add buttons to layout.
        layout.addWidget(self.openImageButton, 0, 0)
        layout.addWidget(self.selectionButton, 1, 0)
        layout.addWidget(self.gridButton, 2, 0)
        layout.addWidget(self.openJsonButton, 3, 0)

        # Add content labels to layout.
        layout.addWidget(self.labelImage, 0, 1)
        layout.addWidget(self.textEditor, 4, 1)

        self.setLayout(layout)

    def getImageFile(self):
        file_name, _ = QFileDialog.getOpenFileName(self, "Open Image File", "./", "Image files (*.jpg *.jpeg *.png *.gif)")
        self.labelImage.setPixmap(QPixmap(file_name))

    def openJsonFile(self):
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

    def activateRectangleSelection(self):
        pass

    def openGridToolDialog(self):
        pass

if __name__ == '__main__':
    app = QApplication(sys.argv)
    demo = DialogApp()
    demo.show()
    sys.exit(app.exec_())
