import React from 'react';
import { shallow } from 'enzyme';
import fs from 'fs';
// Note that Jest does not have access to Electron modules
// remote is mocked in /inernals/mocks/electronMock.js
import { remote } from 'electron';
import ShapeVideo from '../ShapeVideo';
import Project from '../Project';

let sv = null;
beforeEach(() => {
  sv = shallow(<ShapeVideo />);
});

describe('new', () => {
  it('toggles new with handleNewToggle', () => {
    expect(sv.state().isNewOpen).toBe(false);
    sv.instance().handleNewToggle();
    expect(sv.state().isNewOpen).toBe(true);
    sv.instance().handleNewToggle();
    expect(sv.state().isNewOpen).toBe(false);
    sv.instance().handleNewToggle();
    expect(sv.state().isNewOpen).toBe(true);
  });

  it('resets project values on new', () => {
    sv.instance().handleNewProject();
    expect(sv.state().project).toMatchObject({
      frames: [],
      name: '',
      video: ''
    });
  });
});

describe('save', () => {
  it('requests file name for saving new project', () => {
    sv.instance().handleNewProject();
    const path = 'app/test/requests file name for saving new project';
    remote.dialog.showSaveDialogSync = jest.fn(() => path);
    sv.instance().handleSaveProject(false);
    expect(remote.dialog.showSaveDialogSync).toBeCalledTimes(1);

    const project = JSON.parse(fs.readFileSync(path));
    expect(project).toMatchObject({
      frames: [],
      name: path,
      video: ''
    });
  });

  it('autosaves if project name is set', () => {
    const path = 'app/test/autosaves if project name is set';
    sv.setState({
      project: new Project(path)
    });
    remote.dialog.showSaveDialogSync = jest.fn(() => path);
    sv.instance().handleSaveProject(false);
    expect(remote.dialog.showSaveDialogSync).toBeCalledTimes(0);

    const project = JSON.parse(fs.readFileSync(path));
    expect(project).toMatchObject({
      frames: [],
      name: path,
      video: ''
    });
  });
});

describe('save as', () => {
  it('opens save dialog even when project name is set', () => {
    const path = 'app/test/autosaves if project name is set';
    sv.setState({
      project: new Project(path)
    });
    remote.dialog.showSaveDialogSync = jest.fn(() => path);
    sv.instance().handleSaveProject(true);
    expect(remote.dialog.showSaveDialogSync).toBeCalledTimes(1);

    const project = JSON.parse(fs.readFileSync(path));
    expect(project).toMatchObject({
      frames: [],
      name: path,
      video: ''
    });
  });
});

describe('open', () => {
  it('opens and overwrites project', () => {
    const path = 'app/test/autosaves if project name is set';
    const project = new Project(path);
    const serialized = JSON.stringify(project);
    fs.writeFileSync(path, serialized);
    remote.dialog.showOpenDialogSync = jest.fn(() => [path]);
    sv.instance().handleOpenProject();
    expect(remote.dialog.showOpenDialogSync).toBeCalledTimes(1);
    expect(sv.state().project.name).toBe(path);
  });
});
