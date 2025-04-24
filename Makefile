include config.mk
include mk/env_setup.mk
include mk/flags.mk

BIN_DIRS = bin
BUILD_DIRS = build build/posix build/linux \
	     build/posix/mutex build/posix/semaphore build/posix/spin \
	     build/linux/futex
DIRS = $(BIN_DIRS) $(BUILD_DIRS)

all: lib

lib: bin/lib$(TARGET).a

lib_standalone: bin/lib$(TARGET)_standalone.a

bin/lib$(TARGET).a: $(DIRS) $(OBJ_OUT)
	@ar rcs $@ $(OBJ_OUT)
	@printf "ar $@\n"

bin/lib$(TARGET)_standalone.a: $(DIRS) $(OBJ_OUT)
	@ar rcs $@ $(OBJ_OUT)
	@printf "ar $@\n"

build/posix/%.o: C_FLAGS+=-pthread
build/%.o: src/%.c
	$(cc_cmd_generic_source)
	$(cc_pretty_print)

$(DIRS):
	@mkdir $@

clean:
	@find build -type f -exec rm {} +
	@find bin -type f -exec rm {} +

.PHONY: all lib lib_standalone lib_so clean
