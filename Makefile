CFLAGS = -Wall -O2 -g
LDFLAGS += -pthread -g -lreadline

COMPAT = compat

COMPAT_HDRS = $(COMPAT)/compat.h
COMPAT_OBJS = $(COMPAT)/strlcpy.o

HDRS = $(COMPAT_HDRS) client.h
OBJS = $(COMPAT_OBJS) log.o mgmtcli.o commands.o text_writer.o tokenizer.o misc.o

APP = mgmtclient

all: $(APP)

$(APP): $(HDRS) $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	$(RM) $(COMPAT)/*.o *.o *~ $(APP)
