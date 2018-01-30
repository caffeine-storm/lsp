BIN:=lsp
OBJECTS:=$(patsubst src/%.c,obj/%.o,$(wildcard src/*.c))
CFLAGS:=-std=c11 -Wall -Wextra -g -Isrc/
DEBUG_CFLAGS:=${CFLAGS} -DLSP_DEBUG
TRACE_CFLAGS:=${CFLAGS} -DLSP_TRACE
LDFLAGS:=-std=c11

all: ${BIN}

check: ${BIN}
	./test/smoke.sh

obj:
	mkdir -p obj

obj/%.o: src/%.c |obj
	${CC} ${CFLAGS} -c $< -o $@

${BIN}: ${OBJECTS}
	${CC} -o $@ ${LDFLAGS} $^

clean:
	rm -rf obj ${BIN}

.PHONY: clean check

