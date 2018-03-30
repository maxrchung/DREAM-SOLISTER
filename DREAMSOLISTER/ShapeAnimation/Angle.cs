using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShapeAnimation {
    struct Angle {
        public const float PI = 3.1416f;

        public float degree {
            get { return degree; }
            set {
                degree = value;
                radian = convertDegreeToRadian(value);
            }
        }
        public float radian {
            get { return radian; }
            set {
                radian = value;
                degree = convertRadianToDegree(value);
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
