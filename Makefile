include config.mk
include mk/env_setup.mk
include mk/flags.mk

BUILD_DIRS = build build/posix build/linux \
	     build/posix/mutex build/posix/semaphore build/posix/spin \
	     build/linux/futex
DIRS = lib $(BUILD_DIRS)

all: lib_static

lib_static: lib/lib$(TARGET).a

lib/lib$(TARGET).a: $(DIRS) $(OBJ_OUT)
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
	@find lib -type f -exec rm {} +

.PHONY: all lib_static lib_so clean
