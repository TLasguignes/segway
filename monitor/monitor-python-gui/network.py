# -*- coding: utf-8 -*-

import socket
import time
import sys

from PyQt5 import QtCore
from globvar import GlobVar

import ipaddress
import threading

# Network event from socket. 
# Event are 'Connected to server' or 'disconnected from server'
class NetworkEvents():
    EVENT_CONNECTED=1
    EVENT_CONNECTION_LOST=0
    UNKNOWN_EVENT=-1

class NetworkAnswers():
     # Decoded answers
    ACK = 1 
    NACK =2
    COM_ERROR =3
    TIMEOUT_ERROR=4
    CMD_REJECTED=5
    UNKNOWN=-1
    
# Network managment class
# Contain a thread for conenction to server and data reception
# Contains functions for sending message to server
# Contains functions for answer decoding
class Network(QtCore.QThread):
    i=0
    reconnectionDelay =0
    receivedAnswer = ""
    receiveFlag = None
    
    receptionEvent = QtCore.pyqtSignal(str)
    connectionEvent= QtCore.pyqtSignal(int)
    logEvent = QtCore.pyqtSignal(str)
    
    # List of possible messages from server
    LABEL_GUI_ANGULAR_POSITION = "AngularPosition"
    LABEL_GUI_ANGULAR_SPEED = "AngularSpeed"
    LABEL_GUI_BATTERY_LEVEL = "Battery"
    LABEL_GUI_LINEAR_SPEED = "LinearSpeed"
    LABEL_GUI_USER_PRESENCE = "User"
    LABEL_GUI_BETA_ANGLE = "Beta"
    LABEL_GUI_TORQUE = "Torque"
    LABEL_GUI_EMERGENCY_STOP = "Emergency"
    LABEL_GUI_LOG = "Log"

    SEPARATOR_CHAR = '='
   
    def __init__(self):
        super(Network, self).__init__()
        self.i =0
        self.receiveFlag = threading.Event()
        
    def run(self):
        print ("Network thread started" )
        self.i =0
        
        while True:
            self.i = self.i+1
                       
            try:
                self.__connect()
                            
                self.connectionEvent.emit(NetworkEvents.EVENT_CONNECTED)
                self.__read()
                
            except (RuntimeError, TimeoutError, socket.gaierror, ConnectionResetError, ConnectionRefusedError) as e:
                print ("exception in network thread: " + str(e))
                if e.__class__ == RuntimeError or \
                   e.__class__== ConnectionResetError or \
                   e.__class__ == ConnectionRefusedError:
                    self.connectionEvent.emit(NetworkEvents.EVENT_CONNECTION_LOST)
                
            except Exception as e:
                print ("unknown exception in network thread: " + str(e))
                       
            time.sleep(2.0)
    
    # Private method for connecting to server     
    def __connect(self) -> None:
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        #self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        try:
            self.sock.connect((GlobVar.address, GlobVar.port))
        except ConnectionRefusedError: 
            raise RuntimeError("Unable to connect to " + GlobVar.address + ":" + str(GlobVar.port))
    
        # In UDP, no way to know if server is running (connect is always successfull). 
        # So, send a single line feed to ping the server
        #self.sock.send(str.encode("\n"))  
        
    # Private method for receiving data from server. 
    # Data received are sent to callback __receiveHandler for decoding
    def __read(self) -> None:
        chunks = []
        bytes_recd = 0
        last_char=0
        
        while True:
            while last_char != 0x0A:
                chunk = self.sock.recv(2048)
                #print ("Chunk =" + str(chunk))
                
                if chunk == b'':
                    raise RuntimeError("Connection lost with " + GlobVar.address + ":" + str(GlobVar.port))
                chunks.append(chunk)
                bytes_recd = bytes_recd + len(chunk)
                last_char=chunk[-1]
            
            self.__receiveHandler(b''.join(chunks).decode("utf-8"))
            chunks = []
            bytes_recd =0
            last_char=0
    
    # private callback for reception and decoding of data. 
    # If no answer is wait, send data to caller callback
    def __receiveHandler(self, data: str) -> None:
        # traitement a faire lors de la reception de donnée
        self.logEvent.emit("< " + data)
        
        # envoie au callback
        self.receptionEvent.emit(data)
    
    def checkAddressIsValid(self, address: str) -> bool:
        try:
            if address == "localhost":
                return True
            
            ip=ipaddress.ip_address(address)
            return True
        
        except ValueError as e:
            return False

