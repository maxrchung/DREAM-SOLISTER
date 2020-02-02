import React from 'react';
import PropTypes from 'prop-types';
import Victor from 'victor';
import TransformType from './TransformType';

export default class SelectPoint extends React.Component {
  static propTypes = {
    position: PropTypes.instanceOf(Victor).isRequired,
    width: PropTypes.number.isRequired,
    onTransformChange: PropTypes.func.isRequired
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
    const { position, width, onTransformChange } = this.props;
    return (
      <div
        className="position-absolute"
        alt="Select Point"
        style={this.getStyling(position, width)}
        role="button"
        tabIndex="-1"
        onMouseDown={() => onTransformChange(TransformType.Scale)}
      />
    );
  }
}
