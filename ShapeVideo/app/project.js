export default class Project {
  constructor(name = '', video = '', frames = []) {
    this.name = name;
    this.video = video;
    this.frames = frames;
    this.shapeCount = 0;
  }
}
