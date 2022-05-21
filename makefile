all: zapni odpni
zapni: zapni.c
	gcc -pthread -o pzip pzip.c -Wall
odpni: odpni.c
	gcc -pthread -o punzip punzip.c -Wall
