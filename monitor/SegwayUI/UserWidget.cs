//
//  AngleUI.cs
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
using System.Collections.Generic;
using Gtk;
using Gdk;

namespace SegwayUI
{
    public class UserWidget
    {
        private Gtk.Image imageWidget;
        private Gtk.Label labelWidget;

        private List<Pixbuf> icons;

        private const int USER_PRESENT = 0;
        private const int USER_NOT_PRESENT = 1;
        private const int USER_INVALID = 2;

        private bool value;
        public bool Value
        {
            get
            {
                return value;
            }

            set
            {
                this.value = value;

                UpdateDisplay();
            }
        }

        private bool invalid;
        public bool Invalid
        {
            get
            {
                return invalid;
            }

            set
            {
                invalid = value;

                UpdateDisplay();
            }
        }

        private void LoadRessources()
        {
            this.icons = new List<Pixbuf>();

            Pixbuf image = Pixbuf.LoadFromResource("SegwayUI.ressources.userPresent.png");
            icons.Add(image);

            image = Pixbuf.LoadFromResource("SegwayUI.ressources.userNotPresent.png");
            icons.Add(image);

            image = Pixbuf.LoadFromResource("SegwayUI.ressources.userNotPresent.png");
            icons.Add(image);
        }

        private void UpdateDisplay()
        {
            if ((imageWidget != null) && (labelWidget != null))
            {
                if (invalid == true)
                {
                    labelWidget.Text = "No information";
                    imageWidget.Pixbuf = icons[USER_INVALID];
                }
                else
                {
                    if (value)
                    {
                        labelWidget.Text = "Present";
                        imageWidget.Pixbuf = icons[USER_PRESENT];
                    }
                    else
                    {
                        labelWidget.Text = "Not present";
                        imageWidget.Pixbuf = icons[USER_NOT_PRESENT];
                    }
                }
            }
        }

        public UserWidget(Gtk.Image imageWidget, Gtk.Label labelWidget)
        {
            this.imageWidget = imageWidget;
            this.labelWidget = labelWidget;

            LoadRessources();
        }
    }
}
