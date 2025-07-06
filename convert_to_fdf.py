from PIL import Image
import numpy as np
import sys
import os

def convert_image_to_fdf(input_path, output_path=None, resize_to=None, scale_height=1.0):
    try:
        img = Image.open(input_path).convert("L")  # Convert to grayscale
        if resize_to:
            img = img.resize(resize_to)

        data = np.array(img)

        # Scale height if needed
        if scale_height != 1.0:
            data = (data * scale_height).astype(int)

        if output_path is None:
            output_path = os.path.splitext(input_path)[0] + ".fdf"

        with open(output_path, "w") as f:
            for row in data:
                f.write(" ".join(map(str, row)) + "\n")

        print(f"✅ Successfully saved FDF map to: {output_path}")

    except Exception as e:
        print(f"❌ Error: {e}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python convert_to_fdf.py <input_image> [width height] [scale]")
        print("Example: python convert_to_fdf.py heightmap.png 1000 1000 0.5")
        sys.exit(1)

    input_file = sys.argv[1]
    resize = (int(sys.argv[2]), int(sys.argv[3])) if len(sys.argv) >= 4 else None
    scale = float(sys.argv[4]) if len(sys.argv) >= 5 else 1.0

    convert_image_to_fdf(input_file, resize_to=resize, scale_height=scale)
