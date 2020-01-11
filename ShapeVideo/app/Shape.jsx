import React from 'react';
import PropTypes from 'prop-types';
import Victor from 'victor';
import ShapeType from './ShapeType';

export default class Shape extends React.Component {
  static propTypes = {
    type: PropTypes.string,
    videoRef: PropTypes.instanceOf(HTMLVideoElement),
    position: PropTypes.instanceOf(Victor)
  };

  static defaultProps = {
    type: ShapeType.None,
    videoRef: null,
    position: new Victor()
  };

  getSrcPath = () => {
    const { type } = this.props;
    const path = type === ShapeType.None ? '' : `assets/${type}.png`;
    return path;
  };

  getStyling = () => {
    const { videoRef, position } = this.props;
    const styling = {
      left: videoRef ? videoRef.clientWidth / 2 + position.x : position.x,
      top: videoRef ? videoRef.clientHeight / 2 + position.y : position.y
    };
    return styling;
  };

  render() {
    const { type } = this.props;
    return (
      <img
        className="position-absolute"
        alt={type}
        src={this.getSrcPath()}
        style={this.getStyling()}
      />
    );
  }
}
