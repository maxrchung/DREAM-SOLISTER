using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShapeAnimation {
    public struct Angle {
        public const float PI = 3.1416f;

        private float _degree;
        public float degree {
            get { return _degree; }
            set {
                _degree = value;
                _radian = convertDegreeToRadian(value);
            }
        }
        private float _radian;
        public float radian {
            get { return _radian; }
            set {
                _radian = value;
                _degree = convertRadianToDegree(value);
            }
        }

        public static Angle createDefaultAngle() {
            var angle = new Angle {
                degree = 0
            };
            return angle;
        }

        public static Angle createFromDegree(float pDegree) {
            var angle = new Angle {
                degree = pDegree
            };
            return angle;
        }

        public static Angle createFromRadian(float pRadian) {
            var angle = new Angle {
                radian = pRadian
            };
            return angle;
        }

        public static float convertDegreeToRadian(float degree) {
            return degree * PI / 180.0f;
        }

        public static float convertRadianToDegree(float radian) {
            return radian * 180.0f / PI;
        }
    }
}
