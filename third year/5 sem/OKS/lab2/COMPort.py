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

    def write_frame(self, data):
        if self.serial_port and self.serial_port.is_open:
            packet = generate_packet(int(self.port_name[3:]), data)
            stuffed_packet = byte_stuffing(packet)
            self.write_data(stuffed_packet)
            return stuffed_packet

    def read_frame(self):
        if self.serial_port and self.serial_port.is_open:
            raw_data = self.read_data()
            if raw_data and raw_data[0:2] == '@p':
                decoded_data = remove_byte_stuffing(str(int(self.port_name[3:]) - 1), raw_data)
                return decoded_data
        return None


def generate_packet(source_port, data):
    flag = f"@{chr(ord('a') + 16 - 1)}"
    destination_address = 0
    source_address = int(source_port)
    fcs = 0

    if len(data) < 16:
        data += '\x00' * (16 - len(data))

    packet = f"{flag} {destination_address} {source_address} {data} {fcs}"

    return packet


def byte_stuffing(data):
    escape_byte = '['
    stuffed_data = ""

    i = 0
    while i < len(data):
        if data[i:i+2] == '@p' and i != 0:
            stuffed_data += escape_byte + 'p'
            i += 2
        elif data[i] == escape_byte:
            stuffed_data += escape_byte * 2
            i += 1
        else:
            stuffed_data += data[i]
            i += 1

    return stuffed_data


def remove_byte_stuffing(number_port, packet):
    escape_byte = '['
    unstuffed_data = ""
    escape = False
    data = packet[6 + len(number_port):len(packet) - 2]
    for byte in data:
        if escape and byte == escape_byte:
            unstuffed_data += byte
            escape = False
        elif escape and byte == 'p':
            unstuffed_data += "@" + byte
            escape = False
        elif byte == escape_byte:
            escape = True
        else:
            unstuffed_data += byte

    return unstuffed_data
