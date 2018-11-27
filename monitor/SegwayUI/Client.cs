//
//  Client.cs
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
using System.Net.Sockets;
using System.Text;

using System.Threading;
            
namespace SegwayUI
{
    /// <summary>
    /// Static class for TCP client
    /// </summary>
    public static class Client
    {
        /// <summary>
        /// Default server name
        /// </summary>
        public const string defaultIP = "10.105.0.64";
        //public const string defaultIP = "localhost";

        /// <summary>
        /// Default server port number
        /// </summary>
        public const int defaultPort = 2345;

        /// <summary>
        /// Tcp client object
        /// </summary>
        private static TcpClient client = null;

        /// <summary>
        /// Stream object used for communication
        /// </summary>
        private static NetworkStream stream = null;

        /// <summary>
        /// buffer containing received message from TCP server
        /// Used to concatenate internal buffers into one
        /// </summary>
        private static byte[] receiveBuffer;

        /// <summary>
        /// String containing received message from tcp server
        /// </summary>
        private static StringBuilder message = new StringBuilder();
      

        /// <summary>
        /// Callback to send received message to upper level
        /// </summary>
        public delegate void ReadEvent(string msg, byte[] buffer);
        public static ReadEvent readEvent = null;


        private static Thread readThread;

        /// <summary>
        /// Open connection to server "host", on default port number.
        /// </summary>
        /// <returns>true if connection succeded, false otherwise</returns>
        /// <param name="host">Hostname to connect to</param>
        public static bool Open(string host)
        {
            return Client.Open(host, defaultPort);
        }

        /// <summary>
        /// Open connection to server "host", with port number "port"
        /// </summary>
        /// <returns>true if connection succeded, false otherwise</returns>
        /// <param name="host">Hostname to connect to</param>
        /// <param name="port">Port number for connection</param>
        public static bool Open(string host, int port)
        {
            bool status = true;

            try
            {
                client = new TcpClient(host, port);

                stream = client.GetStream();

                // Start reading tcp stream and call "ReadCallback" method when newLength data
                // will be received
                // initially, "newLength" is equal to 1, so first call to ReadCallback
                // will be done after reception of 1 byte.

                // received data are stored in buffer
                // Next reading will be done in ReadCallback method

                //stream.BeginRead(buffer, 0, newLength, new AsyncCallback(ReadCallback), message);

                // Start reading thread
                message.Clear();
                readThread = new Thread(new ThreadStart(ReadCallback));
                readThread.Start();
            }
            catch (ArgumentNullException e)
            {
                Console.WriteLine("ArgumentNullException: " + e);
                status = false;
            }
            catch (SocketException e)
            {
                Console.WriteLine("SocketException: " + e.ToString());
                status = false;
            }
            catch (Exception e)
            {
                Console.WriteLine("Unknown Exception: " + e.ToString());
                status = false;
            }

            return status;
        }

        /// <summary>
        /// Close connection to server
        /// </summary>
        public static void Close()
        {
            if (stream != null) stream.Close();
            if (client != null) client.Close();
        }

        /// <summary>
        /// Callback call by stream.BeginRead after reception of newLength data
        /// </summary>
        /// <param name="ar">Not sure of what is it, but needed for terminate reading</param>
        private static void ReadCallback()
        {
            char character;
            int data;

            while (client.Connected)
            {
                try
                {
                    data = stream.ReadByte();
                }
                catch (ObjectDisposedException e)
                {
                    Console.WriteLine("Connection to server dropped: " + e.ToString());
                    return;
                }
                catch (System.IO.IOException e)
                {
                    Console.WriteLine("Connection to server dropped: " + e.ToString());
                    return;
                }

                if (data>=0) // a data was read
                {
                    character = (char)data;

                    if (character != '\n')
                    {
                        message.Append(character); 

                        if (receiveBuffer == null) receiveBuffer = new byte[1];
                        else Array.Resize<byte>(ref receiveBuffer, receiveBuffer.Length + 1); // resize currrent buffer

                        receiveBuffer[receiveBuffer.Length - 1] = (byte)data;
                    }
                    else // end of string found
                    {
                        readEvent?.Invoke(message.ToString(), receiveBuffer);

                        message.Clear();
                        receiveBuffer = null;
                    }
                }
            }
        }

        /// <summary>
        /// Write a string to server
        /// </summary>
        /// <returns>Nothing</returns>
        /// <param name="mes">Message to send to server</param>
        public static void Write(string mes)
        {
            if (client.Connected)
            {
                byte[] writeBuffer = Encoding.UTF8.GetBytes(mes);

                stream.Write(writeBuffer, 0, mes.Length);
            }
        }
    }
}
