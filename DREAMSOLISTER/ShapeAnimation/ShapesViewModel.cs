using System.Collections.ObjectModel;

namespace ShapeAnimation {
    public class ShapesViewModel {
        public ObservableCollection<SAShape> shapes { get; set; }
        public SAShape selected { get; set; }

        public ShapesViewModel() {
            shapes = new ObservableCollection<SAShape>();
            var rectangle = new SARectangle() {
                position = new Vector(100, 100),
                rotation = Angle.createFromRadian(1.0f),
                scaleVector = new Vector(1, 2)
            };
            shapes.Add(rectangle);

            //var ellipse = new SAEllipse() {
            //    position = new Vector(100, 100),
            //    rotation = Angle.createFromRadian(1.0f),
            //    scaleVector = new Vector(2, 1)
            //};
            //shapes.Add(ellipse);

            //var semicircle = new SASemicircle() {
            //    position = new Vector(100, 100),
            //    rotation = Angle.createFromRadian(1.0f),
            //    scaleVector = new Vector(1, 2)
            //};
            //shapes.Add(semicircle);

            var triangle = new SATriangle() {
                position = new Vector(200, 200),
                rotation = Angle.createFromRadian(1.0f),
                scaleVector = new Vector(2, 1)
            };
            shapes.Add(triangle);
            selected = triangle;
        }
    }
}