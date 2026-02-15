# webp: magick

check_exists magick

webp() {
  magick "$f" "png:$cache_f"
}

convert_and_show_image webp
