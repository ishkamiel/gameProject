RM = /bin/rm
CC = /usr/bin/g++

BUILD_DIR = build

########################
# Build config     
########################

#CC_FLAGS = -std=c++11 -g -Wall -lGL -lGLU -lglut 
CC_FLAGS = -std=c++11 -g -Wall
LD_FLAGS = 

CPP_DIR = src
OBJ_DIR = $(BUILD_DIR)/obj
CPP_FILES = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJ_FILES = $(subst src/, $(OBJ_DIR)/, $(CPP_FILES:.cpp=.o))

########################
# Test config
########################

T_BIN = $(BUILD_DIR)/run_tests

T_CC_FLAGS = $(CC_FLAGS) 
T_LD_FLAGS = $(LD_FLAGS) -Wl,--no-as-needed -lcppunit

T_CPP_DIR = test
T_OBJ_DIR = $(BUILD_DIR)/ojb_t
T_CPP_FILES = $(wildcard $(T_CPP_DIR)/*.cpp) $(wildcard $(T_CPP_DIR)/*/*.cpp)
T_OBJ_FILES = $(subst $(T_CPP_DIR)/, $(T_OBJ_DIR)/, $(T_CPP_FILES:.cpp=.o))
	
########################
# Targets
########################

default: test

all: clean build build_test

clean:
	$(RM) -rf $(T_OBJ_DIR) $(OBJ_DIR) $(T_BIN)

########################
# Build targets
########################

build: $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(CPP_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -o $@ -c $<

########################
# Testings targets
########################

test: build build_test
	valgrind -q --leak-check=yes ./$(T_BIN)

$(T_OBJ_DIR)/%.o: $(T_CPP_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(T_CC_FLAGS) -o $@ -c $<

build_test: $(T_OBJ_FILES)
	$(CC) $(T_LD_FLAGS) -o $(T_BIN) $^
	#$(CC) $(TEST_LD_FLAGS) -o $@ $^

