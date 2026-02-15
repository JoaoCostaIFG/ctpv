# epub: pandoc

if exists pandoc && pandoc -f epub -t plain --wrap=auto --columns="$w" -- "$f" 2>/dev/null | head -n "$h"; then
  exit 0
elif exists unzip; then
  # Fallback: direct extraction
  unzip -qc "$f" '*.xhtml' '*.html' 2>/dev/null | sed 's/<[^>]*>//g' | head -n "$h"
else
  exit 127
fi
