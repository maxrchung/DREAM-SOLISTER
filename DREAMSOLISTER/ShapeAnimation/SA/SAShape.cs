using System.Numerics;
using System.Windows.Media;
using System.Windows;
using System.Collections.Generic;
using System;

namespace ShapeAnimation {
    public class SAShape {
        public const float fixedSize = 100.0f;

        public Angle rotation { get; set; }
        public Vector2 scaleVector { get; set; }                        
        public float fade { get; set; }

        public Color color { get; set; }
        public Brush Color {
            get {
                return new SolidColorBrush(color);
            }
        }

        public Vector2 position { get; set; }
        public SAVector2 Position {
            get {
                return new SAVector2(position);
            }
        }

        public Vector2 size {
            get {
                return scaleVector * fixedSize;
            }
        }
        public SAVector2 Size {
            get {
                return new SAVector2(size);
            }
        }

        public SAVector2 translation {
            get {
                return new SAVector2(new Vector2(position.X - size.X / 2, position.Y - size.Y / 2));
            }
        }

        public List<SAVector2> corners {
            get {
                var width = Application.Current.FindResource("cornerWidth");
                var radius = Convert.ToSingle(width) / 2;
                var half = size / 2;
                return new List<SAVector2> {
                    new SAVector2(new Vector2(position.X - half.X - radius, position.Y - half.Y - radius)),
                    new SAVector2(new Vector2(position.X - half.X - radius, position.Y + half.Y - radius)),
                    new SAVector2(new Vector2(position.X + half.X - radius, position.Y - half.Y - radius)),
                    new SAVector2(new Vector2(position.X + half.X - radius, position.Y + half.Y - radius)),
                };
            }
        }

        public SAShape(Vector2 pPosition, Angle pRotation, Vector2 pScaleVector, float pFade, Color pColor) {
            position = pPosition;
            rotation = pRotation;
            scaleVector = pScaleVector;
            fade = pFade;
            color = pColor;
        }
    }
}
