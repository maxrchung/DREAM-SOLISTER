import React from 'react';
import PropTypes from 'prop-types';
import Victor from 'victor';
import ShapeType from './ShapeType';

export default class Shape extends React.Component {
  static propTypes = {
    type: PropTypes.string,
    video: PropTypes.instanceOf(HTMLVideoElement),
    position: PropTypes.instanceOf(Victor)
  };

  static defaultProps = {
    type: ShapeType.None,
    video: null,
    position: new Victor()
  };

  getSrcPath = () => {
    const { type } = this.props;
    const path = type === ShapeType.None ? '' : `assets/${type}.png`;
    return path;
  };

  getStyling = () => {
    const { video, position } = this.props;
    const videoScale = video.clientHeight / 2;
    const newPosition = new Victor(
      video.clientWidth / 2 + position.x * videoScale,
      video.clientHeight / 2 + position.y * videoScale
    );

    const styling = {
      transform: `translate(${newPosition.x}px, ${newPosition.y}px)`
    };

    return styling;
  };

  render() {
    const { type, video } = this.props;
    return (
      video && (
        <img alt={type} src={this.getSrcPath()} style={this.getStyling()} />
      )
    );
  }
}
