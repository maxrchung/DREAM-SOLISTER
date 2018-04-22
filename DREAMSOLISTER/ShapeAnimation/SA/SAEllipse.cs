using System.Numerics;
using System.Windows;
using System.Windows.Media;

namespace ShapeAnimation {
    class SAEllipse : SAShape {
        private Point origin {
            get {
                return new Point(size.X / 2, size.Y / 2);
            }
        }
        public Point Origin {
            get {
                return origin;
            }
        }

        public SAEllipse(Vector2 position, Angle rotation, Vector2 scaleVector, float fade, Color color)
            : base(position, rotation, scaleVector, fade, color) {}

        public SAEllipse()
            : base(new Vector2(), Angle.createDefaultAngle(), new Vector2(1.0f), 1.0f, Colors.Black) {}
    }
}
