#!/usr/bin/env python3

import curses
from curses.ascii import ACK
from email.message import Message
import os
import socket
import threading
from  queue import Queue
import time
import sys

import argparse
from unittest.mock import DEFAULT

from locale import atof, setlocale, LC_NUMERIC

DEFAULT_PORT = 5544
DEFAULT_ADDRESS = 'localhost'

setlocale(LC_NUMERIC, 'fr_FR.UTF-8')
#atof('123,456')

class GlobVar:
    port = DEFAULT_PORT              # default server port
    timeout=1.0              # default waiting time for an answer. May be increased for debugging purpose
    address = DEFAULT_ADDRESS    # default server address. Use this with 'nc -l <port>' for testing on your machine

    # do not modify value below this line
    
    connectedToPi = False

    angularPosition = 0.0
    angularSpeed = 0.0
    linearSpeed = 0.0
    betaAngle=0.0
    torque=0.0
    batteryLevel=0.0
    
    userPresence=False
    emergencyStop=False
    
    message = []
    
    lastCommand = ""
    exceptionmsg= ""
    
    dataReceived=False
    
# Network event from socket. 
# Event are 'Connected to server' or 'disconnected from server'
class NetworkEvents:
    EVENT_CONNECTED=1
    EVENT_CONNECTION_LOST=0
    UNKNOWN_EVENT=-1
    
# Network managment class
# Contain a thread for connection to server and data reception
# Contains functions for sending message to server
# Contains functions for answer decoding
class Network():
    receiveCallback=None
    eventCallback=None
    reconnectionDelay =0
    waitForAnswer=False
    receiveEvent = None
    receivedAnswer = ""
    
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
    
    # Initialisation method.
    def __init__(self, receiveCallback=None, eventCallback=None) -> None:
        self.receiveCallback = receiveCallback
        self.eventCallback = eventCallback
        self.waitForAnswer=False
        self.receiveEvent = threading.Event()
    
    # Reception thread used for connecting to server and receiving data.
    # Never stop, auto reconnect if connection is lost
    # Send event when conencting to or disconnecting from server
    # send received message to appropriate callback
    def ReceptionThread(self) -> None:   
        while True:
            try:
                self.__connect()
                
                if self.eventCallback != None:
                    self.eventCallback(NetworkEvents.EVENT_CONNECTED)
                self.__read()
                
            except (RuntimeError, TimeoutError, socket.gaierror, ConnectionResetError) as e:
                if e.__class__ == RuntimeError or e.__class__== ConnectionResetError:
                    if self.eventCallback != None:
                        self.eventCallback(NetworkEvents.EVENT_CONNECTION_LOST)
            
            except Exception as e:
                pass
            
            time.sleep(2.0)
         
    # Method helper for starting reception thread    
    def startReceptionThread(self) -> None:
        self.threadId = threading.Thread(target=self.ReceptionThread, args=())
        self.threadId.daemon=True
        self.threadId.start()
            
    # Private method for connecting to server     
    def __connect(self) -> None:
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        
        try:
            self.sock.connect((GlobVar.address, GlobVar.port))
        except ConnectionRefusedError: 
            raise RuntimeError("Unable to connect to " + GlobVar.address + ":" + str(GlobVar.port))
    
        self.waitForAnswer=False
        
    # Private method for sending raw data to server
    def __write(self, msg: str) -> None:
        totalsent = 0
        if msg[-1] != '\n':
            msg = msg + '\n'
            
        MSGLEN = len(msg)
        msgbytes = bytes(msg,'UTF-8')
        
        while totalsent < MSGLEN:
            sent = self.sock.send(msgbytes[totalsent:])
            if sent == 0:
                GlobVar.connectedToPi=False
                raise RuntimeError("Unable to send data to " + GlobVar.address + ":" + str(GlobVar.port))
            totalsent = totalsent + sent
            
    # Private method for receiving data from server. 
    # Data received are sent to callback __receiveHandler for decoding
    def __read(self) -> None:
        chunks = []
        bytes_recd = 0
        last_char=0
        
        while True:
            while last_char != 0x0A:
                chunk = self.sock.recv(2048)
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
    def __receiveHandler(self, data: str) -> None:
        if self.receiveCallback != None:
            self.receiveCallback(data)

    # Private method for sending command to server
    def __sendCommand(self,cmd, waitans: bool) -> str:
        if waitans == True:
            self.waitForAnswer = True
        else:
            self.waitForAnswer = False
            
        self.__write(cmd)
        
        if waitans:
            ans = self.ANSWER_TIMEOUT
            try:
                self.receiveEvent.wait(timeout=GlobVar.timeout) # Max waiting time = GlobVar.timeout
                
                if self.receiveEvent.is_set():
                    ans=self.receivedAnswer
                    self.receivedAnswer=""
                else:
                    ans=self.ANSWER_TIMEOUT
                       
                self.receiveEvent.clear()
            except TimeoutError:
                ans=self.ANSWER_TIMEOUT
            except Exception as e:
                GlobVar.exceptionmsg = str(e)
                
            self.waitForAnswer=False
            return ans
        else:
            return self.ANSWER_ACK

