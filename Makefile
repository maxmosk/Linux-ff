.PHONY: all clean debug


CC=gcc
CFLAGS=-DNDEBUG -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith \
    -Wcast-align -Wstrict-prototypes -Wstrict-overflow=2 -Wwrite-strings \
    -Waggregate-return -Wcast-qual -Wswitch-default -Wswitch-enum -Wconversion \
    -Wunreachable-code -Wformat=2 -Winit-self -Wuninitialized \
    -Wpointer-arith -Wold-style-definition -Wstrict-prototypes \
    -Wmissing-prototypes -Werror-implicit-function-declaration -Wlogical-op \
    -Wduplicated-cond -Wcast-qual -Wcast-align -Wformat-security \
    -Wlarger-than=32768 -Wstack-usage=8192 -Wmissing-declarations \
    -Wchar-subscripts -Wno-varargs -Wunused -Wvariadic-macros \
    -Wno-missing-field-initializers -Wno-narrowing -Wswitch-default \
    -Wsync-nand -Wsuggest-final-types -Wsign-conversion \
    -Wsuggest-attribute=noreturn -Winline -Wopenmp-simd -Wpacked \
    -Wredundant-decls -Waggressive-loop-optimizations -Wempty-body \
    -Wformat-nonliteral -Wformat-signedness -pedantic -std=c99 -I$(HEADERDIR)
CLDFLAGS=


SOURCEDIR=src/code
HEADERDIR=src/include
BUILDDIR=build
SOURCES=$(wildcard $(SOURCEDIR)/*.c)
HEADFILES=$(wildcard $(HEADERDIR)/*.h)
OBJFILES=$(patsubst $(SOURCEDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
EXECUTABLE=$(BUILDDIR)/ff


all: $(BUILDDIR) $(EXECUTABLE)


debug: CFLAGS+= -ggdb3 -O0 \
    -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr \
    -pie -fcheck-new -fstack-check -fstack-protector -fstrict-overflow \
    -flto-odr-type-merging -fno-omit-frame-pointer -fPIE -UNDEBUG -DDEBUG_PRINT
debug: CLDFLAGS+= -lasan
debug: all


$(BUILDDIR):
	mkdir $(BUILDDIR)

$(EXECUTABLE): $(OBJFILES)
	$(CC) $(CLDFLAGS) $(CFLAGS) -o $@ $(BUILDDIR)/*.o

$(OBJFILES): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.c $(HEADFILES)
	$(CC) -c $(CFLAGS) -o $@ $<


clean:
	rm -rf $(BUILDDIR)

