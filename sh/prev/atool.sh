# archive: atool

check_exists atool

atool -l -- "$f" | wrap_bat
