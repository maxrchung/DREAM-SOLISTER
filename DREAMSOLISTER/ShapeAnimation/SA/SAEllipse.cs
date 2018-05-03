using System.Windows.Media;

namespace ShapeAnimation {
    class SAEllipse : SAShape {
        public SAEllipse(Vector position, Angle rotation, Vector scaleVector, float fade, Color color)
            : base(position, rotation, scaleVector, fade, color) {
            type = SAShapeType.Ellipse;
        }

        public SAEllipse()
            : base() {
            type = SAShapeType.Ellipse;
        }

        public override SAShape copy() {
            return new SAEllipse(position, rotation, scaleVector, fade, color);
        }
    }
}
