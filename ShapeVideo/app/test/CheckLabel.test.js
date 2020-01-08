import React from 'react';
import { shallow, mount } from 'enzyme';
import CheckLabel from '../CheckLabel';

describe('sets checked', () => {
  it('sets checked to true', () => {
    const check = mount(
      <CheckLabel checked label="Check" name="check" onChange={() => {}} />
    );
    expect(check.props().checked).toBe(true);
  });

  it('sets checked to false', () => {
    const check = mount(
      <CheckLabel
        checked={false}
        label="Check"
        name="check"
        onChange={() => {}}
      />
    );
    expect(check.props().checked).toBe(false);
  });

  it('sets name', () => {
    const check = mount(
      <CheckLabel checked label="Check" name="chk-name" onChange={() => {}} />
    );
    expect(check.props().name).toBe('chk-name');
  });

  it('sets label', () => {
    const check = mount(
      <CheckLabel
        checked
        label="Check Label"
        name="check"
        onChange={() => {}}
      />
    );
    expect(check.props().label).toBe('Check Label');
  });

  it('toggles checked', () => {
    class Parent extends React.Component {
      constructor(props) {
        super(props);
        this.state = {
          isChecked: true
        };
      }

      handleChange = () => {
        this.setState(prev => ({
          isChecked: !prev.isChecked
        }));
      };

      render() {
        const { isChecked } = this.state;
        return (
          <CheckLabel
            checked={isChecked}
            label="Check"
            name="check"
            onChange={this.handleChange}
          />
        );
      }
    }
    const parent = shallow(<Parent />);
    const check = parent.find(CheckLabel);
    expect(parent.state().isChecked).toBe(true);

    check.props().onChange();
    expect(parent.state().isChecked).toBe(false);

    check.props().onChange();
    expect(parent.state().isChecked).toBe(true);
  });
});
