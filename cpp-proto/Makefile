BIN:=$(notdir $(shell pwd))
SRCFILES:=$(shell find src/ -name *.cpp)
TMPOBJS:=${SRCFILES:.cpp=.o}
OBJFILES:=${foreach TMP,$(TMPOBJS),$(subst src/,obj/,$(TMP))}
CC=gcc
CXXFLAGS=-std=c++0x
INCLUDES:=-Isrc/

all : obj ${BIN}

obj :
	mkdir -p obj/

obj/%.o : src/%.cpp
	@mkdir -p $(@D)
	${CXX} ${CXXFLAGS} -c $^ ${INCLUDES} -o $@

${BIN} : ${OBJFILES}
	@mkdir -p $(@D)
	${CXX} $^ -o $@


clean :
	rm -rf obj ${BIN}

.PHONY: clean

