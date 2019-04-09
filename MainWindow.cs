//
//  MainWindow.cs
//
//  Author:
//       Di MERCURIO Sébastien <dimercur@insa-toulouse.fr>
//
//  Copyright (c) 2018 INSA - DGEI
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
using System;
using Gtk;
using Gdk;

using SegwayUI;

public partial class MainWindow : Gtk.Window
{
    GlobalVariables globalVariables;
    MessageLog messageLogDialog;
    SegwayCommandManager segwayManager;

    public MainWindow() : base(Gtk.WindowType.Toplevel)
    {
        Build();

        globalVariables = new GlobalVariables();

        globalVariables.AngularPositionWidget = new JaugeWidget(drawingareaAngle, "Angular Position (rad)", -35*Math.PI/180, 35*Math.PI/180);
        globalVariables.AngularPositionWidget.FillColor = new Cairo.Color(0.1, 0.8, 0.3);
        globalVariables.AngularPosition = 0;

        globalVariables.TorqueWidget = new JaugeWidget(drawingareaTorque, "Torque (N.m)", -15, 15);
        globalVariables.TorqueWidget.FillColor = new Cairo.Color(0.8, 0.0, 0.3); 
        globalVariables.Torque = 0.0;

        globalVariables.AngularSpeedWidget = new JaugeWidget(drawingareaAngularSpeed, "Angular Speed (rad/s)", -Math.PI, Math.PI);
        globalVariables.AngularSpeedWidget.FillColor = new Cairo.Color(0.5, 0.5, 0.0); 
        globalVariables.AngularSpeed = 0.0;

        globalVariables.LinearSpeedWidget = new JaugeWidget(drawingareaLinearSpeed, "Linear Speed (m/s)",0,200);
        globalVariables.LinearSpeedWidget.FillColor = new Cairo.Color(0.8, 0.2, 0.2);
        globalVariables.LinearSpeed = 0;  

        globalVariables.BetaAngleWidget = new JaugeWidget(drawingareaBeta, "User Angle \"Beta\" (rad)", -35*Math.PI/180, 35*Math.PI/180);
        globalVariables.BetaAngleWidget.FillColor = new Cairo.Color(0.1, 0.1, 0.7);
        globalVariables.BetaAngle = 0.0;

        globalVariables.BatteryLevelWidget = new BatteryWidget(imageBattery, labelBattery);
        globalVariables.BatteryLevel = 0.0;

        globalVariables.UserPresenceWidget = new UserWidget(imageUser, labelUser);
        globalVariables.UserPresence = false;

        globalVariables.EmergencyStopWidget = new EmergencyWidget(imageEmergency, labelEmergency);
        globalVariables.EmergencyStop = false;

        messageLogDialog = new MessageLog();
        messageLogDialog.Hide();

        segwayManager = new SegwayCommandManager(HandleCommandReceivedEvent);
        entryServerAddress.Text = Client.defaultIP.ToString();
        entryServerPort.Text = Client.defaultPort.ToString();

        globalVariables.InvalidateAll();
        ChangeSensitivity(false);
    }

    protected void OnDeleteEvent(object sender, DeleteEventArgs a)
    {
        Application.Quit();
        a.RetVal = true;
    }

    protected void UpdateMessageLogger(string s)
    {
        messageLogDialog.Add(s);
    }

    void HandleCommandReceivedEvent(string header, string data, byte[] buffer)
    {
        Gtk.Application.Invoke(delegate {
            UpdateMessageLogger(header + "=" + data+"\n");
        });

        if (header != null)
        {
            if (header.ToLower().Contains(SegwayCommandList.AngularPosition.ToLower()))
            {
                if (data != null)
                {
                    double param=0.0;

                    try
                    {
                        param = Convert.ToDouble(data.ToLower());    
                    }
                    catch (FormatException)
                    {
                        Console.WriteLine("AngularPosition: data misformated !!");
                        return;
                    }

                    globalVariables.AngularPosition = param;
                }
                else Console.WriteLine("AngularPosition received without data !!");
            }

            if (header.ToLower().Contains(SegwayCommandList.AngularSpeed.ToLower()))
            {
                if (data != null)
                {
                    double param = 0.0;

                    try
                    {
                        param = Convert.ToDouble(data.ToLower());
                    }
                    catch (FormatException)
                    {
                        Console.WriteLine("AngularSpeed: data misformated !!");
                        return;
                    }

                    globalVariables.AngularSpeed = param;
                }
                else Console.WriteLine("AngularSpeed received without data !!");
            }

            if (header.ToLower().Contains(SegwayCommandList.BatteryLevel.ToLower()))
            {
                if (data != null)
                {
                    double param = 0.0;

                    try
                    {
                        param = Convert.ToDouble(data.ToLower());
                    }
                    catch (FormatException)
                    {
                        Console.WriteLine("BatteryLevel: data misformated !!");
                        return;
                    }

                    globalVariables.BatteryLevel = param;
                }
                else Console.WriteLine("BatteryLevel received without data !!");
            }

            if (header.ToLower().Contains(SegwayCommandList.BetaAngle.ToLower()))
            {
                if (data != null)
                {
                    double param = 0.0;

                    try
                    {
                        param = Convert.ToDouble(data.ToLower());
                    }
                    catch (FormatException)
                    {
                        Console.WriteLine("BetaAngle: data misformated !!");
                        return;
                    }

                    globalVariables.BetaAngle = param;
                }
                else Console.WriteLine("BetaAngle received without data !!");
            }

            if (header.ToLower().Contains(SegwayCommandList.EmergencyStop.ToLower()))
            {
                if (data != null)
                {
                    bool param = false;

                    try
                    {
                        param = Convert.ToBoolean(data.ToLower());
                    }
                    catch (FormatException)
                    {
                        Console.WriteLine("EmergencyStop: data misformated !!");
                        return;
                    }

                    globalVariables.EmergencyStop = param;
                }
                else Console.WriteLine("EmergencyStop received without data !!");
            }

            if (header.ToLower().Contains(SegwayCommandList.LinearSpeed.ToLower()))
            {
                if (data != null)
                {
                    double param = 0.0;

                    try
                    {
                        param = Convert.ToDouble(data.ToLower());
                    }
                    catch (FormatException)
                    {
                        Console.WriteLine("LinearSpeed: data misformated !!");
                        return;
                    }

                    globalVariables.LinearSpeed = param;
                }
                else Console.WriteLine("LinearSpeed received without data !!");
            }

            if (header.ToLower().Contains(SegwayCommandList.Torque.ToLower()))
            {
                if (data != null)
                {
                    double param = 0.0;

                    try
                    {
                        param = Convert.ToDouble(data.ToLower());
                    }
                    catch (FormatException)
                    {
                        Console.WriteLine("Torque: data misformated !!");
                        return;
                    }

                    globalVariables.Torque = param;
                }
                else Console.WriteLine("Torque received without data !!");
            }

            if (header.ToLower().Contains(SegwayCommandList.UserPresence.ToLower()))
            {
                if (data != null)
                {
                    bool param = false;

                    try
                    {
                        param = Convert.ToBoolean(data.ToLower());
                    }
                    catch (FormatException)
                    {
                        Console.WriteLine("UserPresence: data misformated !!");
                        return;
                    }

                    globalVariables.UserPresence = param;
                }
                else Console.WriteLine("UserPresence received without data !!");
            }
        }
    }

