rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

CC = gcc

ifeq ($(OS),Windows_NT)
OUT_NAME = joy.dll
RM = del
PLATFORM_BIN = windows.a
EXTRA_FLAGS = "-DWINDOWS=" -Wl,--subsystem,windows
else
OUT_NAME = libjoy.so
RM = rm
PLATFORM_BIN = linux.a
EXTRA_FLAGS =
endif

BUILD_COMMAND = -shared -Wl,--whole-archive common.a $(PLATFORM_BIN) -Wl,--no-whole-archive -o $(OUT_NAME)

all: common.a $(PLATFORM_BIN)
	$(CC) $(BUILD_COMMAND) $(EXTRA_FLAGS)

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
