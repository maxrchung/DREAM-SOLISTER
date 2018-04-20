using System.Numerics;
using System.Windows.Media;
using System.Windows;

namespace ShapeAnimation {
    class SASemicircle : SAShape {
        public Rect clip {
            get {
                var boundaries = new Size(size.X, size.Y / 2.0f);
                return new Rect(boundaries);
            }
        }

        public SAVector2 translation {
            get {
                return new SAVector2(new Vector2(position.X - size.X / 2, position.Y - size.Y / 4));
            }
        }

        public SASemicircle(Vector2 position, Angle rotation, Vector2 scaleVector, float fade, Color color)
            : base(position, rotation, scaleVector, fade, color) { }

        public SASemicircle()
            : base(new Vector2(), Angle.createDefaultAngle(), new Vector2(1.0f), 1.0f, Colors.Black) { }
    }
}
