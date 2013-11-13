BIN:=$(notdir $(shell pwd))
SRCFILES:=$(shell find src/ -name *.cpp)
TMPOBJS:=${SRCFILES:.c=.o}
OBJFILES:=${foreach TMP,$(TMPOBJS),$(subst src/,obj/,$(TMP))}
CC=gcc
INCLUDES:=-Isrc/

all : obj ${BIN}

obj :
	mkdir -p obj/

obj/%.o : src/%.c
	${CPP} -c $^ ${INCLUDES} -o $@

${BIN} : ${OBJFILES}
	${CPP} $^ -o $@


clean :
	rm -rf obj ${BIN}

.PHONY: clean

