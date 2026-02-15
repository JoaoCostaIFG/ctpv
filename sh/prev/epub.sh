# epub: pandoc

if exists pandoc; then
  pandoc -f epub -t plain --wrap=auto --columns="$w" -- "$f" 2>/dev/null && exit 0
fi

if exists unzip; then
  # Fallback: direct extraction
  unzip -qc "$f" '*.xhtml' '*.html' 2>/dev/null | sed 's/<[^>]*>//g' | wrap_bat
  exit 0
fi

exit 127
