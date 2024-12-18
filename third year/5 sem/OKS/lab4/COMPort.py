import serial
import serial.tools.list_ports
from crc_helpers import compute_crc8, cyclic_shift_correction, introduce_error


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
            crc = compute_crc8(packet)
            packet_with_crc = packet + chr(crc)
            stuffed_packet = byte_stuffing(packet_with_crc)
            self.write_data(stuffed_packet)
            return stuffed_packet

    def read_frame(self):
        if self.serial_port and self.serial_port.is_open:
            raw_data = self.read_data()
            if raw_data and raw_data[0:2] == '@p':
                result_tuple = remove_byte_stuffing(str(int(self.port_name[3:]) - 1), raw_data)
                message_data = result_tuple[0]
                received_crc = ord(result_tuple[1])
                data_after_chance_of_int_error = introduce_error(message_data)
                corrected_data = cyclic_shift_correction(data_after_chance_of_int_error, int(received_crc))
                return message_data
        return None


def generate_packet(source_port, data):
    flag = f"@{chr(ord('a') + 16 - 1)}"
    destination_address = 0
    source_address = int(source_port)

    if len(data) < 16:
        data += '\x00' * (16 - len(data))

    packet = f"{flag} {destination_address} {source_address} {data} "

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
    number_of_last_space = 0
    escape = False

    for i in range(len(packet) - 1, -1, -1):
        if packet[i] == ' ':
            number_of_last_space = i
            break

    received_crc = packet[number_of_last_space + 1:]
    data = packet[6 + len(number_port): number_of_last_space]
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

    return unstuffed_data, received_crc
