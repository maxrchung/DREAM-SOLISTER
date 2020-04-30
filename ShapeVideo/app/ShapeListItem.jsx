import React from 'react';
import PropTypes from 'prop-types';

export default class ShapeListItem extends React.Component {
  static propTypes = {
    id: PropTypes.number.isRequired,
    selectedId: PropTypes.number.isRequired,
    type: PropTypes.string.isRequired,
    onClick: PropTypes.func.isRequired
  };

  render() {
    const { id, selectedId, type, onClick } = this.props;
    const highlight = id === selectedId ? 'stylish-color-dark' : '';

    return (
      <>
        <div
          alt="List Item"
          className={`shape-list-item px-2 py-1 ${highlight}`}
          onClick={() => onClick(id)}
          role="presentation"
        >{`${id} - ${type}`}</div>
      </>
    );
  }
}
