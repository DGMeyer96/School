#sample Makefile for using OpenGL of Red Hat Linux 7.x
#CS 420, Tong Yu, Fall 2002

PROG	= maze
CFLAGS	= -w -s -O2 -ansi -DSHM
XLIBS	= -lX11 -lXext -lXmu -lXext -lXmu -lXt -lXi -lSM -lICE 
#-lSDL
LIBS	= -lglut -lGLU -lGL  -ltiff -lpng -lGLEW -libSOIL.a
LIBDIR	= -L/usr/X11/lib -L/usr/X11R6/lib  -L../  -L.
INCLS	= -I/usr/X11R/include -I../SOIL -I../ 

#source codes
DIR=../
SRCS = $(PROG).cpp Shader.cpp
#OBJ1 = $(SRCS:.cpp=.o) 
#OBJ1 = $(SRCS:.cpp=.o) scene.o 
#substitute .cpp by .o to obtain object filenames
#OBJS =  $(OBJ1)  Shader.o 
OBJ1 = $(SRCS:.cpp=.o) 

#$< evaluates to the target's dependencies, 
#$@ evaluates to the target

$(PROG): $(OBJS)  $(OBJ1)
	g++ -o $@ $(OBJS) $(OBJ1) $(LIBDIR) $(LIBS) $(XLIBS)

$(OBJS): 
	echo $(INCLS)
	gcc -c  $*.c $(INCLS)

$(OBJ1):
	g++ -c $*.cpp $(INCLS)  

clean:
	rm $(OBJ1) $(PROG)