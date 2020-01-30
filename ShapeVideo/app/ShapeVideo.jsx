import { remote } from 'electron';
import fs from 'fs';
import React from 'react';
import Victor from 'victor';
import Project from './Project';
import NewModal from './NewModal';
import Slider from './Slider';
import CheckLabel from './CheckLabel';
import Shape from './Shape';
import ShapeType from './ShapeType';

export default class ShapeVideo extends React.Component {
  constructor(props) {
    super(props);

    this.setMenu();

    this.state = {
      isNewOpen: false,
      project: new Project(),
      isVideoVisible: true,
      videoOpacity: 1,
      areShapesVisible: true,
      shapesOpacity: 1,
      videoTime: 0,
      shapes: {},
      mousePos: new Victor(),
      selectedShapeId: -1
    };
  }

  componentDidMount() {
    window.addEventListener('resize', this.handleResize);
    document.addEventListener('mousemove', this.handleMouseMove);
  }

  componentWillUnmount() {
    window.removeEventListener('resize', this.handleResize);
    document.removeEventListener('mousemove', this.handleMouseMove);
  }

  handleResize = () => this.forceUpdate();

  handleMouseMove = e => {
    // pageX vs screnX vs clientX: https://stackoverflow.com/a/21452887
    this.setState({
      mousePos: new Victor(e.clientX, e.clientY)
    });
  };

  setMenu = () => {
    const isMac = remote.process.platform === 'darwin';
    let menuTemplate = isMac
      ? [
          {
            label: 'ShapeVideo',
            submenu: [
              { role: 'about' },
              { type: 'separator' },
              { role: 'services' },
              { type: 'separator' },
              { role: 'hide' },
              { role: 'hideothers' },
              { role: 'unhide' },
              { type: 'separator' },
              { role: 'quit' }
            ]
          }
        ]
      : [];

    menuTemplate = [
      ...menuTemplate,
      {
        label: 'Project',
        submenu: [
          {
            label: 'New',
            accelerator: 'CmdOrCtrl+N',
            click: () => this.handleNewToggle()
          },
          {
            label: 'Save',
            accelerator: 'CmdOrCtrl+S',
            click: () => this.handleSaveProject(false)
          },
          {
            label: 'Save As...',
            accelerator: 'CmdOrCtrl+Shift+S',
            click: () => this.handleSaveProject(true)
          },
          {
            label: 'Open...',
            accelerator: 'CmdOrCtrl+O',
            click: () => this.handleOpenProject()
          }
        ]
      },
      {
        label: 'Video',
        submenu: [
          {
            label: 'Load...',
            accelerator: 'CmdOrCtrl+L',
            click: () => this.handleLoadVideo()
          },
          {
            label: 'Toggle Visibility',
            accelerator: 'Q',
            click: () => this.handleVideoToggle()
          },
          {
            label: 'Play/Pause',
            accelerator: 'Space',
            click: () => this.handlePlayVideo()
          },
          {
            label: 'Restart',
            accelerator: 'X',
            click: () => this.handleRestartVideo()
          }
        ]
      },
      {
        label: 'Shapes',
        submenu: [
          {
            label: 'Toggle Visibility',
            accelerator: 'W',
            click: () => this.handleShapesToggle()
          },
          {
            label: 'Add Rectangle',
            accelerator: '1',
            click: () => this.handleAddRectangle()
          },
          {
            label: 'Add Triangle',
            accelerator: '2',
            click: () => this.handleAddTriangle()
          },
          {
            label: 'Add Circle',
            accelerator: '3',
            click: () => this.handleAddCircle()
          },
          {
            label: 'Add Semicircle',
            accelerator: '4',
            click: () => this.handleAddSemicircle()
          },
          {
            label: 'Deselect',
            accelerator: 'Esc',
            click: () => this.handleDeselectShape()
          }
        ]
      }
    ];
    const template = remote.Menu.buildFromTemplate(menuTemplate);
    remote.Menu.setApplicationMenu(template);
  };

  handleNewToggle = (_, isNewOpen) => {
    this.setState(state => ({
      isNewOpen: isNewOpen === undefined ? !state.isNewOpen : isNewOpen
    }));
  };

  handleNewProject = () => {
    this.setState(state => ({
      isNewOpen: !state.isNewOpen,
      project: new Project()
    }));
  };

