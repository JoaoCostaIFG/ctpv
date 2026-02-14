# webp: magick

webp() {
  magick "$f" "png:$cache_f"
}

convert_and_show_image webp
