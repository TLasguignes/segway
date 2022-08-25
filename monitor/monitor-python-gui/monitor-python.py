#!/usr/bin/env python3

from email.message import Message
import os

import time
import sys

from PyQt5 import (QtCore, QtWidgets,QtGui)

from main_window import Ui_MainWindow
from log_dialog import Ui_Dialog
from network import *
from globvar import GlobVar

import ressources
import math
from locale import atof, setlocale, LC_NUMERIC

class Window(QtWidgets.QMainWindow, Ui_MainWindow):
    _msg_dialog= None
    _uiTimer=None
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setupUi(self)
        
        self.DisableUIWidgets()
        
        self.lineEdit_address.setText(GlobVar.address)
        self.lineEdit_port.setText(str(GlobVar.port))
        
        self._msg_dialog=QtWidgets.QDialog()
        self._msg_dialog.ui= Ui_Dialog()
        self._msg_dialog.ui.setupUi(self._msg_dialog)
        
        self.networkThread = Network()
        
        self.connectSignalSlots()
        
        # Start network thread and wait for event indicating monitor is connected to a target
        self.networkThread.start()
        
        # Create ui timer
        self._uiTimer = QtCore.QTimer()
        self._uiTimer.timeout.connect(self.OnUITimeout)
        
    def connectSignalSlots(self):
        # Buttons
        self.pushButton_Log.pressed.connect(self.OnMenu_OpenMessageLog)
        
        # LineEdit
        self.lineEdit_address.textChanged.connect(self.OnLineEditChange_Address)
        self.lineEdit_port.textChanged.connect(self.OnLineEditChange_Port)
        
        # Menu
        self.action_OpenMessageLog.triggered.connect(self.OnMenu_OpenMessageLog)
        self.action_Quitter.triggered.connect(self.OnMenu_Quitter)
        
        # Message Dialog
        self._msg_dialog.ui.pushButton_clearLog.pressed.connect(self.OnButtonPress_ClearLog)
        self._msg_dialog.ui.pushButton_closeLog.pressed.connect(self.OnButtonPress_CloseLog)
        
        # Network signals
        self.networkThread.receptionEvent.connect(self.OnReceptionEvent)
        self.networkThread.connectionEvent.connect(self.OnConnectionEvent)
        self.networkThread.logEvent.connect(self.OnLogEvent)
        #self.networkThread.answerEvent.connect(self.OnAnswerEvent)
    
    def EnableUIWidgets(self):
        #self.verticalLayout_progressbars.setEnabled(True)
        
        self.icon_battery.setEnabled(True)
        self.icon_user.setEnabled(True)
        self.icon_emergency.setEnabled(True)
        self.label_battery.setEnabled(True)
        self.label_user.setEnabled(True)
        self.label_emergency.setEnabled(True)

        self.pushButton_Log.setEnabled(True)
                      
    def DisableUIWidgets(self):
        #self.verticalLayout_progressbars.setEnabled(False)
        
        self.icon_battery.setEnabled(False)
        self.icon_user.setEnabled(False)
        self.icon_emergency.setEnabled(False)
        self.label_battery.setEnabled(False)
        self.label_user.setEnabled(False)
        self.label_emergency.setEnabled(False)
        
        self.pushButton_Log.setEnabled(False)
            
    @QtCore.pyqtSlot(str)  
    def OnLineEditChange_Address(self, text):
        if self.networkThread.checkAddressIsValid(text):
            GlobVar.address = text
        
    @QtCore.pyqtSlot(str)  
    def OnLineEditChange_Port(self, text):
        GlobVar.port = int(text)
        
    @QtCore.pyqtSlot() 
    def OnMenu_OpenMessageLog(self):
        self._msg_dialog.show()
       
    @QtCore.pyqtSlot()  
    def OnMenu_Quitter(self):
        self._msg_dialog.hide()
        self.close()
          
    def closeEvent(self, event):
        self._msg_dialog.hide()
        event.accept()
          
    @QtCore.pyqtSlot() 
    def OnButtonPress_ClearLog(self):
        plainTextEdit=self._msg_dialog.ui.plainTextEdit
        plainTextEdit.document().clear()
        
    @QtCore.pyqtSlot() 
    def OnButtonPress_CloseLog(self):
        self._msg_dialog.hide()
        
    # Callback used to decode non answer message from server (mainly battery level and log message)
    @QtCore.pyqtSlot(str) 
    def OnReceptionEvent(self, s) -> None: 
        msgList = s.split('\n')
        
        for msg in msgList:
            if msg != "":
                str_split = msg.split(Network.SEPARATOR_CHAR)
                GlobVar.dataReceived = True
                
                if Network.LABEL_GUI_ANGULAR_POSITION.lower() in str_split[0].lower():
                    try:
                        GlobVar.angularPosition = atof(str_split[1])
                    except Exception as e:
                        GlobVar.angularPosition = 0.0
                
                elif Network.LABEL_GUI_ANGULAR_SPEED.lower() in str_split[0].lower():   
                    try:
                        GlobVar.angularSpeed = atof(str_split[1])
                    except:
                        GlobVar.angularSpeed = 0.0
                
                elif Network.LABEL_GUI_BATTERY_LEVEL.lower() in str_split[0].lower():
                    try:
                        GlobVar.batteryLevel = atof(str_split[1])
                    except:
                        GlobVar.batteryLevel = 0.0
                
                elif Network.LABEL_GUI_LINEAR_SPEED.lower() in str_split[0].lower():
                    try:
                        GlobVar.linearSpeed = atof(str_split[1])
                    except:
                        GlobVar.linearSpeed = 0.0
                
                elif Network.LABEL_GUI_USER_PRESENCE.lower() in str_split[0].lower():
                    if "true" in str_split[1].lower():
                        GlobVar.userPresence=True
                    else:
                        GlobVar.userPresence=False
                
                elif Network.LABEL_GUI_BETA_ANGLE.lower() in str_split[0].lower():
                    try:
                        GlobVar.betaAngle = atof(str_split[1])
                    except:
                        GlobVar.betaAngle = 0.0
                
                elif Network.LABEL_GUI_TORQUE.lower() in str_split[0].lower():
                    try:
                        GlobVar.torque = atof(str_split[1])
                    except:
                        GlobVar.torque = 0.0
                
                elif Network.LABEL_GUI_EMERGENCY_STOP.lower() in str_split[0].lower():
                    if "true" in str_split[1].lower():
                        GlobVar.emergencyStop=True
                    else:
                        GlobVar.emergencyStop=False
                
                elif Network.LABEL_GUI_LOG.lower() in str_split[0].lower():
                    pass
                
                else:
                    print ("unknown message: " + msg)

    # Callback for connection/deconnection event from network manager
    @QtCore.pyqtSlot(int) 
    def OnConnectionEvent(self, event) -> None:       
        if event == NetworkEvents.EVENT_CONNECTED:
            GlobVar.connectedToPi = True
            print ("Connected to server")
            
            self.label_connectionStatus.setText("Connected")
            self.EnableUIWidgets()
            self._uiTimer.start(100)
        elif event == NetworkEvents.EVENT_CONNECTION_LOST:
            GlobVar.connectedToPi = False
            print ("Disconnected from server")
            
            self.label_connectionStatus.setText("Not connected")
            self.DisableUIWidgets()
            self._uiTimer.stop()
    
    # Callback for log event from network manager
    @QtCore.pyqtSlot(str) 
    def OnLogEvent(self, txt) -> None:
        self._msg_dialog.ui.plainTextEdit.textCursor().insertText(txt)
    
    @QtCore.pyqtSlot()
    def OnUITimeout(self) -> None:
        #print ("UI event")
        if GlobVar.dataReceived == True:
            GlobVar.dataReceived= False
            
            valf = ((GlobVar.betaAngle+0.61) *100.0)/(2*0.61)
            if valf<0.0:
               valf=0.0
            elif valf>100.0:
               valf=100.0    
            
            self.progressBar_Angle_Beta.setValue(int(valf))  
            self.label_Beta.setText("{:.2f} rad".format(GlobVar.betaAngle))  
            
            valf = ((GlobVar.angularPosition+0.61) *100.0)/(2*0.61)
            if valf<0.0:
                valf=0.0
            elif valf>100.0:
                valf=100.0    

            self.progressBar_Angular_Position.setValue(int(valf))         
            self.label_AngularPosition.setText("{:.2f} rad".format(GlobVar.angularPosition))  
            
            valf = ((GlobVar.angularSpeed + math.pi) *100.0)/(2*math.pi)
            if valf<0.0:
                valf=0.0
            elif valf>100.0:
                valf=100.0    

            self.progressBar_Angular_Speed.setValue(int(valf))
            self.label_AngularSpeed.setText("{:.2f} rad/s".format(GlobVar.angularSpeed)) 
            
            valf = ((GlobVar.torque+15.0) *100.0)/(2*15.0)
            if valf<0.0:
                valf=0.0
            elif valf>100.0:
                valf=100.0    

            self.progressBar_Torque.setValue(int(valf))
            self.label_Torque.setText("{:.2f} N.m".format(GlobVar.torque))
            
            valf = (GlobVar.linearSpeed *100.0)/(200.0)
            if valf<0.0:
                valf=0.0
            elif valf>100.0:
                valf=100.0    

            self.progressBar_Linear_Speed.setValue(int(valf))
            self.label_LinearSpeed.setText("{:.2f} m/s".format(GlobVar.linearSpeed))
            
            if GlobVar.userPresence == True:
                self.icon_user.setPixmap(QtGui.QPixmap(":/icons/userPresent.png"))
                self.label_user.setText("Present")
            else:
                self.icon_user.setPixmap(QtGui.QPixmap(":/icons/userNotPresent.png"))
                self.label_user.setText("Not present")
                
            if GlobVar.emergencyStop == True:
                self.icon_emergency.setPixmap(QtGui.QPixmap(":/icons/emergency-on.png"))
                self.label_emergency.setText("Emergency")
            else:
                self.icon_emergency.setPixmap(QtGui.QPixmap(":/icons/emergency-off.png"))
                self.label_emergency.setText("No emergency")

            self.label_battery.setText("{:.1f} %".format(GlobVar.batteryLevel))
            if GlobVar.batteryLevel >= 88.0:
                self.icon_battery.setPixmap(QtGui.QPixmap(":/icons/battery100.png"))  
            elif GlobVar.batteryLevel >= 63.0:
                self.icon_battery.setPixmap(QtGui.QPixmap(":/icons/battery75.png")) 
            elif GlobVar.batteryLevel >= 38.0:
                self.icon_battery.setPixmap(QtGui.QPixmap(":/icons/battery50.png"))  
            elif GlobVar.batteryLevel >= 12.0:
                self.icon_battery.setPixmap(QtGui.QPixmap(":/icons/battery25.png")) 
            else:
                self.icon_battery.setPixmap(QtGui.QPixmap(":/icons/battery0.png")) 
                         
try: 
    if len(sys.argv)>=2:
        GlobVar.address = sys.argv[1]
    else:
        print ("No target address specified: using localhost:5544")
        print ("Usage: monitor-python.py address [port]")
        
        #exit (-1) # Comment this line for connecting to localhost
        
    if len(sys.argv)>=3:
        GlobVar.port = int(sys.argv[2])
        
    app = QtWidgets.QApplication(sys.argv)
    window = Window()
    window.show()
    app.exec_()
    
except KeyboardInterrupt: # exception when pressing CTRL-C
    print ("Bye bye")

