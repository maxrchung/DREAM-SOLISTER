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
  it('seeks video', () => {
    expect(sv.state().videoTime).toBe(0);

    sv.instance().handleSeekVideo(0.5);
    expect(sv.state().videoTime).toBe(0.5);

    sv.instance().handleSeekVideo(1);
    expect(sv.state().videoTime).toBe(1);
  });

  it('formats time', () => {
    expect(sv.instance().formatVideoTimeInSeconds(0)).toBe('00:00:000');
    expect(sv.instance().formatVideoTimeInSeconds(600)).toBe('10:00:000');
    expect(sv.instance().formatVideoTimeInSeconds(60)).toBe('01:00:000');
    expect(sv.instance().formatVideoTimeInSeconds(10)).toBe('00:10:000');
    expect(sv.instance().formatVideoTimeInSeconds(1)).toBe('00:01:000');
    expect(sv.instance().formatVideoTimeInSeconds(0.1)).toBe('00:00:100');
    expect(sv.instance().formatVideoTimeInSeconds(0.01)).toBe('00:00:010');
    expect(sv.instance().formatVideoTimeInSeconds(0.001)).toBe('00:00:001');
    expect(sv.instance().formatVideoTimeInSeconds(671.111)).toBe('11:11:111');
  });
});
