//
//  MessageLog.cs
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
    public partial class MessageLog : Gtk.Dialog
    {
        public MessageLog()
        {
            this.Build();
        }

        protected void OnButtonOkClicked(object sender, EventArgs e)
        {
            this.Hide();
        }

        protected void OnClose(object sender, EventArgs e)
        {   
            this.Hide();

        }

        protected void OnDeleteEvent(object o, Gtk.DeleteEventArgs args)
        {
            this.Hide();
            args.RetVal = true;
        }

        public void Add (string s)
        {
            textviewMessageLog.Buffer.InsertAtCursor(s);
        }

        public void Clear()
        {
            textviewMessageLog.Buffer.Clear();            
        }
    }
}
