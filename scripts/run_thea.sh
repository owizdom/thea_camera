#!/bin/bash
# Thea Camera App Launcher

echo "Starting Thea Camera App..."
echo "=========================="

# Check if the app exists
if [ -f "./thea_camera.app/Contents/MacOS/thea_camera" ]; then
    echo "Launching Qt-based Thea Camera App..."
    ./thea_camera.app/Contents/MacOS/thea_camera
else
    echo "Error: Thea camera app not found!"
    echo "Please run 'make' first to build the application."
    exit 1
fi
