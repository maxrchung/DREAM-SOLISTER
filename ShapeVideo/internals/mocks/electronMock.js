export const remote = {
  dialog: {
    showOpenDialogSync: jest.fn(),
    showSaveDialogSync: jest.fn()
  },
  Menu: {
    buildFromTemplate: jest.fn(),
    setApplicationMenu: jest.fn()
  },
  process: {
    platform: jest.fn()
  }
};

export default '';
