BIN:=lsp
OBJECTS:=$(patsubst src/%.c,obj/%.o,$(wildcard src/*.c))
DEPS:=${OBJECTS:.o=.d}
CPPFLAGS:=-Isrc/
CFLAGS:=-std=c11 -Wall -Wextra -g
DEBUG_CFLAGS:=${CFLAGS} -DLSP_DEBUG
TRACE_CFLAGS:=${CFLAGS} -DLSP_TRACE
LDFLAGS:=-std=c11

all: ${BIN}

check: ${BIN}
	./test/smoke.sh

obj:
	mkdir -p obj

# Build '.d' makefiles that force .o targets to depend on their .c and any
# relevant .h files.
obj/%.d: src/%.c |obj
	@${CC} ${CPPFLAGS} ${CFLAGS} -MM $< -o $@
	@sed -i $@ -e 's,${@:.d=.o},${@:.d=.o} $@,'
	@sed -i $@ -e '1s,^,obj/,'

-include ${DEPS}

obj/%.o: src/%.c |obj
	${CC} ${CPPFLAGS} ${CFLAGS} -c $< -o $@

${BIN}: ${OBJECTS}
	${CC} -o $@ ${LDFLAGS} $^

clean:
	rm -rf obj ${BIN}

.PHONY: clean check

