import React from 'react';
import PropTypes from 'prop-types';

export default class Slider extends React.Component {
  static propTypes = {
    value: PropTypes.number.isRequired,
    onChange: PropTypes.func.isRequired
  };

  render() {
    const { value, onChange } = this.props;
    return (
      <input
        type="range"
        className="custom-range"
        min="0"
        max="1"
        step="any"
        value={value}
        onChange={onChange}
      />
    );
  }
}
