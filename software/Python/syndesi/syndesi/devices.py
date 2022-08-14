import socket
import concurrent.futures

from syndesi.settings import SYNDESI_PORT
from syndesi.frame import Frame
from syndesi.frame_contents import FrameContent
from syndesi import frame_contents


RECV_TIMEOUT = 1


class Device():
    def __init__(self, ip_address):
        """
        Device instance

        Parameters
        ----------
        ip_address : str
            IP descriptor (IPv4 or IPv6)
        """
        self._IP = ip_address

    def __repr__(self) -> str:
        """
        Returns device's ip address
        """
        return f"Device at {self._IP}"

    def send(self, content : FrameContent):
        """
        Sends a frame to the device

        Parameters
        ----------
        frame : Frame
        """
        frame = Frame()
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP) as device_socket:
            device_socket.connect((self._IP, SYNDESI_PORT))
            device_socket.sendall(frame.value(content))
            device_socket.settimeout(0.2)
            try:
                device_socket.recvfrom(50)
            except socket.timeout:
                pass

def open_device(descriptor : str = None):
    """
    Opens a device, if the descriptor doesn't uniquely identify a device, the first device is returned
    
    Parameters
    ----------
    descriptor : str
        Device descriptor

    Returns
    -------
    device : Device
        Device handle
    """
    devices = list_devices(descriptor)
    if len(devices) == 0:
        raise ValueError("Device wasn't found")
        return None
    else:
        if len(devices) > 1:
            print(f"Multiple devices found ({len(devices)}")
        return devices[0]

def _device_checker(interface_ip):
    print(f"address : {interface_ip}")
    found_devices = []
    
    frame = Frame()
    frameContent = frame_contents.DEVICE_DISCOVER_request()

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    sock.bind((interface_ip, 0))
    sock.sendto(frame.value(frameContent), ("255.255.255.255", SYNDESI_PORT))

    sock.settimeout(RECV_TIMEOUT)

    while True:
        try:
            data, server = sock.recvfrom(200)
            print(f"Received : {data}")
        except socket.timeout:
            break
        else:
            # A device has responded
            found_devices.append(Device(server[0]))
    return found_devices


def list_devices(descriptor : str = None):
    """
    Returns a list of devices corresponding to the descriptor.
    Each host interface is checked with a thread. The function is ended once all
    threads are finished

    Parameters
    ----------
    descriptor : str
        Devices descriptor
    
    Returns
    -------
    devices : list of Devices
    """
    devices = []    
    with concurrent.futures.ThreadPoolExecutor() as executor:
        # List all ethernet interfaces
        interfaces = socket.getaddrinfo(host=socket.gethostname(), port=None, family=socket.AF_INET)

        threads = [executor.submit(_device_checker, interface[-1][0]) for interface in interfaces]

        for future in concurrent.futures.as_completed(threads):
            try:
                data = future.result()
            except Exception as exc:
                print(f'generated an exception : {exc}')
            else:
                print(f'output : {data}')
                devices += data
        print(f"All devices : {devices}")
    
    return devices