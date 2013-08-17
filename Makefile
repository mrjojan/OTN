# define the C compiler to use
CC:= g++ -std=c++11

# define any directories containing header files other than /usr/include
INCLUDES:=-I/usr/include/libxml2 -I/usr/include/glib-2.0 -I/usr/include/gstreamer-1.0 -I/usr/lib/arm-linux-gnueabi/glib-2.0/include

# define library paths in addition to /usr/lib
# if I wanted to include libraries not in /usr/lib I'd specify
# their path using -Lpath, something like:
LFLAGS:=-L/opt/gstreamer/lib/ 

# define any libraries to link into executable:
# if I want to link in libraries (libx.so or libx.a) I use the -llibname 
# option, something like (this will link in libmylib.so and libm.so:
LIBS:= -lgstrtsp-0.10 -lgobject-2.0 -lglib-2.0 -lgstrtspserver-1.0 -lgstreamer-1.0 -lpthread

# define the C++ source files
SRCS:=$(wildcard src/*.cpp)

# compiler flags:
# -g3   adds debugging information to the executable file
# -Wall turns on most, but not all, compiler warnings
# -O0 0 level to synchronization
#  -c for create .o files
CFLAGS:=-O0 -g3 -Wall -c 

# Below we are replacing the suffix .cpp of all words in the macro SRCS
# with the .o suffix
OBJS:=$(addprefix obj/,$(notdir $(SRCS:.cpp=.o)))

#H_FILES:=src/OTNRTSPStreamer.h srs/OTNClient.h src/OTNClientServer.h src/OTNThread.h

#This is for pkg-config
PKG_CONFIG:=`pkg-config --cflags --libs gstreamer-1.0 gstreamer-rtsp-1.0`

# define the executable file ` result
RESULT:= bin/result

$(RESULT):$(OBJS)
	mkdir -p bin
	$(CC) $^ -o $@ $(LFLAGS) $(LIBS)

obj/%.o: src/%.cpp 
	mkdir -p obj
	$(CC) $(INCLUDES) $(CFLAGS) $^ -o $@ $(PKG_CONFIG)

all:
	@echo $(SRCS)
	@echo $(OBJS)	
clean:
	rm -fr bin obj $(RESULT) *.gch
