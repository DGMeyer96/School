#sample Makefile for using OpenGL of Red Hat Linux 7.x
#CS 420, Tong Yu, Fall 2002

#PROG	= env-sphere
#PROG	= env-torus
#PROG	= genspheremap
PROG	= environment-map

CFLAGS	= -w -s -O2 -ansi -DSHM
XLIBS	= -lX11 -lXext  -lSDL
LIBS	= -lglut -lGLU -lGL  -ltiff -lpng12
LIBDIR	= -L/usr/X11/lib -L/usr/X11R6/lib 
LIBSDL =  -L/usr/local/lib -Wl,-rpath,/usr/local/lib -lSDL  -lSDL_image -lSDL_mixer
INCLS	= -I/usr/X11R/include -I/share/mesa/include -I../ -I$(TOP)/include -I$(UTILDIR) -I$(UTILDIR)/canvas -I$(UTILDIR)/../imageio -I../../util/imageio

UTILOBJS =  ../../util/imageio/imageio.o 
#source codes
DIR=../
SRCS = $(PROG).cpp 
OBJ1 = $(SRCS:.cpp=.o)  
#OBJ1 = $(SRCS:.cpp=.o) scene.o 
#substitute .cpp by .o to obtain object filenames
OBJS =  

#$< evaluates to the target's dependencies, 
#$@ evaluates to the target

$(PROG): $(OBJS)  $(OBJ1)
	g++ -o $@ $(OBJS) $(OBJ1) $(UTILOBJS) $(LIBDIR) $(LIBS) $(XLIBS) $(LIBSDL)

$(OBJS): 
	echo $(INCLS)
	gcc -c  $*.c $(INCLS)

$(OBJ1):
	g++ -c $*.cpp $(INCLS)  

run:
	export LD_LIBRARY_PATH=.; ./$(PROG)  #for tiff


clean:
	rm $(OBJ1)

clean1:
	rm ../$(temp)

