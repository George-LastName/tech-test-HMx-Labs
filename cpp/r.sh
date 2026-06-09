#!/usr/bin/env bash

set -euo pipefail

# Resolve project dir to this script's location so it works from any cwd.
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$PROJECT_DIR/build"

# Defaults
ASAN=OFF
TSAN=OFF
TIDY=OFF
IWYU=OFF
DO_CLEAN=0
DO_TESTS=0
DO_CONSOLE=0

usage() {
    cat <<EOF
Usage: ./b.sh [options]

Configures CMake with the chosen flags, builds, then optionally runs.

CMake flag toggles:
  -a    Enable AddressSanitizer  (-DENABLE_ASAN=ON)
  -t    Enable ThreadSanitizer   (-DENABLE_TSAN=ON)
  -y    Enable clang-tidy        (-DENABLE_CLANG_TIDY=ON)
  -i    Enable include-what-you-use (-DENABLE_IWYU=ON)

Build:
  -x    Clean (cmake --target clean)

Run after build:
  -T    Run ./Tests
  -C    Run ./ConsoleApp
  -h    Show this help

Examples:
  ./r.sh                # configure + build with defaults
  ./r.sh -x -a -T       # clean, build with ASAN, run Tests
  ./r.sh -y             # build with clang-tidy enabled
  ./r.sh -TC            # build, then run Tests and ConsoleApp
EOF
}

while getopts ":atyixTCh" opt; do
    case "$opt" in
        a) ASAN=ON ;;
        t) TSAN=ON ;;
        y) TIDY=ON ;;
        i) IWYU=ON ;;
        x) DO_CLEAN=1 ;;
        T) DO_TESTS=1 ;;
        C) DO_CONSOLE=1 ;;
        h) usage; exit 0 ;;
        \?) echo "Unknown option: -$OPTARG" >&2; usage; exit 1 ;;
        :)  echo "Option -$OPTARG requires an argument." >&2; exit 1 ;;
    esac
done

if [[ "$ASAN" == ON && "$TSAN" == ON ]]; then
    echo "Error: ASAN and TSAN cannot both be enabled (CMake will fatal-error)." >&2
    exit 1
fi

if [[ "$TIDY" == ON && "$IWYU" == ON ]]; then
    echo "Error: Clang-tidy and iwyu should not be enabled at the same time." >&2
    exit 1
fi

if (( DO_CLEAN )); then
    echo "==> Cleaning $BUILD_DIR"
    cmake --build "$BUILD_DIR" --target clean 2>/dev/null || true
fi

echo "==> Configuring (ASAN=$ASAN TSAN=$TSAN CLANG_TIDY=$TIDY IWYU=$IWYU)"
cmake -S "$PROJECT_DIR" -B "$BUILD_DIR" \
    -DENABLE_ASAN="$ASAN" \
    -DENABLE_TSAN="$TSAN" \
    -DENABLE_CLANG_TIDY="$TIDY" \
    -DENABLE_IWYU="$IWYU"

# Determine if output should be captured to a report file
REPORT_FILE=""
[[ "$TIDY" == ON ]] && REPORT_FILE="$PROJECT_DIR/clang_tidy_report.txt"
[[ "$IWYU" == ON ]]  && REPORT_FILE="$PROJECT_DIR/iwyu_report.txt"

echo "==> Building"
if [[ -n "$REPORT_FILE" ]]; then
    echo "    Capturing output to $REPORT_FILE"
    cmake --build "$BUILD_DIR" 2>&1 | tee "$REPORT_FILE"
else
    cmake --build "$BUILD_DIR"
fi

if (( DO_TESTS )); then

    echo "==> Running Tests"
    (cd "$BUILD_DIR" && ./Tests)
fi

if (( DO_CONSOLE )); then
    echo "==> Running ConsoleApp"
    (cd "$BUILD_DIR" && ./ConsoleApp)
fi

echo "==> Done."
