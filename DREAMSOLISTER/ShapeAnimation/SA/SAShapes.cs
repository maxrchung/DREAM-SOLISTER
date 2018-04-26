using System;
using System.Collections.ObjectModel;

namespace ShapeAnimation {
    public class SAShapes : ObservableCollection<SAShape> {
        public SAShapes() {
            var rectangle = new SARectangle() {
                position = new Vector(100, 100),
                rotation = Angle.createFromRadian(1.0f),
                scaleVector = new Vector(1, 2)
            };
            Add(rectangle);

            //var ellipse = new SAEllipse() {
            //    position = new Vector(100, 100),
            //    rotation = Angle.createFromRadian(1.0f),
            //    scaleVector = new Vector(2, 1)
            //};
            //Add(ellipse);

            //var semicircle = new SASemicircle() {
            //    position = new Vector(100, 100),
            //    rotation = Angle.createFromRadian(1.0f),
            //    scaleVector = new Vector(1, 2)
            //};
            //Add(semicircle);

            var triangle = new SATriangle() {
                position = new Vector(200, 200),
                rotation = Angle.createFromRadian(1.0f),
                scaleVector = new Vector(2, 1)
            };
            Add(triangle);
        }
    }
}