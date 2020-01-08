import React from 'react';
import PropTypes from 'prop-types';
import {
  MDBBtn,
  MDBModal,
  MDBModalBody,
  MDBModalHeader,
  MDBModalFooter
} from 'mdbreact';

export default class NewModal extends React.Component {
  static propTypes = {
    isNewOpen: PropTypes.bool.isRequired,
    onNewToggle: PropTypes.func.isRequired,
    onNewProject: PropTypes.func.isRequired
  };

  render() {
    const { isNewOpen, onNewToggle, onNewProject } = this.props;

    return (
      <MDBModal isOpen={isNewOpen} toggle={onNewToggle}>
        <MDBModalHeader toggle={onNewToggle}>New Project</MDBModalHeader>
        <MDBModalBody>
          Are you sure you want to start a new project? Existing changes will be
          lost.
        </MDBModalBody>
        <MDBModalFooter>
          <MDBBtn onClick={onNewProject}>OK</MDBBtn>
          <MDBBtn onClick={onNewToggle}>Cancel</MDBBtn>
        </MDBModalFooter>
      </MDBModal>
    );
  }
}
