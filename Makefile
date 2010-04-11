
CC=g++

debug = 0
debug_verbose = 0
memmgr = 1
symtbl = 1
# Should change the .y depending on symtbl

ifeq ($(debug),0)
CCFLAGS=-MMD -O2 -W -Wall -Wno-unused -Iinclude -DYYERROR_VERBOSE
else
CCFLAGS=-MMD -O0 -g -ggdb -Iinclude -W -Wall -Wno-unused -DYYERROR_VERBOSE -D_DEBUG
ifeq ($(debug_verbose),1)
CCFLAGS:=$(CCFLAGS) -D_DEBUG_VERBOSE
endif
endif

ifeq ($(memmgr),1)
CCFLAGS:=$(CCFLAGS) -D_MEMMGR
endif

ifeq ($(symtbl),1)
CCFLAGS:=$(CCFLAGS) -D_SYMTBL
endif


LINKFLAGS=-L. -lcore

CORE_SRC=\
	src/builtins.cpp \
	src/context.cpp \
	src/instruction.cpp \
	src/object.cpp \
	src/stack.cpp \
	src/callstack.cpp \
	src/exception.cpp \
	src/heap.cpp \
	src/hashmap.cpp \
	src/symbol.cpp
CORE_OBJ=$(CORE_SRC:.cpp=.o)
CORE_DEP=($CORE_SRC:.cpp=.d)

CALC_SRC=src/slang.parser.c src/slang.lexer.c src/parser.c
CALC_OBJ=$(CALC_SRC:.c=.o)
CALC_DEP=$(CALC_SRC:.c=.d)

TESTHEAP_SRC=src/tests/heap.cpp
TESTHEAP_OBJ=$(TESTHEAP_SRC:.cpp=.o)
TESTHEAP_DEP=$(TESTHEAP_SRC:.cpp=.d)

all: core slang

core: libcore.a

libcore.a: $(CORE_OBJ)
	ar -cr $@ $^
	ranlib $@

slang: core $(CALC_OBJ)
	$(CC) -o $@ $(CALC_OBJ) $(LINKFLAGS)

testheap: core $(TESTHEAP_OBJ)
	$(CC) -o $@ $(TESTHEAP_OBJ) $(LINKFLAGS)

.cpp.o:
	$(CC) -o $@ $(CCFLAGS) -c $<

.c.o:
	$(CC) -o $@ $(CCFLAGS) -c $<

#src/%.lexer.c: src/%.l
#	flex --header-file=`dirname $@`/`basename $@ .c`.h -o $@ $^
#
#src/%.parser.c: src/%.y
#	bison -v -d -o $@ $^

# Need to be a bit more explicit here because lexer and parser
# headers are automatically generated, -MMD won't help here

src/slang.lexer.o: src/slang.lexer.c src/slang.parser.h src/parser.h \
	include/context.h include/object.h include/heap.h include/symbol.h \
	include/hashmap.h include/callstack.h include/stack.h include/object.h \
	include/instruction.h include/stack.h include/context.h \
	include/builtins.h include/callstack.h include/exception.h

src/slang.parser.o: src/slang.parser.c src/parser.h include/context.h \
	include/object.h include/heap.h include/symbol.h include/hashmap.h \
	include/callstack.h include/stack.h include/object.h \
	include/instruction.h include/stack.h include/context.h \
	include/builtins.h include/callstack.h include/exception.h \
	src/slang.lexer.h

src/slang.lexer.c src/slang.lexer.h: src/slang.l
	flex --header-file=src/slang.lexer.h -osrc/slang.lexer.c src/slang.l

src/slang.parser.c src/slang.parser.h: src/slang.y
	bison -v -d -o src/slang.parser.c src/slang.y

-include $(CORE_DEP)
-include $(CALC_DEP)

clean:
	rm -f src/*.o
	rm -f src/*.d
	rm -f src/*.lexer.*
	rm -f src/*.parser.*
	rm -f slang
	rm -f testheap
	rm -f libcore.a


