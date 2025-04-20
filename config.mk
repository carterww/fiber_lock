CC = cc
C_OPT_FLAGS = -O2
TARGET = fiber_lock

# boolean
# Compile assert statements
COMPILE_ASSERTS=1

# enum { posix }
# Mutex implementation
MUTEX_IMPL=posix

# enum { posix }
# Semaphore implementation
SEMAPHORE_IMPL=posix

# enum { posix }
# Spinlock implementation
SPINLOCK_IMPL=posix

# enum { linux }
# Futex implementation
FUTEX_IMPL=linux
