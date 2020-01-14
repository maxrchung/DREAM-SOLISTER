import React from 'react';
import PropTypes from 'prop-types';

export default class CheckLabel extends React.Component {
  static propTypes = {
    checked: PropTypes.bool.isRequired,
    disabled: PropTypes.bool,
    label: PropTypes.string.isRequired,
    name: PropTypes.string.isRequired,
    onChange: PropTypes.func.isRequired
  };

  static defaultProps = {
    disabled: false
  };

  render() {
    const { checked, disabled, label, name, onChange } = this.props;
    return (
      <div className="form-check">
        <label className="form-check-label" htmlFor={name}>
          <input
            className="form-check-input"
            disabled={disabled}
            type="checkbox"
            name={name}
            checked={checked}
            onChange={onChange}
          />
          {label}
        </label>
      </div>
    );
  }
}
