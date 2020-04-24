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
import TransformType from './TransformType';

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
      selectedShapeId: -1,
      transformType: TransformType.None
    };
  }

  componentDidMount() {
    window.addEventListener('resize', this.handleResize);
    document.addEventListener('mousemove', e => {
      const { mousePos, selectedShapeId, shapes, transformType } = this.state;
      const { video } = this;
      this.handleMouseMove(
        e,
        mousePos,
        selectedShapeId,
        shapes,
        transformType,
        video
      );
    });
    document.addEventListener('mouseup', () =>
      this.handleTransformChange(TransformType.None)
    );
  }

  handleResize = () => this.forceUpdate();

  handleMouseMove = (
    e,
    oldMousePos,
    selectedShapeId,
    shapes,
    transformType,
    video
  ) => {
    const newMousePos = new Victor(e.clientX, e.clientY);
    if (e.buttons === 1 && selectedShapeId >= 0) {
      const shape = { ...shapes[selectedShapeId] };
      const newPosition = this.mousePosToPosition(newMousePos, video);
      const oldPosition = this.mousePosToPosition(oldMousePos, video);
      const diffPosition = newPosition.clone().subtract(oldPosition);

      switch (transformType) {
        case TransformType.Scale: {
          const newShapePosition = newPosition.clone().subtract(shape.position);
          const oldShapePosition = oldPosition.clone().subtract(shape.position);
          const newRotated = newShapePosition.clone().rotate(-shape.rotation);
          const oldRotated = oldShapePosition.clone().rotate(-shape.rotation);
          const diffScale = newRotated.clone().divide(oldRotated);

          // Handle cases if transform approaches too close to center
          if (!Number.isFinite(diffScale.x) || diffScale.x === 0) {
            diffScale.x = 1;
          }
          if (!Number.isFinite(diffScale.y) || diffScale.y === 0) {
            diffScale.y = 1;
          }

          shape.scale.multiply(diffScale);
          break;
        }
        case TransformType.Rotate: {
          console.log('Rotate transform');
          break;
        }
        default: {
          shape.position.add(diffPosition);
          break;
        }
      }

      this.setState(prev => ({
        shapes: {
          ...prev.shapes,
          [selectedShapeId]: shape
        }
      }));
    }

    // pageX vs screenX vs clientX: https://stackoverflow.com/a/21452887
    this.setState({
      mousePos: newMousePos
    });
  };

  handleTransformChange = transformType => {
    this.setState({
      transformType
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
            label: 'Open...',
            accelerator: 'CmdOrCtrl+O',
            click: () => this.handleOpenProject()
          },
          {
            label: 'Save',
            accelerator: 'CmdOrCtrl+S',
            click: () => {
              const { project } = this.state;
              this.handleSaveProject(false, project);
            }
          },
          {
            label: 'Save As...',
            accelerator: 'CmdOrCtrl+Shift+S',
            click: () => {
              const { project } = this.state;
              this.handleSaveProject(true, project);
            }
          }
        ]
      },
      {
        label: 'Video',
        submenu: [
          {
            label: 'Load...',
            accelerator: 'CmdOrCtrl+L',
            click: () => {
              const { project } = this.state;
              this.handleLoadVideo(project);
            }
          },
          {
            label: 'Toggle Visibility',
            accelerator: 'Q',
            click: () => this.handleVideoToggle()
          },
          {
            label: 'Play/Pause',
            accelerator: 'Space',
            click: () => {
              const { video } = this;
              this.handlePlayVideo(video);
            }
          },
          {
            label: 'Restart',
            accelerator: 'X',
            click: () => {
              const { video } = this;
              this.handleRestartVideo(video);
            }
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
            click: () => {
              const { mousePos } = this.state;
              const { video } = this;
              this.handleAddRectangle(mousePos, video);
            }
          },
          {
            label: 'Add Triangle',
            accelerator: '2',
            click: () => {
              const { mousePos } = this.state;
              const { video } = this;
              this.handleAddTriangle(mousePos, video);
            }
          },
          {
            label: 'Add Circle',
            accelerator: '3',
            click: () => {
              const { mousePos } = this.state;
              const { video } = this;
              this.handleAddCircle(mousePos, video);
            }
          },
          {
            label: 'Add Semicircle',
            accelerator: '4',
            click: () => {
              const { mousePos } = this.state;
              const { video } = this;
              this.handleAddSemicircle(mousePos, video);
            }
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

  handleNewToggle = () => {
    this.setState(prev => ({
      isNewOpen: !prev.isNewOpen
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

  handleSaveProject = (needsDialog, project) => {
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

  handleLoadVideo = project => {
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

  // https://developer.mozilla.org/en-US/docs/Web/API/HTMLMediaElement/readyState
  isVideoReady = video => {
    return video && video.duration && video.readyState >= 3;
  };

  handleSeekVideo = (video, videoTime) => {
    if (this.isVideoReady(video)) {
      const timeInSeconds = videoTime * video.duration;
      this.video.currentTime = timeInSeconds;
    }
  };

  handleFormatVideoTime = (video, videoTime) => {
    const timeInSeconds = this.isVideoReady(video)
      ? videoTime * video.duration
      : 0;

    return this.formatVideoTimeInSeconds(timeInSeconds);
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

  handlePlayVideo = video => {
    if (this.isVideoReady(video)) {
      if (video.paused) {
        this.video.play();
      } else {
        this.video.pause();
      }
    }
  };

  handleRestartVideo = video => {
    if (this.isVideoReady(video)) {
      this.video.currentTime = 0;
      this.setState({
        videoTime: 0
      });
    }
  };

  handleVideoTimeUpdate = video => {
    if (this.isVideoReady(video)) {
      const fraction = video.currentTime / video.duration;
      this.setState({
        videoTime: fraction
      });
    }
  };

  mousePosToPosition = (mousePos, video) => {
    const { offsetLeft, offsetTop, clientWidth, clientHeight } = video;

    const adjustedMouse = mousePos
      .clone()
      .subtract(new Victor(offsetLeft, offsetTop));
    const midPoint = new Victor(clientWidth / 2, clientHeight / 2);

    const distanceVec = adjustedMouse.clone().subtract(midPoint);
    const position = distanceVec
      .clone()
      .divide(new Victor(clientWidth / 2, clientWidth / 2));
    return position;
  };

  addShape = (mousePos, video, type) => {
    if (!video) {
      return;
    }

    const position = this.mousePosToPosition(mousePos, video);

    this.setState(prev => ({
      shapes: {
        ...prev.shapes,
        [prev.project.shapeCount]: {
          id: prev.project.shapeCount,
          type,
          position,
          rotation: 0,
          scale: new Victor(1, 1)
        }
      },
      selectedShapeId: prev.project.shapeCount,
      project: {
        ...prev.project,
        shapeCount: prev.project.shapeCount + 1
      }
    }));
  };

  handleAddRectangle = (mousePos, video) => {
    this.addShape(mousePos, video, ShapeType.Rectangle);
  };

  handleAddTriangle = (mousePos, video) => {
    this.addShape(mousePos, video, ShapeType.Triangle);
  };

  handleAddCircle = (mousePos, video) => {
    this.addShape(mousePos, video, ShapeType.Circle);
  };

  handleAddSemicircle = (mousePos, video) => {
    this.addShape(mousePos, video, ShapeType.Semicircle);
  };

  handleSelectShape = (oldSelectedShapeId, newSelectedShapeId) => {
    if (oldSelectedShapeId >= 0) {
      return;
    }
    this.setState({
      selectedShapeId: newSelectedShapeId
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
    const { video } = this;

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
              onTimeUpdate={() => this.handleVideoTimeUpdate(video)}
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
                    id={shape.id}
                    key={shape.id}
                    video={this.video}
                    type={shape.type}
                    position={shape.position}
                    rotation={shape.rotation}
                    scale={shape.scale}
                    selectedId={selectedShapeId}
                    onClick={newSelectedShapeId =>
                      this.handleSelectShape(
                        selectedShapeId,
                        newSelectedShapeId
                      )
                    }
                    onTransformChange={this.handleTransformChange}
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
              onChange={e => this.handleSeekVideo(video, e.target.value)}
            />
          </div>
          <div className="col-auto p-2">
            {this.handleFormatVideoTime(video, videoTime)}
          </div>
        </div>
      </div>
    );
  }
}
