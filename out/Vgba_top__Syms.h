// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header

#ifndef _Vgba_top__Syms_H_
#define _Vgba_top__Syms_H_

#include "verilated.h"

// INCLUDE MODULE CLASSES
#include "Vgba_top.h"
#include "Vgba_top___024unit.h"
#include "Vgba_top_dma_unit.h"
#include "Vgba_top_obj_row_buffer.h"

// SYMS CLASS
class Vgba_top__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;
    
    // SUBCELL STATE
    Vgba_top*                      TOPp;
    Vgba_top___024unit             TOP____024unit;
    Vgba_top_dma_unit              TOP__gba_top__DOT__dma__DOT__dma0;
    Vgba_top_dma_unit              TOP__gba_top__DOT__dma__DOT__dma1;
    Vgba_top_dma_unit              TOP__gba_top__DOT__dma__DOT__dma2;
    Vgba_top_dma_unit              TOP__gba_top__DOT__dma__DOT__dma3;
    Vgba_top_obj_row_buffer        TOP__gba_top__DOT__gfx__DOT__gfx__DOT__obj_circ__DOT__ordb__DOT__even;
    Vgba_top_obj_row_buffer        TOP__gba_top__DOT__gfx__DOT__gfx__DOT__obj_circ__DOT__ordb__DOT__odd;
    
    // CREATORS
    Vgba_top__Syms(Vgba_top* topp, const char* namep);
    ~Vgba_top__Syms() {}
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    
} VL_ATTR_ALIGNED(64);

#endif // guard
