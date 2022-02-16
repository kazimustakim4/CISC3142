CC=g++
CFLAGS = -g -wall
all: $(TARGET)
$(TARGET) : clean compile run
compile: file_in.cpp
	$(CC) $(CFLAGS) -o $(TARGET) file_in.cpp
clean:
	$(RM) $(TARGET)
run:
	./${TARGET}