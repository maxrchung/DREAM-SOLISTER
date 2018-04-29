using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Threading;

namespace ShapeAnimation {
    public partial class MainWindow : Window {
        private SAShape selected;
        private Canvas shapesCanvas;

        private TimeSpan timerInterval = TimeSpan.FromMilliseconds(15);
        private DispatcherTimer moveTimer = new DispatcherTimer(DispatcherPriority.Render);
        private Vector moveOffset;
        private DispatcherTimer rotateTimer = new DispatcherTimer(DispatcherPriority.Render);
        private Angle previousRotation;
        private DispatcherTimer scaleTimer = new DispatcherTimer(DispatcherPriority.Render);

        public MainWindow() {
            moveTimer.Interval = timerInterval;
            moveTimer.Tick += new EventHandler(moveTimerTick);

            rotateTimer.Interval = timerInterval;
            rotateTimer.Tick += new EventHandler(rotateTimerTick);

            scaleTimer.Interval = timerInterval;
            scaleTimer.Tick += new EventHandler(scaleTimerTick);

            InitializeComponent();

            // These require InitializeComponent() to be called first
            var viewModel = (ShapesViewModel)DataContext;
            selected = viewModel.selected;
            shapesCanvas = (Canvas)FindName("shapesCanvas");
        }

        private Vector getMousePosition() {
            var mousePosition = Mouse.GetPosition(shapesCanvas);
            return new Vector((float)mousePosition.X, (float)mousePosition.Y);
        }

        private void moveTimerTick(object sender, EventArgs e) {
            selected.position = getMousePosition() - moveOffset;
        }
        private void rotateTimerTick(object sender, EventArgs e) {
            var rotation = (getMousePosition() - selected.position).angle;
            var rotateOffset = rotation - previousRotation;
            previousRotation = rotation;
            selected.rotation += rotateOffset;
        }
        private void scaleTimerTick(object sender, EventArgs e) {
            var mousePosition = getMousePosition() - selected.position;
            var unrotate = mousePosition.rotate(-selected.rotation.radian);
            var scaleVector = new Vector(Math.Abs(unrotate.x), Math.Abs(unrotate.y)) / SAShape.fixedSize * 2;
            selected.scaleVector = scaleVector;
        }

        private void rotateMouseDown(object sender, System.Windows.Input.MouseButtonEventArgs e) {
            if (!rotateTimer.IsEnabled) {
                rotateTimer.Start();
                previousRotation = (getMousePosition() - selected.position).angle;
            }
        }
        private void scaleMouseDown(object sender, System.Windows.Input.MouseButtonEventArgs e) {
            scaleTimer.Start();
        }

        private void shapeMouseDown(object sender, System.Windows.Input.MouseButtonEventArgs e) {
            selection.RaiseEvent(e);
        }
        private void selectionMouseDown(object sender, System.Windows.Input.MouseButtonEventArgs e) {
            if (!moveTimer.IsEnabled) {
                moveTimer.Start();
                moveOffset = getMousePosition() - selected.position;
            }
        }
        private void backgroundMouseUp(object sender, MouseButtonEventArgs e) {
            moveTimer.Stop();
            rotateTimer.Stop();
            scaleTimer.Stop();
        }
    }
}
