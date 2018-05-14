using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows.Media;

namespace ShapeAnimation {
    public class ViewModel : INotifyPropertyChanged {
        public event PropertyChangedEventHandler PropertyChanged;
        protected void NotifyPropertyChanged(string name) {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }

        private ObservableCollection<SAShape> _shapes = new ObservableCollection<SAShape>();
        public ObservableCollection<SAShape> shapes {
            get {
                return _shapes;
            }
            set {
                _shapes = value;
                NotifyPropertyChanged("shapes");
            }
        }
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
            //shapes = new ObservableCollection<SAShape>();
            //var rectangle = new SARectangle() {
            //    position = new Vector(100, 100),
            //    rotation = Angle.fromRadian(1.0f),
            //    color = Color.FromRgb(255, 120, 20),
            //    scaleVector = new Vector(1, 2)
            //};
            //shapes.Add(rectangle);

            //var ellipse = new SAEllipse() {
            //    position = new Vector(100, 100),
            //    rotation = Angle.fromRadian(1.0f),
            //    scaleVector = new Vector(2, 1)
            //};
            //shapes.Add(ellipse);

            //var semicircle = new SASemicircle() {
            //    position = new Vector(100, 100),
            //    rotation = Angle.fromRadian(1.0f),
            //    scaleVector = new Vector(1, 2)
            //};
            //shapes.Add(semicircle);

            //var triangle = new SATriangle() {
            //    position = new Vector(200, 200),
            //    rotation = Angle.fromRadian(1.0f),
            //    scaleVector = new Vector(2, 1)
            //};
            //shapes.Add(triangle);
        }
    }
}