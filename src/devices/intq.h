#ifndef DEVICES_INTQ_H
#define DEVICES_INTQ_H

#include "threads/interrupt.h"
#include "threads/synch.h"

/* An "interrupt queue", a circular buffer shared between
   kernel threads and external interrupt handlers.

   Interrupt queue functions can be called from kernel threads or
   from external interrupt handlers.  Except for intq_init(),
   interrupts must be off in either case.

   The interrupt queue has the structure of a "monitor".  Locks
   and condition variables from threads/synch.h cannot be used in
   this case, as they normally would, because they can only
   protect kernel threads from one another, not from interrupt
   handlers. */

/* tom: these routines are a way to buffer characters on their
 * way to/from an I/O device, like the serial port or the keyboard.
 * A very important constraint is that an interrupt handler
 * CANNOT call a blocking operation, like a semaphore_P
 * lock_acquire or condition_wait -- the reason is that we want
 * the interrupt handler to always be able to complete, so that
 * we can reenable interrupts.
 *
 * The same code is used for both directions.  (In my opinion,
 * this makes it more complex than it needs to be, but ok.)
 * The buffer is circular -- so there is a front pointer and a last pointer
 * that are incremented as characters are put into the buffer and removed.
 *
 * On the way out, the sender thread queues characters.  If the buffer
 * is empty, that means we need to send the character onto the device.
 * If the buffer is full, the sender must wait until there is room.
 * As long as the buffer isn't full, the sender can return right away,
 * after incrementing last.
 *
 * The interrupt handler occurs asynchronously -- it says that
 * a previously sent character is done.  So the pointer to the next
 * character to send can be advanced, and if there is another character
 * in the queue, we can send it to the device, causing another interrupt
 * in the future.  We also need to wake up any thread that is waiting 
 * for room in the buffer (but without grabbing a lock -- since we can't
 * wait in the interrupt handler!)
 *
 * On the way in, the receiving thread looks at the queue. 
 * If the queue is not-empty, it pulls the character off the front and
 * returns it, advancing the front pointer.  Otherwise the thread waits
 * for a character to arrive.  The interrupt handler means that a
 * character has arrived, so it puts the character at the end of the queue
 * (if there's room -- if not, it has to drop the character on the floor)
 * and wakes up anyone who is waiting.
 */

/* tom: another downside of this particular implementation is that
 * it depends on interrupt enable/disable for mutual exclusion, and so 
 * it would not work on a multiprocessor (disabling interrupts only 
 * disables them on one processor -- it does not provide mutual 
 * exclusion between other processors.  A better design is described 
 * in the book.  The easiest is to have a high priority thread
 * that waits for characters to arrive; the interrupt handler can
 * send a semaphore-V to wake up the high priority thread. That thread
 * can then handle the character, putting it in a queue, grabbing locks
 * as needed, etc, and then do a semaphore-P until there's more work to do.
 * That would be multiprocessor safe.
 */


/* Queue buffer size, in bytes. */
#define INTQ_BUFSIZE 64

/* A circular queue of bytes. */
struct intq
  {
    /* Waiting threads. */
    struct lock lock;           /* Only one thread may wait at once. */
    struct thread *not_full;    /* Thread waiting for not-full condition. */
    struct thread *not_empty;   /* Thread waiting for not-empty condition. */

    /* Queue. */
    uint8_t buf[INTQ_BUFSIZE];  /* Buffer. */
    int head;                   /* New data is written here. */
    int tail;                   /* Old data is read here. */
  };

void intq_init (struct intq *);
bool intq_empty (const struct intq *);
bool intq_full (const struct intq *);
uint8_t intq_getc (struct intq *);
void intq_putc (struct intq *, uint8_t);

#endif /* devices/intq.h */
