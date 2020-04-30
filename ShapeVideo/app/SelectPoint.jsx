import React from 'react';
import PropTypes from 'prop-types';
import Victor from 'victor';
import TransformType from './TransformType';

export default class SelectPoint extends React.Component {
  static propTypes = {
    onTransformChange: PropTypes.func.isRequired,
    position: PropTypes.instanceOf(Victor).isRequired,
    width: PropTypes.number.isRequired
  };

  getRotateStyling = (position, width) => {
    const styling = {
      transform: [
        `translate(-50%, -50%)`,
        `translate(${position.x}px, ${position.y}px)`
      ].join(' '),
      width: `${width}px`,
      height: `${width}px`,
      opacity: 0.25,
      backgroundColor: 'blue',
      borderRadius: '50%',
      userSelect: 'none'
    };
    return styling;
  };

  getScaleStyling = (position, width) => {
    const styling = {
      transform: [
        `translate(-50%, -50%)`,
        `translate(${position.x}px, ${position.y}px)`
      ].join(' '),
      width: `${width}px`,
      height: `${width}px`,
      opacity: 0.5,
      backgroundColor: 'red',
      borderRadius: '50%',
      userSelect: 'none'
    };
    return styling;
  };

  render() {
    const { onTransformChange, position, width } = this.props;
    return (
      <>
        <div
          alt="Rotate Point"
          className="position-absolute"
          onMouseDown={() => onTransformChange(TransformType.Rotate)}
          role="presentation"
          style={this.getRotateStyling(position, width)}
        />
        <div
          alt="Scale Point"
          className="position-absolute"
          onMouseDown={() => onTransformChange(TransformType.Scale)}
          role="presentation"
          style={this.getScaleStyling(position, width / 3)}
        />
      </>
    );
  }
}
