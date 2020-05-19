const fs = require('fs');

const doubleFrameRate = path => {
  const input = fs.readFileSync(path);

  const state = { ...JSON.parse(input) };

  // Halve delta
  state.framesDelta /= 2;

  // Double frame rate
  const newFrames = [];
  state.frames.forEach(frame => {
    newFrames.push(frame);
    newFrames.push(frame);
  });
  state.frames = newFrames;

  const output = JSON.stringify(state);
  fs.writeFileSync(path, output);
};

const path =
  'C:\\Users\\Wax Chug da Gwad\\Desktop\\DREAMSOLISTER\\DREAMSOLISTER\\DREAMSOLISTER\\guitarSolo.sheo';
doubleFrameRate(path);
