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
using Gtk;
using Gdk;
using Pango;
using Cairo;

namespace SegwayUI
{
    public class JaugeWidget
    {
        private Cairo.Color sensitiveFillColor = new Cairo.Color(0.8, 0.8, 0.8);
        private Cairo.Color sensitiveBorderColor = new Cairo.Color(0.5, 0.5, 0.5);
        private Cairo.Color sensitiveFontColor = new Cairo.Color(0.5, 0.5, 0.5);

        private DrawingArea drawingWidget;
        private double minValue;

        public double MinValue
        {
            get
            {
                return minValue;
            }

            set
            {
                minValue = value;

                // Redraw the widget
                if (drawingWidget != null)
                {
                    Gtk.Application.Invoke(delegate {
                        drawingWidget.QueueDraw();
                    });
                }
            }
        }

        private double maxValue;

        public double MaxValue
        {
            get
            {
                return maxValue;
            }

            set
            {
                maxValue = value;

                // Redraw the widget
                if (drawingWidget != null)
                {
                    Gtk.Application.Invoke(delegate {
                        drawingWidget.QueueDraw();
                    });
                }
            }
        }

        private double currentValue;

        public double CurrentValue
        {
            get
            {
                return currentValue;
            }

            set
            {
                currentValue = value;

                if (currentValue > maxValue) currentValue = maxValue;
                if (currentValue < minValue) currentValue = minValue;

                // Redraw the widget
                if (drawingWidget != null)
                {
                    Gtk.Application.Invoke(delegate {
                        drawingWidget.QueueDraw();
                    });
                }
            }
        }

        private string title;

        public string Title
        {
            get
            {
                return title;
            }

            set
            {
                title = value;

                // Redraw the widget
                if (drawingWidget != null)
                {
                    Gtk.Application.Invoke(delegate {
                        drawingWidget.QueueDraw();
                    });
                }
            }
        }

        private Cairo.Color fillColor;

        public Cairo.Color FillColor
        {
            get
            {
                return fillColor;
            }

            set
            {
                fillColor = value;

                // Redraw the widget
                if (drawingWidget != null)
                {
                    Gtk.Application.Invoke(delegate {
                        drawingWidget.QueueDraw();
                    });
                }
            }
        }

        private Cairo.Color borderColor;

        public Cairo.Color BorderColor
        {
            get
            {
                return borderColor;
            }

            set
            {
                borderColor = value;

                // Redraw the widget
                if (drawingWidget != null)
                {
                    Gtk.Application.Invoke(delegate {
                        drawingWidget.QueueDraw();
                    });
                }
            }
        }

        private Cairo.Color fontColor;

        public Cairo.Color FontColor
        {
            get
            {
                return fontColor;
            }

            set
            {
                fontColor = value;

                // Redraw the widget
                if (drawingWidget != null)
                {
                    Gtk.Application.Invoke(delegate {
                        drawingWidget.QueueDraw();
                    });
                }
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

                // Redraw the widget
                if (drawingWidget != null)
                {
                    Gtk.Application.Invoke(delegate {
                        drawingWidget.QueueDraw();
                    });
                }
            }
        }

        public bool Sensitive
        {
            get
            {
                if (drawingWidget != null) return drawingWidget.Sensitive;
                else return false;
            }

            set
            {
                if (drawingWidget != null)
                {
                    drawingWidget.Sensitive = value;

                    Gtk.Application.Invoke(delegate {
                        drawingWidget.QueueDraw();
                    });
                }
            }
        }

        private bool jobInProgress = false;

        private void InitJaugeWidget(string title, double min, double max)
        {
            this.title = title;

            this.minValue = min;
            this.maxValue = max;
            this.currentValue = min;

            this.fillColor = new Cairo.Color(0.0, 0.0, 0.0);
            this.borderColor = new Cairo.Color(0.0, 0.0, 0.0);
            this.fontColor = new Cairo.Color(0.0, 0.0, 0.0);

            if (drawingWidget!=null)
                drawingWidget.ExposeEvent += new ExposeEventHandler(HandleExposeEventHandler);
        }

        public JaugeWidget(DrawingArea drawingArea)
        {
            drawingWidget = drawingArea;

            InitJaugeWidget("", 0.0, 100.0);
        }

        public JaugeWidget(DrawingArea drawingArea, string title)
        {
            drawingWidget = drawingArea;

            InitJaugeWidget(title, 0.0, 100.0);
        }

        public JaugeWidget(DrawingArea drawingArea, string title,
                      double min, double max)
        {
            drawingWidget = drawingArea;

            InitJaugeWidget(title, min, max);
        }

        private double DegreeToRadian(double degree)
        {
            return degree * (Math.PI / 180.0);
        }

