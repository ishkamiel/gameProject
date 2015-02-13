
RM = /bin/rm
CC = /usr/bin/g++
CC_FLAGS = -std=c++11 -g -Wall -lGL -lGLU -lglut 
LD_FLAGS = 

CPP_FILES = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
#//OBJ_FILES = $(addprefix obj/, $(notdir $(CPP_FILES:.cpp=.o)))
OBJ_FILES = $(subst src/, obj/, $(CPP_FILES:.cpp=.o))

default: test

test: build
	valgrind -q --leak-check=yes ./build

build: $(OBJ_FILES)
	$(CC) $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp
	#mkdir -p obj
	mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -o $@ -c $<

clean:
	$(RM) -rf obj run_tests obj_test
