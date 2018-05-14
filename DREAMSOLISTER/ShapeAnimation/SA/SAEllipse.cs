using System.Runtime.Serialization;
using System.Windows.Media;

namespace ShapeAnimation {
    [DataContract]
    class SAEllipse : SAShape {
        public SAEllipse(Vector position, Angle rotation, Vector scaleVector, Color color)
            : base(position, rotation, scaleVector, color) {
            type = SAShapeType.Ellipse;
        }

        public SAEllipse()
            : base() {
            type = SAShapeType.Ellipse;
        }

        public override SAShape copy() {
            return new SAEllipse(position, rotation, scaleVector, color);
        }
    }
}
