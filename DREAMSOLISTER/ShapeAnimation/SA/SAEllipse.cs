using System.Windows.Media;

namespace ShapeAnimation {
    class SAEllipse : SAShape {
        public SAEllipse(Vector position, Angle rotation, Vector scaleVector, float fade, Color color)
            : base(position, rotation, scaleVector, fade, color) {}

        public SAEllipse()
            : base() {}
    }
}
