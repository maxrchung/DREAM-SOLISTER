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

  getRotateStyling = (position, width) => {
    const styling = {
      transform: `translate(${position.x - width / 2}px,
          ${position.y - width / 2}px)`,
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
      transform: `translate(${position.x - width / 2}px,
        ${position.y - width / 2}px)`,
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
    const { position, width, onTransformChange } = this.props;
    return (
      <>
        <div
          className="position-absolute"
          alt="Select Point"
          style={this.getRotateStyling(position, width * 2.5)}
          role="button"
          tabIndex="-1"
          onMouseDown={() => onTransformChange(TransformType.Rotate)}
        />
        <div
          className="position-absolute"
          alt="Select Point"
          style={this.getScaleStyling(position, width)}
          role="button"
          tabIndex="-1"
          onMouseDown={() => onTransformChange(TransformType.Scale)}
        />
      </>
    );
  }
}
