from tkinter import Tk
from interface import PortInterface

if __name__ == "__main__":
    root = Tk()
    window1 = PortInterface(root, "Работа с COM-портами")
    root.mainloop()
