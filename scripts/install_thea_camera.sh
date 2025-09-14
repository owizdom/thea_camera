#!/bin/bash
# Thea Camera App Installer

echo "Thea Camera App Installer"
echo "========================="

# Check if we're on macOS
if [[ "$OSTYPE" != "darwin"* ]]; then
    echo "Error: This installer is for macOS only."
    exit 1
fi

# Check if the app bundle exists
if [ ! -d "Thea Camera.app" ]; then
    echo "Error: Thea Camera.app not found!"
    echo "Please run 'make' first to build the application."
    exit 1
fi

# Create Applications directory if it doesn't exist
if [ ! -d "/Applications" ]; then
    echo "Error: /Applications directory not found!"
    exit 1
fi

# Install the app
echo "Installing Thea Camera to /Applications..."
sudo cp -R "Thea Camera.app" "/Applications/"

if [ $? -eq 0 ]; then
    echo "✅ Thea Camera installed successfully!"
    echo ""
    echo "You can now:"
    echo "1. Find 'Thea Camera' in your Applications folder"
    echo "2. Launch it from Launchpad or Spotlight"
    echo "3. Grant camera permissions when prompted"
    echo ""
    echo "The app will save photos to ~/Pictures/Thea/"
    echo "and videos to ~/Movies/Thea/"
else
    echo "❌ Installation failed!"
    exit 1
fi
