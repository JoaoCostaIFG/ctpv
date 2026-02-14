setup_image 1

# tell ctpv server to exit
printf '\0' >"$fifo"

# Kill running icat
icat_pid="$(kitty_icat_pid)"
if [ -e "$icat_pid" ]; then
	pid="$(cat "$icat_pid")"
	kill "$pid"
fi
