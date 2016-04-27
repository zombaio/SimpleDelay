CC = g++
DYN = .dll
EXT = 
SRC = ../src/
SDK = ../vst2.x/
FFLAGS = -fmessage-length=0
MFLAGS = -mmmx
CFLAGS = -Wall -std=c++11 -Os -s -c $(MFLAGS) $(FFLAGS) -I$(SDK)
LFLAGS = -Wall -s -shared -static exports.def
LIBS = 

OBJSDK = vstplugmain.o audioeffect.o audioeffectx.o
OBJ = main.o simpledelay.o
BIN = SimpleDelay$(DYN)

all: $(OBJSDK) $(OBJ)
	$(CC) $(LFLAGS) $(OBJ) $(OBJSDK) -o $(BIN) $(LIBS)
	
%.o: $(SRC)%.cpp
	$(CC) $(CFLAGS) -o $@ $<
	
vstplugmain.o: $(SDK)vstplugmain.cpp
	$(CC) $(CFLAGS) -o $@ $<

audioeffect.o: $(SDK)audioeffect.cpp
	$(CC) $(CFLAGS) -o $@ $<
	
audioeffectx.o: $(SDK)audioeffectx.cpp
	$(CC) $(CFLAGS) -o $@ $<
	
clean:
	rm $(OBJSDK) $(OBJ)
