rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

CC = gcc

ifeq ($(OS),Windows_NT)
OUT_NAME = joy.dll
RM = del
PLATFORM_FILES = $(call rwildcard,windows,*.c)
EXTRA_FLAGS = "-DWINDOWS=" -Wl,--subsystem,windows
else
OUT_NAME = libjoy.so
RM = rm
PLATFORM_FILES = $(call rwildcard,linux,*.c)
EXTRA_FLAGS =
endif

COMMON_FILES = $(call rwildcard,common,*.c)

all: $(OUT_NAME)

$(OUT_NAME):
	$(CC) -shared $(COMMON_FILES) $(PLATFORM_FILES) -o $(OUT_NAME) -fPIC $(EXTRA_FLAGS) -g

clean:
	-$(RM) $(OUT_NAME)

.PHONY: $(OUT_NAME)
