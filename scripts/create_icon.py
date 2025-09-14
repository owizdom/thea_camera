#!/usr/bin/env python3
"""
Create a simple app icon for Thea Camera
"""

from PIL import Image, ImageDraw, ImageFont
import os

def create_app_icon():
    # Create a 512x512 icon
    size = 512
    img = Image.new('RGBA', (size, size), (0, 0, 0, 0))
    draw = ImageDraw.Draw(img)
    
    # Create a camera-like icon
    # Main body (rounded rectangle)
    body_margin = 50
    body_rect = [body_margin, body_margin, size - body_margin, size - body_margin]
    draw.rounded_rectangle(body_rect, radius=30, fill=(45, 45, 45, 255))
    
    # Camera lens (circle)
    lens_center = (size // 2, size // 2)
    lens_radius = 120
    draw.ellipse([lens_center[0] - lens_radius, lens_center[1] - lens_radius,
                  lens_center[0] + lens_radius, lens_center[1] + lens_radius],
                 fill=(20, 20, 20, 255))
    
    # Inner lens ring
    inner_radius = 80
    draw.ellipse([lens_center[0] - inner_radius, lens_center[1] - inner_radius,
                  lens_center[0] + inner_radius, lens_center[1] + inner_radius],
                 fill=(60, 60, 60, 255))
    
    # Flash (small rectangle)
    flash_rect = [size // 2 + 60, size // 2 - 40, size // 2 + 80, size // 2 - 20]
    draw.rounded_rectangle(flash_rect, radius=5, fill=(255, 255, 255, 255))
    
    # "T" text in the center
    try:
        # Try to use a system font
        font_size = 100
        font = ImageFont.truetype("/System/Library/Fonts/Arial.ttf", font_size)
    except:
        # Fallback to default font
        font = ImageFont.load_default()
    
    text = "T"
    bbox = draw.textbbox((0, 0), text, font=font)
    text_width = bbox[2] - bbox[0]
    text_height = bbox[3] - bbox[1]
    text_x = lens_center[0] - text_width // 2
    text_y = lens_center[1] - text_height // 2
    
    draw.text((text_x, text_y), text, fill=(255, 255, 255, 255), font=font)
    
    # Save the icon
    img.save('thea_camera_icon.png')
    print("Created thea_camera_icon.png")
    
    # Create different sizes for the app bundle
    sizes = [16, 32, 64, 128, 256, 512, 1024]
    for s in sizes:
        resized = img.resize((s, s), Image.Resampling.LANCZOS)
        resized.save(f'icon_{s}x{s}.png')
        print(f"Created icon_{s}x{s}.png")

if __name__ == "__main__":
    create_app_icon()
