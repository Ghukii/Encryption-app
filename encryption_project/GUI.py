import sys
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QLineEdit, QTextEdit
from PyQt5 import uic
import cyphers
# cmake /home/ghukii/anaconda3/lib/python3.11/site-packages/pybind11/share/cmakepybind11 ..

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        uic.loadUi('ui/main.ui', self)

        self.CaesarWidget = Caesar_widget()
        self.TransposeWidget = Transpose_widget()

        self.CaesarButton = self.findChild(QPushButton, 'Caesar')
        self.TransposeButton = self.findChild(QPushButton, 'Transposition')

        self.CaesarButton.clicked.connect(self.switchWidgetCaesar)
        self.TransposeButton.clicked.connect(self.switchWidgetTranspose)

    def switchWidgetCaesar(self):
        self.hide()
        self.CaesarWidget.show()

    def switchWidgetTranspose(self):
        self.hide()
        self.TransposeWidget.show()


class Caesar_widget(QWidget):
    def __init__(self):
        super().__init__()
        uic.loadUi('ui/caesar.ui', self)

        self.encryptButton = self.findChild(QPushButton, 'encryptButton')
        self.decryptButton = self.findChild(QPushButton, 'decryptButton')
        self.back = self.findChild(QPushButton, 'back')

        self.input = self.findChild(QLineEdit, 'input')
        self.input_key = self.findChild(QLineEdit, 'input_key')

        self.output = self.findChild(QTextEdit, 'output')

        self.encryptButton.clicked.connect(self.encrypt)
        self.decryptButton.clicked.connect(self.decrypt)
        self.back.clicked.connect(self.goBack)

        self.ErrorWidget = ErrorWidget()

    def check(self, phrase, key):
        
        if not phrase or not key or not(key.isdigit()) or not(1 <= int(key) <= 25):
            return False
        
        elif phrase:
            for i in phrase:
                if i.isalpha() and (not ('a' <= i <= 'z') and not ('A' <= i <= 'Z')):
                    return False
                
        return True

    def encrypt(self):
        phrase = self.input.text()
        key = self.input_key.text()

        if self.check(phrase, key):

            C = cyphers.Caesar(phrase, int(key), "encrypt")
        
            self.output.setText(C.get_cypher())
        
        else:
            self.ErrorWidget.show()

    def decrypt(self):
        phrase = self.input.text()
        key = self.input_key.text()

        if self.check(phrase, key):

            C = cyphers.Caesar(phrase, int(key), "decrypt")
        
            self.output.setText(C.get_phrase())

        else:
            self.ErrorWidget.show()

    def goBack(self):
        self.hide()
        main.show()

class Transpose_widget(QWidget):
    def __init__(self):
        super().__init__()
        uic.loadUi("ui/transpose.ui", self)

        self.encryptButton = self.findChild(QPushButton, 'encryptButton')
        self.decryptButton = self.findChild(QPushButton, 'decryptButton')
        self.back = self.findChild(QPushButton, 'back')

        self.input = self.findChild(QLineEdit, 'input')
        self.input_key = self.findChild(QLineEdit, 'input_key')

        self.output = self.findChild(QTextEdit, 'output')

        self.encryptButton.clicked.connect(self.encrypt)
        self.decryptButton.clicked.connect(self.decrypt)
        self.back.clicked.connect(self.goBack)

        self.ErrorWidget = ErrorWidget()
    
    def goBack(self):
        self.hide()
        main.show()

    def check_key(self, key):
        s = set(list(range(1, len(key) + 1)))

        for i in key:
            s.add(int(i))

        if len(list(s)) != len(key):
            return False
        
        return True

    def check(self, phrase, key):
        
        if not phrase or not key or len(key) ** 2 < len(phrase) or not(key.isdigit()):
            return False
        
        elif phrase:
            for i in phrase:
                if i.isalpha() and (not ('a' <= i <= 'z') and not ('A' <= i <= 'Z')):
                    return False
                
        return True
    
    def encrypt(self):

        phrase = self.input.text()
        key = self.input_key.text()

        if self.check(phrase, key) and self.check_key(key):

            T = cyphers.Transpose_cypher(phrase, int(key), 'encrypt')

            self.output.setText(T.get_result())
        
        else:
            self.ErrorWidget.show()

    def decrypt(self):

        phrase = self.input.text()
        key = self.input_key.text()

        if self.check(phrase, key) and self.check_key(key):

            T = cyphers.Transpose_cypher(phrase, int(key), 'decrypt')

            self.output.setText(T.get_result())
        
        else:
            self.ErrorWidget.show()

class ErrorWidget(QWidget):
    def __init__(self):
        super().__init__()
        uic.loadUi("ui/error.ui", self)

        self.ok_button = self.findChild(QPushButton, "OK")

        self.ok_button.clicked.connect(self.hide)



if __name__ == '__main__':
    try:
        app = QApplication(sys.argv)
        main = MainWindow()
        main.show()
        sys.exit(app.exec_())
        
    except Exception as e:
        print(f"Произошла ошибка: {e}")