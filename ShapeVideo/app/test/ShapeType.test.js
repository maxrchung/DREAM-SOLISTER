import ShapeType from '../ShapeType';

describe('values', () => {
  it('sets expected values', () => {
    expect(ShapeType.Rectangle).toBe('Rectangle');
    expect(ShapeType.Triangle).toBe('Triangle');
    expect(ShapeType.Circle).toBe('Circle');
    expect(ShapeType.Semicircle).toBe('Semicircle');
  });
});