        private double ValueToAngle(double value)
        {
            if (value == minValue) return -180.0;
            else
            {
                double val = (1 - ((value - minValue) / (maxValue - minValue))) * -180.0;

                return val;
            }
        }

        private void HandleExposeEventHandler(object o, ExposeEventArgs args)
        {
            jobInProgress = true;

            DrawingArea area = (DrawingArea)o;
            Cairo.Context cr = Gdk.CairoHelper.Create(area.GdkWindow);

            Cairo.Color localFillColor, localBorderColor, localFontColor, localStrikeoutColor;
            double val = currentValue;
            int width, height;

            if (Sensitive == false)
            {
                localFillColor = sensitiveFillColor;
                localBorderColor= sensitiveBorderColor;
                localFontColor= sensitiveFontColor;
                localStrikeoutColor= sensitiveBorderColor;
            }
            else
            {
                localFillColor = fillColor;
                localBorderColor = borderColor;
                localFontColor = fontColor;
                localStrikeoutColor = new Cairo.Color(0.85, 0, 0);
            }

            width = area.Allocation.Width;
            height = area.Allocation.Height;
            cr.SelectFontFace("Cantarell", FontSlant.Normal, FontWeight.Bold);
            cr.SetSourceColor(localFontColor);
            cr.SetFontSize(16);

            string text = title;
            TextExtents te = cr.TextExtents(text);
            cr.MoveTo((width - te.Width) / 2,
                      te.Height / 2 + 10);
            cr.ShowText(text);

            if (val < minValue) val = minValue;
            else if (val > maxValue) val = maxValue;

            if (invalid == true) val = minValue;

            //// Draw external border of widget
            //cr.LineWidth = 1;
            ////cr.SetSourceRGB(0.0, 0.0, 0.0);
            //cr.SetSourceColor(this.borderColor);

            //cr.Rectangle(new PointD(0, 0), width, height);
            cr.Stroke();

            int radius = (width < height ? width : height) / 2 - 10;
            cr.LineWidth = 2;

            cr.Translate(width / 2, (height / 2) + (height / 3));
            cr.Arc(0, 0, radius, DegreeToRadian(-180), DegreeToRadian(ValueToAngle(val)));
            cr.ArcNegative(0, 0, radius - 40, DegreeToRadian(ValueToAngle(val)), DegreeToRadian(-180));
            cr.ClosePath();

            //cr.SetSourceRGB(0.7, 0.2, 0.0);
            cr.SetSourceColor(localFillColor);
            cr.FillPreserve();

            //cr.SetSourceRGB(0, 0, 0);
            cr.SetSourceColor(localBorderColor);
            cr.Stroke();

            //cr.SetSourceRGB(0, 0, 0);
            cr.SetSourceColor(localBorderColor);
            cr.Arc(0, 0, radius, DegreeToRadian(ValueToAngle(val)), DegreeToRadian(0));
            cr.ArcNegative(0, 0, radius - 40, DegreeToRadian(0), DegreeToRadian(ValueToAngle(val)));
            cr.ClosePath();
            cr.Stroke();

            //cr.SetSourceRGB(0, 0, 0);
            cr.SetSourceColor(localFontColor);
            cr.SelectFontFace("Cantarell", FontSlant.Normal, FontWeight.Normal);
            text = currentValue.ToString("F2");
            te = cr.TextExtents(text);
            cr.MoveTo(-te.Width / 2,
                      te.Height / 2 - 5);
            cr.ShowText(text);

            cr.MoveTo(0, 0);
            text = minValue.ToString("F2");
            te = cr.TextExtents(text);
            cr.MoveTo(-te.Width - radius - 10,
                      te.Height / 2 - 5);
            cr.ShowText(text);

            cr.MoveTo(0, 0);
            text = maxValue.ToString("F2");
            te = cr.TextExtents(text);
            cr.MoveTo(+radius + 10,
                      te.Height / 2 - 5);
            cr.ShowText(text);

            cr.MoveTo(0, 0);
            text = ((maxValue + minValue) / 2).ToString("F2");
            te = cr.TextExtents(text);
            cr.MoveTo(-te.Width / 2,
                      -radius - te.Height - 5);
            cr.ShowText(text);

            if (this.invalid == true)
            {
                cr.Translate(-width / 2, -((height / 2) + (height / 3)));

                cr.MoveTo(new PointD(20, 20));
                cr.LineTo(new PointD(width - 20, height - 20));
                cr.LineWidth = 5;
                cr.SetSourceColor(localStrikeoutColor);
                cr.Stroke();
            }

            ((IDisposable)cr.GetTarget()).Dispose();
            ((IDisposable)cr).Dispose();

            jobInProgress = false;
        }
    }
}
