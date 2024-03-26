# Compiler
CC = g++
CC_FLAGS = -O3
SRC = $(wildcard src/*.cpp)
LIB =
CUDA_SRCS =
CUDA_FLAGS =


# Include directories
INCLUDE_DIRS = -I./include

# Files
TARGET = benchmark
SRC += benchmark.cpp

OBJS =  $(SRC:.cpp=.o)

# Targets
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CC_FLAGS) $(INCLUDE_DIRS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CC) $(CC_FLAGS) $(INCLUDE_DIRS) $(CUDA_FLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
