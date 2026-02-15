# Kill running icat
icat_pid="$(kitty_icat_pid)"
if [ -e "$icat_pid" ]; then
  pid="$(cat "$icat_pid")"
  kill "$pid" 2>/dev/null
  rm -f "$icat_pid"
fi

is_kitty && kitty_clear
