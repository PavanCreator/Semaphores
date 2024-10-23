CC = g++ 
CFLAGS = -Iinclude -I /usr/local/include/opencv4/ 
SRC = src
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
EXEC = test
OUTPUT = build


all: $(OUTPUT)/$(EXEC)
$(OUTPUT)/$(EXEC): $(OBJS)
	$(CC) -g -o $@ $^ -pthread -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui -lrt
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS) $(OUTPUT)/$(EXEC) 