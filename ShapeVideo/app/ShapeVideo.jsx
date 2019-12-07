import React from 'react';
import {
  MDBContainer,
  MDBBtn,
  MDBModal,
  MDBModalBody,
  MDBModalHeader,
  MDBModalFooter
} from 'mdbreact';

export default class ShapeVideo extends React.Component {
  constructor(props) {
    super(props);

    this.state = {
      isConfirmOpen: true
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
          console.log('New');
        }
        break;
      default:
        break;
    }
  };

  handleConfirmToggle = () => {
    const { isConfirmOpen } = this.state;
    this.setState({
      isConfirmOpen
    });
  };

  render() {
    const { isConfirmOpen } = this.state;

    return (
      <MDBContainer>
        <MDBBtn onClick={this.toggle}>Modal</MDBBtn>
        <MDBModal isOpen={isConfirmOpen} toggle={this.handleConfirmToggle}>
          <MDBModalHeader toggle={this.toggle}>MDBModal title</MDBModalHeader>
          <MDBModalBody>Hello there</MDBModalBody>
          <MDBModalFooter>
            <MDBBtn color="secondary" onClick={this.toggle}>
              Close
            </MDBBtn>
            <MDBBtn color="primary">Save changes</MDBBtn>
          </MDBModalFooter>
        </MDBModal>
      </MDBContainer>
    );
  }
}
