#ifndef _FIBER_LOCK_FUTEX_LINUX_SYSCALL_H
#define _FIBER_LOCK_FUTEX_LINUX_SYSCALL_H

#define _POSIX_C_SOURCE 199309L
#define _GNU_SOURCE

#include <stdint.h>
#include <time.h>

long _fiber_lock_futex_syscall_linux_timeout(uint32_t *futex1, uint32_t *futex2,
					     int futex_op, uint32_t value1,
					     const struct timespec *timeout,
					     uint32_t value3);
long _fiber_lock_futex_syscall_linux_value2(uint32_t *futex1, uint32_t *futex2,
					    int futex_op, uint32_t value1,
					    uint32_t value2, uint32_t value3);

#endif /* _FIBER_LOCK_FUTEX_LINUX_SYSCALL_H */
