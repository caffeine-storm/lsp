BIN:=lsp
OBJECTS:=$(patsubst src/%.c,obj/%.o,$(wildcard src/*.c))
CFLAGS:=-std=c11 -Wall -Wextra -g -Isrc/
LDFLAGS:=-std=c11

all: ${BIN}

check: ${BIN}
	./test/smoke.sh

obj:
	mkdir -p obj

obj/%.o: src/%.c |obj
	${CC} -c $< ${CFLAGS} -o $@

${BIN}: ${OBJECTS}
	${CC} -o $@ ${LDFLAGS} $^

clean:
	rm -rf obj ${BIN}

.PHONY: clean check

