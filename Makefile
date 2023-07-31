CFLAGS = -Wall -O2 -g
LDFLAGS += -pthread -g -lreadline

COMPAT = compat
DAEMON = daemon

FREQ_SYNC = $(DAEMON)/frequency_synchronization
FREQ_SYNC_SHOW = $(FREQ_SYNC)/show
FREQ_SYNC_CONF = $(FREQ_SYNC)/configure

COMPAT_HDRS = $(COMPAT)/compat.h
COMPAT_OBJS = $(COMPAT)/strlcpy.o

FREQ_SYNC_HDRS = $(FREQ_SYNC_SHOW)/*.h  $(FREQ_SYNC_CONF)/*.h
FREQ_SYNC_OBJS = $(FREQ_SYNC_SHOW)/show.o  $(FREQ_SYNC_CONF)/configure.o

MGMT_CLIENT_HDRS = client.h
MGMT_CLIENT_OBJS = log.o mgmtcli.o commands.o text_writer.o tokenizer.o misc.o show.o configure.o

HDRS = $(FREQ_SYNC_HDRS) $(COMPAT_HDRS) $(MGMT_CLIENT_HDRS)
OBJS = $(FREQ_SYNC_OBJS) $(COMPAT_OBJS) $(MGMT_CLIENT_OBJS)

APP = mgmtclient

all: $(APP)

$(APP): $(HDRS) $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	$(RM) $(COMPAT_OBJS) $(FREQ_SYNC_OBJS) *.o *~ $(APP)
