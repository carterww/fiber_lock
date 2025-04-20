#define _POSIX_C_SOURCE (199309L)

#include <errno.h>

#include "debug.h"
#include "fiber_lock/semaphore.h"

#if defined(FIBER_LOCK_SEMAPHORE_INTERCEPT)
#define fiber_sem_getvalue _fiber_sem_getvalue
#endif

int fiber_sem_getvalue(fiber_semaphore *sem, int *value_out)
{
	int res;

	fiber_assert(sem != NULL);
	fiber_assert(value_out != NULL);
	res = sem_getvalue(sem, value_out);

	if (res == 0) {
		return res;
	}

	fiber_assert(errno != EINVAL); /* sem is not a valid semaphore */

	switch (errno) {
	default:
		panic(1);
	}
}
