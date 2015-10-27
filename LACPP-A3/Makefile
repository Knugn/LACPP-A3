CXXFLAGS = -std=c++0x -O2 -g -Wall -pthread  -fgnu-tm -fmessage-length=0
LIBS =
# -fgnu-tm
SRC=src
OBJ=obj
BIN=bin
DBG=$(BIN)/debug
RLS=$(BIN)/release

all:	 $(BIN)/transactions.exe $(BIN)/exercise3.exe $(BIN)/exercise4.exe $(BIN)/exercise5.exe $(BIN)/relaxed.exe $(BIN)/work-stealing.exe

$(BIN)/exercise3.exe: $(OBJ)/exercise3.o $(OBJ)/deque.o
	mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -o "$@" "$?" $(LIBS)

$(BIN)/work-stealing.exe: $(OBJ)/work-stealing.o $(OBJ)/deque.o
	mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -o "$@" "$?" $(LIBS)

#hello.exe: 	$(OBJ)/hello.o
#	mkdir -p $(BIN)
#	$(CXX) $(CXXFLAGS) -o "$(BIN)/$@" $? $(LIBS)

# Generic binary make target for single object file
$(BIN)/%.exe: 	$(OBJ)/%.o
	mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -o "$@" "$?" $(LIBS)

$(OBJ)/%.o: $(SRC)/%.cpp
	mkdir -p $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o "$@" "$<"

clean:
	rm -rf $(OBJ) $(BIN)

# Please make, don't remove our .o files
.PRECIOUS: $(OBJ)/%.o
