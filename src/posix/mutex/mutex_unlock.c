#define _POSIX_C_SOURCE (199506L)

#include <errno.h>

#include "debug.h"
#include "fiber_lock/mutex.h"

#if defined(FIBER_LOCK_MUTEX_INTERCEPT)
#define fiber_mutex_unlock _fiber_mutex_unlock
#endif

int fiber_mutex_unlock(fiber_mutex *mut)
{
	int res;

	fiber_assert(mut != NULL);
	res = pthread_mutex_unlock(mut);

	/* Invalid mutex */
	fiber_assert(res != EINVAL);
	/* Max number of recursive locks exceeded */
	fiber_assert(res != EAGAIN);
	/* Caller does not own the mutex */
	fiber_assert(res != EPERM);

	switch (res) {
	case 0:
		return res;
	default:
		panic(1);
	}
}

#if defined(FIBER_LOCK_MUTEX_INTERCEPT)
#undef fiber_mutex_unlock
int (*fiber_mutex_unlock_fn_ptr)(fiber_mutex *) = _fiber_mutex_unlock;
#endif
