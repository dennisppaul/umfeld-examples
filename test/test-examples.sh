#!/usr/bin/env bash

# configurable top-level folders (space-separated)
EXAMPLE_DIRS=("Processing/Basics" "Processing/Topics" "Basics" "Audio" "Advanced")

# how many seconds to let each example run
RUN_DURATION=3

# build directory (inside test folder)
BUILD_DIR="build-test-examples"

# logs directory (inside test folder)
LOG_DIR="logs"

# root directory where examples live (relative to this script)
EXAMPLES_ROOT=".."

# results csv
RESULTS_FILE="test-results.csv"

# color + emoji helpers (still shown in console)
GREEN="\033[0;32m"
RED="\033[0;31m"
RESET="\033[0m"
CHECK="${GREEN}✅${RESET}"
CROSS="${RED}❌${RESET}"

# clean and prepare build and log directories
mkdir -p "$BUILD_DIR"
rm -rf "$LOG_DIR"
mkdir -p "$LOG_DIR"

# init CSV
: > "$RESULTS_FILE"
echo "Category,Example,Build,Run,ExitCode,Executable,LogFile" >> "$RESULTS_FILE"

echo "--- Testing selected example folders: ${EXAMPLE_DIRS[*]}"
echo "--- start time: $(date) "
echo 

for CATEGORY in "${EXAMPLE_DIRS[@]}"; do
    CATEGORY_PATH="$EXAMPLES_ROOT/$CATEGORY"

    if [ ! -d "$CATEGORY_PATH" ]; then
        echo -e "${CROSS} ${CATEGORY} (not found)"
        continue
    fi

    echo "--- $CATEGORY"
    while IFS= read -r -d '' EXAMPLE; do
        # must be a dir with a CMakeLists.txt
        [ -f "$EXAMPLE/CMakeLists.txt" ] || continue

        REL_PATH="${EXAMPLE#$EXAMPLES_ROOT/}"
        BUILD_SUBDIR="$BUILD_DIR/$REL_PATH"
        mkdir -p "$BUILD_SUBDIR"

        BUILD_RESULT="Fail"
        RUN_RESULT="N/A"
        EXIT_CODE=""
        EXECUTABLE=""
        LOG_FILE="$LOG_DIR/$(echo "$REL_PATH" | tr / -).log"

        cmake -S "$EXAMPLE" -B "$BUILD_SUBDIR" &> /dev/null
        if cmake --build "$BUILD_SUBDIR" &> /dev/null; then
            BUILD_RESULT="Success"

            # try to find a runnable binary in the build dir (first executable file)
            while IFS= read -r -d '' f; do
                if [ -f "$f" ] && [ -x "$f" ]; then
                    EXECUTABLE="$f"
                    break
                fi
            done < <(find "$BUILD_SUBDIR" -maxdepth 1 -type f -print0)

            if [ -x "$EXECUTABLE" ]; then
                # run briefly and capture output to log
                nohup "$EXECUTABLE" >> "$LOG_FILE" 2>&1 &
                PID=$!
                sleep "$RUN_DURATION"
                kill "$PID" &> /dev/null
                wait "$PID" 2>/dev/null
                EXIT_CODE=$?

                # consider SIGTERM(143) as success too
                if [ "$EXIT_CODE" -eq 0 ] || [ "$EXIT_CODE" -eq 143 ]; then
                    RUN_RESULT="Success"
                    echo -e "--- $CHECK $REL_PATH"
                else
                    RUN_RESULT="Fail"
                    echo -e "--- $CROSS $REL_PATH (runtime failed: exit code $EXIT_CODE)"
                fi
            else
                RUN_RESULT="Fail"
                EXIT_CODE="127"
                echo -e "--- $CROSS $REL_PATH (no executable)"
            fi
        else
            echo -e "--- $CROSS $REL_PATH (build failed)"
        fi

        # CSV row
        # (quote fields that can contain spaces)
        printf "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n" \
            "$CATEGORY" "$REL_PATH" "$BUILD_RESULT" "$RUN_RESULT" "${EXIT_CODE:-}" "${EXECUTABLE:-}" "${LOG_FILE:-}" \
            >> "$RESULTS_FILE"

    done < <(find "$CATEGORY_PATH" -mindepth 1 -type d -print0)
done

echo
echo "--- end time  : $(date) "
echo
echo "CSV summary written to $RESULTS_FILE"
echo
