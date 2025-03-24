CC = g++
CFLAGS = -Iinclude -I/c/opencv/install/include -L/c/opencv/install/x64/mingw/lib \
         -lopencv_core4120 -lopencv_highgui4120 -lopencv_imgcodecs4120 -lopencv_imgproc4120
SRC = src/main.cpp src/ColorDetector.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = bin/test_opencv

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS)

clean:
	rm -f bin/test_opencv