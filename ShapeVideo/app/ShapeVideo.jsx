import React from 'react';
import {
  MDBContainer,
  MDBBtn,
  MDBModal,
  MDBModalBody,
  MDBModalHeader,
  MDBModalFooter
} from 'mdbreact';
import Project from './project';

export default class ShapeVideo extends React.Component {
  constructor(props) {
    super(props);

    this.state = {
      isConfirmOpen: false,
      project: new Project()
    };
  }

  componentDidMount() {
    document.addEventListener('keydown', this.handleKeyDown);
  }

  componentWillUnmount() {
    document.removeEventListener('keydown', this.handleKeyDown);
  }

  handleKeyDown = e => {
    switch (e.key) {
      case 'n':
        if (e.ctrlKey) {
          this.handleConfirmToggle(e, true);
        }
        break;
      default:
        break;
    }
  };

  handleConfirmToggle = (_, isConfirmOpen) => {
    this.setState(state => ({
      isConfirmOpen:
        isConfirmOpen === undefined ? !state.isConfirmOpen : isConfirmOpen
    }));
  };

  handleNewProject = () => {
    this.setState(state => ({
      isConfirmOpen: !state.isConfirmOpen,
      project: new Project()
    }));
  };

  render() {
    const { isConfirmOpen, project } = this.state;

    return (
      <MDBContainer>
        <MDBBtn onClick={this.handleConfirmToggle}>New</MDBBtn>
        <MDBModal isOpen={isConfirmOpen} toggle={this.handleConfirmToggle}>
          <MDBModalHeader toggle={this.handleConfirmToggle}>
            New Project
          </MDBModalHeader>
          <MDBModalBody>
            Are you sure you want to start a new project? Existing changes will
            be lost.
          </MDBModalBody>
          <MDBModalFooter>
            <MDBBtn onClick={this.handleNewProject}>OK</MDBBtn>
            <MDBBtn onClick={this.handleConfirmToggle}>Cancel</MDBBtn>
          </MDBModalFooter>
        </MDBModal>

        <h5>Project</h5>
        <ul>
          <li>Name: {project.name}</li>
          <li>Video: {project.videoFilePath}</li>
        </ul>
      </MDBContainer>
    );
  }
}
