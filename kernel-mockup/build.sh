#!/bin/bash

relink_needed=0

CC=${CC:-clang}

NUM_JOBS=$(nproc)

mkdir -p bin

SRC_FILES=$(find src/ -name "*.c")

compile() {
    echo "Compiling $src_file"
    $CC -Isrc -Isrc/lua -c $1 -o $2
}

for src_file in $SRC_FILES; do
    obj_file="bin/$(basename "${src_file%.*}.o")"
    if [ ! -f "$obj_file" ] || [ "$src_file" -nt "$obj_file" ]; then
        compile "$src_file" "$obj_file" &
        relink_needed=1
        PIDS+=($!)
        if (( ${#PIDS[@]} >= NUM_JOBS )); then
            wait -n
            PIDS=($(jobs -rp))
        fi
    fi
done

wait "${PIDS[@]}"

if [ $relink_needed -eq 1 ]; then
    $CC -lm bin/*.o -o bin/mockup
fi

echo "Successfully compiled"
