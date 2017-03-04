################################################################################
#
# iChargerMon Makefile
#
################################################################################

# Sources ######################################################################

SRCS = src/main.cpp
SRCS += src/serial_icharger.cpp
SRCS += src/serial_icharger_state.cpp
SRCS += src/mod_bus_icharger.cpp

# Binary Targets ###############################################################

BIN = ichargermon

# Compiler Flags ###############################################################

CFLAGS  = -std=c++11
CFLAGS += -Isrc/
CFLAGS += -Wall
CFLAGS += `pkg-config --cflags $(LIBHIDAPI)`

# HIDAPI Support ###############################################################

# When targetting Linux there are two options given for hidapi, but neither are
# called 'hidapi' which mandates the use of this condition.

HOST_OS = $(shell uname)

ifeq ($(HOST_OS), Linux)
LIBHIDAPI = hidapi-libusb
else
LIBHIDAPI = hidapi
endif

# Linker Flags #################################################################

LDFLAGS = `pkg-config --libs $(LIBHIDAPI)`

# Build Targets ################################################################

all: $(BIN)

$(BIN): $(SRCS)
	g++ $(CFLAGS) $(LDFLAGS) $^ -o $@

run_ichargermon: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)
