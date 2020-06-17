all : lizserver lizclient
lizserver : server.c
	gcc -o lizserver server.c
lizclient : client.c
	gcc -o lizclient client.c
