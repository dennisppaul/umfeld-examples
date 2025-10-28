#!/usr/bin/env zsh

# Find all .cpp files containing 'void setup() {'
grep -Irl --include='*.cpp' 'void setup() {' . | while read -r file; do
    echo "Updating $file"
    # Insert colorMode line after 'void setup() {'
    sed -i '' '/void setup() {/a\
    \colorMode(RGB, 1.0, 1.0, 1.0, 1.0);
    ' "$file"
done
