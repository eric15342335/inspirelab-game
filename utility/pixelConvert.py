import sys
from PyQt5.QtWidgets import QApplication, QWidget, QGridLayout, QPushButton, QVBoxLayout, QTextEdit, QScrollArea, QMenuBar, QMenu, QAction, QFileDialog, QMessageBox, QSplitter, QInputDialog
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QImage
import re

background_color = "background-color: black"
button_color = "background-color: white"
button_size = 20
grid_width = 128
grid_height = 64

class ButtonGrid(QWidget):
    def __init__(self, width=grid_width, height=grid_height):
        super().__init__()
        self.width = width
        self.height = height
        self.buttons = [[0] * self.width for _ in range(self.height)]
        self.initUI()

    def initUI(self):
        self.setWindowTitle(f"{grid_width}x{grid_height} Button Grid")

        layout = QVBoxLayout()

        self.menu_bar = QMenuBar(self)
        file_menu = self.menu_bar.addMenu("File")
        edit_menu = self.menu_bar.addMenu("Edit")
        help_menu = self.menu_bar.addMenu("Help")
        
        save_action = QAction("Save to Text File", self)
        save_action.triggered.connect(self.save_to_file)
        file_menu.addAction(save_action)
        
        load_action = QAction("Load Text File", self)
        load_action.triggered.connect(self.load_from_file)
        file_menu.addAction(load_action)
        
        black_action = QAction("Set All Black", self)
        black_action.triggered.connect(self.set_all_black)
        edit_menu.addAction(black_action)

        white_action = QAction("Set All White", self)
        white_action.triggered.connect(self.set_all_white)
        edit_menu.addAction(white_action)
        
        load_image_action = QAction("Load Image", self)
        load_image_action.triggered.connect(self.load_image_file)
        file_menu.addAction(load_image_action)

        exit_action = QAction("Exit", self)
        exit_action.triggered.connect(self.close)
        file_menu.addAction(exit_action)

        input_text_action = QAction("Input Text", self)
        input_text_action.triggered.connect(self.input_text)
        file_menu.addAction(input_text_action)

        about_action = QAction("About", self)
        about_action.triggered.connect(self.show_about)
        help_menu.addAction(about_action)
        
        layout.setMenuBar(self.menu_bar)

        splitter = QSplitter(Qt.Vertical)

        self.scroll_area = QScrollArea()
        self.scroll_area.setWidgetResizable(True)
        self.scroll_content = QWidget()
        self.grid_layout = QGridLayout(self.scroll_content)
        self.scroll_content.setLayout(self.grid_layout)
        self.grid_layout.setSpacing(1)  # Reduce gaps between buttons

        button_size = 20  # Adjust button size here
        for y in range(self.height):
            for x in range(self.width):
                button = QPushButton()
                button.setFixedSize(button_size, button_size)
                button.setStyleSheet(background_color)
                button.clicked.connect(lambda _, x=x, y=y: self.toggle_button(x, y))
                self.grid_layout.addWidget(button, y, x)

        self.scroll_area.setWidget(self.scroll_content)
        splitter.addWidget(self.scroll_area)

        output_layout = QVBoxLayout()
        self.output_button = QPushButton("Generate C Array")
        self.output_button.clicked.connect(self.generate_c_array)
        output_layout.addWidget(self.output_button)

        self.output_text = QTextEdit()
        self.output_text.setReadOnly(False)  # Allow user to input C array
        output_layout.addWidget(self.output_text)

        output_widget = QWidget()
        output_widget.setLayout(output_layout)
        splitter.addWidget(output_widget)

        layout.addWidget(splitter)
        self.setLayout(layout)
        self.resize(800, 600)
        self.showMaximized()

    def toggle_button(self, x, y):
        self.buttons[y][x] = 1 - self.buttons[y][x]
        button = self.grid_layout.itemAtPosition(y, x).widget()
        button.setStyleSheet(button_color if self.buttons[y][x] == 1 else background_color)

    def generate_c_array(self):
        c_array = []
        for y in range(0, self.height, 8):#
            for x in range(self.width):#
                byte = 0
                for bit in range(8):
                    if y + bit < self.height and self.buttons[y + bit][x] == 1:
                        byte |= (1 << bit)
                c_array.append(byte)
        
        c_array_str = ', '.join(f'0x{byte:02X}' for byte in c_array)
        output = f'uint8_t image_data[{self.width * (self.height // 8)}] = {{ {c_array_str} }};'
        self.output_text.setPlainText(output)

    def save_to_file(self):
        options = QFileDialog.Options()
        file_name, _ = QFileDialog.getSaveFileName(self, "Save C Array", "", "Text Files (*.txt);;All Files (*)", options=options)
        if file_name:
            with open(file_name, 'w') as file:
                file.write(self.output_text.toPlainText())

    def input_text(self):
        text, ok = QInputDialog.getMultiLineText(self, "Input C Array", "Enter C array:", "", flags=Qt.Dialog | Qt.WindowSystemMenuHint | Qt.WindowTitleHint)
        if ok and text:
            self.output_text.setPlainText(text)
            self.parse_c_array(text)

    def load_from_file(self):
        options = QFileDialog.Options()
        file_name, _ = QFileDialog.getOpenFileName(self, "Load C Array", "", "Text Files (*.txt);;All Files (*)", options=options)
        if file_name:
            with open(file_name, 'r') as file:
                data = file.read()
                self.output_text.setPlainText(data)
                self.parse_c_array(data)

    def load_image_file(self):
        options = QFileDialog.Options()
        file_name, _ = QFileDialog.getOpenFileName(self, "Load PNG Image", "", "PNG Files (*.png);;All Files (*)", options=options)
        if file_name:
            image = QImage(file_name)
            if image.isNull():
                QMessageBox.warning(self, "Error", "Failed to load image.")
                return

            # Ensure the image is of the correct size
            if image.width() != self.width or image.height() != self.height:
                QMessageBox.warning(self, "Error", f"Image must be exactly {self.width}x{self.height} pixels.")
                return

            for y in range(self.height):
                for x in range(self.width):
                    color = image.pixelColor(x, y)
                    self.buttons[y][x] = 1 if color.value() < 128 else 0  # Assuming a threshold for black/white
                    button = self.grid_layout.itemAtPosition(y, x).widget()
                    button.setStyleSheet(button_color if self.buttons[y][x] == 1 else background_color)

    def set_all_black(self):
        for y in range(self.height):
            for x in range(self.width):
                self.buttons[y][x] = 0
                button = self.grid_layout.itemAtPosition(y, x).widget()
                button.setStyleSheet(background_color)

    def set_all_white(self):
        for y in range(self.height):
            for x in range(self.width):
                self.buttons[y][x] = 1
                button = self.grid_layout.itemAtPosition(y, x).widget()
                button.setStyleSheet(button_color)

    def parse_c_array(self, data):
        # Find the array elements within the braces
        match = re.search(r'\{([^}]+)\}', data)
        if not match:
            QMessageBox.warning(self, "Error", "Invalid C array format.")
            return

        c_array_str = match.group(1)
        c_array = [int(byte.strip(), 16) for byte in c_array_str.split(',')]

        # Clear the current button states
        self.buttons = [[0] * self.width for _ in range(self.height)]
        
        byte_index = 0
        for y in range(0, self.height, 8):
            for x in range(grid_width):
                if byte_index < len(c_array):
                    byte = c_array[byte_index]
                    byte_index += 1
                    for bit in range(8):
                        if y + bit < self.height:
                            self.buttons[y + bit][x] = (byte >> bit) & 1
                            button = self.grid_layout.itemAtPosition(y + bit, x).widget()
                            button.setStyleSheet(button_color if self.buttons[y + bit][x] == 1 else background_color)
        self.set_all_black()

    def show_about(self):
        QMessageBox.about(self, "About", f"{grid_width}x{grid_height} Button Grid")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    app.setAttribute(Qt.AA_EnableHighDpiScaling)  # Enable high DPI scaling
    app.setAttribute(Qt.AA_UseHighDpiPixmaps)     # Use high DPI pixmaps

    window = ButtonGrid()
    window.show()

    sys.exit(app.exec_())
