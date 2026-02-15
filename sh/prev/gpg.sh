# gpg-encrypted: gpg

# "showgpg" option must be enabled for this preview to work
[ -z "$showgpg" ] && exit 127

check_exists gpg

gpg -d -- "$f" 2>&1 | wrap_bat
