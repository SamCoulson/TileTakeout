CC=g++

CFLAGS=-Wall -std=c99 

LDFLAGS=-I ./include/ 

TARGET=-o tiletakeout 

SDIR=src

ODIR=obj
	  
blocker : src/main.o src/csdlgraphics.o src/cgrid.o src/cgame.o src/ccollision.o src/cintroscrn.o
	${CC} ${CFLAGS} ${LDFLAGS} ${TARGET} src/main.o src/csdlgraphics.o src/cgrid.o src/cgame.o src/ccollision.o \
		src/cintroscrn.o -lmingw32 -lSDLmain -lSDL -lSDL_ttf -lSDL_image -mconsole 
clean:
	-del $(SDIR)\*.o
	-del tiletakeout
