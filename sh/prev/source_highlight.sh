# text: source-highlight

check_exists source-highlight

source-highlight \
	--tab=4 --out-format=esc \
	--style=esc256.style --failsafe \
	-i "$f" | wrap_bat
