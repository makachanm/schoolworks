#!/bin/zsh

SUBC_BIN="./subc"
TEST_DIR="../test"

for c_file in $TEST_DIR/*.c; do
    base="${c_file%.*}"
    out_file="${base}.out"
    filename=$(basename "$c_file")

    echo "$filename"

    ../src/subc "$(basename "$c_file")" 2>&1 | diff -u "$out_file" -
    
    if [ $? -eq 0 ]; then
        echo "PASS"
    fi
done
