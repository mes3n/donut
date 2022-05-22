# Variables to control Makefile operation

CC = g++
MYDIR = .
SRC_DIR = $(MYDIR)/src
OBJ_DIR = $(MYDIR)/obj
BIN_DIR = $(MYDIR)/bin
CFLAGS = -Wall -g
LDFLAGS = -Wall -g

# create list of object files from source files but replace ".cpp" and "src"
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp))


main: $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $(BIN_DIR)/$@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

all: clean main


.PHONY: clean
clean:
	rm -r $(BIN_DIR) $(OBJ_DIR)
	mkdir $(BIN_DIR) $(OBJ_DIR)
