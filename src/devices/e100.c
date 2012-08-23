#include "devices/e100.h"
#include "devices/timer.h"
#include "threads/io.h"
#include "threads/malloc.h"
#include "threads/thread.h"

void pci_e100_init(void *e100);

int pci_e100_attach(struct pci_func *pcif)
{
  printf("E100: Device found.\n");
  pci_func_enable(pcif);
  struct e100_csr* e100 = (struct e100_csr*)pcif->reg_base[1];

  // Create a kernel thread for managing the device.
  thread_create("E100 Manager", PRI_DEFAULT, &pci_e100_init, e100);
  return 0;
}

void pci_e100_init(void *csr)
{
  struct e100_csr* e100 = (struct e100_csr*)csr;
  // Software reset.  Takes up to 10us to complete
  outl((uint16_t)&e100->port, 0x0);
  timer_sleep(10);

  //printf("E100: Initializing Transmit Buffer.\n");
  //void* tx_loc = malloc(E100_TX_RING_SIZE * sizeof());
}
