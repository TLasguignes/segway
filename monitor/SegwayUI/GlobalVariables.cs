//
//  GlobalVariables.cs
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

namespace SegwayUI
{
    public class GlobalVariables
    {
        public enum VarID
        {
            AngularPositionID,
            BetaAngleID,
            AngularSpeedID,
            BatteryLevelID,
            LinearSpeedID,
            TorqueID,
            UserPresenceID,
            EmergencyStopID
        };

        private const int TIMEOUT = 1000;

        public delegate void InvalidEvent(VarID id);
        public InvalidEvent InvalidEventHandler = null;
        public delegate void UpdatedEvent(VarID id);
        public UpdatedEvent UpdatedEventHandler = null;

        private System.Timers.Timer angularPositionTimer = new System.Timers.Timer();
        private System.Timers.Timer betaAngleTimer = new System.Timers.Timer();
        private System.Timers.Timer angularSpeedTimer = new System.Timers.Timer();
        private System.Timers.Timer batteryLevelTimer = new System.Timers.Timer();
        private System.Timers.Timer linearSpeedTimer = new System.Timers.Timer();
        private System.Timers.Timer torqueTimer = new System.Timers.Timer();
        private System.Timers.Timer userPresenceTimer = new System.Timers.Timer();
        private System.Timers.Timer emergencyStopTimer = new System.Timers.Timer();

        private JaugeWidget angularPositionWidget;
        public JaugeWidget AngularPositionWidget
        {
            get
            {
                return angularPositionWidget;
            }

            set
            {
                angularPositionWidget = value;
            }
        }

        public double AngularPosition
        {
            get
            {
                return angularPositionWidget.CurrentValue;
            }

            set
            {
                angularPositionWidget.CurrentValue = value;
                AngularPositionInvalid = false;
                //angularPositionTimer.Start();
            }
        }

        private JaugeWidget betaAngleWidget;
        public JaugeWidget BetaAngleWidget
        {
            get
            {
                return betaAngleWidget;
            }

            set
            {
                betaAngleWidget = value;
            }
        }

        public double BetaAngle
        {
            get
            {
                return betaAngleWidget.CurrentValue;
            }

            set
            {
                betaAngleWidget.CurrentValue = value;
                BetaAngleInvalid = false;
                //betaAngleTimer.Start();
            }
        }

        private JaugeWidget angularSpeedWidget;
        public JaugeWidget AngularSpeedWidget
        {
            get
            {
                return angularSpeedWidget;
            }

            set
            {
                angularSpeedWidget = value;
            }
        }

        public double AngularSpeed
        {
            get
            {
                return angularSpeedWidget.CurrentValue;
            }

            set
            {
                angularSpeedWidget.CurrentValue = value;
                AngularSpeedInvalid = false;
                //angularSpeedTimer.Start();
            }
        }

        private BatteryWidget batteryLevelWidget;
        public BatteryWidget BatteryLevelWidget
        {
            get
            {
                return batteryLevelWidget;
            }

            set
            {
                batteryLevelWidget = value;
            }
        }

        public double BatteryLevel
        {
            get
            {
                return batteryLevelWidget.Value;
            }

            set
            {
                batteryLevelWidget.Value = value;
                BatteryLevelInvalid = false;
                //batteryLevelTimer.Start();
            }
        }

        private JaugeWidget linearSpeedWidget;
        public JaugeWidget LinearSpeedWidget
        {
            get
            {
                return linearSpeedWidget;
            }

            set
            {
                linearSpeedWidget = value;
            }
        }

        public double LinearSpeed
        {
            get
            {
                return linearSpeedWidget.CurrentValue;
            }

            set
            {
                linearSpeedWidget.CurrentValue = value;
                LinearSpeedInvalid = false;
                //linearSpeedTimer.Start();
            }
        }

        private JaugeWidget torqueWidget;
        public JaugeWidget TorqueWidget
        {
            get
            {
                return torqueWidget;
            }

            set
            {
                torqueWidget = value;
            }
        }

        public double Torque
        {
            get
            {
                return torqueWidget.CurrentValue;
            }

            set
            {
                torqueWidget.CurrentValue = value;
                TorqueInvalid = false;
                //torqueTimer.Start();
            }
        }

        private UserWidget userPresenceWidget;
        public UserWidget UserPresenceWidget
        {
            get
            {
                return userPresenceWidget;
            }

            set
            {
                userPresenceWidget = value;
            }
        }

        public bool UserPresence
        {
            get
            {
                return userPresenceWidget.Value;
            }

            set
            {
                userPresenceWidget.Value = value;
                UserPresenceInvalid = false;
                //userPresenceTimer.Start();
            }
        }

        private EmergencyWidget emergencyStopWidget;
        public EmergencyWidget EmergencyStopWidget
        {
            get
            {
                return emergencyStopWidget;
            }

            set
            {
                emergencyStopWidget = value;
            }
        }

        public bool EmergencyStop
        {
            get
            {
                return emergencyStopWidget.Value;
            }

            set
            {
                emergencyStopWidget.Value = value;
                EmergencyStopInvalid = false;
                //emergencyStopTimer.Start();
            }
        }

        public bool AngularPositionInvalid
        {
            get
            {
                return angularPositionWidget.Invalid;
            }

            set
            {
                angularPositionWidget.Invalid = value;
            }
        }

        public bool BetaAngleInvalid
        {
            get
            {
                return betaAngleWidget.Invalid;
            }

            set
            {
                betaAngleWidget.Invalid = value;
            }
        }

