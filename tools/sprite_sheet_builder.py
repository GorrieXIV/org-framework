from PyQt5.QtWidgets import (
    QApplication,
    QMainWindow,
    QWidget,
    QFileDialog,
    QTextEdit,
    QPushButton,
    QLabel,
    QGridLayout,
    QFormLayout,
    QDialog,
    QDialogButtonBox,
    QLineEdit,
)
from PyQt5.QtGui import (
    QPixmap,
    QBrush,
    QPainter,
    QColor
)
from PyQt5.QtCore import QDir, QRect

import simplejson as json
import sys

class SheetBuilderMainWindow(QWidget):
    def __init__(self):

        # Set window dimensions and title.
        super().__init__()
        self.resize(800, 600)
        self.setWindowTitle("ORG Engine Sprite Sheet Builder")

        self.imageLoaded = False
        self.gridSpriteWidth = None
        self.gridSpriteHeight = None
        self.gridSpriteColumns = None
        self.gridSpriteRows = None
        self.gridSpecified = False

        self.openImageButton = QPushButton("Open Image File")
        self.openImageButton.clicked.connect(self.getImageFile)

        self.selectionButton = QPushButton("Selection Tool")
        self.selectionButton.clicked.connect(self.activateRectangleSelection)

        self.gridButton = QPushButton("Grid Tool")
        self.gridButton.clicked.connect(self.openGridToolDialog)

        self.openJsonButton = QPushButton("Edit Sprite Sheet JSON")
        self.openJsonButton.clicked.connect(self.openJsonFile)

        self.labelImage = QLabel()
        self.textEditor = QTextEdit()

        layout = QGridLayout()

        # Add buttons to layout.
        layout.addWidget(self.openImageButton, 0, 0)
        layout.addWidget(self.selectionButton, 0, 1)
        layout.addWidget(self.gridButton, 0, 2)
        layout.addWidget(self.openJsonButton, 0, 3)

        # Add content labels to layout.
        layout.addWidget(self.labelImage, 1, 0, 1, 4)
        layout.addWidget(self.textEditor, 2, 0, 4, 4)

        self.setLayout(layout)

    def getImageFile(self):
        fileName, _ = QFileDialog.getOpenFileName(self, "Open Image File", "./", "Image files (*.jpg *.jpeg *.png *.gif)")
        if fileName:
            self.labelImage.setPixmap(QPixmap(fileName))
            self.imageLoaded = True

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
        dialog = GridToolDialogBox()
        if dialog.exec():
            gridDimensions = dialog.getInputs()
            self.gridSpriteWidth = gridDimensions[0]
            self.gridSpriteHeight = gridDimensions[1]
            self.gridSpriteColumns = gridDimensions[2]
            self.gridSpriteRows = gridDimensions[3]
            self.gridSpecified = True

    def paintEvent(self, e):
        painter = QPainter(self)
        brush = QBrush(QColor(100, 10, 10, 40))
        painter.setBrush(brush)

        if self.imageLoaded and self.gridSpecified:
            try:
                painter.drawRect(
                    int(0), int(0), int(self.gridSpriteWidth), int(self.gridSpriteHeight)
                )
            except ValueError as e:
                print("Invalid inputs given for grid dimensions.")

class GridToolDialogBox(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)

        self.spriteWidth = QLineEdit(self)
        self.spriteHeight = QLineEdit(self)
        self.columns = QLineEdit(self)
        self.rows = QLineEdit(self)
        formSubmitBox = QDialogButtonBox(
            QDialogButtonBox.Ok | QDialogButtonBox.Cancel,
            self
        )

        layout = QFormLayout(self)
        layout.addRow("Sprite Width", self.spriteWidth)
        layout.addRow("Sprite Height", self.spriteHeight)
        layout.addRow("Number of Columns", self.columns)
        layout.addRow("Number of Rows", self.rows)
        layout.addWidget(formSubmitBox)

        formSubmitBox.accepted.connect(self.accept)
        formSubmitBox.rejected.connect(self.reject)

    def getInputs(self):
        return (
            self.spriteWidth.text(),
            self.spriteHeight.text(),
            self.columns.text(),
            self.rows.text()
        )

if __name__ == '__main__':
    app = QApplication(sys.argv)
    sheetBuilder = SheetBuilderMainWindow()
    sheetBuilder.show()
    sys.exit(app.exec_())
