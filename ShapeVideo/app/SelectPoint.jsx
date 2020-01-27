import React from 'react';
import PropTypes from 'prop-types';
import Victor from 'victor';

export default class SelectPoint extends React.Component {
  static propTypes = {
    position: PropTypes.instanceOf(Victor).isRequired,
    width: PropTypes.number.isRequired
  };

  getStyling = (position, width) => {
    const styling = {
      transform: `translate(${position.x}px, ${position.y}px)`,
      width: `${width}px`,
      height: `${width}px`,
      opacity: 0.5,
      backgroundColor: 'red',
      borderRadius: '50%'
    };
    return styling;
  };

  render() {
    const { position, width } = this.props;
    return (
      <div
        className="position-absolute"
        alt="Select Point"
        src="assets/Circle.png"
        style={this.getStyling(position, width)}
      />
    );
  }
}
