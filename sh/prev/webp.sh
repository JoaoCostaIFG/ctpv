# webp: magick

webp() {
  magick "$f" "jpg:$cache_f"
}

convert_and_show_image webp
