PROGS_mathgame_OBJS := mathgame.o
PROGS_mathgame_OBJS := $(PROGS_mathgame_OBJS:%=$(TDIR)/mathgame/%)
ALL_OBJS += $(PROGS_mathgame_OBJS)

$(TDIR)/bin/mathgame : $(TSTART) $(PROGS_mathgame_OBJS) $(TLIBC)

