CC=gcc
EDIT=/usr/bin/vim -p
EXEC=lg_cmd

comp: clean
	$(CC) -I. -o $(EXEC)  daemon.c 

clean:
	rm -frv $(EXEC)
edit:
	$(EDIT) *.c *.h
