import { remote } from 'electron';
import fs from 'fs';
import React from 'react';
import { MDBContainer, MDBBtn } from 'mdbreact';
import Project from './Project';
import NewModal from './NewModal';

export default class ShapeVideo extends React.Component {
  constructor(props) {
    super(props);

    this.state = {
      isNewOpen: false,
      project: new Project()
    };
  }

  componentDidMount() {
    document.addEventListener('keydown', this.handleKeyDown);
  }

  componentWillUnmount() {
    document.removeEventListener('keydown', this.handleKeyDown);
  }

  static dialogOptions = {
    filters: [
      { name: 'ShapeVideo (.sheo)', extensions: ['sheo'] },
      { name: 'All Files (*)', extensions: ['*'] }
    ],
    properties: ['openFile', 'showHiddenFiles', 'createDirectory']
  };

  // To handle both Windows and Apple shortcuts, we'll allow both ctrl and meta
  hasSpecialKey = e => {
    return e.ctrlKey || e.metaKey;
  };

  handleKeyDown = e => {
    switch (e.key) {
      case 'n':
        if (this.hasSpecialKey(e)) {
          this.handleNewToggle(e, true);
        }
        break;
      case 's':
        if (this.hasSpecialKey(e)) {
          this.handleSaveProject();
        }
        break;
      case 'o':
        if (this.hasSpecialKey(e)) {
          this.handleOpenProject();
        }
        break;
      default:
        break;
    }
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

  handleOpenProject = () => {
    const path = remote.dialog.showOpenDialogSync(ShapeVideo.dialogOptions);
    if (path[0]) {
      const serialized = fs.readFileSync(path);
      const project = JSON.parse(serialized);
      this.setState({
        project
      });
    }
  };

  handleSaveProject = needsDialog => {
    const { project } = this.state;

    let serialized = '';
    let path = project.name;
    if (!path || needsDialog) {
      path = remote.dialog.showSaveDialogSync(ShapeVideo.dialogOptions);
      // If no path is picked, then don't proceed with save
      if (!path) {
        return;
      }

      // To be semantically correct, we want a Project instance, not a generic object
      const newProject = Object.assign(new Project(), {
        ...project,
        name: path
      });
      this.setState({
        project: newProject
      });
      serialized = JSON.stringify(newProject);
    } else {
      serialized = JSON.stringify(project);
    }
    fs.writeFileSync(path, serialized);
  };

  render() {
    const { isNewOpen, project } = this.state;

    return (
      <MDBContainer>
        <MDBBtn onClick={this.handleNewToggle}>New</MDBBtn>
        <NewModal
          isNewOpen={isNewOpen}
          onNewToggle={this.handleNewToggle}
          onNewProject={this.handleNewProject}
        />

        <MDBBtn onClick={() => this.handleSaveProject(false)}>Save</MDBBtn>
        <MDBBtn onClick={() => this.handleSaveProject(true)}>Save As</MDBBtn>

        <MDBBtn onClick={this.handleOpenProject}>Open</MDBBtn>

        <h5>Project</h5>
        <ul>
          <li>Name: {project.name}</li>
          <li>Video: {project.videoFilePath}</li>
        </ul>
      </MDBContainer>
    );
  }
}
