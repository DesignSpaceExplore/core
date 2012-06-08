#ifndef AHBSLAVE_H
#define AHBSLAVE_H 

#include <stdint.h>

#include <greencontrol/config.h>
#include <greensocket/initiator/multi_socket.h>
#include <greenreg_ambasockets.h>

#include <tlm.h>
#include <amba.h>
#include <systemc.h>

#include "ahbdevice.h"
#include "verbose.h"
#include "msclogger.h"

template<class BASE=sc_module>
class AHBSlave : public BASE, public AHBDevice {
 public:
  SC_HAS_PROCESS(AHBSlave);
        
  AHBSlave(sc_core::sc_module_name mn, 
           uint8_t hindex, 
           uint8_t vendor, 
           uint8_t device, 
           uint8_t version, 
           uint8_t irq, 
           amba::amba_layer_ids ambaLayer, 
           uint32_t bar0 = 0, 
           uint32_t bar1 = 0, 
           uint32_t bar2 = 0, 
           uint32_t bar3 = 0);
  
  ~AHBSlave();

  /// AHB Slave Socket
  ///
  /// Receives instructions (mem access) from CPU
  ::amba::amba_slave_socket<32> ahb;

  /// Interface to functional part of the model
  virtual uint32_t exec_func(tlm::tlm_generic_payload &gp, sc_time &delay) = 0;

  /// TLM blocking transport functions
  virtual void b_transport(tlm::tlm_generic_payload& gp, sc_time& delay);

  /// TLM debug transport function
  virtual uint32_t transport_dbg(tlm::tlm_generic_payload& gp);

  void wait_state_count();

  /// TLM non-blocking transport function
  virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_core::sc_time& delay);

  /// Accept new transaction (busy or not)
  void requestThread();

  /// Thread for interfacing functional part of the model in AT mode
  void responseThread();

 private: 
  /// Ready to accept new transaction (send END_REQ)
  sc_event unlock_event;

  /// Event queues for AT mode
  tlm_utils::peq_with_get<tlm::tlm_generic_payload> m_RequestPEQ;
  tlm_utils::peq_with_get<tlm::tlm_generic_payload> m_ResponsePEQ;

  bool busy;
  uint32_t wait_states;
 uint32_t m_wait_states;
  sc_core::sc_time clockcycle;
};

#include "ahbslave2.tpp"

#endif // AHBSLAVE_H


/* vim: set expandtab noai ts=4 sw=4: */
/* -*- mode: c-mode; tab-width: 4; indent-tabs-mode: nil; -*- */