CC=g++

CFLAGS=-Wall -std=c99 

LDFLAGS=-I ./include/ 

TARGET=-o tiletakeout 

SDIR=src

ODIR=obj
	  
blocker : src/main.o src src/cgame.o src/cintroscrn.o
	${CC} ${CFLAGS} ${LDFLAGS} ${TARGET} src/main.o src/cgame.o src/cintroscrn.o \
		-L./gamelibrary -lgamelib -lmingw32 -lSDLmain -lSDL -lSDL_ttf -lSDL_image -mconsole 
clean:
	-del $(SDIR)\*.o
	-del tiletakeout
