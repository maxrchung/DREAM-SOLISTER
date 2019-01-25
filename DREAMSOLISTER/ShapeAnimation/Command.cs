using System.Windows.Input;

namespace ShapeAnimation {
    public static class Command {
        public static RoutedCommand deselect = new RoutedCommand();
        public static RoutedCommand delete = new RoutedCommand();
        public static RoutedCommand createRectangle = new RoutedCommand();
        public static RoutedCommand createTriangle = new RoutedCommand();
        public static RoutedCommand createEllipse = new RoutedCommand();
        public static RoutedCommand createSemicircle = new RoutedCommand();
        public static RoutedCommand copy = new RoutedCommand();
        public static RoutedCommand eyeDrop = new RoutedCommand();
        public static RoutedCommand moveUp = new RoutedCommand();
        public static RoutedCommand moveDown = new RoutedCommand();
        public static RoutedCommand moveToTop = new RoutedCommand();
        public static RoutedCommand moveToBottom = new RoutedCommand();
        public static RoutedCommand toggleVisibilityBG = new RoutedCommand();
        public static RoutedCommand toggleVisibilityShapes = new RoutedCommand();
    }
}