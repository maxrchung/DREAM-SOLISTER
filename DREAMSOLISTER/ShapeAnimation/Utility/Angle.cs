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
        
        public static Angle operator +(Angle left, Angle right) {
            return fromRadian(left.radian + right.radian);
        }
        public static Angle operator -(Angle left, Angle right) {
            return fromRadian(left.radian - right.radian);
        }

        public static Angle fromDefault() {
            var angle = new Angle {
                degree = 0
            };
            return angle;
        }
        public static Angle fromDegree(float pDegree) {
            var angle = new Angle {
                degree = pDegree
            };
            return angle;
        }
        public static Angle fromRadian(float pRadian) {
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
