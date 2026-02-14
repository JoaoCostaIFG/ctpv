# 3d: f3d

check_exists f3d

threed() {
  f3d --output="$cache_f" --resolution=1920,1080 --no-background "$f"
}

convert_and_show_image threed
