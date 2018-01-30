#!/bin/bash

# Some smoke tests for lsp

ret=0

function works() {
	[[ $1 -eq 0 ]]
}

function breaks() {
	[[ $1 -ne 0 ]]
}

function check_generic() {
	echo -n "$1... "
	./lsp &> /dev/null
	$2 $?
	if [[ $? -eq 0 ]]; then
		echo "PASS"
	else
		echo "FAIL"
		ret=1
	fi
}

function check() {
	check_generic "$1" works
}

function check_error() {
	check_generic "$1" breaks
}

check "empty program" < /dev/null

check "return success" <<EOF
0 exit
EOF

check_error "return failure" <<EOF
1 exit
EOF

check_error "unbound name" <<EOF
foo
EOF

check "string literal" <<EOF
"foo"
EOF

exit $ret

