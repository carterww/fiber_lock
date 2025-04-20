include config.mk
include common.mk

C_WARNING_FLAGS = -Werror -Wall -Wextra -Wno-unused -Wfloat-equal \
		  -Wdouble-promotion -Wformat-overflow -Wformat=2 \
		  -Wnull-dereference -Wmissing-include-dirs -Wswitch-default \
		  -Wswitch-enum
C_FLAGS = -std=c89 $(C_OPT_FLAGS) $(C_WARNING_FLAGS) $(C_CONFIG_FLAGS) $(INCLUDES)

BIN_DIRS = bin
BUILD_DIRS = build build/posix build/linux \
	     build/posix/mutex build/posix/semaphore build/posix/spin \
	     build/linux/futex
DIRS = $(BIN_DIRS) $(BUILD_DIRS)

Q = @
cc_cmd_generic_source = $(Q)$(CC) $(C_FLAGS) -c $< -o $@
cc_pretty_print  = @printf "CC $<\n"

ifneq ($(Q),@)
	cc_pretty_print =
endif

all: lib

lib: $(DIRS) $(OBJ_OUT)
	@ar rcs bin/lib$(TARGET).a $(OBJ_OUT)
	@printf "ar lib$(TARGET).a\n"

lib_so: C_FLAGS+=-fpic
lib_so: clean $(DIRS) $(OBJ_OUT)
	@$(CC) $(C_FLAGS) -shared -o bin/lib$(TARGET).so $(OBJ_OUT)
	@printf "CC -shared lib$(TARGET).so\n"

build/posix/%.o: C_FLAGS+=-pthread
build/%.o: src/%.c
	$(cc_cmd_generic_source)
	$(cc_pretty_print)

$(DIRS):
	@mkdir $@

clean:
	@find build -type f -exec rm {} +
	@find bin -type f -exec rm {} +

.PHONY: all lib lib_so clean
