CC=gcc
EDIT=/usr/bin/vim -p

comp: clean
	$(CC) -I. -o log_cmd deamon.c 

clean:
	rm -frv log_cmd
edit:
	$(EDIT) *.c *.h
