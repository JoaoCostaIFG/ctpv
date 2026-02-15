# iso: isoinfo 7z

# Try isoinfo first (specific to ISO files)
if exists isoinfo; then
  {
    echo "=== ISO Information ==="
    isoinfo -d -i "$f" 2>/dev/null
    echo ""
    echo "=== File Listing ==="
    isoinfo -l -i "$f" 2>/dev/null
  } | wrap_bat
  exit $?
fi

# Fallback to 7z (can list ISO contents)
if exists 7z; then
  7z l "$f" | wrap_bat
  exit $?
fi

exit 127
