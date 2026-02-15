# markdown: mdcat

check_exists mdcat

MDCAT_PAGER= PAGER=cat mdcat -p -l --columns "$w" -- "$f"
