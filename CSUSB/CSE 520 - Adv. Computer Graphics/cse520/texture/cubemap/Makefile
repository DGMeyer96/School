# Makefile for CS 520 using glsl
# T.L. Yu, Feb. 2009

#PROG = particle
PROG=cubemap
#TOP = /pool/u/class/cs520/Mesa-7.0.3

#include $(TOP)/configs/current

INCDIR =   -I/pool/u/class/cs520/imageio/

#LIBS = -L$(TOP)/lib -l$(GLUT_LIB) -l$(GLU_LIB) -l$(GL_LIB) $(APP_LIB_DEPS) -L$(TOP)/../glew/lib -lGLEW 
LIBS    = -lglut -lGLU -lGL -lGLEW -ltiff  -lpng12

IMGIO = /pool/u/class/cs520/imageio/imageio.o


#source codes
SRCS = $(PROG).cpp
#substitute .cpp by .o to obtain object filenames
OBJS = $(SRCS:.cpp=.o) 

CC=g++

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@ $(IMGIO)

$(OBJS): $(SRCS) 
	$(CC) -c $*.cpp $(INCDIR)

run:
	export LD_LIBRARY_PATH=$(TOP)/lib; ./$(PROG)  

clean:
	-rm -f $(OBJS)  *~
