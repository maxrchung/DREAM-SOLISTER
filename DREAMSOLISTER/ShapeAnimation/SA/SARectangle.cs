using System.Numerics;
using System.Windows.Media;
using System.Windows;

namespace ShapeAnimation {
    public class SARectangle : SAShape {
        public PointCollection points {
            get {
                var half = size / 2;
                var collection = new PointCollection() {
                    new Point(position.X - half.X, position.Y - half.Y),
                    new Point(position.X + half.X, position.Y - half.Y),
                    new Point(position.X + half.X, position.Y + half.Y),
                    new Point(position.X - half.X, position.Y + half.Y),
                };
                return collection;
            }
        }

        public SARectangle(Vector2 position, Angle rotation, Vector2 scaleVector, float fade, Color color)
            : base(position, rotation, scaleVector, fade, color) {}

        public SARectangle()
            : base(new Vector2(), Angle.createDefaultAngle(), new Vector2(1.0f), 1.0f, Colors.Black) {}
    }
}
