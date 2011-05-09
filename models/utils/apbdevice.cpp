//*********************************************************************
// Copyright 2010, Institute of Computer and Network Engineering,
//                 TU-Braunschweig
// All rights reserved
// Any reproduction, use, distribution or disclosure of this program,
// without the express, prior written consent of the authors is 
// strictly prohibited.
//
// University of Technology Braunschweig
// Institute of Computer and Network Engineering
// Hans-Sommer-Str. 66
// 38118 Braunschweig, Germany
//
// ESA SPECIAL LICENSE
//
// This program may be freely used, copied, modified, and redistributed
// by the European Space Agency for the Agency's own requirements.
//
// The program is provided "as is", there is no warranty that
// the program is correct or suitable for any purpose,
// neither implicit nor explicit. The program and the information in it
// contained do not necessarily reflect the policy of the 
// European Space Agency or of TU-Braunschweig.
//*********************************************************************
// Title:      ahbdevice.cpp
//
// ScssId:
//
// Origin:     HW-SW SystemC Co-Simulation SoC Validation Platform
//
// Purpose:    contains the implementation of a baseclass
//             for all ahb tlm models. It implements the the device
//             information register needed for the plug and play
//             interface.
//
// Method:
//
// Modified on $Date$
//          at $Revision$
//          by $Author$
//
// Principal:  European Space Agency
// Author:     VLSI working group @ IDA @ TUBS
// Maintainer: Rolf Meyer
// Reviewed:
//*********************************************************************

#include "apbdevice.h"
#include "verbose.h"

APBDevice::APBDevice(uint8_t vendorid, uint16_t deviceid,
                     uint8_t version, uint8_t irq, APBDevice::device_type type, 
                     uint16_t mask, bool cacheable,
                     bool prefetchable, uint16_t address) {
    m_register[0] = (irq & 0x1F) | ((version & 0x1F) << 5)
            | ((deviceid & 0xFFF) << 12) | (vendorid << 24);
    m_register[1] = (static_cast<uint8_t>(type) | (mask << 4) | 
                    (cacheable << 16) | (prefetchable << 17) | (address << 20));
}

APBDevice::~APBDevice() {
}

void APBDevice::print_device_info(char *name) const {
    // Display APB slave information
    v::info << name << "APB slave @" << v::uint32 << get_base_addr_()
                    << " size: " << v::uint32 << get_size_() << " byte" << v::endl;
}

const uint32_t *APBDevice::get_device_info() const {
    return m_register;
}

const APBDevice::device_type APBDevice::get_type() const {
    return static_cast<APBDevice::device_type>(m_register[0]>>30);
}

const uint32_t APBDevice::get_base() const {
    return (m_register[1] >> 20) & 0xFFF;
}

const uint32_t APBDevice::get_mask() const {
    return  (m_register[1] >>  4) & 0xFFF;
}

sc_dt::uint64 APBDevice::get_base_addr() {
    uint32_t addr = get_base();
    uint32_t mask = get_mask();
    return (addr & mask) << 8;
}

const uint32_t APBDevice::get_base_addr_() const {
    uint32_t addr = get_base();
    uint32_t mask = get_mask();
    return (addr & mask) << 8;
}

sc_dt::uint64 APBDevice::get_size() {
    uint32_t mask = get_mask();
    return (((~mask & 0xFFF) + 1) << 8);
}

const uint32_t APBDevice::get_size_() const {
    uint32_t mask = get_mask();
    return (((~mask & 0xFFF) + 1) << 8);
}