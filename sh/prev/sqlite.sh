# sqlite: sqlite3

check_exists sqlite3

# Show database schema and sample data from each table
{
  sqlite3 "$f" <<'SQL'
.headers on
.mode column

-- Show all tables
SELECT '=== Tables ===' AS '';
.tables

-- Show schema for all tables
SELECT '' AS '', '=== Schema ===' AS '';
.schema

-- Show sample data from each table (first 10 rows)
SELECT '' AS '', '=== Sample Data ===' AS '';
SQL

  # Get table names and show sample from each
  sqlite3 "$f" "SELECT name FROM sqlite_master WHERE type='table' AND name NOT LIKE 'sqlite_%';" | while read -r table; do
    if [ -n "$table" ]; then
      echo ""
      echo "=== Table: $table ==="
      sqlite3 -header -column "$f" "SELECT * FROM \"$table\" LIMIT 10;" 2>/dev/null || true
    fi
  done
} | wrap_bat
