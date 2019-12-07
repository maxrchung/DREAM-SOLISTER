import React, { Fragment } from 'react';
import { render } from 'react-dom';
import './app.global.css';
import { AppContainer as ReactHotAppContainer } from 'react-hot-loader';
import ShapeVideo from './ShapeVideo';

const AppContainer = process.env.PLAIN_HMR ? Fragment : ReactHotAppContainer;

render(
  <AppContainer>
    <ShapeVideo />
  </AppContainer>,
  document.getElementById('root')
);
