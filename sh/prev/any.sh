# any: bat cat exiftool

# Check if file is binary using 'file' command
is_binary() {
  file --mime-encoding -- "$f" | grep -q binary
}

# For text files, try bat first, then cat
display_text() {
  batcmd=$(get_bat_cmd)
  $batcmd -- "$f"
}

# For binary files, try exiftool
display_binary() {
  if exists exiftool; then
    exiftool -- "$f" || true
  else
    # No exiftool available for binary files, show it's binary
    echo "Binary file: cannot display"
  fi
}

# Main logic: check if binary and display accordingly
if ! is_binary; then
  display_text
else
  display_binary
fi
