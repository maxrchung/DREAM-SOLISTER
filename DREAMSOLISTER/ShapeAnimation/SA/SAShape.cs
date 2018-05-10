using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.Serialization;
using System.Windows;
using System.Windows.Media;

namespace ShapeAnimation {
    [DataContract]
    [KnownType(typeof(SAEllipse))]
    [KnownType(typeof(SARectangle))]
    [KnownType(typeof(SASemicircle))]
    [KnownType(typeof(SATriangle))]
    public abstract class SAShape : INotifyPropertyChanged {
        public event PropertyChangedEventHandler PropertyChanged;
        protected void NotifyPropertyChanged(string name) {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }

        public const float fixedSize = 100.0f;

        public SAShapeType type { get; set; }

        public float fade { get; set; }

        [DataMember]
        private Color _color;
        public Color color {
            get {
                return _color;
            }
            set {
                _color = value;
                NotifyPropertyChanged("color");
                NotifyPropertyChanged("brush");
            }
        }
        public Brush brush {
            get {
                return new SolidColorBrush(color);
            }
        }

        private Vector _position;
        public Vector position {
            get {
                return _position;
            }
            set {
                _position = value;
                NotifyPropertyChanged("position");
                NotifyPropertyChanged("translation");
                NotifyPropertyChanged("points");
                NotifyPropertyChanged("rotateCorners");
                NotifyPropertyChanged("scaleCorners");
            }
        }
        private Angle _rotation;
        public Angle rotation {
            get {
                return _rotation;
            }
            set {
                _rotation = value;
                NotifyPropertyChanged("rotation");
                NotifyPropertyChanged("translation");
                NotifyPropertyChanged("points");
                NotifyPropertyChanged("rotateCorners");
                NotifyPropertyChanged("scaleCorners");
            }
        }
        private Vector _scaleVector;
        public Vector scaleVector {
            get {
                return _scaleVector;
            }
            set {
                _scaleVector = value;
                NotifyPropertyChanged("size");
                NotifyPropertyChanged("translation");
                NotifyPropertyChanged("points");
                NotifyPropertyChanged("rotateCorners");
                NotifyPropertyChanged("scaleCorners");
                NotifyPropertyChanged("doubleHeight");
                NotifyPropertyChanged("clip");
            }
        }

        public Vector size {
            get {
                return scaleVector * fixedSize;
            }
        }
        public Vector translation {
            get {
                return new Vector(position.x, position.y) - size / 2;
            }
        }
        public List<Vector> rotateCorners {
            get {
                var width = Application.Current.FindResource("rotateCornerWidth");
                // width is object so must use Convert.ToSingle
                var radius = new Vector(Convert.ToSingle(width) / 2);
                var half = size / 2;
                var v = new List<Vector> {
                    new Vector(position.x - half.x, position.y - half.y).rotateFrom(rotation.radian, position) - radius,
                    new Vector(position.x - half.x, position.y + half.y).rotateFrom(rotation.radian, position) - radius,
                    new Vector(position.x + half.x, position.y - half.y).rotateFrom(rotation.radian, position) - radius,
                    new Vector(position.x + half.x, position.y + half.y).rotateFrom(rotation.radian, position) - radius
                };
                return v;
            }
        }
        public List<Vector> scaleCorners {
            get {
                var width = Application.Current.FindResource("scaleCornerWidth");
                // width is object so must use Convert.ToSingle
                var radius = new Vector(Convert.ToSingle(width) / 2);
                var half = size / 2;
                var v = new List<Vector> {
                    new Vector(position.x - half.x, position.y - half.y).rotateFrom(rotation.radian, position) - radius,
                    new Vector(position.x - half.x, position.y + half.y).rotateFrom(rotation.radian, position) - radius,
                    new Vector(position.x + half.x, position.y - half.y).rotateFrom(rotation.radian, position) - radius,
                    new Vector(position.x + half.x, position.y + half.y).rotateFrom(rotation.radian, position) - radius
                };
                return v;
            }
        }

        public SAShape(Vector pPosition, Angle pRotation, Vector pScaleVector, float pFade, Color pColor) {
            position = pPosition;
            rotation = pRotation;
            scaleVector = pScaleVector;
            fade = pFade;
            color = pColor;
        }

        public SAShape() {
            position = new Vector();
            rotation = Angle.fromDefault();
            scaleVector = new Vector(1.0f);
            fade = 1.0f;
            color = Colors.Black;
        }

        abstract public SAShape copy();
    }
}
