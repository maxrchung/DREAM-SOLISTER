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
        currFrameIndex,
        frames,
        mousePosX,
        mousePosY,
        selectedShapeId,
        transformType
      } = this.state;
      const { video } = this;
      const mousePos = new Victor(mousePosX, mousePosY);
      this.handleMouseMove(
        e,
        mousePos,
        selectedShapeId,
        transformType,
        video,
        frames,
        currFrameIndex
      );
    });
    document.addEventListener('mouseup', () =>
      this.handleTransformChange(TransformType.None)
    );
  }

  resetState = () => {
    return {
      areShapesVisible: true,
      // Changing the frames input values wipes out all the current frames, so
      // we want to prevent accidental cases of this destructive operation
      canEditFrames: true,
      currFrameIndex: 0,
      frames: [{}],
      // Frames configuration values are in milliseconds
      framesStart: 0,
      framesDelta: 0,
      framesEnd: 0,
      isNewOpen: false,
      isVideoVisible: true,
      layers: [],
      mousePosX: 0,
      mousePosY: 0,
      projectPath: '',
      selectedShapeId: -1,
      shapesOpacity: 1,
      transformType: TransformType.None,
      videoOpacity: 1,
      videoTime: 0,
      videoPath: '',
      shapeCount: 0
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
              const { videoTime } = this.state;
              const { video } = this;
              this.handlePlayVideo(video, videoTime);
            }
          },
          {
            label: 'Restart',
            accelerator: 'X',
            click: () => {
              const { framesStart } = this.state;
              const { video } = this;
              this.handleRestartVideo(video, framesStart);
            }
          }
        ]
      },
      {
        label: 'Frames',
        submenu: [
          {
            label: 'Create Next',
            accelerator: 'CmdOrCtrl+Right',
            click: () => {
              const {
                frames,
                framesStart,
                framesDelta,
                framesEnd
              } = this.state;
              this.handleCreateNextFrame(
                frames,
                framesStart,
                framesDelta,
                framesEnd
              );
            }
          },
          {
            label: 'Next',
            accelerator: 'Right',
            click: () => {
              const {
                currFrameIndex,
                frames,
                framesStart,
                framesDelta
              } = this.state;
              this.handleNextFrame(
                frames,
                currFrameIndex,
                framesStart,
                framesDelta
              );
            }
          },
          {
            label: 'Previous',
            accelerator: 'Left',
            click: () => {
              const {
                currFrameIndex,
                frames,
                framesStart,
                framesDelta
              } = this.state;
              this.handlePreviousFrame(
                frames,
                currFrameIndex,
                framesStart,
                framesDelta
              );
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
              this.handleAddShape(ShapeType.Rectangle);
            }
          },
          {
            label: 'Add Triangle',
            accelerator: '2',
            click: () => {
              this.handleAddShape(ShapeType.Triangle);
            }
          },
          {
            label: 'Add Circle',
            accelerator: '3',
            click: () => {
              this.handleAddShape(ShapeType.Circle);
            }
          },
          {
            label: 'Add Semicircle',
            accelerator: '4',
            click: () => {
              this.handleAddShape(ShapeType.Semicircle);
            }
          },
          {
            label: 'Get Color',
            accelerator: 'E',
            click: () => {
              const {
                currFrameIndex,
                frames,
                mousePosX,
                mousePosY,
                selectedShapeId
              } = this.state;
              const { canvas, video } = this;
              const mousePos = new Victor(mousePosX, mousePosY);
              this.handleGetColor(
                mousePos,
                selectedShapeId,
                canvas,
                video,
                frames,
                currFrameIndex
              );
            }
          },
          {
            label: 'Paste',
            accelerator: 'V',
            click: () => {
              const {
                currFrameIndex,
                frames,
                mousePosX,
                mousePosY,
                selectedShapeId,
                shapeCount,
                layers
              } = this.state;
              const { video } = this;
              const mousePos = new Victor(mousePosX, mousePosY);
              this.handlePasteShape(
                mousePos,
                video,
                selectedShapeId,
                shapeCount,
                layers,
                frames,
                currFrameIndex
              );
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
              const { currFrameIndex, frames, selectedShapeId } = this.state;
              this.handleDeleteShape(selectedShapeId, frames, currFrameIndex);
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
              const { selectedShapeId, layers } = this.state;
              this.handleLayerUp(selectedShapeId, layers);
            }
          },
          {
            label: 'Move Down',
            accelerator: 'S',
            click: () => {
              const { selectedShapeId, layers } = this.state;
              this.handleLayerDown(selectedShapeId, layers);
            }
          },
          {
            label: 'Move Top',
            accelerator: 'D',
            click: () => {
              const { selectedShapeId, layers } = this.state;
              this.handleLayerTop(selectedShapeId, layers);
            }
          },
          {
            label: 'Move Bottom',
            accelerator: 'F',
            click: () => {
              const { selectedShapeId, layers } = this.state;
              this.handleLayerBottom(selectedShapeId, layers);
            }
          }
        ]
      }
    ];
    const template = remote.Menu.buildFromTemplate(menuTemplate);
    remote.Menu.setApplicationMenu(template);
  };

  handleResize = () => this.forceUpdate();

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

  handleMouseMove = (
    e,
    oldMousePos,
    selectedShapeId,
    transformType,
    video,
    frames,
    currFrameIndex
  ) => {
    const frame = frames[currFrameIndex];
    const newMousePos = new Victor(e.clientX, e.clientY);
    if (e.buttons === 1 && selectedShapeId >= 0) {
      const shape = { ...frame[selectedShapeId] };
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

      const newFrames = [...frames];
      newFrames[currFrameIndex][selectedShapeId] = shape;
      this.setState({
        frames: newFrames
      });
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
    if (projectPath && !needsDialog) {
      const serialized = JSON.stringify(state);
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
        projectPath: newPath,
        canEditFrames: false
      };
      this.setState(newState, () => {
        const serialized = JSON.stringify(this.state);
        fs.writeFileSync(newPath, serialized);
      });
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

  handleFormatVideoTime = (video, videoTime) => {
    const timeInSeconds = this.isVideoReady(video)
      ? videoTime * video.duration
      : 0;

    return this.formatVideoTimeInSeconds(timeInSeconds);
  };

  handlePlayVideo = (video, videoTime) => {
    if (!this.isVideoReady(video)) {
      return;
    }
    if (video.paused) {
      // We set the current time when playing to handle a case of playing video
      // after opening an existing project
      const timeInSeconds = videoTime * video.duration;
      this.video.currentTime = timeInSeconds;
      this.video.play();
    } else {
      this.video.pause();
    }
  };

  handleRestartVideo = (video, framesStart) => {
    if (!this.isVideoReady(video)) {
      return;
    }
    this.video.currentTime = framesStart / 1000;
  };

  handleVideoTimeUpdate = (video, frames, framesStart, framesDelta) => {
    if (!this.isVideoReady(video)) {
      return;
    }
    const currentTime = video.currentTime * 1000;
    const start = Number.parseFloat(framesStart);
    const delta = Number.parseFloat(framesDelta);
    let currFrameIndex = 0;
    while (currFrameIndex < frames.length - 1) {
      if (currentTime < start + (currFrameIndex + 1) * delta) {
        break;
      }
      currFrameIndex += 1;
    }

    const fraction = video.currentTime / video.duration;
    this.setState({
      videoTime: fraction,
      currFrameIndex
    });
  };

  handleFramesInput = (prop, value) => {
    this.setState(
      {
        [prop]: value,
        currFrameIndex: 0,
        frames: [{}],
        layers: []
      },
      () => {
        const { video } = this;
        if (!this.isVideoReady(video)) {
          return;
        }

        const { framesStart } = this.state;
        const start = Number.parseFloat(framesStart / 1000, 10);
        video.currentTime = Number.isNaN(start) || start < 0 ? 0 : start;
      }
    );
  };

  handleEditFrameToggle = () => {
    this.setState(prev => ({
      canEditFrames: !prev.canEditFrames
    }));
  };

  setFrameTime = (start, delta, currFrameIndex) => {
    const timeInSeconds = start / 1000 + (currFrameIndex * delta) / 1000;
    this.video.currentTime = timeInSeconds;
  };

  handleCreateNextFrame = (frames, framesStart, framesDelta, framesEnd) => {
    const start = Number.parseInt(framesStart, 10);
    const delta = Number.parseInt(framesDelta, 10);
    const end = Number.parseInt(framesEnd, 10);
    if (
      Number.isNaN(start) ||
      Number.isNaN(delta) ||
      Number.isNaN(end) ||
      start < 0 ||
      delta < 1 ||
      end <= start ||
      start + frames.length * delta > end
    ) {
      return;
    }

    const newFrame = { ...frames[frames.length - 1] };
    this.setState({
      currFrameIndex: frames.length,
      frames: [...frames, newFrame]
    });

    this.setFrameTime(start, delta, frames.length);
  };

  handleNextFrame = (frames, currFrameIndex, framesStart, framesDelta) => {
    const nextIndex =
      currFrameIndex === frames.length - 1
        ? frames.length - 1
        : currFrameIndex + 1;

    const start = Number.parseInt(framesStart, 10);
    const delta = Number.parseInt(framesDelta, 10);
    this.setFrameTime(start, delta, nextIndex);
  };

  handlePreviousFrame = (frames, currFrameIndex, framesStart, framesDelta) => {
    const prevIndex = currFrameIndex === 0 ? 0 : currFrameIndex - 1;
    const start = Number.parseInt(framesStart, 10);
    const delta = Number.parseInt(framesDelta, 10);
    this.setFrameTime(start, delta, prevIndex);
  };

  handleAddShape = type => {
    const { video } = this;

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

    const {
      currFrameIndex,
      frames,
      mousePosX,
      mousePosY,
      layers,
      selectedShapeId,
      shapeCount
    } = this.state;
    const mousePos = new Victor(mousePosX, mousePosY);
    const position = this.mousePosToPosition(mousePos, video);

    const newFrames = [...frames];
    newFrames[currFrameIndex][shapeCount] = {
      colorR: 255,
      colorG: 255,
      colorB: 255,
      id: shapeCount,
      positionX: position.x,
      positionY: position.y,
      rotation: 0,
      scaleX: 1,
      scaleY: 1,
      type
    };

    let newLayers;
    if (selectedShapeId === -1) {
      newLayers = [...layers, shapeCount];
    } else {
      const selectedIndex = layers.findIndex(id => id === selectedShapeId);
      newLayers = [
        ...layers.slice(0, selectedIndex + 1),
        shapeCount,
        ...layers.slice(selectedIndex + 1)
      ];
    }

    this.setState(
      {
        layers: newLayers,
        selectedShapeId: shapeCount,
        frames: newFrames,
        shapeCount: shapeCount + 1
      },
      () => {
        const { selectedShapeId: newSelectedShapeId } = this.state;
        this.scrollShapeIntoView(newSelectedShapeId);
      }
    );
  };

  handleGetColor = (
    mousePos,
    selectedShapeId,
    canvas,
    video,
    frames,
    currFrameIndex
  ) => {
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
      const [colorR, colorG, colorB] = data;

      const newFrames = [...frames];
      const newShape = newFrames[currFrameIndex][selectedShapeId];
      newShape.colorR = colorR;
      newShape.colorG = colorG;
      newShape.colorB = colorB;
      this.setState({
        frames: newFrames
      });
    }
  };

  handlePasteShape = (
    mousePos,
    video,
    selectedShapeId,
    shapeCount,
    layers,
    frames,
    currFrameIndex
  ) => {
    if (!video || selectedShapeId < 0) {
      return;
    }

    const position = this.mousePosToPosition(mousePos, video);
    const newFrames = [...frames];
    const shape = newFrames[currFrameIndex][selectedShapeId];
    newFrames[currFrameIndex][shapeCount] = {
      colorR: shape.colorR,
      colorG: shape.colorG,
      colorB: shape.colorB,
      id: shapeCount,
      positionX: position.x,
      positionY: position.y,
      rotation: shape.rotation,
      scaleX: shape.scaleX,
      scaleY: shape.scaleY,
      type: shape.type
    };

    this.setState(
      {
        layers: [...layers, shapeCount],
        selectedShapeId: shapeCount,
        frames: newFrames,
        shapeCount: shapeCount + 1
      },
      () => {
        const { selectedShapeId: newSelectedShapeId } = this.state;
        this.scrollShapeIntoView(newSelectedShapeId);
      }
    );
  };

  scrollShapeIntoView = shapeId => {
    document.getElementById(`shape-list-item-${shapeId}`).scrollIntoView();
  };

  handleSelectShape = (selectedShapeId, newSelectedShapeId) => {
    if (selectedShapeId >= 0) {
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

  handleDeselectShape = () => {
    this.setState({
      selectedShapeId: -1
    });
  };

  handleDeleteShape = (selectedShapeId, frames, currFrameIndex) => {
    if (selectedShapeId < 0) {
      return;
    }
    const newFrames = [...frames];
    delete newFrames[currFrameIndex][selectedShapeId];
    this.setState(prev => ({
      frames: newFrames,
      layers: prev.layers.filter(shapeId => shapeId !== selectedShapeId),
      selectedShapeId: -1
    }));
  };

  handleLayerUp = (selectedShapeId, layers) => {
    if (selectedShapeId < 0) {
      return;
    }
    const index = layers.findIndex(id => id === selectedShapeId);
    if (index === 0) {
      return;
    }
    const newLayers = [...layers];
    newLayers[index] = newLayers[index - 1];
    newLayers[index - 1] = selectedShapeId;
    this.setState({
      layers: newLayers
    });
  };

  handleLayerDown = (selectedShapeId, layers) => {
    if (selectedShapeId < 0) {
      return;
    }
    const index = layers.findIndex(id => id === selectedShapeId);
    if (index === layers.length - 1) {
      return;
    }
    const newLayers = [...layers];
    newLayers[index] = newLayers[index + 1];
    newLayers[index + 1] = selectedShapeId;
    this.setState({
      layers: newLayers
    });
  };

  handleLayerTop = (selectedShapeId, layers) => {
    if (selectedShapeId < 0) {
      return;
    }
    if (layers[0] === selectedShapeId) {
      return;
    }
    const newLayers = [
      selectedShapeId,
      ...layers.filter(id => id !== selectedShapeId)
    ];
    this.setState({
      layers: newLayers
    });
  };

  handleLayerBottom = (selectedShapeId, layers) => {
    if (selectedShapeId < 0) {
      return;
    }
    if (layers[layers.length - 1] === selectedShapeId) {
      return;
    }
    const newLayers = [
      ...layers.filter(id => id !== selectedShapeId),
      selectedShapeId
    ];
    this.setState({
      layers: newLayers
    });
  };

  render() {
    const {
      areShapesVisible,
      canEditFrames,
      currFrameIndex,
      frames,
      framesStart,
      framesDelta,
      framesEnd,
      isNewOpen,
      isVideoVisible,
      layers,
      selectedShapeId,
      shapesOpacity,
      videoOpacity,
      videoPath,
      videoTime
    } = this.state;
    const { video } = this;
    const frame = frames[currFrameIndex];

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
              onTimeUpdate={() =>
                this.handleVideoTimeUpdate(
                  video,
                  frames,
                  framesStart,
                  framesDelta
                )
              }
            >
              <track kind="captions" label="DREAM SOLISTER" />
            </video>

            {areShapesVisible && (
              <div
                className="position-absolute"
                style={{ opacity: shapesOpacity }}
              >
                {layers.map(shapeId => {
                  const shape = frame[shapeId];
                  // It's possible that layer may contain a shape that's not in
                  // the current frame
                  if (shape === undefined) {
                    return;
                  }
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
              <div className="form-row">
                <div className="col-12">
                  <CheckLabel
                    checked={canEditFrames}
                    label="Allow Editing of Frames Configuration"
                    name="chk-edit-frame"
                    onChange={this.handleEditFrameToggle}
                  />
                </div>
              </div>

              <div className="form-row align-items-center">
                <div className="col-5">Frames Start</div>
                <div className="col-7">
                  <input
                    className="form-control"
                    disabled={!canEditFrames}
                    onChange={e =>
                      this.handleFramesInput('framesStart', e.target.value)
                    }
                    type="number"
                    value={framesStart}
                  />
                </div>
              </div>

              <div className="form-row align-items-center mt-1">
                <div className="col-5">Frames Delta</div>
                <div className="col-7">
                  <input
                    className="form-control"
                    disabled={!canEditFrames}
                    onChange={e =>
                      this.handleFramesInput('framesDelta', e.target.value)
                    }
                    type="number"
                    value={framesDelta}
                  />
                </div>
              </div>

              <div className="form-row align-items-center mt-1">
                <div className="col-5">Frames End</div>
                <div className="col-7">
                  <input
                    className="form-control"
                    disabled={!canEditFrames}
                    onChange={e =>
                      this.handleFramesInput('framesEnd', e.target.value)
                    }
                    type="number"
                    value={framesEnd}
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
                {layers.map(shapeId => {
                  const shape = frame[shapeId];
                  if (shape === undefined) {
                    return (
                      <div
                        alt="List Item"
                        className="px-2 py-1"
                        role="presentation"
                      >
                        {shapeId}
                      </div>
                    );
                  }
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
