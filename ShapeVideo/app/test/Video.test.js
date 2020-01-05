import React from 'react';
import { shallow } from 'enzyme';
import fs from 'fs';
import { remote } from 'electron';
import ShapeVideo from '../ShapeVideo';

let sv = null;
beforeEach(() => {
  sv = shallow(<ShapeVideo />);
});

describe('load', () => {
  it('loads video', () => {
    const path = 'app/test/loads video';
    fs.writeFileSync(path, '');
    remote.dialog.showOpenDialogSync = jest.fn(() => [path]);
    sv.instance().handleLoadVideo();
    expect(sv.state().project.video).toBe(path);
  });

  it('saves loaded video', () => {
    const videoPath = 'app/test/saves loaded video';
    remote.dialog.showOpenDialogSync = jest.fn(() => [videoPath]);
    sv.instance().handleLoadVideo();

    const projectPath = `${videoPath}.sheo`;
    remote.dialog.showSaveDialogSync = jest.fn(() => projectPath);
    sv.instance().handleSaveProject();

    sv.instance().handleNewProject();
    expect(sv.state().project.video).toBe('');

    remote.dialog.showOpenDialogSync = jest.fn(() => [projectPath]);
    sv.instance().handleOpenProject();
    expect(sv.state().project.video).toBe(videoPath);
  });
});

describe('visibility', () => {
  it('toggles visibility', () => {
    expect(sv.state().isVideoVisible).toBe(true);

    sv.instance().handleVideoToggle();
    expect(sv.state().isVideoVisible).toBe(false);

    sv.instance().handleVideoToggle();
    expect(sv.state().isVideoVisible).toBe(true);
  });

  it('sets opacity', () => {
    expect(sv.state().videoOpacity).toBe(1);

    sv.instance().handleVideoOpacity(0.5);
    expect(sv.state().videoOpacity).toBe(0.5);

    sv.instance().handleVideoOpacity(0);
    expect(sv.state().videoOpacity).toBe(0);
  });
});

describe('trackbar', () => {
  it('starts at 0', () => {
    expect(sv.state().videoTime).toBe(0);
  });
});
