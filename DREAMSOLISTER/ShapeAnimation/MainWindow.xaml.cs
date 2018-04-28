using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Threading;

namespace ShapeAnimation {
    public partial class MainWindow : Window {
        private ShapesViewModel viewModel;
        private Canvas shapesCanvas;

        private TimeSpan timerInterval = TimeSpan.FromMilliseconds(15);
        private DispatcherTimer moveTimer = new DispatcherTimer(DispatcherPriority.Render);
        private Vector moveOffset;
        private DispatcherTimer scaleTimer = new DispatcherTimer(DispatcherPriority.Render);

        public MainWindow() {
            moveTimer.Interval = timerInterval;
            moveTimer.Tick += new EventHandler(moveTimerTick);

            scaleTimer.Interval = timerInterval;
            scaleTimer.Tick += new EventHandler(scaleTimerTick);

            InitializeComponent();

            // These require InitializeComponent() to be called first
            viewModel = (ShapesViewModel)DataContext;
            shapesCanvas = (Canvas)FindName("shapesCanvas");
        }

        private Vector getMousePosition() {
            var mousePosition = Mouse.GetPosition(shapesCanvas);
            return new Vector((float)mousePosition.X, (float)mousePosition.Y);
        }

        private void moveTimerTick(object sender, EventArgs e) {
            viewModel.selected.position = getMousePosition() - moveOffset;
        }
        private void scaleTimerTick(object sender, EventArgs e) {

        }

        private void scaleCornerMouseDown(object sender, System.Windows.Input.MouseButtonEventArgs e) {
            scaleTimer.Start();
        }

        private void moveMouseDown(object sender, System.Windows.Input.MouseButtonEventArgs e) {
            if (!moveTimer.IsEnabled) {
                moveTimer.Start();
                moveOffset = getMousePosition() - viewModel.selected.position;
            }
        }

        private void moveMouseUp(object sender, MouseButtonEventArgs e) {
            moveTimer.Stop();
        }
    }
}
