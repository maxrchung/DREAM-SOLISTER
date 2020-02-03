import React from 'react';
import PropTypes from 'prop-types';
import Victor from 'victor';
import ShapeType from './ShapeType';
import SelectPoint from './SelectPoint';

export default class Shape extends React.Component {
  static propTypes = {
    type: PropTypes.string.isRequired,
    video: PropTypes.instanceOf(HTMLVideoElement).isRequired,
    position: PropTypes.instanceOf(Victor).isRequired,
    rotation: PropTypes.number.isRequired,
    scale: PropTypes.instanceOf(Victor).isRequired,
    id: PropTypes.number.isRequired,
    selectedId: PropTypes.number.isRequired,
    onClick: PropTypes.func.isRequired,
    onTransformChange: PropTypes.func.isRequired
  };

  getSrcPath = () => {
    const { type } = this.props;
    const path = type === ShapeType.None ? '' : `assets/${type}.png`;
    return path;
  };

  rotatePointAroundCenter = (point, center, rotation, pointHalfWidth) => {
    const rotated = point.clone().rotate(rotation);
    const added = rotated.add(center);
    const rounded = new Victor(Math.round(added.x), Math.round(added.y));
    const widthAdjusted = new Victor(
      rounded.x - pointHalfWidth,
      rounded.y - pointHalfWidth
    );
    return widthAdjusted;
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
    const pointTL = this.rotatePointAroundCenter(
      new Victor(-shapeHalfSize.x, -shapeHalfSize.y),
      center,
      rotation,
      pointHalfWidth
    );
    const pointTR = this.rotatePointAroundCenter(
      new Victor(shapeHalfSize.x, -shapeHalfSize.y),
      center,
      rotation,
      pointHalfWidth
    );
    const pointBL = this.rotatePointAroundCenter(
      new Victor(-shapeHalfSize.x, shapeHalfSize.y),
      center,
      rotation,
      pointHalfWidth
    );
    const pointBR = this.rotatePointAroundCenter(
      new Victor(shapeHalfSize.x, shapeHalfSize.y),
      center,
      rotation,
      pointHalfWidth
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

  getLayoutStyling = (position, scale) => {
    const styling = {
      transform: [
        `translate(${position.x}px, ${position.y}px)`,
        `scale(${scale.x}, ${scale.y})`
      ].join(' '),
      transformOrigin: 'top left',
      userSelect: 'none'
    };

    return styling;
  };

  getImageStyling = (rotation, id, selectedId) => {
    let styling = {
      transform: `rotate(${rotation}rad)`
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

  render() {
    const {
      type,
      video,
      position,
      rotation,
      scale,
      id,
      selectedId,
      onClick,
      onTransformChange
    } = this.props;

    const {
      shapeScale,
      shapePosition,
      pointWidth,
      pointTL,
      pointTR,
      pointBL,
      pointBR
    } = this.getCalculations(video, position, scale, rotation);

    return (
      video && (
        <>
          {/* Mega brain: https://stackoverflow.com/a/8963136 */}
          <div
            className="position-absolute"
            onClick={() => onClick(id)}
            role="presentation"
            style={this.getLayoutStyling(shapePosition, shapeScale)}
          >
            <img
              alt={type}
              draggable={false}
              src={this.getSrcPath()}
              style={this.getImageStyling(rotation, id, selectedId)}
            />
          </div>

          {id === selectedId &&
            [pointTL, pointTR, pointBL, pointBR].map(value => (
              <SelectPoint
                key={value}
                position={value}
                width={pointWidth}
                onTransformChange={onTransformChange}
              />
            ))}
        </>
      )
    );
  }
}
