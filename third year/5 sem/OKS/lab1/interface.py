import tkinter as tk
from tkinter import messagebox
from tkinter import ttk
from COMPort import COMPort
import threading


class PortInterface:
    def __init__(self, root, window_name):
        self.root = root
        self.root.title(window_name)
        self.root.resizable(False, False)
        self.root.configure(bg="#F5F5DC")

        self.label_control = tk.Label(root, text="Окно управления")
        self.label_control.pack(pady=5)
        self.label_send = tk.Label(root, text="Выберите COM-порт для отправки:")
        self.label_send.pack(pady=2)
        self.combobox_send = ttk.Combobox(root, state="readonly")
        self.combobox_send.pack(pady=2)
        self.combobox_send.bind("<Button-1>", self.update_ports_send)
        self.combobox_send.bind("<<ComboboxSelected>>", self.connect_send_port)

        self.label_receive = tk.Label(root, text="Выберите COM-порт для приёма:")
        self.label_receive.pack(pady=5)
        self.combobox_receive = ttk.Combobox(root, state="readonly")
        self.combobox_receive.pack(pady=2)
        self.combobox_receive.bind("<Button-1>", self.update_ports_receive)
        self.combobox_receive.bind("<<ComboboxSelected>>", self.connect_receive_port)

        self.input_label = tk.Label(root, text="Окно ввода")
        self.input_label.pack(pady=5)
        self.input_text = tk.Text(root, height=5, width=40)
        self.input_text.pack(padx=100, pady=2)
        self.input_text.bind("<KeyPress>", self.check_enter)

        self.output_label = tk.Label(root, text="Окно вывода")
        self.output_label.pack(pady=5)
        self.output_text = tk.Text(root, height=7, width=40)
        self.output_text.pack(pady=2)
        self.output_text.configure(state='disabled')

        self.status_label = tk.Label(root, text="Окно статуса")
        self.status_label.pack(pady=5)
        self.status_text = tk.Text(root, height=7, width=40, state='disabled')
        self.status_text.pack(pady=2)
        self.status_text.configure(state='disabled')

        self.debug_label = tk.Label(root, text="Окно отладочной информации")
        self.debug_label.pack(pady=5)
        self.debug_text = tk.Text(root, height=7, width=40, state='disabled')
        self.debug_text.pack(pady=2)
        self.debug_text.configure(state='disabled')

        self.com_send = None
        self.com_receive = None

        self.receive_thread = None
        self.is_receiving = False

        self.number_receive = 0
        self.number_send = 0

        self.root.protocol("WM_DELETE_WINDOW", self.on_close)

        self.display_port_settings()

    def check_enter(self, event):
        if event.keysym == "Return":
            self.send_data()
            return "break"

    def update_ports_send(self, event=None):
        ports = COMPort.get_available_ports()
        ports = [port for port in ports if port != "COM3"]
        receive_port = self.combobox_receive.get()

        if receive_port and receive_port.startswith("COM"):
            port_number = int(receive_port[3:])
            exclude_ports = [f"COM{port_number}", f"COM{port_number - 1}"]
            ports = [port for port in ports if port not in exclude_ports]
        self.combobox_send['values'] = ['Не выбран'] + ports

    def update_ports_receive(self, event=None):
        ports = COMPort.get_available_ports()
        ports = [port for port in ports if port != "COM3"]
        send_port = self.combobox_send.get()

        if send_port and send_port.startswith("COM"):
            port_number = int(send_port[3:])
            exclude_ports = [f"COM{port_number}", f"COM{port_number + 1}"]
            ports = [port for port in ports if port not in exclude_ports]
        self.combobox_receive['values'] = ['Не выбран'] + ports

    def connect_send_port(self, event=None):
        send_port = self.combobox_send.get()
        if self.com_send:
            self.com_send.close()
            self.update_status(f"Порт {self.com_send.port_name} закрыт.")
            self.update_debug(f"Порт {self.com_send.port_name} успешно закрыт.")
            self.com_send = None

        if send_port and send_port != "Не выбран":
            self.com_send = COMPort(send_port)
            try:
                self.com_send.open()
                self.update_status(f"Порт {send_port} открыт для отправки.")
                self.update_debug(f"Порт {send_port} успешно открыт для отправки.")
            except Exception as e:
                messagebox.showerror("Ошибка", f"Не удалось открыть порт для отправки. Данный порт выбран в другом окне."
                                               f" Выберите другой COM-порт, соответсвуюйщий топологии.")
                self.com_send = None

    def connect_receive_port(self, event=None):
        receive_port = self.combobox_receive.get()
        if self.com_receive:
            self.stop_receiving()
            self.com_receive.close()
            self.update_status(f"Порт {self.com_receive.port_name} закрыт.")
            self.update_debug(f"Порт {self.com_receive.port_name} успешно закрыт.")
            self.com_receive = None

        if receive_port and receive_port != "Не выбран":
            self.com_receive = COMPort(receive_port)
            try:
                self.com_receive.open()
                self.update_status(f"Порт {receive_port} открыт для приёма.")
                self.update_debug(f"Порт {receive_port} успешно открыт для приёма.")
                self.start_receiving()
            except Exception as e:
                messagebox.showerror("Ошибка", f"Не удалось открыть порт для приёма. Данный порт открыт в другом окне."
                                               f" Выберите другой COM-порт, соответсвуюйщий топологии.")
                self.com_receive = None

    def send_data(self):
        if self.com_send:
            data = self.input_text.get('1.0', tk.END).strip()
            if data:
                self.com_send.write_data(data)
                self.number_send += 1
                self.update_status(f"Отправлено: {len(data)} байт")
                self.update_status(f"Количество отправленных порций: {self.number_send}")
                self.update_debug(f"Успешно отправлено: {len(data)} байт")
            else:
                messagebox.showwarning("Ошибка", "Введите данные для отправки")
        else:
            messagebox.showwarning("Ошибка", "Порт отправки не подключен")

    def start_receiving(self):
        self.is_receiving = True
        self.receive_thread = threading.Thread(target=self.receive_data_loop)
        self.receive_thread.start()

    def stop_receiving(self):
        self.is_receiving = False
        if self.receive_thread:
            self.receive_thread.join()
            self.receive_thread = None

    def receive_data_loop(self):
        while self.is_receiving:
            if self.com_receive:
                data = self.com_receive.read_data()
                if data:
                    self.output_text.configure(state='normal')
                    self.output_text.delete('1.0', tk.END)
                    self.output_text.insert(tk.END, data + "\n")
                    self.output_text.configure(state='disabled')
                    self.number_receive += 1
                    self.update_status(f"Принято: {len(data)} байт")
                    self.update_status(f"Количество принятых порций: {self.number_receive}")
                    self.update_debug(f"Успешно принято: {len(data)} байт")

    def update_status(self, message):
        self.status_text.configure(state='normal')
        self.status_text.insert(tk.END, message + "\n")
        self.status_text.configure(state='disabled')
        self.status_text.see(tk.END)

    def update_debug(self, message):
        self.debug_text.configure(state='normal')
        self.debug_text.insert(tk.END, message + "\n")
        self.debug_text.configure(state='disabled')
        self.debug_text.see(tk.END)

    def display_port_settings(self):
        general_settings = (
            "Скорость передачи (baudrate): 9600\n"
            "Биты данных (bytesize): 8\n"
            "Стоповые биты (stopbits): 1\n"
            "Четность (parity): None\n"
            "Таймаут (timeout): 1 секунда\n"
        )
        self.update_status(general_settings)

    def on_close(self):
        self.stop_receiving()
        if self.com_send:
            self.com_send.close()
        if self.com_receive:
            self.com_receive.close()
        self.root.destroy()
