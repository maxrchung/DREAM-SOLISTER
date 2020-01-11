import React from 'react';
import { shallow } from 'enzyme';
import Victor from 'victor';
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

describe('position', () => {
  it('sets default position', () => {
    const shape = shallow(<Shape position={new Victor()} />);
    expect(shape.props().style).toMatchObject({
      left: 0,
      top: 0
    });
  });

  it('sets position', () => {
    const shape = shallow(<Shape position={new Victor(100, 100)} />);
    console.log(shape.props());
    console.log(shape.props().position);
    expect(shape.props().style).toMatchObject({
      left: 100,
      top: 100
    });
  });
});
