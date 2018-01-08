#!/bin/bash

# Do a few quick scans to see if there are some simple style annoyances.

ret=0

# Check for leading spaces
ack "^ " src/
if [[ $? -eq 0 ]]; then
	ret=1
fi

# Check for a space followed by a tab
ack " \t" src/
if [[ $? -eq 0 ]]; then
	ret=1
fi

# Check for double-space; also catches spaces-for-tabs
ack "  " src/
if [[ $? -eq 0 ]]; then
	ret=1
fi

# Check for trailing whitespace
ack "\s\s$" src/
if [[ $? -eq 0 ]]; then
	ret=1
fi

exit $ret
