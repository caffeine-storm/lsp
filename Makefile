BIN:=lsp
OBJECTS:=obj/lsp.o
CFLAGS:=-std=c99 -Wall -g
LDFLAGS:=-std=c99

all: ${BIN}

obj:
	mkdir -p obj

obj/%.o: src/%.c obj
	gcc -c $< ${CFLAGS} -o $@

${BIN}: ${OBJECTS}
	gcc $^ ${LDFLAGS} -o $@

