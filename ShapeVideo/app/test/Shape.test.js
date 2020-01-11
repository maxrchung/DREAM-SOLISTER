import React from 'react';
import { shallow } from 'enzyme';
import Shape from '../Shape';
import ShapeType from '../ShapeType';

describe('type', () => {
  it('sets rectangle', () => {
    const shape = shallow(<Shape type={ShapeType.Rectangle} />);
    expect(shape.find('img').props().src).toBe('assets/Rectangle.png');
  });

  it('sets triangle', () => {
    const shape = shallow(<Shape type={ShapeType.Triangle} />);
    expect(shape.find('img').props().src).toBe('assets/Triangle.png');
  });

  it('sets circle', () => {
    const shape = shallow(<Shape type={ShapeType.Circle} />);
    expect(shape.find('img').props().src).toBe('assets/Circle.png');
  });

  it('sets semicircle', () => {
    const shape = shallow(<Shape type={ShapeType.Semicircle} />);
    expect(shape.find('img').props().src).toBe('assets/Semicircle.png');
  });

  it('sets none', () => {
    const shape = shallow(<Shape type={ShapeType.None} />);
    expect(shape.find('img').props().src).toBe('');
  });
});
