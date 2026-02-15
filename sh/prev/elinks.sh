# html: elinks

check_exists elinks

elinks \
  -dump 1 -dump-width "$w" \
  -no-references -no-numbering <"$f"
