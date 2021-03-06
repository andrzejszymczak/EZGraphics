
CC = g++ 
OPT =  -Wall -I/usr/include/glm -I.  -O2
LIBOPT =  -L/usr/lib/nvidia-331/ -lglut -lGL -lGLEW
SOURCES = buffer.cpp framebuffer.cpp glutwrapper.cpp handlerbase.cpp menucreator.cpp mesh.cpp program.cpp shader.cpp texture.cpp tfprogram.cpp trackballhandler.cpp vertexarray.cpp 
OBJECTS = $(subst .cpp,.o,$(SOURCES))

all : $(SOURCES) demo1 demo2 demo3 demo4 depthpeel teapot

demo1 : $(OBJECTS) demo1.o Makefile
	$(CC) $(OPT) -o demo1 $(OBJECTS) demo1.o $(LIBOPT)

demo2 : $(OBJECTS) demo2.o Makefile
	$(CC) $(OPT) -o demo2 $(OBJECTS) demo2.o $(LIBOPT)

demo3 : $(OBJECTS) demo3.o Makefile
	$(CC) $(OPT) -o demo3 $(OBJECTS) demo3.o $(LIBOPT)

demo4 : $(OBJECTS) demo4.o Makefile
	$(CC) $(OPT) -o demo4 $(OBJECTS) demo4.o $(LIBOPT)

depthpeel : $(OBJECTS) depthpeel.o Makefile
	$(CC) $(OPT) -o depthpeel $(OBJECTS) depthpeel.o $(LIBOPT)

teapot : $(OBJECTS) teapot.o Makefile
	$(CC) $(OPT) -o teapot $(OBJECTS) teapot.o $(LIBOPT)

%.o: %.cpp *.h Makefile
	$(CC) $(OPT) -c -o $@ $< 

doc :
	doxygen

clean : 
	rm *.o demo1 demo2 demo3 demo4 depthpeel teapot
	rm -rf html latex

