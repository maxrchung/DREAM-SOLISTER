using System.Windows.Media;
using System.Windows;

namespace ShapeAnimation {
    class SASemicircle : SAShape {
        public Rect clip {
            get {
                var boundaries = new Size(size.x, size.y);
                return new Rect(boundaries);
            }
        }

        public float doubleHeight {
            get {
                return size.y * 2;
            }
        }

        public SASemicircle(Vector position, Angle rotation, Vector scaleVector, float fade, Color color)
            : base(position, rotation, scaleVector, fade, color) {
            type = SAShapeType.Semicircle;
        }

        public SASemicircle()
            : base() {
            type = SAShapeType.Semicircle;
        }

        public override SAShape copy() {
            return new SASemicircle(position, rotation, scaleVector, fade, color);
        }
    }
}
