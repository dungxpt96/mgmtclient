CFLAGS = -Wall -O2 -g
LDFLAGS += -pthread -g -lreadline

COMPAT = compat
DAEMON = daemon

LIB = lib

LIB_HDRS = $(LIB)/*.h
LIB_SRCS =  $(shell ls $(LIB)/*.c)
LIB_OBJS = $(LIB_SRCS:.c=.o)

FREQ_SYNC = $(DAEMON)/freqsync

FREQ_SYNC_SHOW = $(FREQ_SYNC)/show
FREQ_SYNC_CONF = $(FREQ_SYNC)/configure

FREQ_SYNC_GLOB_HDRS = $(FREQ_SYNC)/*.h
FREQ_SYNC_GLOB_SRCS = $(shell ls $(FREQ_SYNC)/freqsync*.c)
FREQ_SYNC_GLOB_OBJS = $(FREQ_SYNC_GLOB_SRCS:.c=.o)

FREQ_SYNC_SHOW_HDRS = $(FREQ_SYNC_SHOW)/*.h
FREQ_SYNC_SHOW_SRCS = $(shell ls $(FREQ_SYNC_SHOW)/freqsync*.c)
FREQ_SYNC_SHOW_OBJS = $(FREQ_SYNC_SHOW_SRCS:.c=.o)

FREQ_SYNC_CONF_HDRS = $(FREQ_SYNC_CONF)/*.h
FREQ_SYNC_CONF_SRCS = $(shell ls $(FREQ_SYNC_CONF)/freqsync*.c)
FREQ_SYNC_CONF_OBJS = $(FREQ_SYNC_CONF_SRCS:.c=.o)

FREQ_SYNC_HDRS = $(FREQ_SYNC_SHOW_HDRS)  $(FREQ_SYNC_CONF_HDRS) $(FREQ_SYNC_GLOB_HDRS)
FREQ_SYNC_OBJS = $(FREQ_SYNC_SHOW_OBJS)  $(FREQ_SYNC_CONF_OBJS) $(FREQ_SYNC_GLOB_OBJS)

COMPAT_HDRS = $(COMPAT)/compat.h
COMPAT_OBJS = $(COMPAT)/strlcpy.o

MGMT_CLIENT_HDRS = client.h
MGMT_CLIENT_OBJS = log.o commands.o text_writer.o tokenizer.o misc.o show.o configure.o

MGMT_SERVER_HDRS = mgmt_server.h
MGMT_SERVER_OBJS = mgmt_server.o

APP_OBJS = mgmtcli.o

HDRS = $(LIB_HDRS) $(FREQ_SYNC_HDRS) $(COMPAT_HDRS) $(MGMT_CLIENT_HDRS) $(MGMT_SERVER_HDRS)
OBJS = $(LIB_OBJS) $(FREQ_SYNC_OBJS) $(COMPAT_OBJS) $(MGMT_CLIENT_OBJS) $(MGMT_SERVER_OBJS)

APP = mgmtclient

all: $(APP) server

$(APP): $(HDRS) $(OBJS) $(APP_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

server: server.o $(HDRS) $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	$(RM) $(OBJS) $(APP_OBJS) *~ *.o

distclean: clean
	$(RM) $(APP) server