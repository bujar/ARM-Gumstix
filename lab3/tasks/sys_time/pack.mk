PROGS_SYS_TIME_OBJS := sys_time.o
PROGS_SYS_TIME_OBJS := $(PROGS_SYS_TIME_OBJS:%=$(TDIR)/sys_time/%)
ALL_OBJS += $(PROGS_SYS_TIME_OBJS)

$(TDIR)/bin/sys_time : $(TSTART) $(PROGS_SYS_TIME_OBJS) $(TLIBC)
