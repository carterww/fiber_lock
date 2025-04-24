#define _POSIX_C_SOURCE (199309L)

#include <errno.h>

#include "debug.h"
#include "fiber_lock/errno.h"
#include "fiber_lock/semaphore.h"

#if defined(FIBER_LOCK_SEMAPHORE_INTERCEPT)
#define fiber_sem_post _fiber_sem_post
#endif

int fiber_sem_post(fiber_semaphore *sem)
{
	int res;

	fiber_assert(sem != NULL);
	res = sem_post(sem);

	if (res == 0) {
		return res;
	}

	fiber_assert(errno != EINVAL); /* sem is not a valid semaphore */

	switch (errno) {
	case EOVERFLOW: /* Max value for semaphore would be exceeded */
		return FBR_LOCK_ESEM_RNG;
	default:
		panic(1);
	}
}

#if defined(FIBER_LOCK_SEMAPHORE_INTERCEPT)
#undef fiber_sem_post
int (*fiber_sem_post_fn_ptr)(fiber_semaphore *) = _fiber_sem_post;
#endif
