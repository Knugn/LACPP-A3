CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -std=c++0x
LIBS =

BIN=bin
OBJ=obj
SRC=src

all:	hello.exe

hello.exe: 	$(OBJ)/hello.o
	mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -o "$(BIN)/$@" $? $(LIBS)

$(OBJ)/%.o: $(SRC)/%.cpp
	mkdir -p $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o "$@" "$<"

clean:
#	rm -f $(OBJ)/* $(BIN)/*
	rm -rf $(OBJ) $(BIN)
