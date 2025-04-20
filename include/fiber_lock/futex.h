/* See LICENSE file for copyright and license details. */

#ifndef FIBER_LOCK_FUTEX_H
#define FIBER_LOCK_FUTEX_H

#if defined(FIBER_LOCK_FUTEX_LINUX)
#if defined(__linux__)
#include <linux/futex.h>
#include <sys/syscall.h>
#else
#error "FIBER_LOCK_FUTEX_LINUX was specified but __linux__ is not defined."
#endif /* __linux__ */

#if !defined(SYS_futex)
#error "FIBER_LOCK_FUTEX_LINUX was specified but SYS_futex is not defined."
#endif /* !SYS_futex */

/* If an error occurs here it is because an int is not 32 bits on your
 * platform. A futex must be 4 bytes aligned to 4 bytes on Linux.
 */
typedef char _static_assert_int_4_bytes[sizeof(int) == 4 ? 1 : -1];
typedef int fiber_futex;
#else
#error "No futex implementation specified."
typedef void fiber_futex;
#endif /* FIBER_LOCK_FUTEX_LINUX */

/* Initialize a fiber_futex to an initial value.
 * @param futex -> Pointer to the futex to initialize.
 * @param value -> Initial value the futex should have.
 */
void fiber_futex_init(fiber_futex *futex, int value);

/* Block indefinitely if the futex's value equals expected. 
 * @param futex -> Pointer to the futex to potentially block on.
 * @param expected -> Value the futex should contain if the thread
 * should block.
 * @returns -> 0 if the thread was woken up by fiber_futex_wake, an
 * error otherwise.
 * @error FBR_LOCK_EAGAIN -> The futex's value did not match expected.
 */
int fiber_futex_wait(fiber_futex *futex, int expected);

/* Block for timeout_ms milliseconds if the futex's value equals expected. 
 * @param futex -> Pointer to the futex to potentially block on.
 * @param expected -> Value the futex should contain if the thread
 * should block.
 * @returns -> 0 if the thread was woken up by fiber_futex_wake, an
 * error otherwise.
 * @error FBR_LOCK_EAGAIN -> The futex's value did not match expected.
 * @error FBR_LOCK_ETIMEDOUT -> The timeout was reached.
 */
int fiber_futex_wait_timeout(fiber_futex *futex, int expected,
			     unsigned long timeout_ms);

/* Wake up at most *num_threads threads waiting on futex.
 * @param futex -> Pointer to the futex the thread(s) are waiting on.
 * @param num_threads -> Pointer to the maximum number of threads to wake.
 * If an error isn't returned, the actual number of threads woken up is put
 * into this variable.
 * @returns -> 0 if the call was successful, an error otherwise.
 * @error FBR_LOCK_EINVAL -> *num_threads is not a positive integer.
 */
int fiber_futex_wake(fiber_futex *futex, int *num_threads);

#endif /* FIBER_LOCK_FUTEX_H */
