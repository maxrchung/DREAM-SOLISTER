import React from 'react';
import PropTypes from 'prop-types';
import Victor from 'victor';
import ShapeType from './ShapeType';

export default class Shape extends React.Component {
  static propTypes = {
    type: PropTypes.string,
    video: PropTypes.instanceOf(HTMLVideoElement),
    position: PropTypes.instanceOf(Victor),
    rotation: PropTypes.number,
    scale: PropTypes.instanceOf(Victor)
  };

  static defaultProps = {
    type: ShapeType.None,
    video: null,
    position: new Victor(),
    rotation: 0,
    scale: new Victor(1, 1)
  };

  getSrcPath = () => {
    const { type } = this.props;
    const path = type === ShapeType.None ? '' : `assets/${type}.png`;
    return path;
  };

  getLayout = () => {
    const { video, position, scale } = this.props;
    const imageWidth = 102;
    const sbWidth = 853.33;
    const sbScale = imageWidth / sbWidth;

    const videoWidth = video.clientWidth;
    const videoHalfWidth = videoWidth / 2;
    const videoHalfHeight = video.clientHeight / 2;
    const videoScale = sbScale * videoWidth;

    const imageScale = new Victor()
      .copy(scale)
      .multiply(new Victor(videoScale / imageWidth, videoScale / imageWidth));
    const imageSize = new Victor()
      .copy(imageScale)
      .multiply(new Victor(imageWidth, imageWidth));
    const imageHalfSize = new Victor()
      .copy(imageSize)
      .multiply(new Victor(0.5, 0.5));

    const newPosition = new Victor(
      Math.round(
        videoHalfWidth + position.x * videoHalfWidth - imageHalfSize.x
      ),
      Math.round(
        videoHalfHeight + position.y * videoHalfWidth - imageHalfSize.y
      )
    );

    const styling = {
      transform: [
        `translate(${newPosition.x}px, ${newPosition.y}px)`,
        `scale(${imageScale.x}, ${imageScale.y})`
      ].join(' '),
      transformOrigin: 'top left'
    };

    return styling;
  };

  getRotation = () => {
    const { rotation } = this.props;
    const styling = {
      transform: `rotate(${rotation}rad)`
    };
    return styling;
  };

  render() {
    const { type, video } = this.props;
    return (
      video && (
        // Mega brain: https://stackoverflow.com/a/8963136
        <div style={this.getLayout()}>
          <img alt={type} src={this.getSrcPath()} style={this.getRotation()} />
        </div>
      )
    );
  }
}
