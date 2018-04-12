using System.Collections.ObjectModel;
using System.Numerics;

namespace ShapeAnimation {
    public class SAShapes : ObservableCollection<SAShape> {
        public SAShapes() {
            var rectangle = new SARectangle() {
                position = new Vector2(100, 100)
            };
            Add(rectangle);
        }
    }
}
