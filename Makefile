CC = gcc
CFLAGS = -std=c99 -O3 -Iinclude -Iinclude/ckociemba
LDFLAGS = -lm

SRC = src/main.cpp src/ColorDetector.cpp \
      src/ckociemba/coordcube.c \
      src/ckociemba/cubiecube.c \
      src/ckociemba/facecube.c \
      src/ckociemba/prunetable_helpers.c \
      src/ckociemba/search.c

TEST_SRC = src/test_kociemba.c \
      src/ckociemba/coordcube.c \
      src/ckociemba/cubiecube.c \
      src/ckociemba/facecube.c \
      src/ckociemba/prunetable_helpers.c \
      src/ckociemba/search.c

TARGET = bin/test_opencv
TEST_TARGET = bin/test_kociemba

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) $(LDFLAGS)

test_kociemba: $(TEST_SRC)
	$(CC) -o $(TEST_TARGET) $(TEST_SRC) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET) $(TEST_TARGET)