    private void ChangeSensitivity(bool sensitivity)
    {
        tableStatus.Sensitive = sensitivity;
        buttonShowLog.Sensitive = sensitivity;

        globalVariables.AngularPositionWidget.Sensitive = sensitivity;
        globalVariables.AngularSpeedWidget.Sensitive = sensitivity;
        globalVariables.BetaAngleWidget.Sensitive = sensitivity;
        globalVariables.LinearSpeedWidget.Sensitive = sensitivity;
        globalVariables.TorqueWidget.Sensitive = sensitivity;
        messageLogDialog.Sensitive = sensitivity;
    }

    protected void OnButtonServerConnectClicked(object sender, EventArgs e)
    {
        string hostname;
        int port;
        bool status = false;

        if (buttonServerConnect.Label.Contains("Connect"))
        {
            hostname = entryServerAddress.Text;
            try
            {
                port = Convert.ToInt32(entryServerPort.Text);
            }
            catch (FormatException)
            {
                MessageDialog md = new MessageDialog(this, DialogFlags.DestroyWithParent,
                                                     MessageType.Error, ButtonsType.Ok,
                                                    "Invalid port number")
                {
                    Title = "Error"
                };

                md.Run();
                md.Destroy();

                return;
            }

            try
            {
                status = segwayManager.Open(hostname, port); 
            }
            catch (Exception)
            {
                MessageDialog md = new MessageDialog(this, DialogFlags.DestroyWithParent,
                                                     MessageType.Error, ButtonsType.Ok,
                                                    "Error while opening port")
                {
                    Title = "Error"
                };

                md.Run();
                md.Destroy();

                return;
            }

            if (status != true)
            {
                MessageDialog md = new MessageDialog(this, DialogFlags.DestroyWithParent,
                                                     MessageType.Error, ButtonsType.Ok,
                                                    "Error while opening port")
                {
                    Title = "Error"
                };

                md.Run();
                md.Destroy();
            }
            else
            {
                buttonServerConnect.Label = "Disconnect";

                try
                {
                    imageConnexion.Pixbuf = Pixbuf.LoadFromResource("SegwayUI.ressources.connected.png");
                }
                catch (ArgumentException a)
                {
                    Console.WriteLine("Error while opening ressource: " +a.ToString());
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Error while opening ressource: " + ex.ToString());
                }
                 
                ChangeSensitivity(true);
            }
        }
        else // deconnection du server
        {
            segwayManager.Close();
            buttonServerConnect.Label = "Connect";

            try
            {
                imageConnexion.Pixbuf = Pixbuf.LoadFromResource("SegwayUI.ressources.disconnected.png");
            }
            catch (ArgumentException a)
            {
                Console.WriteLine("Error while opening ressource: " + a.ToString());
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error while opening ressource: " + ex.ToString());
            }

            ChangeSensitivity(false);
            messageLogDialog.Clear();
        }
    }

    protected void OnButtonShowLogClicked(object sender, EventArgs e)
    {
        messageLogDialog.Show();
    }

    protected void OnQuitActionActivated(object sender, EventArgs e)
    {
        Console.WriteLine("Bye bye 2");
        if (segwayManager != null) segwayManager.Close();
        this.Destroy();
        Application.Quit();
    }

    protected void OnShowLogActionActivated(object sender, EventArgs e)
    {
        throw new NotImplementedException("Menu event not yet implemented.");
    } 
}
