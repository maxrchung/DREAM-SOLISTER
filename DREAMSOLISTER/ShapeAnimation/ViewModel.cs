using System.Collections.ObjectModel;
using System.ComponentModel;

namespace ShapeAnimation {
    public class ViewModel : INotifyPropertyChanged {
        public event PropertyChangedEventHandler PropertyChanged;
        protected void NotifyPropertyChanged(string name) {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }

        public ObservableCollection<SAShape> shapes { get; set; }
        private SAShape _selected;
        public SAShape selected {
            get {
                return _selected;
            }
            set {
                _selected = value;
                NotifyPropertyChanged("selected");
            }
        }

        public ViewModel() {
            shapes = new ObservableCollection<SAShape>();
            var rectangle = new SARectangle() {
                position = new Vector(100, 100),
                rotation = Angle.fromRadian(1.0f),
                scaleVector = new Vector(1, 2)
            };
            shapes.Add(rectangle);

            var ellipse = new SAEllipse() {
                position = new Vector(100, 100),
                rotation = Angle.fromRadian(1.0f),
                scaleVector = new Vector(2, 1)
            };
            shapes.Add(ellipse);

            var semicircle = new SASemicircle() {
                position = new Vector(100, 100),
                rotation = Angle.fromRadian(1.0f),
                scaleVector = new Vector(1, 2)
            };
            shapes.Add(semicircle);

            var triangle = new SATriangle() {
                position = new Vector(200, 200),
                rotation = Angle.fromRadian(1.0f),
                scaleVector = new Vector(2, 1)
            };
            shapes.Add(triangle);
        }
    }
}