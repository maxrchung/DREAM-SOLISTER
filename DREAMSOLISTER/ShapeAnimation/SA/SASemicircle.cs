using System.Windows;
using System.Windows.Media;
using System.Runtime.Serialization;

namespace ShapeAnimation {
    [DataContract]
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

        public SASemicircle(Vector position, Angle rotation, Vector scaleVector, Color color)
            : base(position, rotation, scaleVector, color) {
            type = SAShapeType.Semicircle;
        }

        public SASemicircle()
            : base() {
            type = SAShapeType.Semicircle;
        }

        public override SAShape copy() {
            return new SASemicircle(position, rotation, scaleVector, color);
        }
    }
}
