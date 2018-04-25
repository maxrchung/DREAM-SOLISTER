using System;
using System.Collections.ObjectModel;

namespace ShapeAnimation {
    public class SAShapes : ObservableCollection<SAShape> {
        public SAShapes() {
            var rectangle = new SARectangle() {
                position = new Vector(100, 100)
            };
            Add(rectangle);

            var ellipse = new SAEllipse() {
                position = new Vector(60, 60)
            };
            Add(ellipse);

            var semicircle = new SASemicircle() {
                position = new Vector(140, 140)
            };
            Add(semicircle);

            var triangle = new SATriangle() {
                position = new Vector(200, 200)
            };
            Add(triangle);
        }
    }
}