import serial
import serial.tools.list_ports


class COMPort:
    def __init__(self, port_name, baudrate=9600):
        self.port_name = port_name
        self.baudrate = baudrate
        self.serial_port = None

    def open(self):
        self.serial_port = serial.Serial(
            port=self.port_name,
            baudrate=self.baudrate,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS,
            timeout=1
        )

    def close(self):
        if self.serial_port and self.serial_port.is_open:
            self.serial_port.close()

    def write_data(self, data):
        if self.serial_port and self.serial_port.is_open:
            self.serial_port.write(data.encode())

    def read_data(self):
        if self.serial_port and self.serial_port.is_open:
            return self.serial_port.read(self.serial_port.in_waiting).decode()
        return ""

    @staticmethod
    def get_available_ports():
        ports = serial.tools.list_ports.comports()
        return [port.device for port in ports]
