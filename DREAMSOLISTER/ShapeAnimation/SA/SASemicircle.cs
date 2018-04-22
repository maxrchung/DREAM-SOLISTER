using System.Numerics;
using System.Windows.Media;
using System.Windows;

namespace ShapeAnimation {
    class SASemicircle : SAShape {
        public Rect clip {
            get {
                var boundaries = new Size(size.X, size.Y);
                return new Rect(boundaries);
            }
        }

        public float doubleHeight {
            get {
                return size.Y * 2;
            }
        }

        public SASemicircle(Vector2 position, Angle rotation, Vector2 scaleVector, float fade, Color color)
            : base(position, rotation, scaleVector, fade, color) { }

        public SASemicircle()
            : base(new Vector2(), Angle.createDefaultAngle(), new Vector2(1.0f), 1.0f, Colors.Black) { }
    }
}
