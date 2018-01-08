#!/bin/bash

# Some smoke tests for lsp

echo -n "empty program... "
./lsp < /dev/null &> /dev/null
if [[ $? -ne 0 ]]; then
	echo "FAIL"
else
	echo "PASS"
fi

