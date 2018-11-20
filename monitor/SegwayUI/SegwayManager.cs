//
//  DestijlCommandManager.cs
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

namespace SegwayUI
{
    /// <summary>
    /// Commands used for robot messages
    /// </summary>
    public static class SegwayCommandList
    {
        public const string AngularPosition = "AngularPosition";
        public const string AngularSpeed = "AngularSpeed";
        public const string BatteryLevel = "Battery";
        public const string LinearSpeed = "LinearSpeed";
        public const string UserPresence = "User";
        public const string BetaAngle = "Beta";
        public const string Torque = "Torque";
        public const string EmergencyStop = "Emergency";
    }

    /// <summary>
    /// Specialization class for command manager, which implemnent destijl protocol between monitor and server
    /// </summary>
    public class SegwayCommandManager
    {
        /// <summary>
        /// Command Manager object
        /// </summary>
        private CommandManager commandManager = null;

        /// <summary>
        /// Part of received message corresponding to command header
        /// </summary>
        private string receivedHeader = null;

        /// <summary>
        /// Part of received message corresponding to command data
        /// </summary>
        private string receivedData = null;

        /// <summary>
        /// Callback for sending received data to application level
        /// </summary>
        public delegate void CommandReceivedEvent(string header, string data, byte[] buffer);
        public CommandReceivedEvent commandReceivedEvent = null;

        /// <summary>
        /// Timeout used for command with acknowledge
        /// </summary>
        public double timeout = 1000;

        /// <summary>
        /// List of available return status
        /// </summary>
        public enum CommandStatus
        {
            Success,
            Rejected,
            InvalidAnswer,
            Busy,
            CommunicationLostWithRobot,
            CommunicationLostWithServer
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SegwayCommandManager"/> class.
        /// </summary>
        /// <param name="callback">Callback reference for reception of data</param>
        public SegwayCommandManager(CommandReceivedEvent callback)
        {
            commandManager = new CommandManager(OnCommandReceived);
            this.commandReceivedEvent += callback;
        }

        /// <summary>
        /// Releases unmanaged resources and performs other cleanup operations before the
        /// <see cref="SegwayCommandManager"/> is reclaimed by garbage collection.
        /// </summary>
        ~SegwayCommandManager()
        {
            if (commandManager != null) commandManager.Close();
        }

        /// <summary>
        /// Callback used for receiving data from lower layer (CommandManager class)
        /// </summary>
        /// <param name="msg">String containing received message</param>
        /// <param name="buffer">Raw buffer to be used when data are not in ascii format (image for example)</param>
        private void OnCommandReceived(string msg, byte[] buffer)
        {
            // Firstly, split message in (at least) two part : header, and data
            string[] msgs = msg.Split('=');

            // If it exist at least on element in string array, it should be command header
            if (msgs.Length >= 1) receivedHeader = msgs[0];
            else receivedHeader = null;

            // if msgs array contains at least two elements, second element is normally data
            if (msgs.Length >= 2) receivedData = msgs[1];
            else receivedData = null;

            // when split is done, provide data to application
            this.commandReceivedEvent?.Invoke(receivedHeader, receivedData, buffer);
        }

        /// <summary>
        /// Open the specified hostname server, using default port number.
        /// </summary>
        /// <returns>true if connection succeded, false otherwise</returns>
        /// <param name="hostname">Hostname to connect to</param>
        public bool Open(string hostname)
        {
            return this.Open(hostname, Client.defaultPort);
        }

        /// <summary>
        /// Open connection to server "host", with port number "port"
        /// </summary>
        /// <returns>true if connection succeded, false otherwise</returns>
        /// <param name="hostname">Hostname to connect to</param>
        /// <param name="port">Port number for connection</param>
        public bool Open(string hostname, int port)
        {
            if (commandManager != null) return commandManager.Open(hostname, port);
            else return false;
        }

        /// <summary>
        /// Close connection to server
        /// </summary>
        public void Close()
        {
            if (commandManager != null) commandManager.Close();
        }
    }
}
