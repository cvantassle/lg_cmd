CC=gcc
EDIT=/usr/bin/vim -p
DBIN=lg_daemon
CBIN=lg_client

all: clean client daemon

daemon: 
	$(CC) -I. -o $(DBIN)  daemon.c 

clean:
	rm -frv $(DBIN)
	rm -frv $(CBIN)

edit:
	$(EDIT) *.c *.h

client:
	$(CC) -I. -o $(CBIN) client.c
