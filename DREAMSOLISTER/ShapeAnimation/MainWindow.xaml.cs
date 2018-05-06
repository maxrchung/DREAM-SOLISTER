﻿using System;
using System.Diagnostics;
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
        private void delete(object sender, ExecutedRoutedEventArgs args) {
            if (viewModel.selected != null) {
                viewModel.shapes.Remove(viewModel.selected);
                viewModel.selected = null;
            }
        }
        private void createRectangle(object sender, ExecutedRoutedEventArgs args) {
            var shape = new SARectangle();
            shape.position = getMousePosition();
            viewModel.shapes.Add(shape);
            viewModel.selected = shape;
        }
        private void createTriangle(object sender, ExecutedRoutedEventArgs args) {
            var shape = new SATriangle();
            shape.position = getMousePosition();
            viewModel.shapes.Add(shape);
            viewModel.selected = shape;
        }
        private void createEllipse(object sender, ExecutedRoutedEventArgs args) {
            var shape = new SAEllipse();
            shape.position = getMousePosition();
            viewModel.shapes.Add(shape);
            viewModel.selected = shape;
        }
        private void createSemicircle(object sender, ExecutedRoutedEventArgs args) {
            var shape = new SASemicircle();
            shape.position = getMousePosition();
            viewModel.shapes.Add(shape);
            viewModel.selected = shape;
        }
        private void copy(object sender, ExecutedRoutedEventArgs args) {
            if (viewModel.selected != null) {
                var shape = viewModel.selected.copy();
                shape.position = getMousePosition();
                viewModel.shapes.Add(shape);
                viewModel.selected = shape;
            }
        }
        #endregion

        #region Timer Tick Events
        private void moveTimerTick(object sender, EventArgs e) {
            // Timers may be off from event
            if (viewModel.selected != null) {
                viewModel.selected.position = getMousePosition() - moveOffset;
            }
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
        private void shapeMouseLeftButtonDown(object sender, MouseButtonEventArgs e) {
            if (viewModel.selected == null) {
                var shape = (Shape)sender;
                var contentPresenter = (ContentPresenter)shape.TemplatedParent;
                var canvas = (Canvas)VisualTreeHelper.GetParent(contentPresenter);
                var index = canvas.Children.IndexOf(contentPresenter);
                viewModel.selected = viewModel.shapes[index];
            }
        }
        private void rotateMouseLeftButtonDown(object sender, MouseButtonEventArgs e) {
            if (viewModel.selected != null && !rotateTimer.IsEnabled) {
                previousRotation = (getMousePosition() - viewModel.selected.position).angle;
                rotateTimer.Start();
                e.Handled = true;
            }
        }
        private void scaleMouseLeftButtonDown(object sender, MouseButtonEventArgs e) {
            if (viewModel.selected != null && !scaleTimer.IsEnabled) {
                var corner = (Ellipse)sender;
                var translateTransform = (TranslateTransform)corner.RenderTransform;
                var topLeft = new Vector((float)translateTransform.X, (float)translateTransform.Y);
                var center = topLeft + new Vector((float)corner.Width) / 2;
                scaleOffset = getMousePosition() - center;
                scaleTimer.Start();
                e.Handled = true;
            }
        }
        private void backgroundMouseLeftButtonDown(object sender, MouseButtonEventArgs e) {
            if (viewModel.selected != null && !moveTimer.IsEnabled) {
                moveOffset = getMousePosition() - viewModel.selected.position;
                moveTimer.Start();
            }
        }
        private void backgroundMouseLeftButtonUp(object sender, MouseButtonEventArgs e) {
            moveTimer.Stop();
            rotateTimer.Stop();
            scaleTimer.Stop();
        }
        private void rotateMouseLeftButtonUp(object sender, MouseButtonEventArgs e) {
            rotateTimer.Stop();
        }
        private void scaleMouseLeftButtonUp(object sender, MouseButtonEventArgs e) {
            scaleTimer.Stop();
        }
        #endregion

        private void redValueTextChanged(object sender, TextChangedEventArgs e) {
            //if (viewModel.selected != null) {
            //    //    var color = viewModel.selected.color;
            //    //    viewModel.selected.color = Color.FromRgb(Convert.ToByte(redValue.Text), color.G, color.B);
            //}
        }
        private void redSliderValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e) {
            if (viewModel.selected != null) {
                var color = viewModel.selected.color;
                viewModel.selected.color = Color.FromRgb(Convert.ToByte(redSlider.Value), color.G, color.B);
            }
        }
        //private void greenValueTextChanged(object sender, TextChangedEventArgs e) {
        //    if (viewModel.selected != null) {
        //        var color = viewModel.selected.color;
        //        viewModel.selected.color = Color.FromRgb(color.R, Convert.ToByte(greenValue.Text), color.B);
        //    }
        //}
        //private void greenSliderValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e) {
        //    if (viewModel.selected != null) {
        //        var color = viewModel.selected.color;
        //        viewModel.selected.color = Color.FromRgb(color.R, Convert.ToByte(greenSlider.Value), color.B);
        //    }
        //}
        //private void blueValueTextChanged(object sender, TextChangedEventArgs e) {
        //    if (viewModel.selected != null) {
        //        var color = viewModel.selected.color;
        //        viewModel.selected.color = Color.FromRgb(color.R, color.G, Convert.ToByte(blueValue.Text));
        //    }
        //}
        //private void blueSliderValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e) {
        //    if (viewModel.selected != null) {
        //        var color = viewModel.selected.color;
        //        viewModel.selected.color = Color.FromRgb(color.R, color.G, Convert.ToByte(blueSlider.Value));
        //    }
        //}
    }
}
