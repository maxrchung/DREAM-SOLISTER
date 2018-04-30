using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace ShapeAnimation {
    public partial class MainWindow : Window {
        #region Variables
        private ViewModel viewModel;
        private Canvas shapesCanvas;

        private TimeSpan timerInterval = TimeSpan.FromMilliseconds(15);
        private DispatcherTimer moveTimer = new DispatcherTimer(DispatcherPriority.Render);
        private Vector moveOffset;
        private DispatcherTimer rotateTimer = new DispatcherTimer(DispatcherPriority.Render);
        private Angle previousRotation;
        private DispatcherTimer scaleTimer = new DispatcherTimer(DispatcherPriority.Render);
        private Vector scaleOffset;
        #endregion

        #region Initialization
        public MainWindow() {
            moveTimer.Interval = timerInterval;
            moveTimer.Tick += new EventHandler(moveTimerTick);

            rotateTimer.Interval = timerInterval;
            rotateTimer.Tick += new EventHandler(rotateTimerTick);

            scaleTimer.Interval = timerInterval;
            scaleTimer.Tick += new EventHandler(scaleTimerTick);

            InitializeComponent();

            // These require InitializeComponent() to be called first
            viewModel = (ViewModel)DataContext;
            shapesCanvas = (Canvas)FindName("shapesCanvas");
        }
        #endregion

        #region Helpers
        private Vector getMousePosition() {
            var mousePosition = Mouse.GetPosition(shapesCanvas);
            return new Vector((float)mousePosition.X, (float)mousePosition.Y);
        }
        #endregion

        #region Commands
        private void deselect(object sender, ExecutedRoutedEventArgs args) {
            viewModel.selected = null;
        }
        #endregion

        #region Timer Tick Events
        private void moveTimerTick(object sender, EventArgs e) {
            viewModel.selected.position = getMousePosition() - moveOffset;
        }
        private void rotateTimerTick(object sender, EventArgs e) {
            var rotation = (getMousePosition() - viewModel.selected.position).angle;
            var rotateOffset = rotation - previousRotation;
            previousRotation = rotation;
            viewModel.selected.rotation += rotateOffset;
        }
        private void scaleTimerTick(object sender, EventArgs e) {
            var position = getMousePosition() - viewModel.selected.position - scaleOffset;
            var unrotate = position.rotate(-viewModel.selected.rotation.radian);
            var scaleVector = new Vector(Math.Abs(unrotate.x), Math.Abs(unrotate.y)) / SAShape.fixedSize * 2;
            viewModel.selected.scaleVector = scaleVector;
        }
        #endregion

        #region Mouse Events
        private void shapeMouseDown(object sender, MouseButtonEventArgs e) {
            if (viewModel.selected == null) {
                var shape = (Shape)sender;
                var contentPresenter = (ContentPresenter)shape.TemplatedParent;
                var canvas = (Canvas)VisualTreeHelper.GetParent(contentPresenter);
                var index = canvas.Children.IndexOf(contentPresenter);
                viewModel.selected = viewModel.shapes[index];
            }

            // Pass event to sibling
            selection.RaiseEvent(e);
        }
        private void rotateMouseDown(object sender, MouseButtonEventArgs e) {
            if (viewModel.selected != null && !rotateTimer.IsEnabled) {
                rotateTimer.Start();
                previousRotation = (getMousePosition() - viewModel.selected.position).angle;
            }
        }
        private void scaleMouseDown(object sender, MouseButtonEventArgs e) {
            if (viewModel.selected != null && !scaleTimer.IsEnabled) {
                scaleTimer.Start();
                var corner = (Ellipse)sender;
                var translateTransform = (TranslateTransform)corner.RenderTransform;
                var topLeft = new Vector((float)translateTransform.X, (float)translateTransform.Y);
                var center = topLeft + new Vector((float)corner.Width) / 2;
                scaleOffset = getMousePosition() - center;
            }
        }
        private void selectionMouseDown(object sender, MouseButtonEventArgs e) {
            if (viewModel.selected != null && !moveTimer.IsEnabled) {
                moveTimer.Start();
                moveOffset = getMousePosition() - viewModel.selected.position;
            }
        }
        private void backgroundMouseUp(object sender, MouseButtonEventArgs e) {
            moveTimer.Stop();
            rotateTimer.Stop();
            scaleTimer.Stop();
        }
        #endregion
    }
}
