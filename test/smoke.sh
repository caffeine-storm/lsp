#!/bin/bash

# Some smoke tests for lsp

ret=0

echo -n "empty program... "
./lsp < /dev/null &> /dev/null
if [[ $? -ne 0 ]]; then
	echo "FAIL"
	ret=1
else
	echo "PASS"
fi

exit $ret

