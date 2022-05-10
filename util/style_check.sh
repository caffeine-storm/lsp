#!/bin/bash

# Do a few quick scans to see if there are some simple style annoyances.

ret=0
target=src/

if [[ $# -ge 1 ]]; then
  echo "setting target to '$1'"
  target="$1"
fi

# Check for a space followed by a tab
ack " \t" "$target"
if [[ $? -eq 0 ]]; then
  ret=1
fi

# Check for trailing whitespace
ack "\s\s$" "$target"
if [[ $? -eq 0 ]]; then
  ret=1
fi

# Check for leading tabs
ack "^\s*\t" "$target"
if [[ $? -eq 0 ]]; then
  ret=1
fi

exit $ret
