/*
 * pagedir_duplicate takes a source page directory and returns a pointer
 * to a new page directory which is a copy of the source directory.
 *
 * Each user virtual address in the source can be found in the new
 * directory, and points to a new page which contains a copy of the
 * data in the frmae mapped by that address in the source.
 * 
 * Returns NULL on failure (e.g. failure of pagedir_create or
 * palloc_get_page) and a valid pointer to a new, duplicate
 * pagedir on success.
 */
uint32_t*
pagedir_duplicate (const uint32_t* src_pd) {
  /* Allocate a new page directory */
  copy_pd = pagedir_create();

  /* then iterate through the old one, copying as we go */
  uint32_t *pd = src_pd; 
  uint32_t *pde;
  for (pde = pd; pde < pd + pd_no(PHYS_BASE); ++pde) {
    if (*pde & PTE_P) {
      uint32_t *pt = pde_get_pt(*pde);
      uint32_t *pte;
      for (pte = pt; pte < pt + PGSIZE / sizeof *pte; pte++) {
        if (*pte & PTE_P) {
          uint32_t* kpage = palloc_get_page (PAL_USER | PAL_ZERO);
          memcpy(kpage, pte_get_page(*pte), PGSIZE);
          uint32_t vdr = ((pde - pd) << PDSHIFT) | ((pte - pt) << PGBITS);
          pagedir_set_page(copy_pd, (void*)vdr, kpage, *pte & PTE_W);
        }
      }
    }
  } 
} 

/*
 * Creates a new struct thread and initializes its fields.
 * The new thread is also added to the all threads list.
 * Sets name to current thread's name, priority to current thread's priority, etc.
 * You may need to also initialize any fields you have added to struct
 * thread here, such as child lists, exit/wait related fields, etc.
 *
 */

struct thread *
create_child_thread () {
  /* Allocate thread. */
  struct thread* new_thread = palloc_get_page (PAL_ZERO);
  if (new_thread == NULL)
    return NULL;

  /* Initialize thread. */
  memset (new_thread, 0, sizeof *new_thread);
  new_thread->status = THREAD_BLOCKED;
  strlcpy (new_thread->name, thread_current()->name, sizeof new_thread->name);
  new_thread->stack = (uint8_t *) new_thread + PGSIZE;
  new_thread->priority = thread_get_priority(); 
  new_thread->magic = THREAD_MAGIC;

  thread_list_add(new_thread);
  new_thread->tid = allocate_tid();

  return new_thread; 
}

/*
 * Simulates a return from an interrupt by setting the stack pointer to point
 * to the passed interrupt frame and jumping to intr_exit.
 * */
static void
jump_to_intr_exit(struct intr_frame frame) {
  intr_enable ();
  asm volatile ("movl %0, %%esp; jmp intr_exit" : : "g" (&frame) : "memory");
  NOT_REACHED();
}

/* 
 * This function sets up the stack of the child thread so that it will end up
 * executing jump_to_intr_exit.
 * */
static void
setup_thread_to_return_from_fork(struct thread *new_thread, struct intr_frame *f) {
  /* setup stack on the new thread such that we'll jump into the right place */
  struct {
    void *eip;             /* Return address. */
    struct intr_frame if_; /* Interrupt frame we'll jump into */
  } *fp;
  struct switch_entry_frame *ef;
  struct switch_threads_frame *sf;

  /* Stack frame for jump_to_intr_exit() */
  new_thread->stack -= sizeof *fp;
  fp = new_thread->stack;
  fp->eip = NULL;
  fp->if_ = *f;
  fp->if_.eax = 0; // set return value to 0, so child gets a 0 out of fork()

  /* Stack frame for switch_entry(). */
  new_thread->stack -= sizeof *ef;
  ef = (struct switch_entry_frame*)new_thread->stack;
  ef->eip = (void (*) (void)) jump_to_intr_exit;

  /* Stack frame for switch_threads(). */
  new_thread->stack -= sizeof *sf;
  sf = (struct switch_threads_frame*)new_thread->stack;
  sf->eip = switch_entry;
  sf->ebp = 0;
}


/*
 * Your implementation of fork should look something like this.
 *
 * */
static pid_t
syscall_fork(struct intr_frame* f) {    
  struct thread* new_thread = create_child_thread();
  
  /* Do any child/parent setup, copy file descriptors, etc.
   * This is all dependent on your implementation of those details. */

  /* Set up the stack of your child process to return to the right place */
  setup_thread_to_return_from_fork(new_thread, f);
  
  /* Copy the paretn's page directory */
  
  new_pagedir = pagedir_duplicate(thread_current->pagedir);
  /* Handle error conditions properly */

  /* Add new thread to the ready queue - it will start executing by returning
   * via 
   *
   * */
  thread_unblock(new_thread);

  /* Parent returns child's pid */
  return new_thread->tid;
}
