using System.Windows.Media;
using System.Windows;

namespace ShapeAnimation {
    class SATriangle : SAShape {
        public PointCollection points {
            get {
                var half = size / 2;
                var collection = new PointCollection() {
                    new Point(position.x - half.x, position.y + half.y),
                    new Point(position.x, position.y - half.y),
                    new Point(position.x + half.x, position.y + half.y)
                };
                return collection;
            }
        }

        public SATriangle(Vector position, Angle rotation, Vector scaleVector, float fade, Color color)
            : base(position, rotation, scaleVector, fade, color) { }

        public SATriangle()
            : base() { }
    }
}
