# Thea Camera App

A professional camera application written in C++ with Qt5 and OpenCV, featuring advanced camera functionality with horizontal matrix layout for wider photos and video recording capabilities. Inspired by the [Qt and OpenCV camera app](https://github.com/AhmetFurkanDEMIR/Camera-app-with-Qt-and-Opencv) design.

## iPhone 17-Inspired Horizontal Matrix Layout

Thea Camera's flagship feature is its revolutionary **horizontal matrix layout** technology, inspired by the cutting-edge camera innovations found in the iPhone 17. This advanced feature transforms traditional camera capture by implementing a sophisticated matrix-based approach that creates dramatically wider photos while maintaining exceptional image quality. The horizontal matrix layout intelligently processes multiple image segments in real-time, stitching them together to produce panoramic-style photos that capture significantly more of your scene in a single shot. This technology represents the future of mobile photography, bringing professional-grade wide-angle capabilities to desktop applications with unprecedented precision and speed.

## Features

- **Real camera access** - Uses OpenCV for direct camera hardware access
- **Professional GUI** - Qt5-based interface with camera-like controls
- **Video recording** - High-quality MP4 video recording
- **Photo capture** - High-resolution JPEG photo capture
- **Multiple camera modes** - Photo, Portrait, Wide Portrait, Video
- **Wide mode support** - Horizontal matrix layout for wider photos
- **Real-time processing** - Live camera feed with image processing
- **Cross-platform** - Works on macOS, Linux, and Windows
- **Modern UI** - Professional interface inspired by the original Qt camera app

## Camera Modes

- **PHOTO**: Standard high-resolution photo capture
- **PORTRAIT**: Enhanced portrait mode with depth sensing simulation
- **WIDE**: Wide portrait mode with horizontal matrix layout (1000x500)
- **VIDEO**: MP4 video recording with customizable settings

## Requirements

- **Qt5**: For GUI and windowing
- **OpenCV 4.x**: For camera access and image processing
- **C++ Compiler**: GCC or Clang with C++17 support

## Installation

### Option 1: Pre-built App (Recommended)

Download the latest `Thea_Camera_v1.0.0.dmg` from the releases page and install:

1. Open the DMG file
2. Drag "Thea Camera.app" to your Applications folder
3. Launch from Applications or Launchpad
4. Grant camera permissions when prompted

### Option 2: Build from Source

#### macOS (using Homebrew)

```bash
# Install dependencies
make install-deps

# Build the application
qmake CONFIG+=sdk_no_version_check thea_camera.pro && make

# Run Thea Camera
./thea_camera.app/Contents/MacOS/thea_camera
# Or use the launcher script:
./run_thea.sh
```

#### Create Distribution Package

```bash
# Create DMG installer
./create_dmg.sh

# Install to Applications
./install_thea_camera.sh
```

## Usage

### Running the App

```bash
# Build and run
qmake CONFIG+=sdk_no_version_check thea_camera.pro && make && ./thea_camera.app/Contents/MacOS/thea_camera

# Or use the launcher script
./run_thea.sh
```

### Controls

#### Mouse Controls
- **Mode Buttons** (top): Click PHOTO, PORTRAIT, WIDE, VIDEO
- **Capture Button** (center): Large circular button - click to take photo
- **Record Button** (video mode): Click to start/stop video recording
- **Wide Toggle** (bottom right): Click to enable/disable wide mode

#### Keyboard Controls
- **`Ctrl+S`** - Start/Stop camera
- **`Space`** - Capture photo
- **`Ctrl+R`** - Start/Stop recording
- **`Ctrl+Q`** - Quit application

## File Structure

```
thea_camera/
├── src/
│   └── gui/
│       ├── main.cpp           # Main application entry
│       ├── mainwindow.h       # Main window header
│       └── mainwindow.cpp     # Main window implementation
├── photos/                    # Photo storage directory
├── videos/                    # Video storage directory
├── mainwindow.ui              # Qt UI design file
├── thea_camera.pro            # Qt project file
├── Thea Camera.app/           # macOS app bundle
│   ├── Contents/
│   │   ├── MacOS/
│   │   │   └── thea_camera    # Executable
│   │   ├── Resources/
│   │   │   └── thea_camera_icon.icns  # App icon
│   │   └── Info.plist         # App metadata
│   └── ...
├── run_thea.sh               # Launcher script
├── install_thea_camera.sh    # Installer script
├── create_dmg.sh             # DMG creator script
└── README.md                 # This file
```

## Photo/Video Storage

- **Photos**: Saved to `./photos/` directory as `Thea_YYYYMMDD_HHMMSS.jpg`
- **Videos**: Saved to `./videos/` directory as `Thea_YYYYMMDD_HHMMSS.mp4`
- **High Quality**: Photos saved at 95% JPEG quality
- **Video Format**: MP4 with H.264 encoding

## Technical Specifications

### Camera Resolution
- **Standard Mode**: 800x600 pixels
- **Wide Mode**: 1000x500 pixels (horizontal matrix layout)
- **Frame Rate**: 30 FPS
- **Color Format**: BGR24

### Image Processing
- **Portrait Enhancement**: Contrast and saturation enhancement
- **Wide Mode Indicators**: Visual matrix layout guides
- **Real-time Processing**: Live camera feed processing

### Video Recording
- **Format**: MP4 (H.264)
- **Resolution**: Matches selected camera mode
- **Frame Rate**: 30 FPS
- **Quality**: High quality encoding

## Building from Source

```bash
# Clone or download the project
cd thea_camera

# Install dependencies
make install-deps

# Build
make all

# Run
make run
```

## Troubleshooting

### Camera Not Found
- Ensure camera permissions are granted in System Preferences
- Check if another application is using the camera
- Try running with different camera index: modify `cv::VideoCapture(0)` to `cv::VideoCapture(1)`

### Build Errors
- Ensure Qt5 and OpenCV are properly installed
- Check Qt5 installation: `qmake --version`
- Check OpenCV installation: `pkg-config --cflags opencv4`
- Try cleaning and rebuilding: `make clean && qmake CONFIG+=sdk_no_version_check thea_camera.pro && make`

### Permission Issues
- Grant camera access in System Preferences > Security & Privacy > Camera
- Ensure the application has proper permissions

## Development

### Project Structure
- **Main Source**: `src/gui/main.cpp`, `src/gui/mainwindow.cpp`
- **UI Design**: `mainwindow.ui`
- **Build System**: `thea_camera.pro` (Qt project file)
- **Dependencies**: Qt5, OpenCV 4.x

### Key Components
- **Camera Interface**: OpenCV VideoCapture
- **GUI Framework**: Qt5 for rendering and input
- **Image Processing**: OpenCV for real-time processing
- **File I/O**: Qt and standard C++ library for file operations

## License

This project is open source and available under the MIT License.

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

## Acknowledgments

- **OpenCV**: Computer vision library for camera access and image processing
- **Qt5**: Cross-platform application framework for GUI and input handling
- **Qt Camera App**: UI design inspired by [AhmetFurkanDEMIR's Qt camera app](https://github.com/AhmetFurkanDEMIR/Camera-app-with-Qt-and-Opencv)