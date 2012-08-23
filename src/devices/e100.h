#ifndef DEVICES_E100_H
#define DEVICES_E100_H

#include "devices/pci.h"

#define E100_VENDORID 0x8086
#define E100_QEMU_DEVICEID 0x1209
#define E100_BOCHS_DEVICEID 0x100e

#define E100_RX_RING_SIZE = 0x100
#define E100_TX_RING_SIZE = 0x100

int pci_e100_attach(struct pci_func *pcif);

// Control / Status Register layout.
struct e100_csr {
  volatile uint16_t scb_status;
  uint16_t          scb_cmd;
  uint32_t          scb_ptr;
  uint32_t          port;
  uint16_t          prvt_1;
  uint16_t          eeprom;
  uint32_t          mdi;
  uint32_t          rx_dma_cnt;
  uint8_t           prvt_2;
  uint16_t          flow_ctrl;
  uint8_t           pmdr;
  uint8_t           ctrl;
  uint8_t           status;
  uint16_t          prvt_3;
};

// Command Block layout.
struct e100_cb {
  volatile uint16_t status;
  uint16_t          cmd;
  uint32_t          address;
};

// Transmit Buffer Descriptor.
struct e100_tbd {
  uint32_t          address;
  uint16_t          size;
  uint16_t          eol;
};

// Transmit command block.
struct e100_tcb {
  struct e100_cb    cb;
  struct e100_tbd*  tbd;
  uint16_t          size;
  uint8_t           threshold;
  uint8_t           tbd_count;
};

// Receive Frame Descriptor.
struct e100_rfd {
  struct e100_cb    cb;
  uint32_t          reserved;
  uint16_t          count;
  uint16_t          size;
};


#endif // DEVICES_E100_H
