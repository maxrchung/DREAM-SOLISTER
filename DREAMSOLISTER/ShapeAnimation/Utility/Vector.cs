using System;
using System.Windows;

namespace ShapeAnimation {
    public class Vector {
        public float x { get; set; }
        public float y { get; set; }

        public static readonly Vector zero = new Vector();
        public static readonly Vector unit = new Vector(1, 0);

        public static Vector operator +(Vector left, Vector right) {
            return new Vector(left.x + right.x, left.y + right.y);
        }

        public static Vector operator -(Vector left, Vector right) {
            return new Vector(left.x - right.x, left.y - right.y);
        }

        public static Vector operator *(Vector left, float right) {
            return new Vector(left.x * right, left.y * right);
        }

        public static Vector operator *(float left, Vector right) {
            return new Vector(left * right.x, left * right.y);
        }

        public static Vector operator /(Vector left, float right) {
            return new Vector(left.x / right, left.y / right);
        }

        public static Vector operator /(float left, Vector right) {
            return new Vector(left / right.x, left / right.y);
        }

        public Vector() {
            x = 0;
            y = 0;
        }

        public Vector(float value) {
            x = value;
            y = value;
        }

        public Vector(float pX, float pY) {
            x = pX;
            y = pY;
        }

        public float lengthSquared() {
            return x * x + y * y;
        }

        public float length() {
            return (float)Math.Sqrt(lengthSquared());
        }

        public Vector copy() {
            return new Vector(x, y);
        }

        public Point toPoint() {
            return new Point(x, y);
        }

        public Vector rotate(float rotation) {
            var rotatedX = x * Math.Cos(rotation) - y * Math.Sin(rotation);
            var rotatedY = x * Math.Sin(rotation) + y * Math.Cos(rotation);
            var rotated = new Vector((float)rotatedX, (float)rotatedY);
            return rotated;
        }

        public Vector rotate(float rotation, Vector rotateFrom) {
            var repositioned = this - rotateFrom;
            var rotated = repositioned.rotate(rotation);
            var positioned = rotated + rotateFrom;
            return positioned;
        }
    }
}
