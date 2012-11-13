uint32_t* pagedir_duplicate (const uint32_t* src_pd);
struct thread * create_child_thread ();
static void jump_to_intr_exit(struct intr_frame frame);
static void setup_thread_to_return_from_fork(struct thread *new_thread, struct intr_frame *f);


