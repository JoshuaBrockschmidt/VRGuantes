# project name
NAME = VRGuantes

# build environment
CC=g++

# source files
SOURCES := $(wildcard src/*.cpp)

# object files
OBJS := $(SOURCES)

# Build flags
INCLUDES    := -Iinclude
BASEFLAGS   := -O2
WARNFLAGS   := -Wall -Wextra -Wshadow -Wcast-align -Wwrite-strings -Winline
WARNFLAGS   += -Wno-attributes -Wno-deprecated-declarations
WARNFLAGS   += -Wno-div-by-zero -Wno-endif-labels -Wfloat-equal
WARNFLAGS   += -Wformat=2 -Wno-format-extra-args -Winit-self
WARNFLAGS   += -Winvalid-pch -Wmissing-format-attribute
WARNFLAGS   += -Wmissing-include-dirs -Wno-multichar -Wshadow
WARNFLAGS   += -Wno-sign-compare -Wswitch -Wsystem-headers
WARNFLAGS   += -Wno-pragmas -Wno-unused-but-set-parameter
WARNFLAGS   += -Wno-unused-but-set-variable -Wno-unused-result
WARNFLAGS   += -Wwrite-strings -Wdisabled-optimization -Wpointer-arith
WARNFLAGS   += -Werror
CFLAGS      := $(INCLUDES) $(BASEFLAGS)
CFLAGS      += -std=c++11

OS := $(shell uname)
ARCH := $(shell uname -m)

ifeq ($(OS), Linux)
  ifeq ($(ARCH), x86_64)
    LEAP_LIBRARY := lib/x64/libLeap.so -Wl,-rpath,lib/x64
  else
    LEAP_LIBRARY := lib/x86/libLeap.so -Wl,-rpath,lib/x86
  endif
else
  # OS X
  LEAP_LIBRARY := lib/libLeap.dylib
endif

all: $(NAME)

# build rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LEAP_LIBRARY)

ifeq ($(OS), Darwin)
	install_name_tool -change @loader_path/libLeap.dylib ../lib/libLeap.dylib Sample
endif

warn: CFLAGS += $(WARNFLAGS)
warn: $(NAME)

debug: CFLAGS += $(WARNFLAGS) -g
debug: $(NAME)

clean:
	rm -f $(NAME)
