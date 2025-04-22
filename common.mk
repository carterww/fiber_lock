C_CONFIG_FLAGS = -D"FIBER_LOCK_COMPILE_ASSERTS=($(COMPILE_ASSERTS))"

OBJ =

ifeq ($(MUTEX_IMPL),posix)
	C_CONFIG_FLAGS+=-D"FIBER_LOCK_MUTEX_POSIX"
	OBJ+=posix/mutex/mutex_init.o
	OBJ+=posix/mutex/mutex_destroy.o
	OBJ+=posix/mutex/mutex_lock.o
	OBJ+=posix/mutex/mutex_unlock.o
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
else
	$(error FUTEX_IMPL was invalid. Valid options: linux.)
endif

INCLUDES = -I./include -I./src -I./deps/fiber_atomic/include
OBJ_OUT = $(patsubst %, build/%, $(OBJ))
