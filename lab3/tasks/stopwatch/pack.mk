PROGS_STOPWATCH_OBJS := stopwatch.o
PROGS_STOPWATCH_OBJS := $(PROGS_STOPWATCH_OBJS:%=$(TDIR)/stopwatch/%)
ALL_OBJS += $(PROGS_STOPWATCH_OBJS)

$(TDIR)/bin/stopwatch : $(TSTART) $(PROGS_STOPWATCH_OBJS) $(TLIBC)

