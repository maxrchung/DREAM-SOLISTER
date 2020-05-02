import { remote } from 'electron';
import fs from 'fs';
import React from 'react';
import Victor from 'victor';
import NewModal from './NewModal';
import Slider from './Slider';
import CheckLabel from './CheckLabel';
import Shape from './Shape';
import ShapeListItem from './ShapeListItem';
import ShapeType from './ShapeType';
import TransformType from './TransformType';

export default class ShapeVideo extends React.Component {
  constructor(props) {
    super(props);

    this.setMenu();

    this.state = {
      ...this.resetState()
    };
  }

  componentDidMount() {
    window.addEventListener('resize', this.handleResize);
    document.addEventListener('mousemove', e => {
      const {
        mousePosX,
        mousePosY,
        selectedShapeId,
        shapes,
        transformType
      } = this.state;
      const { video } = this;
      const mousePos = new Victor(mousePosX, mousePosY);
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

  resetState = () => {
    return {
      areShapesVisible: true,
      frameStart: 0,
      frameDelta: 0,
      frameEnd: 0,
      isNewOpen: false,
      isVideoVisible: true,
      mousePosX: 0,
      mousePosY: 0,
      projectPath: '',
      shapesOpacity: 1,
      videoOpacity: 1,
      videoTime: 0,
      videoPath: '',
      shapeCount: 0,
      shapes: {},
      selectedShapeId: -1,
      transformType: TransformType.None,
      frame: []
    };
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
              this.handleSaveProject(false, this.state);
            }
          },
          {
            label: 'Save As...',
            accelerator: 'CmdOrCtrl+Shift+S',
            click: () => {
              this.handleSaveProject(true, this.state);
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
              this.handleLoadVideo();
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
              const { mousePosX, mousePosY } = this.state;
              const { video } = this;
              const mousePos = new Victor(mousePosX, mousePosY);
              this.handleAddRectangle(mousePos, video);
            }
          },
          {
            label: 'Add Triangle',
            accelerator: '2',
            click: () => {
              const { mousePosX, mousePosY } = this.state;
              const { video } = this;
              const mousePos = new Victor(mousePosX, mousePosY);
              this.handleAddTriangle(mousePos, video);
            }
          },
          {
            label: 'Add Circle',
            accelerator: '3',
            click: () => {
              const { mousePosX, mousePosY } = this.state;
              const { video } = this;
              const mousePos = new Victor(mousePosX, mousePosY);
              this.handleAddCircle(mousePos, video);
            }
          },
          {
            label: 'Add Semicircle',
            accelerator: '4',
            click: () => {
              const { mousePosX, mousePosY } = this.state;
              const { video } = this;
              const mousePos = new Victor(mousePosX, mousePosY);
              this.handleAddSemicircle(mousePos, video);
            }
          },
          {
            label: 'Get Color',
            accelerator: 'E',
            click: () => {
              const {
                mousePosX,
                mousePosY,
                selectedShapeId,
                shapes
              } = this.state;
              const { canvas, video } = this;
              const mousePos = new Victor(mousePosX, mousePosY);
              this.handleGetColor(
                mousePos,
                selectedShapeId,
                shapes,
                canvas,
                video
              );
            }
          },
          {
            label: 'Paste',
            accelerator: 'V',
            click: () => {
              const {
                mousePosX,
                mousePosY,
                selectedShapeId,
                shapes
              } = this.state;
              const { video } = this;
              const mousePos = new Victor(mousePosX, mousePosY);
              this.handlePasteShape(mousePos, video, selectedShapeId, shapes);
            }
          },
          {
            label: 'Deselect',
            accelerator: 'Esc',
            click: () => this.handleDeselectShape()
          },
          {
            label: 'Delete',
            accelerator: 'Delete',
            click: () => {
              const { selectedShapeId, shapes } = this.state;
              this.handleDeleteShape(selectedShapeId, shapes);
            }
          }
        ]
      },
      {
        label: 'Layers',
        submenu: [
          {
            label: 'Move Up',
            accelerator: 'A',
            click: () => {
              const { selectedShapeId, frame } = this.state;
              this.handleLayerUp(selectedShapeId, frame);
            }
          },
          {
            label: 'Move Down',
            accelerator: 'S',
            click: () => {
              const { selectedShapeId, frame } = this.state;
              this.handleLayerDown(selectedShapeId, frame);
            }
          },
          {
            label: 'Move Top',
            accelerator: 'D',
            click: () => {
              const { selectedShapeId, frame } = this.state;
              this.handleLayerTop(selectedShapeId, frame);
            }
          },
          {
            label: 'Move Bottom',
            accelerator: 'F',
            click: () => {
              const { selectedShapeId, frame } = this.state;
              this.handleLayerBottom(selectedShapeId, frame);
            }
          }
        ]
      }
    ];
    const template = remote.Menu.buildFromTemplate(menuTemplate);
    remote.Menu.setApplicationMenu(template);
  };

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
      const shapePosition = new Victor(shape.positionX, shape.positionY);

      switch (transformType) {
        case TransformType.Scale: {
          const newShapePosition = newPosition.clone().subtract(shapePosition);
          const oldShapePosition = oldPosition.clone().subtract(shapePosition);
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

          shape.scaleX *= diffScale.x;
          shape.scaleY *= diffScale.y;
          break;
        }
        case TransformType.Rotate: {
          const newShapePosition = newPosition.clone().subtract(shapePosition);
          const oldShapePosition = oldPosition.clone().subtract(shapePosition);

          const oldRotation = oldShapePosition.angle();
          const newRotated = newShapePosition.rotate(-oldRotation);
          const diffRotation = newRotated.angle();

          shape.rotation += diffRotation;
          break;
        }
        default: {
          shape.positionX += diffPosition.x;
          shape.positionY += diffPosition.y;
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
      mousePosX: newMousePos.x,
      mousePosY: newMousePos.y
    });
  };

  handleTransformChange = transformType => {
    this.setState({
      transformType
    });
  };

  handleNewToggle = () => {
    this.setState(prev => ({
      isNewOpen: !prev.isNewOpen
    }));
  };

  handleNewProject = () => {
    this.setState({
      ...this.resetState()
    });
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
    const state = JSON.parse(serialized);
    this.setState(state);
  };

  handleSaveProject = (needsDialog, state) => {
    const { projectPath } = state;
    let serialized = '';
    if (projectPath && !needsDialog) {
      serialized = JSON.stringify(state);
      fs.writeFileSync(projectPath, serialized);
    } else {
      const newPath = remote.dialog.showSaveDialogSync(
        ShapeVideo.projectDialogOptions
      );
      // If no path is picked, then don't proceed with save
      if (!newPath) {
        return;
      }

      const newState = {
        ...this.state,
        projectPath: newPath
      };
      this.setState(newState);
      serialized = JSON.stringify(newState);
      fs.writeFileSync(newPath, serialized);
    }
  };

  handleLoadVideo = () => {
    const paths = remote.dialog.showOpenDialogSync(
      ShapeVideo.videoDialogOptions
    );

    if (!paths) {
      return;
    }

    this.setState({
      videoPath: paths[0]
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
    if (!this.isVideoReady(video)) {
      return;
    }
    const timeInSeconds = videoTime * video.duration;
    this.video.currentTime = timeInSeconds;
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
    if (!this.isVideoReady(video)) {
      return;
    }
    if (video.paused) {
      this.video.play();
    } else {
      this.video.pause();
    }
  };

  handleRestartVideo = video => {
    if (!this.isVideoReady(video)) {
      return;
    }
    this.video.currentTime = 0;
    this.setState({
      videoTime: 0
    });
  };

  handleVideoTimeUpdate = video => {
    if (this.isVideoReady(video)) {
      const fraction = video.currentTime / video.duration;
      this.setState({
        videoTime: fraction
      });
    }
  };

  mousePosToVideoPos = (mousePos, offsetLeft, offsetTop) => {
    const adjustedMouse = mousePos
      .clone()
      .subtract(new Victor(offsetLeft, offsetTop));
    return adjustedMouse;
  };

  mousePosToPosition = (mousePos, video) => {
    const { offsetLeft, offsetTop, clientWidth, clientHeight } = video;
    const videoPos = this.mousePosToVideoPos(mousePos, offsetLeft, offsetTop);

    const midPoint = new Victor(clientWidth / 2, clientHeight / 2);
    const distanceVec = videoPos.clone().subtract(midPoint);
    const position = distanceVec
      .clone()
      .divide(new Victor(clientWidth / 2, clientWidth / 2));
    return position;
  };

  addShape = (mousePos, video, type) => {
    if (!video) {
      return;
    }

    // Prevent shape from being added if we are focused on an input. Adding
    // shapes uses hotkeys 1, 2, 3, 4 which can conflict when entering into
    // numbers into inputs.
    const inputs = document.getElementsByTagName('input');
    for (let i = 0; i < inputs.length; i += 1) {
      if (inputs[i] === document.activeElement) {
        return;
      }
    }

    const position = this.mousePosToPosition(mousePos, video);

    this.setState(
      prev => ({
        frame: [...prev.frame, prev.shapeCount],
        selectedShapeId: prev.shapeCount,
        shapes: {
          ...prev.shapes,
          [prev.shapeCount]: {
            colorR: 255,
            colorG: 255,
            colorB: 255,
            id: prev.shapeCount,
            positionX: position.x,
            positionY: position.y,
            rotation: 0,
            scaleX: 1,
            scaleY: 1,
            type
          }
        },
        shapeCount: prev.shapeCount + 1
      }),
      () => {
        const { selectedShapeId } = this.state;
        this.scrollShapeIntoView(selectedShapeId);
      }
    );
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

  handleGetColor = (mousePos, selectedShapeId, shapes, canvas, video) => {
    if (canvas && video) {
      const {
        offsetLeft,
        offsetTop,
        clientWidth,
        clientHeight,
        videoWidth,
        videoHeight
      } = video;
      this.canvas.width = videoWidth;
      this.canvas.height = videoHeight;
      this.canvas.style.width = `${videoWidth}px`;
      this.canvas.style.height = `${videoHeight}px`;

      const videoPos = this.mousePosToVideoPos(mousePos, offsetLeft, offsetTop);
      // The video may be scaled differently to the displayed pixels so we need
      // to convert the mouse position from display resolution to video
      // resolution.
      const scale = new Victor(
        videoWidth / clientWidth,
        videoHeight / clientHeight
      );
      videoPos.multiply(scale);

      const ctx = canvas.getContext('2d');
      ctx.drawImage(video, 0, 0);
      const { data } = ctx.getImageData(videoPos.x, videoPos.y, 1, 1);

      this.setState({
        shapes: {
          ...shapes,
          [selectedShapeId]: {
            ...shapes[selectedShapeId],
            colorR: data[0],
            colorG: data[1],
            colorB: data[2]
          }
        }
      });
    }
  };

  handlePasteShape = (mousePos, video, oldSelectedShapeId, shapes) => {
    if (!video || oldSelectedShapeId < 0) {
      return;
    }

    const position = this.mousePosToPosition(mousePos, video);
    const shape = shapes[oldSelectedShapeId];

    this.setState(
      prev => ({
        frame: [...prev.frame, prev.shapeCount],
        selectedShapeId: prev.shapeCount,
        shapes: {
          ...prev.shapes,
          [prev.shapeCount]: {
            colorR: shape.colorR,
            colorG: shape.colorG,
            colorB: shape.colorB,
            id: prev.shapeCount,
            positionX: position.x,
            positionY: position.y,
            rotation: shape.rotation,
            scaleX: shape.scaleX,
            scaleY: shape.scaleY,
            type: shape.type
          }
        },
        shapeCount: prev.shapeCount + 1
      }),
      () => {
        const { selectedShapeId } = this.state;
        this.scrollShapeIntoView(selectedShapeId);
      }
    );
  };

  handleSelectShape = (oldSelectedShapeId, newSelectedShapeId) => {
    if (oldSelectedShapeId >= 0) {
      return;
    }
    this.handleListSelect(newSelectedShapeId);
  };

  handleListSelect = selectedShapeId => {
    this.setState({
      selectedShapeId
    });

    this.scrollShapeIntoView(selectedShapeId);
  };

  scrollShapeIntoView = shapeId => {
    document.getElementById(`shape-list-item-${shapeId}`).scrollIntoView();
  };

  handleDeselectShape = () => {
    this.setState({
      selectedShapeId: -1
    });
  };

  handleDeleteShape = (selectedShapeId, shapes) => {
    if (selectedShapeId < 0) {
      return;
    }
    const newShapes = shapes;
    delete newShapes[selectedShapeId];
    this.setState(prev => ({
      frame: prev.frame.filter(shapeId => shapeId !== selectedShapeId),
      selectedShapeId: -1,
      shapes: newShapes
    }));
  };

  handleLayerUp = (selectedShapeId, frame) => {
    if (selectedShapeId < 0) {
      return;
    }
    const index = frame.findIndex(id => id === selectedShapeId);
    if (index === 0) {
      return;
    }
    const newFrame = [...frame];
    newFrame[index] = newFrame[index - 1];
    newFrame[index - 1] = selectedShapeId;
    this.setState({
      frame: newFrame
    });
  };

  handleLayerDown = (selectedShapeId, frame) => {
    if (selectedShapeId < 0) {
      return;
    }
    const index = frame.findIndex(id => id === selectedShapeId);
    if (index === frame.length - 1) {
      return;
    }
    const newFrame = [...frame];
    newFrame[index] = newFrame[index + 1];
    newFrame[index + 1] = selectedShapeId;
    this.setState({
      frame: newFrame
    });
  };

  handleLayerTop = (selectedShapeId, frame) => {
    if (selectedShapeId < 0) {
      return;
    }
    if (frame[0] === selectedShapeId) {
      return;
    }
    const newFrame = [
      selectedShapeId,
      ...frame.filter(id => id !== selectedShapeId)
    ];
    this.setState({
      frame: newFrame
    });
  };

  handleLayerBottom = (selectedShapeId, frame) => {
    if (selectedShapeId < 0) {
      return;
    }
    if (frame[frame.length - 1] === selectedShapeId) {
      return;
    }
    const newFrame = [
      ...frame.filter(id => id !== selectedShapeId),
      selectedShapeId
    ];
    this.setState({
      frame: newFrame
    });
  };

  handleInputChange = (prop, value) => {
    this.setState({
      [prop]: value
    });
  };

  render() {
    const {
      areShapesVisible,
      frame,
      frameStart,
      frameDelta,
      frameEnd,
      isNewOpen,
      isVideoVisible,
      selectedShapeId,
      shapes,
      shapesOpacity,
      videoOpacity,
      videoPath,
      videoTime
    } = this.state;
    const { video } = this;

    return (
      <div className="d-flex flex-column vh-100 elegant-color-dark white-text overflow-hidden">
        <NewModal
          isNewOpen={isNewOpen}
          onNewToggle={this.handleNewToggle}
          onNewProject={this.handleNewProject}
        />

        <div className="d-flex flex-grow-1 h-100">
          <div className="d-flex col p-2">
            <canvas
              className="d-none"
              ref={element => {
                this.canvas = element;
              }}
            />
            <video
              className="w-100"
              ref={element => {
                this.video = element;
              }}
              src={videoPath}
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
                {frame.map(shapeId => {
                  const shape = shapes[shapeId];
                  return (
                    <Shape
                      colorR={shape.colorR}
                      colorG={shape.colorG}
                      colorB={shape.colorB}
                      id={shape.id}
                      key={shape.id}
                      onMouseDown={newSelectedShapeId =>
                        this.handleSelectShape(
                          selectedShapeId,
                          newSelectedShapeId
                        )
                      }
                      onTransformChange={this.handleTransformChange}
                      positionX={shape.positionX}
                      positionY={shape.positionY}
                      rotation={shape.rotation}
                      scaleX={shape.scaleX}
                      scaleY={shape.scaleY}
                      selectedId={selectedShapeId}
                      type={shape.type}
                      video={this.video}
                    />
                  );
                })}
              </div>
            )}
          </div>

          <div className="d-flex flex-column col-auto p-2 stylish-color-dark h-100">
            <div className="p-2 stylish-color">
              <div className="form-row align-items-center mt-1">
                <div className="col-5">Frame Start</div>
                <div className="col-7">
                  <input
                    className="form-control"
                    onChange={e =>
                      this.handleInputChange('frameStart', e.target.value)
                    }
                    type="number"
                    value={frameStart}
                  />
                </div>
              </div>

              <div className="form-row align-items-center mt-1">
                <div className="col-5">Frame Delta</div>
                <div className="col-7">
                  <input
                    className="form-control"
                    onChange={e =>
                      this.handleInputChange('frameDelta', e.target.value)
                    }
                    type="number"
                    value={frameDelta}
                  />
                </div>
              </div>

              <div className="form-row align-items-center mt-1">
                <div className="col-5">Frame End</div>
                <div className="col-7">
                  <input
                    className="form-control"
                    onChange={e =>
                      this.handleInputChange('frameEnd', e.target.value)
                    }
                    type="number"
                    value={frameEnd}
                  />
                </div>
              </div>
            </div>

            <div className="mt-2 p-2 stylish-color">
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
            </div>

            <div className="mt-2 p-2 h-100 stylish-color d-flex flex-column h-100">
              {/* I was able to get scroll working by jamming h-100 to parents of
              this element and following these guidelines:
              https://stackoverflow.com/a/39124696/13183186 */}
              <div className="overflow-auto h-100">
                {frame.map(shapeId => {
                  const shape = shapes[shapeId];
                  return (
                    <ShapeListItem
                      key={shape.id}
                      id={shape.id}
                      onClick={newSelectedShapeId =>
                        this.handleListSelect(newSelectedShapeId)
                      }
                      selectedId={selectedShapeId}
                      type={shape.type}
                    />
                  );
                })}
              </div>
            </div>
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
