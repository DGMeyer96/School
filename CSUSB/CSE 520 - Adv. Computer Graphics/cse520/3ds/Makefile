#sample Makefile for using OpenGL of Red Hat Linux 7.x
#CS 420, Tong Yu, Fall 2002

PROG	=  display_3ds
CFLAGS	= -w -s -O2 -ansi -DSHM
XLIBS	= -lX11 -lXext -lXmu -lXext -lXmu -lXt -lXi -lSM -lICE
LIBS	= -lglut -lGLU -lGL -lib3ds.a
LIBDIR	= -L/usr/X11/lib -L/usr/X11R6/lib  -L/home/csusb.edu/005051094/cse520/3ds  -L. 
SRCS = $(PROG).cpp
#source codes
#substitute .cpp by .o to obtain object filenames
OBJ1 = $(SRCS:.cpp=.o)
OBJS =  $(OBJ1)  main.o 3dsdump.o

#$< evaluates to the target's dependencies, 
#$@ evaluates to the target

$(PROG): $(OBJS)
	g++ -o $@ $(OBJS)  $(LIBDIR) $(LIBS) $(XLIBS)

$(OBJS): 
	g++ -c  $*.cpp $(INCLS) 

run:
	export LD_LIBRARY_PATH=/usr/lib64; ./$(PROG)


clean:
	rm $(OBJ1) 

