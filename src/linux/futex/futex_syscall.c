#include "futex_syscall.h"

#include <stdint.h>
#include <time.h>

#include <sys/syscall.h>
#include <unistd.h>

long _fiber_lock_futex_syscall_linux_timeout(uint32_t *futex1, uint32_t *futex2,
					     int futex_op, uint32_t value1,
					     const struct timespec *timeout,
					     uint32_t value3)
{
	return syscall(SYS_futex, futex1, futex_op, value1, timeout, futex2,
		       value3);
}

long _fiber_lock_futex_syscall_linux_value2(uint32_t *futex1, uint32_t *futex2,
					    int futex_op, uint32_t value1,
					    uint32_t value2, uint32_t value3)
{
	uintptr_t value2_uptr = (uintptr_t)value2;
	void *value2_as_ptr = (void *)value2_uptr;
	return syscall(SYS_futex, futex1, futex_op, value1, value2_as_ptr,
		       futex2, value3);
}
