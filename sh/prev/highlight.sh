# text: highlight

check_exists highlight

highlight \
  --replace-tabs=4 --out-format=ansi \
  --style='pablo' --force \
  --line-length "$w" --wrap-simple -- "$f"
