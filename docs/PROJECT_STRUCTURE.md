# Thea Camera - Project Structure

## Overview
This document describes the organization and structure of the Thea Camera project.

## Directory Structure

```
thea_camera/
├── src/                          # Source code
│   └── gui/                      # GUI components
│       ├── main.cpp              # Application entry point
│       ├── mainwindow.h          # Main window header
│       └── mainwindow.cpp        # Main window implementation
├── assets/                       # Static assets
│   ├── icons/                    # Application icons
│   │   ├── icon_*.png           # Various icon sizes
│   │   ├── thea_camera_icon.png  # Main icon
│   │   ├── thea_camera_icon.svg  # SVG source
│   │   └── thea_camera_icon.iconset/ # macOS icon set
│   └── screenshots/              # App screenshots
├── build/                        # Build artifacts (generated)
│   ├── *.o                      # Object files
│   ├── moc_*.cpp                # Qt MOC generated files
│   ├── moc_*.h                  # Qt MOC headers
│   └── ui_mainwindow.h          # Generated UI header
├── dist/                         # Distribution packages
│   └── *.dmg                    # macOS installer packages
├── scripts/                      # Build and utility scripts
│   ├── create_dmg.sh            # DMG creation script
│   ├── create_icon.py           # Icon generation script
│   ├── create_simple_icon.py    # Simple icon creation
│   └── install_thea_camera.sh   # Installation script
├── docs/                         # Documentation
│   └── PROJECT_STRUCTURE.md     # This file
├── photos/                       # Photo storage (user data)
│   └── .gitkeep                 # Keep directory in git
├── videos/                       # Video storage (user data)
│   └── .gitkeep                 # Keep directory in git
├── Thea Camera.app/              # macOS application bundle
│   ├── Contents/
│   │   ├── MacOS/
│   │   │   └── thea_camera      # Executable
│   │   ├── Resources/
│   │   │   └── thea_camera_icon.icns # App icon
│   │   └── Info.plist           # App metadata
│   └── ...
├── mainwindow.ui                 # Qt UI design file
├── thea_camera.pro              # Qt project file
├── run_thea.sh                  # Quick launcher script
├── README.md                    # Main documentation
└── .gitignore                   # Git ignore rules
```

## File Descriptions

### Source Code
- **`src/gui/main.cpp`**: Application entry point, creates QApplication and MainWindow
- **`src/gui/mainwindow.h`**: Main window class declaration with Qt signals/slots
- **`src/gui/mainwindow.cpp`**: Main window implementation with camera logic

### UI Design
- **`mainwindow.ui`**: Qt Designer UI file defining the interface layout
- **`thea_camera.pro`**: Qt project file with build configuration

### Assets
- **`assets/icons/`**: All application icons in various sizes and formats
- **`assets/screenshots/`**: App screenshots for documentation

### Build System
- **`build/`**: Contains all generated build artifacts (excluded from git)
- **`dist/`**: Distribution packages ready for release

### Scripts
- **`scripts/create_dmg.sh`**: Creates macOS DMG installer
- **`scripts/install_thea_camera.sh`**: Installs app to Applications folder
- **`scripts/create_icon.py`**: Generates application icons

### Documentation
- **`README.md`**: Main project documentation
- **`docs/PROJECT_STRUCTURE.md`**: This file

## Build Process

1. **Source**: Edit files in `src/gui/`
2. **UI**: Modify `mainwindow.ui` in Qt Designer
3. **Build**: Run `qmake CONFIG+=sdk_no_version_check thea_camera.pro && make`
4. **Test**: Run `./Thea Camera.app/Contents/MacOS/thea_camera`
5. **Package**: Run `./scripts/create_dmg.sh`

## Distribution

The app is distributed as:
- **Source code**: Git repository with build instructions
- **macOS DMG**: `dist/Thea_Camera_v1.0.0.dmg` for easy installation
- **App bundle**: `Thea Camera.app` for direct installation

## Dependencies

- **Qt5**: GUI framework
- **OpenCV 4.x**: Camera access and image processing
- **macOS**: Target platform (10.13+)
