#define _POSIX_C_SOURCE (199309L)

#include <errno.h>

#include "debug.h"
#include "fiber_lock/errno.h"
#include "fiber_lock/semaphore.h"

#if defined(FIBER_LOCK_SEMAPHORE_INTERCEPT)
#define fiber_sem_trywait _fiber_sem_trywait
#endif

int fiber_sem_trywait(fiber_semaphore *sem)
{
	int res;

	fiber_assert(sem != NULL);
	res = sem_trywait(sem);

	if (res == 0) {
		return res;
	}

	fiber_assert(errno != EINVAL); /* sem is not a valid semaphore */

	switch (errno) {
	case EINTR: /* Call interrupted by signal */
		return FBR_LOCK_EINTR;
	case EAGAIN: /* Could not wait on semaphore without blocking */
		return FBR_LOCK_EAGAIN;
	default:
		panic(1);
	}
}

#if defined(FIBER_LOCK_SEMAPHORE_INTERCEPT)
#undef fiber_sem_trywait
int (*fiber_sem_trywait_fn_ptr)(fiber_semaphore *) = _fiber_sem_trywait;
#endif