  static projectDialogOptions = {
    filters: [
      { name: 'ShapeVideo (.sheo)', extensions: ['sheo'] },
      { name: 'All Files (.*)', extensions: ['*'] }
    ],
    properties: ['openFile', 'createDirectory']
  };

  static videoDialogOptions = {
    filters: [
      { name: 'Video (.mp4, .webm, .ogg)', extensions: ['mp4', 'webm', 'ogg'] },
      { name: 'All Files (.*)', extensions: ['*'] }
    ],
    properties: ['openFile', 'createDirectory']
  };

  handleOpenProject = () => {
    const paths = remote.dialog.showOpenDialogSync(
      ShapeVideo.projectDialogOptions
    );
    if (!paths) {
      return;
    }

    const serialized = fs.readFileSync(paths[0]);
    const project = JSON.parse(serialized);
    this.setState({
      project
    });
  };

  handleSaveProject = needsDialog => {
    const { project } = this.state;

    let serialized = '';
    let path = project.name;
    if (!path || needsDialog) {
      path = remote.dialog.showSaveDialogSync(ShapeVideo.projectDialogOptions);
      // If no path is picked, then don't proceed with save
      if (!path) {
        return;
      }

      const newProject = {
        ...project,
        name: path
      };
      this.setState({
        project: newProject
      });
      serialized = JSON.stringify(newProject);
    } else {
      serialized = JSON.stringify(project);
    }
    fs.writeFileSync(path, serialized);
  };

  handleLoadVideo = () => {
    const { project } = this.state;

    const paths = remote.dialog.showOpenDialogSync(
      ShapeVideo.videoDialogOptions
    );

    if (!paths) {
      return;
    }

    this.setState({
      project: {
        ...project,
        video: paths[0]
      }
    });
  };

  handleVideoToggle = () => {
    this.setState(prev => ({
      isVideoVisible: !prev.isVideoVisible
    }));
  };

  handleVideoOpacity = videoOpacity => {
    this.setState({
      videoOpacity: parseFloat(videoOpacity)
    });
  };

  handleShapesToggle = () => {
    this.setState(prev => ({
      areShapesVisible: !prev.areShapesVisible
    }));
  };

  handleShapesOpacity = shapesOpacity => {
    this.setState({
      shapesOpacity: parseFloat(shapesOpacity)
    });
  };

  handleSeekVideo = videoTime => {
    const { video } = this;
    if (this.isVideoReady(video)) {
      const timeInSeconds = videoTime * video.duration;
      video.currentTime = timeInSeconds;
    }
  };

  handleFormatVideoTime = () => {
    const { video } = this;
    const { videoTime } = this.state;

    // https://developer.mozilla.org/en-US/docs/Web/API/HTMLMediaElement/readyState
    const timeInSeconds = this.isVideoReady(video)
      ? videoTime * video.duration
      : 0;

    return this.formatVideoTimeInSeconds(timeInSeconds);
  };

  isVideoReady = video => {
    return video && video.duration && video.readyState >= 3;
  };

  formatVideoTimeInSeconds = timeInSeconds => {
    const dateTime = new Date(null);
    // There are some floating inconsistencies if we try and use .setSeconds()
    dateTime.setMilliseconds(timeInSeconds * 1000);
    const minutes = dateTime
      .getMinutes()
      .toString()
      .padStart(2, '0');
    const seconds = dateTime
      .getSeconds()
      .toString()
      .padStart(2, '0');
    const milliseconds = dateTime
      .getMilliseconds()
      .toString()
      .padStart(3, '0');
    const formatted = `${minutes}:${seconds}:${milliseconds}`;
    return formatted;
  };

  handlePlayVideo = () => {
    const { video } = this;
    if (this.isVideoReady(video)) {
      if (video.paused) {
        video.play();
      } else {
        video.pause();
      }
    }
  };

  handleRestartVideo = () => {
    const { video } = this;
    if (this.isVideoReady(video)) {
      video.currentTime = 0;
      this.setState({
        videoTime: 0
      });
    }
  };

  handleVideoTimeUpdate = () => {
    const { video } = this;
    if (this.isVideoReady(video)) {
      const fraction = video.currentTime / video.duration;
      this.setState({
        videoTime: fraction
      });
    }
  };

