#include "devices/e100.h"
#include "threads/io.h"

int pci_e100_attach(struct pci_func *pcif)
{
  printf("E100: Device found.\n");
  pci_func_enable(pcif);
  struct e100_csr* e100 = (struct e100_csr*)pcif->reg_base[1];
  printf("E100: iobase=0x%x\n", pcif->reg_base[1]);
  software_reset(e100);
  return 0;
}

void software_reset(struct e100_csr *e100)
{
  outl(&e100->port, 0x0);
}
