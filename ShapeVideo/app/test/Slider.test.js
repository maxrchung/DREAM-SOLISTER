import React from 'react';
import { shallow, mount } from 'enzyme';
import Slider from '../Slider';

describe('sets value', () => {
  it('sets value to 0', () => {
    const slider = shallow(<Slider value={0} onChange={() => {}} />);
    expect(slider.props().value).toBe(0);
  });

  it('sets value to 1', () => {
    const slider = shallow(<Slider value={1} onChange={() => {}} />);
    expect(slider.props().value).toBe(1);
  });

  it('changes value to 0.5', () => {
    class Parent extends React.Component {
      constructor(props) {
        super(props);
        this.state = {
          value: 0
        };
      }

      handleChange = () => {
        this.setState(prev => ({
          value: prev.value + 0.5
        }));
      };

      render() {
        const { value } = this.state;
        return <Slider value={value} onChange={this.handleChange} />;
      }
    }
    const parent = mount(<Parent />);
    const slider = parent.find(Slider);
    expect(parent.state().value).toBe(0);

    slider.props().onChange();
    expect(parent.state().value).toBe(0.5);
  });
});
