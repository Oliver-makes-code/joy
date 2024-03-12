CC = gcc

ifeq ($(OS),Windows_NT)
OUT_NAME = joy.dll
RM = del
FLAGS = "-DWINDOWS="
else
OUT_NAME = libjoy.so
RM = rm
endif

ifeq ($(OS),Windows_NT)
all: common.o windows.o
	$(CC) -shared common.o windows.o -o $(OUT_NAME) $(FLAGS)  -Wl,--subsystem,windows
else
all: common.o linux.o
	$(CC) -shared common.o linux.o -o $(OUT_NAME) $(FLAGS)
endif

common.o:
	$(CC) -c common/*.c -o common.o $(FLAGS)

linux.o:
	$(CC) -c linux/*.c -o linux.o $(FLAGS)

windows.o:
	$(CC) -c windows/*.c -o windows.o $(FLAGS)

clean:
	-$(RM) common.o
	-$(RM) windows.o
	-$(RM) linux.o
	-$(RM) $(OUT_NAME)
