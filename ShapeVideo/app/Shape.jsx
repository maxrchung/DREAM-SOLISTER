import React from 'react';
import PropTypes from 'prop-types';
import Victor from 'victor';
import ShapeType from './ShapeType';
import SelectPoint from './SelectPoint';

export default class Shape extends React.Component {
  static propTypes = {
    type: PropTypes.string,
    video: PropTypes.instanceOf(HTMLVideoElement),
    position: PropTypes.instanceOf(Victor),
    rotation: PropTypes.number,
    scale: PropTypes.instanceOf(Victor),
    id: PropTypes.number.isRequired,
    selectedId: PropTypes.number.isRequired,
    onClick: PropTypes.func.isRequired
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

  getCalculations = (video, position, scale, rotation) => {
    const imageWidth = 102;
    const sbWidth = 853.33;
    const sbScale = imageWidth / sbWidth;

    const videoWidth = video.clientWidth;
    const videoHalfWidth = videoWidth / 2;
    const videoHalfHeight = video.clientHeight / 2;
    const videoScale = sbScale * videoWidth;

    const shapeScale = scale
      .clone()
      .multiply(new Victor(videoScale / imageWidth, videoScale / imageWidth));
    const shapeSize = shapeScale
      .clone()
      .multiply(new Victor(imageWidth, imageWidth));
    const shapeHalfSize = shapeSize.clone().multiply(new Victor(0.5, 0.5));

    const center = new Victor(
      videoHalfWidth + position.x * videoHalfWidth,
      videoHalfHeight + position.y * videoHalfWidth
    );
    const shapePosition = new Victor(
      Math.round(center.x - shapeHalfSize.x),
      Math.round(center.y - shapeHalfSize.y)
    );

    // Select point positions
    const pointWidth = 8;
    const pointHalfWidth = pointWidth / 2;
    const pointTL = new Victor(
      Math.round(center.x - shapeHalfSize.x - pointHalfWidth),
      Math.round(center.y - shapeHalfSize.y - pointHalfWidth)
    ).rotate(rotation);
    const pointTR = new Victor(
      Math.round(center.x + shapeHalfSize.x - pointHalfWidth),
      Math.round(center.y - shapeHalfSize.y - pointHalfWidth)
    ).rotate(rotation);
    const pointBL = new Victor(
      Math.round(center.x - shapeHalfSize.x - pointHalfWidth),
      Math.round(center.y + shapeHalfSize.y - pointHalfWidth)
    ).rotate(rotation);
    const pointBR = new Victor(
      Math.round(center.x + shapeHalfSize.x - pointHalfWidth),
      Math.round(center.y + shapeHalfSize.y - pointHalfWidth)
    );

    return {
      shapeScale,
      shapePosition,
      pointWidth,
      pointTL,
      pointTR,
      pointBL,
      pointBR
    };
  };

  getLayoutStyling = (position, scale, id, selectedId) => {
    let styling = {
      transform: [
        `translate(${position.x}px, ${position.y}px)`,
        `scale(${scale.x}, ${scale.y})`
      ].join(' '),
      transformOrigin: 'top left'
    };

    // Add background shade if selected
    if (id === selectedId) {
      styling = {
        ...styling,
        backgroundColor: 'rgba(0, 0, 0, 0.2)'
      };
    }

    return styling;
  };

  getImageStyling = rotation => {
    const styling = {
      transform: `rotate(${rotation}rad)`
    };
    return styling;
  };

  render() {
    const {
      type,
      video,
      position,
      rotation,
      scale,
      id,
      selectedId,
      onClick
    } = this.props;
    const calc = this.getCalculations(video, position, scale, rotation);

    return (
      video && (
        <>
          {/* Mega brain: https://stackoverflow.com/a/8963136 */}
          <div
            className="position-absolute"
            onClick={() => onClick(id)}
            role="presentation"
            style={this.getLayoutStyling(
              calc.shapePosition,
              calc.shapeScale,
              id,
              selectedId
            )}
          >
            <img
              alt={type}
              src={this.getSrcPath()}
              style={this.getImageStyling(rotation)}
            />
          </div>

          {id === selectedId && (
            <>
              <SelectPoint position={calc.pointTL} width={calc.pointWidth} />
              <SelectPoint position={calc.pointTR} width={calc.pointWidth} />
              <SelectPoint position={calc.pointBL} width={calc.pointWidth} />
              <SelectPoint position={calc.pointBR} width={calc.pointWidth} />
            </>
          )}
        </>
      )
    );
  }
}