# Thread for updating display
def threadRefreshScreen(currentWindow) -> None:
    while 1:
        currentWindow.clear()
        currentWindow.addstr("Connected to " + GlobVar.address + ":" + str(GlobVar.port) +" = " + str(GlobVar.connectedToPi))
        currentWindow.move(2,0)
        currentWindow.addstr("Torque = " + str(GlobVar.torque))
        currentWindow.move(3,0)
        currentWindow.addstr("Angular Position = " + str(GlobVar.angularPosition))
        currentWindow.move(4,0)
        currentWindow.addstr("Angular Speed = " + str(GlobVar.angularSpeed))
        currentWindow.move(5,0)
        currentWindow.addstr("Linear Speed = " + str(GlobVar.linearSpeed))
        currentWindow.move(6,0)
        currentWindow.addstr("Beta angle = " + str(GlobVar.betaAngle))
        currentWindow.move(8,0)
        currentWindow.addstr("Battery level = " + str(GlobVar.batteryLevel))
        currentWindow.move(10,0)
        currentWindow.addstr("User presence = " + str(GlobVar.userPresence))
        currentWindow.move(11,0)
        currentWindow.addstr("Emergency Stop = " + str(GlobVar.emergencyStop))
        #currentWindow.move(12,0)
        #currentWindow.addstr("Last command received = " + str(GlobVar.lastCommand))
        currentWindow.move(13,0)
        currentWindow.addstr("Messages received (log)")
        
        # up to 8 messages
        for i in range(0,len(GlobVar.message)):
            currentWindow.move(14+i,0)
            currentWindow.addstr("[mes "+str(i)+ "] ")
            currentWindow.addstr(str(GlobVar.message[i]))
        
        currentWindow.move(23,0)
        currentWindow.addstr("           CTRL-C = Quit program")
        currentWindow.refresh()
        time.sleep(0.5)

# Thread for reading keyboard keys and sending corresponding commands to server
# def threadGetKeys(win: curses.window, net:Network) -> None:
#     while 1: 
#         try:                          
#             key = win.getkey() 
#             win.addstr(" KEY = " + key)
            
#             GlobVar.currentMovement = "Stop"
#             if GlobVar.connectedToPi:
#                 if key == "KEY_UP":
#                     GlobVar.currentMovement = "Go Forward"
#                     GlobVar.last_answer = net.robotGoForward()
#                 elif key == "KEY_DOWN":
#                     GlobVar.currentMovement = "Go Backward"
#                     GlobVar.last_answer = net.robotGoBackward()
#                 elif key == "KEY_RIGHT":
#                     GlobVar.currentMovement = "Go Right"
#                     GlobVar.last_answer = net.robotGoRight()
#                 elif key == "KEY_LEFT":
#                     GlobVar.currentMovement = "Go Left"
#                     GlobVar.last_answer = net.robotGoLeft()
#                 elif key == " ":
#                     GlobVar.currentMovement = "Stop" 
#                     GlobVar.last_answer = net.robotStop() 
#                 elif key == "R" or key == 'r':
#                     GlobVar.last_answer = net.robotReset() 
#                     GlobVar.dumberStarted=False
#                 elif key == "U" or key == 'u':
#                     GlobVar.last_answer = net.robotStartWithoutWatchdog()
#                     if GlobVar.last_answer == net.ACK:
#                         GlobVar.dumberStarted=True
#                     else:
#                         GlobVar.dumberStarted=False 
#                 elif key == "W" or key == 'w':
#                     GlobVar.last_answer = net.robotStartWithWatchdog() 
#                     if GlobVar.last_answer == net.ACK:
#                         GlobVar.dumberStarted=True
#                     else:
#                         GlobVar.dumberStarted=False 
#                 elif key == "C" or key=='c':
#                     GlobVar.last_answer = net.robotCloseCom()
#                     GlobVar.connectedToDumber=False
#                     GlobVar.dumberStarted=False
#                 elif key == "O" or key =='o':
#                     GlobVar.last_answer = net.robotOpenCom() 
#                     if GlobVar.last_answer == net.ACK:
#                         GlobVar.connectedToDumber=True
#                     else:
#                         GlobVar.connectedToDumber=False         
            
#             #if key == os.linesep or key =='q' or key == 'Q':
#             #    break  
            
#         except Exception as e:
#             GlobVar.exceptionmsg="Exception received: " + str(e)

