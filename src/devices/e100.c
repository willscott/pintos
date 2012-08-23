#include "devices/e100.h"
#include "devices/timer.h"
#include "threads/io.h"
#include "threads/malloc.h"
#include "threads/thread.h"
#include <net.h>

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
  size_t i;
  struct e100_tcb* tx_loc;

  struct e100_csr* e100 = (struct e100_csr*)csr;
  // Software reset.  Takes up to 10us to complete
  outl((uint16_t)&e100->port, 0x0);
  timer_sleep(10);

  printf("E100: Initializing Transmit Buffer.\n");
  size_t tx_frame = sizeof(struct e100_tcb) + NET_MTU;
  size_t tx_size = E100_TX_RING_SIZE * tx_frame;
  tx_loc = malloc(tx_size);
  for (i = 0; i < E100_TX_RING_SIZE; i++) {
    struct e100_tcb* hdr = tx_loc + i * tx_frame;
    hdr->cb.status = E100_CB_STATUS_C;
    hdr->cb.cmd = E100_CB_CMD_S;
    hdr->cb.address = tx_frame * ((i + 1) % E100_TX_RING_SIZE);
    // Indicate data immediately follows the header.
    hdr->data_addr = 0xffffffff;
    hdr->threshold = 0xE0; // Maximum Threshold.
    hdr->tbd_count = 0;
  }
  // Notify the device of the tx buffer.
  outl((uint16_t)&e100->scb_ptr, tx_loc);
  outw((uint16_t)&e100->scb_cmd, 0x10);
  
  printf("E100: Initializing Receive Buffer.\n");
}
