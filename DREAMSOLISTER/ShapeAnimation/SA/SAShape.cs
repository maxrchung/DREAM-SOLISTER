using System.Windows.Media;
using System.Windows;
using System.Collections.Generic;
using System;

namespace ShapeAnimation {
    public class SAShape {
        public const float fixedSize = 100.0f;

        public Angle rotation { get; set; }
        public Vector scaleVector { get; set; }                        
        public float fade { get; set; }

        public Color color { get; set; }
        public Brush brush {
            get {
                return new SolidColorBrush(color);
            }
        }

        public Vector position { get; set; }

        public Vector size {
            get {
                return scaleVector * fixedSize;
            }
        }

        public Vector translation {
            get {
                return new Vector(position.x - size.x / 2, position.y - size.y / 2);
            }
        }

        public List<Vector> corners {
            get {
                var width = Application.Current.FindResource("cornerWidth");
                var radius = Convert.ToSingle(width) / 2;
                var half = size / 2;
                return new List<Vector> {
                    new Vector(position.x - half.x - radius, position.y - half.y - radius),
                    new Vector(position.x - half.x - radius, position.y + half.y - radius),
                    new Vector(position.x + half.x - radius, position.y - half.y - radius),
                    new Vector(position.x + half.x - radius, position.y + half.y - radius),
                };
            }
        }

        public SAShape(Vector pPosition, Angle pRotation, Vector pScaleVector, float pFade, Color pColor) {
            position = pPosition;
            rotation = pRotation;
            scaleVector = pScaleVector;
            fade = pFade;
            color = pColor;
        }

        public SAShape() {
            position = new Vector();
            rotation = Angle.createDefaultAngle();
            scaleVector = new Vector(1.0f);
            fade = 1.0f;
            color = Colors.Black;
        }
    }
}
