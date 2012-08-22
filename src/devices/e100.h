#ifndef DEVICES_E100_H
#define DEVICES_E100_H

#include "devices/pci.h"

#define E100_VENDORID 0x8086
#define E100_QEMU_DEVICEID 0x1209
#define E100_BOCHS_DEVICEID 0x100e

int pci_e100_attach(struct pci_func *pcif);

struct e100_csr {
  uint16_t          scb_cmd;
  volatile uint16_t scb_status;
  uint32_t          scb_ptr;
  uint32_t          port;
  uint16_t          eeprom;
  uint16_t          prvt_1;
  uint32_t          mdi;
  uint32_t          rx_dma_cnt;
  uint8_t           pmdr;
  uint16_t          flow_ctrl;
  uint8_t           prvt_2;
  uint16_t          prvt_3;
  uint8_t           status;
  uint8_t           ctrl;
};

#endif // DEVICES_E100_H
