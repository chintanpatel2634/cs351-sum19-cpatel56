CC      = gcc
CFLAGS  = -g -Wall

all: mycat myzip myunzip

mycat myzip myunzip: % : %.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJS) mycat myzip myunzip
