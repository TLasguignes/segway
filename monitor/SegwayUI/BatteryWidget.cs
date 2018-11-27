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
    public class BatteryWidget
    {
        private Gtk.Image imageWidget;
        private Gtk.Label labelWidget;

        private List<Pixbuf> icons;

        private const int BATTERY_100 = 0;
        private const int BATTERY_75 = 1;
        private const int BATTERY_50 = 2;
        private const int BATTERY_25 = 3;
        private const int BATTERY_0 = 4;
        private const int BATTERY_INVALID = 5;

        private double value;
        public double Value
        {
            get
            {
                return value;
            }

            set
            {
                this.value = value;
                if (this.value > 100.0) this.value = 100.0;
                if (this.value < 0.0) this.value = 0.0;

                Gtk.Application.Invoke(delegate {
                    UpdateDisplay();
                });
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

                Gtk.Application.Invoke(delegate {
                    UpdateDisplay();
                });
            }
        }

        private void LoadRessources()
        {
            this.icons = new List<Pixbuf>();

            Pixbuf image = Pixbuf.LoadFromResource("SegwayUI.ressources.battery100.png");
            icons.Add(image);

            image = Pixbuf.LoadFromResource("SegwayUI.ressources.battery75.png");
            icons.Add(image);

            image = Pixbuf.LoadFromResource("SegwayUI.ressources.battery50.png");
            icons.Add(image);

            image = Pixbuf.LoadFromResource("SegwayUI.ressources.battery25.png");
            icons.Add(image);

            image = Pixbuf.LoadFromResource("SegwayUI.ressources.battery0.png");
            icons.Add(image);

            image = Pixbuf.LoadFromResource("SegwayUI.ressources.batteryInvalid.png");
            icons.Add(image);
        }

        private void UpdateDisplay()
        {
            int val = (int)this.value;

            if ((imageWidget != null) && (labelWidget != null))
            {
                if (invalid == true)
                {
                    labelWidget.Text = "No information";
                    imageWidget.Pixbuf = icons[BATTERY_INVALID];
                }
                else
                {
                    labelWidget.Text = Convert.ToString(this.value) + "%";

                    if (val > 87) imageWidget.Pixbuf = icons[BATTERY_100];
                    else if (val > 62) imageWidget.Pixbuf = icons[BATTERY_75];
                    else if (val > 37) imageWidget.Pixbuf = icons[BATTERY_50];
                    else if (val > 12) imageWidget.Pixbuf = icons[BATTERY_25];
                    else imageWidget.Pixbuf = icons[BATTERY_0];
                }
            }
        }

        public BatteryWidget(Gtk.Image imageWidget, Gtk.Label labelWidget)
        {
            this.imageWidget = imageWidget;
            this.labelWidget = labelWidget;

            LoadRessources();
        }
    }
}
