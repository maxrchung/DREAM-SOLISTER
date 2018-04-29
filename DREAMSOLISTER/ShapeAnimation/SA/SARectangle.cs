﻿using System.Windows.Media;
using System.Windows;

namespace ShapeAnimation {
    public class SARectangle : SAShape {
        public PointCollection points {
            get {
                var half = size / 2;
                var collection = new PointCollection() {
                    new Vector(position.x - half.x, position.y - half.y).rotateFrom(rotation.radian, position).toPoint(),
                    new Vector(position.x + half.x, position.y - half.y).rotateFrom(rotation.radian, position).toPoint(),
                    new Vector(position.x + half.x, position.y + half.y).rotateFrom(rotation.radian, position).toPoint(),
                    new Vector(position.x - half.x, position.y + half.y).rotateFrom(rotation.radian, position).toPoint(),
                };
                return collection;
            }
        }

        public SARectangle(Vector position, Angle rotation, Vector scaleVector, float fade, Color color)
            : base(position, rotation, scaleVector, fade, color) {}

        public SARectangle()
            : base() {}
    }
}