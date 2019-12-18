
PROG	= maze
TOP = /usr/include/GL
CFLAGS	= -w -s -O2 -ansi -DSHM
LIBS	= -lglut -lGLU -lGL -lGLEW -ltiff -lpng12 
INCLS   = -I/usr/X11R/include   -I/facstaff/class/cs520/imageio
LIBDIR  = -L/usr/X11/lib -L/usr/X11R6/lib
IMGIO = /facstaff/class/cs520/imageio/imageio.o

#-L$(SHADER_DIR)/lib
#source codes
SRCS = $(PROG).cpp  Cube.cpp
#substitute .cpp by .o to obtain object filenames
OBJ1 = $(SRCS:.cpp=.o)
OBJS = $(OBJ1)  Shader.o 

#$< evaluates to the target's dependencies, 
#$@ evaluates to the target

$(PROG): $(OBJS)
	g++ -o $@ $(OBJS)  $(LIBDIR) $(LIBS) $(XLIBS) $(IMGIO)

$(OBJS): 
	g++ -c  $*.cpp $(INCLS) 

clean:
	rm $(OBJ1) $(PROG)