        public bool AngularSpeedInvalid
        {
            get
            {
                return angularSpeedWidget.Invalid;
            }

            set
            {
                angularSpeedWidget.Invalid = value;
            }
        }

        public bool BatteryLevelInvalid
        {
            get
            {
                return batteryLevelWidget.Invalid;
            }

            set
            {
                batteryLevelWidget.Invalid = value;
            }
        }

        public bool LinearSpeedInvalid
        {
            get
            {
                return linearSpeedWidget.Invalid;
            }

            set
            {
                linearSpeedWidget.Invalid = value;
            }
        }

        public bool TorqueInvalid
        {
            get
            {
                return torqueWidget.Invalid;
            }

            set
            {
                torqueWidget.Invalid = value;
            }
        }

        public bool UserPresenceInvalid
        {
            get
            {
                return userPresenceWidget.Invalid;
            }

            set
            {
                userPresenceWidget.Invalid = value;
            }
        }

        public bool EmergencyStopInvalid
        {
            get
            {
                return emergencyStopWidget.Invalid;
            }

            set
            {
                emergencyStopWidget.Invalid = value;
            }
        }

        public GlobalVariables()
        {
            // init des variables
            angularPositionWidget = new JaugeWidget(null);
            betaAngleWidget = new JaugeWidget(null);
            angularSpeedWidget = new JaugeWidget(null);
            batteryLevelWidget = new BatteryWidget(null, null);
            linearSpeedWidget = new JaugeWidget(null);
            torqueWidget = new JaugeWidget(null);
            userPresenceWidget = new UserWidget(null, null);
            emergencyStopWidget = new EmergencyWidget(null, null);

            angularPositionWidget.CurrentValue = 0.0;
            betaAngleWidget.CurrentValue = 0.0;
            angularSpeedWidget.CurrentValue = 0.0;
            batteryLevelWidget.Value = 0.0;
            linearSpeedWidget.CurrentValue = 0.0;
            torqueWidget.CurrentValue = 0.0;
            userPresenceWidget.Value = false;
            emergencyStopWidget.Value = false;

            AngularPositionInvalid = true;
            BetaAngleInvalid = true;
            AngularSpeedInvalid = true;
            BatteryLevelInvalid = true;
            LinearSpeedInvalid = true;
            TorqueInvalid = true;
            UserPresenceInvalid = true;
            EmergencyStopInvalid = true;

            angularPositionTimer.Elapsed += new System.Timers.ElapsedEventHandler(ElapsedEventHandler);
            betaAngleTimer.Elapsed += new System.Timers.ElapsedEventHandler(ElapsedEventHandler);
            angularSpeedTimer.Elapsed += new System.Timers.ElapsedEventHandler(ElapsedEventHandler);
            batteryLevelTimer.Elapsed += new System.Timers.ElapsedEventHandler(ElapsedEventHandler);
            linearSpeedTimer.Elapsed += new System.Timers.ElapsedEventHandler(ElapsedEventHandler);
            torqueTimer.Elapsed += new System.Timers.ElapsedEventHandler(ElapsedEventHandler);
            userPresenceTimer.Elapsed += new System.Timers.ElapsedEventHandler(ElapsedEventHandler);
            emergencyStopTimer.Elapsed += new System.Timers.ElapsedEventHandler(ElapsedEventHandler);

            angularPositionTimer.Interval = TIMEOUT;
            betaAngleTimer.Interval = TIMEOUT;
            angularSpeedTimer.Interval = TIMEOUT;
            batteryLevelTimer.Interval = TIMEOUT;
            linearSpeedTimer.Interval = TIMEOUT;
            torqueTimer.Interval = TIMEOUT;
            userPresenceTimer.Interval = TIMEOUT;
            emergencyStopTimer.Interval = TIMEOUT;
        }

        public void InvalidateAll()
        {
            angularPositionTimer.Stop();
            betaAngleTimer.Stop();
            angularSpeedTimer.Stop();
            batteryLevelTimer.Stop();
            linearSpeedTimer.Stop();
            torqueTimer.Stop();
            userPresenceTimer.Stop();
            emergencyStopTimer.Stop();

            AngularPositionInvalid = true;
            BetaAngleInvalid = true;
            AngularSpeedInvalid = true;
            BatteryLevelInvalid = true;
            LinearSpeedInvalid = true;
            TorqueInvalid = true;
            UserPresenceInvalid = true;
            EmergencyStopInvalid = true;
        }

        private void ElapsedEventHandler(object sender, System.Timers.ElapsedEventArgs e)
        {
            System.Timers.Timer timer = (System.Timers.Timer)sender;

            if (timer == angularPositionTimer){
                AngularPositionInvalid = true;
                angularPositionTimer.Stop();
            }
            else if (timer == betaAngleTimer){
                betaAngleTimer.Stop();
                BetaAngleInvalid = true;
            }
            else if (timer == angularSpeedTimer){
                angularSpeedTimer.Stop();
                AngularSpeedInvalid = true;
            }
            else if (timer == batteryLevelTimer){
                batteryLevelTimer.Stop();
                BatteryLevelInvalid = true;
            }
            else if (timer == linearSpeedTimer){
                linearSpeedTimer.Stop();
                LinearSpeedInvalid = true;
            }
            else if (timer == torqueTimer){
                torqueTimer.Stop();
                TorqueInvalid = true;
            }
            else if (timer == userPresenceTimer){
                userPresenceTimer.Stop();
                UserPresenceInvalid = true;
            }
            else if (timer == emergencyStopTimer){
                emergencyStopTimer.Stop();
                EmergencyStopInvalid = true;
            }
            else {
                Console.WriteLine("Invalid timer expired");
            }
        }
    }
}
