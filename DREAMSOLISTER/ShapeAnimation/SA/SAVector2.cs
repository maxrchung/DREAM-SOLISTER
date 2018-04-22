using System.Numerics;

namespace ShapeAnimation {
    public class SAVector2 {
        public Vector2 wrapped;
        public float X {
            get {
                return wrapped.X;
            }
        }
        public float Y {
            get {
                return wrapped.Y;
            }
        }

        public SAVector2(Vector2 pWrapped) {
            wrapped = pWrapped;
        }
    }
}
