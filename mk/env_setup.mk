ifeq (,$(wildcard config.mk))
$(error Please copy config.def.mk to config.mk before running any make targets. \
	This separation ensures your config isn't tracked into git.)
endif

C_CONFIG_FLAGS = -D"FIBER_LOCK_COMPILE_ASSERTS=($(COMPILE_ASSERTS))"

OBJ =

ifeq ($(ENV),norm)
C_CONFIG_FLAGS+=-D"FIBER_LOCK_BUILD_ENV_NORM"
else ifeq ($(ENV),debug)
C_CONFIG_FLAGS+=-D"FIBER_LOCK_BUILD_ENV_DEBUG" -g
else ifeq ($(ENV),test)
C_CONFIG_FLAGS+=-D"FIBER_LOCK_BUILD_ENV_TEST" -g
else
$(error ENV was invalid.)
endif

ifeq ($(MUTEX_IMPL),posix)
C_CONFIG_FLAGS+=-D"FIBER_LOCK_MUTEX_POSIX"
OBJ+=posix/mutex/mutex_init.o
OBJ+=posix/mutex/mutex_destroy.o
OBJ+=posix/mutex/mutex_lock.o
OBJ+=posix/mutex/mutex_unlock.o
else ifeq ($(MUTEX_IMPL),none)
else
$(error MUTEX_IMPL was invalid. Valid options: posix.)
endif

ifeq ($(SEMAPHORE_IMPL),posix)
C_CONFIG_FLAGS+=-D"FIBER_LOCK_SEMAPHORE_POSIX"
OBJ+=posix/semaphore/sem_init.o
OBJ+=posix/semaphore/sem_destroy.o
OBJ+=posix/semaphore/sem_wait.o
OBJ+=posix/semaphore/sem_trywait.o
OBJ+=posix/semaphore/sem_post.o
OBJ+=posix/semaphore/sem_getvalue.o
else ifeq ($(SEMAPHORE_IMPL),none)
else
$(error SEMAPHORE_IMPL was invalid. Valid options: posix.)
endif

ifeq ($(SPINLOCK_IMPL),posix)
C_CONFIG_FLAGS+=-D"FIBER_LOCK_SPIN_POSIX"
OBJ+=posix/spin/spin_init.o
OBJ+=posix/spin/spin_destroy.o
OBJ+=posix/spin/spin_lock.o
OBJ+=posix/spin/spin_trylock.o
OBJ+=posix/spin/spin_unlock.o
else ifeq ($(SPINLOCK_IMPL),none)
else
$(error SPINLOCK_IMPL was invalid. Valid options: posix.)
endif

ifeq ($(FUTEX_IMPL),linux)
C_CONFIG_FLAGS+=-D"FIBER_LOCK_FUTEX_LINUX"
OBJ+=linux/futex/futex_syscall.o
OBJ+=linux/futex/futex_load.o
OBJ+=linux/futex/futex_set.o
OBJ+=linux/futex/futex_add.o
OBJ+=linux/futex/futex_sub.o
OBJ+=linux/futex/futex_exchange.o
OBJ+=linux/futex/futex_cmp_xchng.o
OBJ+=linux/futex/futex_wait.o
OBJ+=linux/futex/futex_wait_timeout.o
OBJ+=linux/futex/futex_wake.o
else ifeq ($(FUTEX_IMPL),none)
else
$(error FUTEX_IMPL was invalid. Valid options: linux.)
endif

ifeq ($(FIBER_LOCK_ALL_INTERCEPT),1)
FIBER_LOCK_MUTEX_INTERCEPT=1
FIBER_LOCK_SEMAPHORE_INTERCEPT=1
FIBER_LOCK_SPIN_INTERCEPT=1
FIBER_LOCK_FUTEX_INTERCEPT=1
endif

ifeq ($(FIBER_LOCK_MUTEX_INTERCEPT),1)
C_CONFIG_FLAGS+=-D"FIBER_LOCK_MUTEX_INTERCEPT"
endif
ifeq ($(FIBER_LOCK_SEMAPHORE_INTERCEPT),1)
C_CONFIG_FLAGS+=-D"FIBER_LOCK_SEMAPHORE_INTERCEPT"
endif
ifeq ($(FIBER_LOCK_SPIN_INTERCEPT),1)
C_CONFIG_FLAGS+=-D"FIBER_LOCK_SPIN_INTERCEPT"
endif
ifeq ($(FIBER_LOCK_FUTEX_INTERCEPT),1)
C_CONFIG_FLAGS+=-D"FIBER_LOCK_FUTEX_INTERCEPT"
endif

INCLUDES = -I./src -I./include -I./deps/fiber_atomic/include
OBJ_OUT = $(patsubst %, build/%, $(OBJ))

Q = @
cc_cmd_generic_source = $(Q)$(CC) $(C_FLAGS) -c $< -o $@
cc_pretty_print  = @printf "CC $<\n"

ifneq ($(Q),@)
cc_pretty_print =
endif
