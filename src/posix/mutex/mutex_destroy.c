#define _POSIX_C_SOURCE (199506L)

#include <errno.h>

#include "debug.h"
#include "fiber_lock/errno.h"
#include "fiber_lock/mutex.h"

#if defined(FIBER_LOCK_MUTEX_INTERCEPT)
#define fiber_mutex_destroy _fiber_mutex_destroy
#endif

int fiber_mutex_destroy(fiber_mutex *mut)
{
	int res;

	fiber_assert(mut != NULL);
	res = pthread_mutex_destroy(mut);

	fiber_assert(res != EINVAL); /* Mutex is invalid */

	switch (res) {
	case 0:
		return res;
	case EBUSY: /* Trying to destroy a locked mutex */
		return FBR_LOCK_EBUSY;
	default:
		panic(1);
	}
}
