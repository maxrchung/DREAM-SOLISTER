import React from 'react';
import PropTypes from 'prop-types';
import Victor from 'victor';

export default class SelectPoint extends React.Component {
  static propTypes = {
    position: PropTypes.instanceOf(Victor).isRequired,
    width: PropTypes.number.isRequired
  };

  getStyling = position => {
    const styling = {
      transform: `translate(${position.x}px, ${position.y}px)`,
      transformOrigin: 'top left'
    };
    return styling;
  };

  render() {
    const { position, width } = this.props;
    return (
      <img
        className="position-absolute"
        alt="Select Point"
        width={width}
        src="assets/Circle.png"
        style={this.getStyling(position)}
      />
    );
  }
}
