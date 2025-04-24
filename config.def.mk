CC = cc
TARGET = fiber_lock

# Compile time options that the user can configure. For now, there are two types:
# booleans: These should be represented as 0 or 1
# enum: These should be represented as one of the values commented above it.

# enum { norm | debug | test }
# Build environment
# norm: Default build that should be used for production.
# debug: Debug build that has symbols built in.
# test: Same as debug. Convenience option to sync with Fiber.
ENV=norm

# enum { thread | address | none }
# Sanitizer to use when compiling in debug or test environments.
# thread: Use clang's or gcc's thread sanitizer.
# address: Use clang's or gcc's address sanitizer and other memory related
# sanitizers.
DEBUG_SANITIZE=none

# boolean
# Whether to produce position-independent code (pic). Shared libraries must use
# PIC so this flag will not affect the lib_so target.
PIC=1

# boolean
# Compile assert statements
COMPILE_ASSERTS=1

# enum { gcc | clang }
# Atomic operation implementation to use.
# Note: gcc and clang use the same impl file so no need to switch between the
# two if switching between the two as CC
ATOMIC_OPERATIONS_IMPL=gcc

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

# boolean
# Convenience option that sets all the other FIBER_LOCK_*_INTERCEPT options to
# 1 if it is 1.
FIBER_LOCK_ALL_INTERCEPT=0

# boolean
# Prepends a "_" to the mutex function names so a user can redefine them. This
# is usually used when the user wants to wrap some behavior around the function.
# If this is true, the function will be available via a global var.
FIBER_LOCK_MUTEX_INTERCEPT=0

# boolean
# Prepends a "_" to the semaphore function names so a user can redefine them. This
# is usually used when the user wants to wrap some behavior around the function.
# If this is true, the function will be available via a global var.
FIBER_LOCK_SEMAPHORE_INTERCEPT=0

# boolean
# Prepends a "_" to the spinlock function names so a user can redefine them. This
# is usually used when the user wants to wrap some behavior around the function.
# If this is true, the function will be available via a global var.
FIBER_LOCK_SPIN_INTERCEPT=0

# boolean
# Prepends a "_" to the futex function names so a user can redefine them. This
# is usually used when the user wants to wrap some behavior around the function.
# If this is true, the function will be available via a global var.
FIBER_LOCK_FUTEX_INTERCEPT=0
