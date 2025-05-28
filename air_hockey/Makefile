# File:        Makefile
# Author:      Ali Younes    <younes.al@northeastern.edu>
# Co-Author:   Ali Tleis     <tleis.a@northeastern.edu>
# Description: Build instructions for the Air Hockey project

IDIR    = ../include
CC      = g++
CFLAGS  = -I$(IDIR) -g -O0
ODIR    = .
LIBS    = -lncurses

_DEPS =
DEPS  = $(patsubst %,$(IDIR)/%,$(_DEPS))
_OBJ  = main.o slider.o air_hockey.o zone.o ball.o key.o
OBJ   = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

air_hockey: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *~ core $(INCDIR)/*~ air_hockey *.o

etags:
	find . -type f -iname "*.[ch]" | xargs etags --append
# File:        Makefile
# Author:      Ali Younes    <younes.al@northeastern.edu>
# Co-Author:   Ali Tleis     <tleis.a@northeastern.edu>
# Description: Build instructions for the Air Hockey project

IDIR    = ../include
CC      = g++
CFLAGS  = -I$(IDIR) -g -O0
ODIR    = .
LIBS    = -lncurses

_DEPS =
DEPS  = $(patsubst %,$(IDIR)/%,$(_DEPS))
_OBJ  = main.o slider.o air_hockey.o zone.o ball.o key.o
OBJ   = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

air_hockey: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *~ core $(INCDIR)/*~ air_hockey *.o

etags:
	find . -type f -iname "*.[ch]" | xargs etags --append

