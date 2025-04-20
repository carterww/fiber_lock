#define _POSIX_C_SOURCE (199309L)

#include <errno.h>

#include "debug.h"
#include "fiber_lock/semaphore.h"

#if defined(FIBER_LOCK_SEMAPHORE_INTERCEPT)
#define fiber_sem_destroy _fiber_sem_destroy
#endif

int fiber_sem_destroy(fiber_semaphore *sem)
{
	int res;

	fiber_assert(sem != NULL);
	res = sem_destroy(sem);

	if (res == 0) {
		return res;
	}

	fiber_assert(errno != EINVAL); /* sem is not a valid semaphore */

	switch (errno) {
	default:
		panic(1);
	}
}
