import { remote } from 'electron';
import fs from 'fs';
import React from 'react';
import Project from './Project';
import NewModal from './NewModal';
import Slider from './Slider';
import CheckLabel from './CheckLabel';

export default class ShapeVideo extends React.Component {
  constructor(props) {
    super(props);

    this.setMenu();

    this.state = {
      isNewOpen: false,
      project: new Project(),
      isVideoVisible: true,
      videoOpacity: 1,
      videoTime: 0
    };
  }

  setMenu = () => {
    const isMac = remote.process.platform === 'darwin';
    const menuTemplate = [
      isMac
        ? {
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
        : {},
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
      }
    ];
    const template = remote.Menu.buildFromTemplate(menuTemplate);
    remote.Menu.setApplicationMenu(template);
  };

  // To handle both Windows and Apple shortcuts, we'll allow both ctrl and meta
  hasSpecialKey = e => {
    return e.ctrlKey || e.metaKey;
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

      // To be semantically correct, we want a Project instance, not a generic object
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

  render() {
    const {
      isNewOpen,
      project,
      isVideoVisible,
      videoOpacity,
      videoTime
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
            {isVideoVisible && (
              <video
                className="w-100"
                ref={element => {
                  this.video = element;
                }}
                src={project.video}
                style={{ opacity: videoOpacity }}
                onTimeUpdate={this.handleVideoTimeUpdate}
              >
                <track kind="captions" label="DREAM SOLISTER" />
              </video>
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
                  <div className="form-check">
                    <label className="form-check-label" htmlFor="chk-shapes">
                      <input
                        className="form-check-input"
                        type="checkbox"
                        id="chk-shapes"
                      />
                      Shapes
                    </label>
                  </div>
                </div>

                <div className="col-7">
                  <input type="range" className="custom-range" />
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
