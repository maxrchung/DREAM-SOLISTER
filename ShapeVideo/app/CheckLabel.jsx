import React from 'react';
import PropTypes from 'prop-types';

export default class CheckLabel extends React.Component {
  static propTypes = {
    checked: PropTypes.bool.isRequired,
    label: PropTypes.string.isRequired,
    name: PropTypes.string.isRequired,
    onChange: PropTypes.func.isRequired
  };

  render() {
    const { checked, label, name, onChange } = this.props;
    return (
      <div className="form-check">
        <label className="form-check-label" htmlFor={name}>
          <input
            className="form-check-input"
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