  addShape = type => {
    if (!this.video) {
      return;
    }

    const { mousePos } = this.state;
    const { offsetLeft, offsetTop, clientWidth, clientHeight } = this.video;

    const adjustedMouse = mousePos
      .clone()
      .subtract(new Victor(offsetLeft, offsetTop));
    const midPoint = new Victor(clientWidth / 2, clientHeight / 2);

    const distanceVec = adjustedMouse.clone().subtract(midPoint);
    const position = distanceVec
      .clone()
      .divide(new Victor(clientWidth / 2, clientWidth / 2));

    this.setState(prev => ({
      shapes: {
        ...prev.shapes,
        [prev.project.shapeCount]: {
          key: prev.project.shapeCount,
          type,
          position,
          id: prev.project.shapeCount
        }
      },
      selectedShapeId: prev.project.shapeCount,
      project: {
        ...prev.project,
        shapeCount: prev.project.shapeCount + 1
      }
    }));
  };

  handleAddRectangle = () => {
    this.addShape(ShapeType.Rectangle);
  };

  handleAddTriangle = () => {
    this.addShape(ShapeType.Triangle);
  };

  handleAddCircle = () => {
    this.addShape(ShapeType.Circle);
  };

  handleAddSemicircle = () => {
    this.addShape(ShapeType.Semicircle);
  };

  handleSelectShape = selectedShapeId => {
    if (selectedShapeId !== -1) {
      return;
    }
    this.setState({
      selectedShapeId
    });
  };

  handleDeselectShape = () => {
    this.setState({
      selectedShapeId: -1
    });
  };

  render() {
    const {
      isNewOpen,
      project,
      isVideoVisible,
      videoOpacity,
      areShapesVisible,
      shapesOpacity,
      videoTime,
      shapes,
      selectedShapeId
    } = this.state;

    return (
      <div className="d-flex flex-column vh-100 elegant-color-dark white-text">
        <NewModal
          isNewOpen={isNewOpen}
          onNewToggle={this.handleNewToggle}
          onNewProject={this.handleNewProject}
        />

        <div className="d-flex flex-grow-1">
          <div className="d-flex col p-2">
            <video
              className="w-100"
              ref={element => {
                this.video = element;
              }}
              src={project.video}
              // Shapes rely on video to be rendered, so we can't
              // just remove the video element to toggle video
              style={{ opacity: isVideoVisible ? videoOpacity : 0 }}
              onTimeUpdate={this.handleVideoTimeUpdate}
            >
              <track kind="captions" label="DREAM SOLISTER" />
            </video>

            {areShapesVisible && (
              <div
                className="position-absolute"
                style={{ opacity: shapesOpacity }}
              >
                {Object.values(shapes).map(shape => (
                  <Shape
                    key={shape.key}
                    type={shape.type}
                    video={this.video}
                    position={shape.position}
                    id={shape.id}
                    selectedId={selectedShapeId}
                    onClick={this.handleSelectShape}
                    rotation={1}
                  />
                ))}
              </div>
            )}
          </div>

          <div className="d-flex flex-column col-auto p-2 stylish-color-dark">
            <form className="p-2 stylish-color">
              <div className="form-row">
                <div className="col-5">
                  <CheckLabel
                    checked={isVideoVisible}
                    label="Video"
                    name="chk-video"
                    onChange={this.handleVideoToggle}
                  />
                </div>

                <div className="col-7">
                  <Slider
                    value={videoOpacity}
                    onChange={e => this.handleVideoOpacity(e.target.value)}
                  />
                </div>
              </div>

              <div className="form-row">
                <div className="col-5">
                  <CheckLabel
                    checked={areShapesVisible}
                    label="Shapes"
                    name="chk-shapes"
                    onChange={this.handleShapesToggle}
                  />
                </div>

                <div className="col-7">
                  <Slider
                    value={shapesOpacity}
                    onChange={e => this.handleShapesOpacity(e.target.value)}
                  />
                </div>
              </div>
            </form>

            <div className="mt-2 p-2 h-100 stylish-color">Shapes</div>
          </div>
        </div>

        <div className="d-flex elegant-color">
          <div className="d-flex col p-2">
            <Slider
              value={videoTime}
              onChange={e => this.handleSeekVideo(e.target.value)}
            />
          </div>
          <div className="col-auto p-2">{this.handleFormatVideoTime()}</div>
        </div>
      </div>
    );
  }
}
