rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

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
all: common.a windows.a
	$(CC) -shared common.a windows.a -o $(OUT_NAME) $(FLAGS)  -Wl,--subsystem,windows
else
all: common.a linux.a
	$(CC) -shared common.a linux.a -o $(OUT_NAME) $(FLAGS)
endif

common.a: $(subst .c,.o,$(call rwildcard,common,*.c))
	ar rcs common.a $(call rwildcard,common,*.o)

linux.a: $(subst .c,.o,$(call rwildcard,linux,*.c))
	ar rcs linux.a $(call rwildcard,linux,*.o)

windows.a: $(subst .c,.o,$(call rwildcard,windows,*.c))
	ar rcs windows.a $(call rwildcard,windows,*.o)

*.o:
	$(CC) -c $(subst .o,.c,$@) -o $@ $(FLAGS)

clean:
	-$(RM) common.a
	-$(RM) windows.a
	-$(RM) linux.a
	-$(RM) $(OUT_NAME)
	-$(RM)  $(call rwildcard,.,*.o)
