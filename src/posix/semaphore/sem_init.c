#define _POSIX_C_SOURCE (199309L)

#include <errno.h>

#include "debug.h"
#include "fiber_lock/errno.h"
#include "fiber_lock/semaphore.h"

#if defined(FIBER_LOCK_SEMAPHORE_INTERCEPT)
#define fiber_sem_init _fiber_sem_init
#endif

int fiber_sem_init(fiber_semaphore *sem, unsigned int initial_value)
{
	int res;

	fiber_assert(sem != NULL);
	res = sem_init(sem, 0, initial_value);

	if (res == 0) {
		return res;
	}

	/* System does not support shared process semaphores. We don't use
         * those so this shouldn't be possible.
         */
	fiber_assert(errno != ENOSYS);

	switch (errno) {
	case EINVAL: /* initial_value exceeds semaphore's max */
		return FBR_LOCK_ESEM_RNG;
	default:
		panic(1);
	}
}

#if defined(FIBER_LOCK_SEMAPHORE_INTERCEPT)
#undef fiber_sem_init
int (*fiber_sem_init_fn_ptr)(fiber_semaphore *, unsigned int) = _fiber_sem_init;
#endif
