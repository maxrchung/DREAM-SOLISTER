import React from 'react';
import PropTypes from 'prop-types';

export default class Slider extends React.Component {
  static propTypes = {
    disabled: PropTypes.bool,
    value: PropTypes.number.isRequired,
    onChange: PropTypes.func.isRequired
  };

  static defaultProps = {
    disabled: false
  };

  render() {
    const { disabled, value, onChange } = this.props;
    return (
      <input
        disabled={disabled}
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
