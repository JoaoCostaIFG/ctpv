# text: bat

batcmd=$(get_bat_cmd)

if [ "$batcmd" = "cat" ]; then
  exit 127
fi

$batcmd -- "$f"
