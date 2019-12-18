export default class Project {
  constructor(frames = [], name = '', videoFilePath = '') {
    this.frames = frames;
    this.name = name;
    this.videoFilePath = videoFilePath;
  }
}
