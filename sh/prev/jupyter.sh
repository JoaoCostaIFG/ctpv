# jupyter: jupyter nbconvert jq

# Try jupyter nbconvert first (best output)
if exists jupyter; then
	jupyter nbconvert --to markdown --stdout "$f" 2>/dev/null | wrap_bat
	exit $?
fi

# Fallback to jq (notebooks are JSON)
if exists jq; then
	# Extract and display cells with their type and content
	jq -r '
		"=== Jupyter Notebook ===\n",
		(.cells[] | 
			"\n## " + (.cell_type | ascii_upcase) + " Cell\n",
			(if .cell_type == "code" then "```" + (.metadata.language // "python") + "\n" else "" end),
			(if (.source | type) == "array" then .source | join("") else .source end),
			(if .cell_type == "code" then "\n```" else "" end),
			(if .outputs and (.outputs | length) > 0 then 
				"\n### Output:\n" + (.outputs | map(
					if .text then (.text | if type == "array" then join("") else . end)
					elif .data then .data | to_entries | .[0].value | if type == "array" then .[0:3] | join("\n") else . end
					else ""
					end
				) | join("\n"))
			else "" end)
		)
	' "$f" 2>/dev/null | wrap_bat
	exit $?
fi

exit 127