# Thread used for requesting battery level, exit if getBatteryLevelPeriod is 0 or below
def threadPeriodic(net: Network) -> None:
    while True:
        time.sleep(0.5)
        if GlobVar.dataReceived == True:
            GlobVar.dataReceived = False
        else:
            GlobVar.angularPosition = 0.0
            GlobVar.angularSpeed=0.0
            GlobVar.batteryLevel=0.0
            GlobVar.betaAngle=0.0
            GlobVar.emergencyStop=False
            GlobVar.linearSpeed=0.0
            GlobVar.torque=0.0
            GlobVar.userPresence=False
            
        # if GlobVar.getBatteryLevelPeriod>0:
        #     time.sleep(GlobVar.getBatteryLevelPeriod)
        
        #     GlobVar.batteryLevel = -1
        #     if GlobVar.connectedToPi:
        #         net.robotGetBattery() 
        # else:
        #     break
        
# Callback used to decode non answer message from server (mainly battery level and log message)
def receptionCallback(s:str) -> None:
    if s[-1] == '\n':
        s = s[:-1]
        
    GlobVar.lastCommand = s
    str_split = s.split(Network.SEPARATOR_CHAR)
    GlobVar.dataReceived = True
    
    if Network.LABEL_GUI_ANGULAR_POSITION.lower() in str_split[0].lower():
        try:
            GlobVar.angularPosition = atof(str_split[1])
        except:
            GlobVar.angularPosition = 0.0
    
    if Network.LABEL_GUI_ANGULAR_SPEED.lower() in str_split[0].lower():   
        try:
            GlobVar.angularSpeed = atof(str_split[1])
        except:
            GlobVar.angularSpeed = 0.0
    
    if Network.LABEL_GUI_BATTERY_LEVEL.lower() in str_split[0].lower():
        try:
            GlobVar.batteryLevel = atof(str_split[1])
        except:
            GlobVar.batteryLevel = 0.0
    
    if Network.LABEL_GUI_LINEAR_SPEED.lower() in str_split[0].lower():
        try:
            GlobVar.linearSpeed = atof(str_split[1])
        except:
            GlobVar.linearSpeed = 0.0
    
    if Network.LABEL_GUI_USER_PRESENCE.lower() in str_split[0].lower():
        try:
            GlobVar.userPresence = bool(str_split[1])
        except:
            GlobVar.userPresence = False
    
    if Network.LABEL_GUI_BETA_ANGLE.lower() in str_split[0].lower():
        try:
            GlobVar.betaAngle = atof(str_split[1])
        except:
            GlobVar.betaAngle = 0.0
    
    if Network.LABEL_GUI_TORQUE.lower() in str_split[0].lower():
        try:
            GlobVar.torque = atof(str_split[1])
        except:
            GlobVar.torque = 0.0
    
    if Network.LABEL_GUI_EMERGENCY_STOP.lower() in str_split[0].lower():
        try:
            GlobVar.emergencyStop = bool(str_split[1])
        except:
            GlobVar.emergencyStop = 0.0
    
    if Network.LABEL_GUI_LOG.lower() in str_split[0].lower():
        try:
            GlobVar.message.append(str(str_split[1]))
        except Exception as e:
            GlobVar.exceptionmsg = str(e)
        
        if len(GlobVar.message) > 8:
            GlobVar.message.pop(0)

# Callback for connection/deconnection event from network manager
def eventCallback(event: NetworkEvents) -> None:
    if event == NetworkEvents.EVENT_CONNECTED:
        GlobVar.connectedToPi = True
    elif event == NetworkEvents.EVENT_CONNECTION_LOST:
        GlobVar.connectedToPi = False

# Main program, wait for keys thread to end (CTRL-C)
def main(win: curses.window) -> None:
    win.keypad(True)
    
    net = Network(receiveCallback=receptionCallback, eventCallback=eventCallback)
    
    net.startReceptionThread()
     
    windowThread = threading.Thread(target=threadRefreshScreen, args=(win,))
    windowThread.daemon=True
    windowThread.start()

    # keyThread = threading.Thread(target=threadGetKeys, args=(win,net,))
    # keyThread.daemon=True
    # keyThread.start()

    periodicThread = threading.Thread(target=threadPeriodic, args=(net,))
    periodicThread.daemon=True
    periodicThread.start()

    windowThread.join()
    
    while True:
        time.sleep(2.0)
 
parser = argparse.ArgumentParser()
parser.add_argument('-p', metavar='port', help='network port (default: ' + str(DEFAULT_PORT) + ')')
parser.add_argument('address', metavar='address', type=str, help='address of rapsberry')
    
args = parser.parse_args()

try:
    if args.p == None:
        args.p = DEFAULT_PORT
except Exception as e:
    args.p = DEFAULT_PORT

GlobVar.address = args.address
GlobVar.port = int(args.p)

# GlobVar.address = DEFAULT_ADDRESS
# GlobVar.port = DEFAULT_PORT

print('Server address "' + GlobVar.address +':'+str(GlobVar.port)+'"')

try:         
    curses.wrapper(main) 
    
except KeyboardInterrupt: # exception when pressing CTRL-C
    print ("Bye bye")

