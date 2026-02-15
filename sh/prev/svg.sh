# svg: magick

check_exists magick

svg() {
  magick "$f" "png:$cache_f"
}

convert_and_show_image svg
