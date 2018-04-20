using System.Numerics;
using System.Windows.Media;

namespace ShapeAnimation {
    public class SAShape {
        public const float fixedSize = 100.0f;

        public Angle rotation { get; set; }
        public Vector2 scaleVector { get; set; }                        
        public float fade { get; set; }

        public Color color { get; set; }
        public Brush Color {
            get {
                return new SolidColorBrush(color);
            }
        }

        public Vector2 position { get; set; }
        public SAVector2 Position {
            get {
                return new SAVector2(position);
            }
        }

        public Vector2 size {
            get {
                return scaleVector * fixedSize;
            }
        }
        public SAVector2 Size {
            get {
                return new SAVector2(size);
            }
        }

        public SAShape(Vector2 pPosition, Angle pRotation, Vector2 pScaleVector, float pFade, Color pColor) {
            position = pPosition;
            rotation = pRotation;
            scaleVector = pScaleVector;
            fade = pFade;
            color = pColor;
        }
    }
}
