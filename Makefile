IDIR=include
ODIR=obj
LDIR=lib
OLDIR=$(ODIR)/lib


CC = gcc
CFLAGS = -Wall -g
LIBS=
DEPS=$(IDIR)/$(wildcard *.h)
SOURCES=$(wildcard *.c)
MY_LIBS=$(wildcard $(LDIR)/*.c)
SOURCES_OBJ=$(patsubst %.c,$(ODIR)/%.o,$(SOURCES))
MY_LIBS_OBJ=$(foreach o, $(patsubst %.c,%.o,$(MY_LIBS)), $(ODIR)/$o)

print-% : ; @echo $* = $($*)

$(ODIR)/%.o : %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

program: $(SOURCES_OBJ) $(MY_LIBS_OBJ)
	$(CC) $(CFLAGS) $(wildcard $(ODIR)/*.o)  $(wildcard $(OLDIR)/*.o) -o program $(LIBS)

clean:
	rm obj/*.o
	rm obj/lib/*.o
	rm program