/* See LICENSE file for copyright and license details. */

#ifndef FIBER_LOCK_SPIN_H
#define FIBER_LOCK_SPIN_H

#if defined(FIBER_LOCK_SPIN_POSIX)
#include <pthread.h>
#include <unistd.h>
#if defined(_POSIX_VERSION) && _POSIX_VERSION >= 200112L
typedef pthread_spinlock_t fiber_spinlock;
#else
#error "FIBER_LOCK_SPIN_POSIX was specified but _POSIX_VERSION does not indicate spinlock support."
#endif /* _POSIX_VERSION */
#else
#error "No spinlock implementation specified."
typedef void fiber_spinlock;
#endif /* FIBER_LOCK_SPIN_POSIX */

/* Initialize a fiber_spinlock. Attempting to initialize an initialized spinlock
 * results in undefined behavior.
 * @param spin -> Pointer to the fiber_spinlock to initialize.
 * @returns -> 0 if the call was successful, an error otherwise.
 * @error FBR_LOCK_EAGAIN -> Insufficient resources to create the spinlock.
 * @error FBR_LOCK_ENOMEM -> Insufficient memory to create the spinlock.
 */
int fiber_spin_init(fiber_spinlock *spin);

/* Destroys a fiber_spinlock. Attempting to destroy an uninitialized or locked spinlock
 * results in undefined behavior
 * @param spin -> Pointer to the fiber_spinlock to destroy.
 * @returns -> 0 if the call was successful, an error otherwise.
 * @note As of now, there are no error codes returned by this function.
 */
int fiber_spin_destroy(fiber_spinlock *spin);

/* Locks an initialized fiber_spinlock. This function should not be called on an uninitialized
 * or locked spinlock held by the caller. Both cases will result in undefined behavior.
 * @param spin -> Pointer to the fiber_spinlock to lock.
 * @returns -> 0 if the call was successful, an error otherwise.
 * @note As of now, there are no error codes returned by this function. All error cases
 * indicate a bug so we panic.
 */
int fiber_spin_lock(fiber_spinlock *spin);

/* Attempts to lock an initialized fiber_spinlock. This function should not be called on
 * an uninitialized or locked spinlock held by the caller. Both cases will result in
 * undefined behavior.
 * @param spin -> Pointer to the fiber_spinlock to lock.
 * @returns -> 0 if the call was successful, an error otherwise.
 * @error FBR_LOCK_EBUSY -> Another thread currently holds the spinlock.
 */
int fiber_spin_trylock(fiber_spinlock *spin);

/* Unlocks an initialized fiber_spinlock. This function should not be called on an uninitialized
 * or spinlock that has already been unlocked. Both cases will result in undefined behavior.
 * @param spin -> Pointer to the fiber_spinlock to unlock.
 * @returns -> 0 if the call was successful, an error otherwise.
 * @note As of now, there are no error codes returned by this function.
 */
int fiber_spin_unlock(fiber_spinlock *spin);

#if defined(FIBER_LOCK_SPIN_INTERCEPT)
extern int (*fiber_spin_init_fn_ptr)(fiber_spinlock *);
extern int (*fiber_spin_destroy_fn_ptr)(fiber_spinlock *);
extern int (*fiber_spin_lock_fn_ptr)(fiber_spinlock *);
extern int (*fiber_spin_trylock_fn_ptr)(fiber_spinlock *);
extern int (*fiber_spin_unlock_fn_ptr)(fiber_spinlock *);
#endif

#endif /* FIBER_LOCK_SPIN_H */
