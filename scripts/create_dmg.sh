#!/bin/bash
# Create DMG installer for Thea Camera

echo "Creating DMG installer for Thea Camera..."
echo "========================================="

# Check if the app exists
if [ ! -d "Thea Camera.app" ]; then
    echo "Error: Thea Camera.app not found!"
    echo "Please run 'make' first to build the application."
    exit 1
fi

# Create a temporary directory for the DMG contents
TEMP_DIR="Thea_Camera_DMG"
mkdir -p "$TEMP_DIR"

# Copy the app to the temp directory
cp -R "Thea Camera.app" "$TEMP_DIR/"

# Create a simple README for the DMG
cat > "$TEMP_DIR/README.txt" << EOF
Thea Camera App
===============

A professional camera application built with Qt5 and OpenCV.

Features:
- Real-time camera feed
- Photo capture with multiple resolutions
- Video recording in MP4 format
- Wide mode for horizontal matrix layout
- Professional Qt5 interface

Installation:
1. Drag "Thea Camera.app" to your Applications folder
2. Launch the app from Applications or Launchpad
3. Grant camera permissions when prompted

The app will save photos to ~/Pictures/Thea/
and videos to ~/Movies/Thea/

For support, visit: https://github.com/your-repo/thea-camera
EOF

# Create the DMG
DMG_NAME="Thea_Camera_v1.0.0.dmg"
hdiutil create -volname "Thea Camera" -srcfolder "$TEMP_DIR" -ov -format UDZO "$DMG_NAME"

if [ $? -eq 0 ]; then
    echo "✅ DMG created successfully: $DMG_NAME"
    echo "You can now distribute this DMG file!"
else
    echo "❌ DMG creation failed!"
    exit 1
fi

# Clean up
rm -rf "$TEMP_DIR"

echo ""
echo "DMG file size:"
ls -lh "$DMG_NAME"
