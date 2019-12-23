export default class Project {
  constructor(name = '', videoFilePath = '', frames = []) {
    this.name = name;
    this.videoFilePath = videoFilePath;
    this.frames = frames;
  }
}
