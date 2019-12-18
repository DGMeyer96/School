
PROG	= render
TOP     = /usr/include/GL
CFLAGS  =  -w -s -O2 -ansi -DSHM
LIBS    = -lglut -lGLU -lGL 
INCLS   = -I/usr/X11R/include -I$(TOP) -I../
LIBDIR  = -L/usr/X11/lib -L/usr/X11R6/lib

#source codes
SRCS = $(PROG).cpp

#substitute .cpp by .o to obtain object filenames
OBJS = $(SRCS:.cpp=.o) 
OBJS1 = ../Point3.o  ../XYZ.o ../Vector3.o
OBJS2 = Matrix44.o Matrix41.o Matrix14.o Matrix4.o
OBJS3 = seashell.o pawns.o vase.o
#$< evaluates to the target's dependencies, 
#$@ evaluates to the target

$(PROG): $(OBJS) $(OBJS1) $(OBJS2) $(OBJS3)
	g++ -o $@ $(OBJS) $(OBJS1) $(OBJS2) $(OBJS3) $(LIBDIR) $(LIBS) $(XLIBS) 
	g++ -o testmat testmat.cpp $(OBJS1) $(OBJS2) $(LIBDIR) $(LIBS) $(XLIBS) $(INCLS)
	g++ -o prism prism.cpp $(OBJS1) $(OBJS2) $(LIBDIR) $(LIBS) $(XLIBS) $(INCLS)
	g++ -o prism1 prism1.cpp $(OBJS1) $(OBJS2) $(LIBDIR) $(LIBS) $(XLIBS) $(INCLS)
	g++ -o tube tube.cpp $(OBJS1) $(OBJS2) $(LIBDIR) $(LIBS) $(XLIBS) $(INCLS)
	g++ -o helix-tube1 helix-tube1.cpp $(OBJS1) $(OBJS2) $(LIBDIR) $(LIBS) $(XLIBS) $(INCLS) 
	g++ -o conic-helix conic-helix.cpp $(OBJS1) $(OBJS2) $(LIBDIR) $(LIBS) $(XLIBS) $(INCLS) 

$(OBJS): 
	g++ -c  $*.cpp $(INCLS) 

$(OBJS1): 
	g++ -c  $*.cpp $(INCLS) 

$(OBJS2):
	g++ -c  $*.cpp $(INCLS) 

$(OBJS3):
	g++ -c  $*.cpp $(INCLS) 

clean:
	rm *.o $(PROG); rm testmat prism prism1 tube helix-tube1  

