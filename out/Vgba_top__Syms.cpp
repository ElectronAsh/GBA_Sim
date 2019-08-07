// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vgba_top__Syms.h"
#include "Vgba_top.h"
#include "Vgba_top___024unit.h"
#include "Vgba_top_dma_unit.h"
#include "Vgba_top_obj_row_buffer.h"

// FUNCTIONS
Vgba_top__Syms::Vgba_top__Syms(Vgba_top* topp, const char* namep)
	// Setup locals
	: __Vm_namep(namep)
	, __Vm_didInit(false)
	// Setup submodule names
	, TOP____024unit                 (Verilated::catName(topp->name(),"$unit"))
	, TOP__gba_top__DOT__dma__DOT__dma0 (Verilated::catName(topp->name(),"gba_top.dma.dma0"))
	, TOP__gba_top__DOT__dma__DOT__dma1 (Verilated::catName(topp->name(),"gba_top.dma.dma1"))
	, TOP__gba_top__DOT__dma__DOT__dma2 (Verilated::catName(topp->name(),"gba_top.dma.dma2"))
	, TOP__gba_top__DOT__dma__DOT__dma3 (Verilated::catName(topp->name(),"gba_top.dma.dma3"))
	, TOP__gba_top__DOT__gfx__DOT__gfx__DOT__obj_circ__DOT__ordb__DOT__even (Verilated::catName(topp->name(),"gba_top.gfx.gfx.obj_circ.ordb.even"))
	, TOP__gba_top__DOT__gfx__DOT__gfx__DOT__obj_circ__DOT__ordb__DOT__odd (Verilated::catName(topp->name(),"gba_top.gfx.gfx.obj_circ.ordb.odd"))
{
    // Pointer to top level
    TOPp = topp;
    // Setup each module's pointers to their submodules
    TOPp->__PVT____024unit          = &TOP____024unit;
    TOPp->__PVT__gba_top__DOT__dma__DOT__dma0  = &TOP__gba_top__DOT__dma__DOT__dma0;
    TOPp->__PVT__gba_top__DOT__dma__DOT__dma1  = &TOP__gba_top__DOT__dma__DOT__dma1;
    TOPp->__PVT__gba_top__DOT__dma__DOT__dma2  = &TOP__gba_top__DOT__dma__DOT__dma2;
    TOPp->__PVT__gba_top__DOT__dma__DOT__dma3  = &TOP__gba_top__DOT__dma__DOT__dma3;
    TOPp->__PVT__gba_top__DOT__gfx__DOT__gfx__DOT__obj_circ__DOT__ordb__DOT__even  = &TOP__gba_top__DOT__gfx__DOT__gfx__DOT__obj_circ__DOT__ordb__DOT__even;
    TOPp->__PVT__gba_top__DOT__gfx__DOT__gfx__DOT__obj_circ__DOT__ordb__DOT__odd  = &TOP__gba_top__DOT__gfx__DOT__gfx__DOT__obj_circ__DOT__ordb__DOT__odd;
    // Setup each module's pointer back to symbol table (for public functions)
    TOPp->__Vconfigure(this, true);
    TOP____024unit.__Vconfigure(this, true);
    TOP__gba_top__DOT__dma__DOT__dma0.__Vconfigure(this, true);
    TOP__gba_top__DOT__dma__DOT__dma1.__Vconfigure(this, false);
    TOP__gba_top__DOT__dma__DOT__dma2.__Vconfigure(this, false);
    TOP__gba_top__DOT__dma__DOT__dma3.__Vconfigure(this, false);
    TOP__gba_top__DOT__gfx__DOT__gfx__DOT__obj_circ__DOT__ordb__DOT__even.__Vconfigure(this, true);
    TOP__gba_top__DOT__gfx__DOT__gfx__DOT__obj_circ__DOT__ordb__DOT__odd.__Vconfigure(this, false);
}
