// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vgba_top.h for the primary calling header

#ifndef _Vgba_top___024unit_H_
#define _Vgba_top___024unit_H_

#include "verilated.h"

class Vgba_top__Syms;

//----------

VL_MODULE(Vgba_top___024unit) {
  public:
    
    // PORTS
    
    // LOCAL SIGNALS
    
    // LOCAL VARIABLES
    
    // INTERNAL VARIABLES
  private:
    Vgba_top__Syms* __VlSymsp;  // Symbol table
  public:
    
    // PARAMETERS
    enum _IDataCUserMode { CUserMode = 0x10U};
    enum _IDataCFIQMode { CFIQMode = 0x11U};
    enum _IDataCIRQMode { CIRQMode = 0x12U};
    enum _IDataCSVCMode { CSVCMode = 0x13U};
    enum _IDataCAbortMode { CAbortMode = 0x17U};
    enum _IDataCUndefMode { CUndefMode = 0x1bU};
    enum _IDataCSystemMode { CSystemMode = 0x1fU};
    enum _IDataCPSRInitVal { CPSRInitVal = 0xd3U};
    enum _IDataCExcAdrUndefined { CExcAdrUndefined = 4U};
    enum _IDataCExcAdrSWI { CExcAdrSWI = 8U};
    enum _IDataCExcAdrPrfAbt { CExcAdrPrfAbt = 0xcU};
    enum _IDataCExcAdrDtAbt { CExcAdrDtAbt = 0x10U};
    enum _IDataCExcAdrIRQ { CExcAdrIRQ = 0x18U};
    enum _IDataCExcAdrFIQ { CExcAdrFIQ = 0x1cU};
    enum _IDataCTT_I { CTT_I = 0U};
    enum _IDataCTT_C { CTT_C = 1U};
    enum _IDataCTT_N { CTT_N = 2U};
    enum _IDataCTT_S { CTT_S = 3U};
    enum _IDataCTS_B { CTS_B = 0U};
    enum _IDataCTS_HW { CTS_HW = 1U};
    enum _IDataCTS_W { CTS_W = 2U};
    enum _IDataCPCInitVal { CPCInitVal = 0U};
    enum _IDataCR_PC { CR_PC = 0xfU};
    enum _IDataCR_LR { CR_LR = 0xeU};
    enum _IDataCThumbImp { CThumbImp = 1U};
    enum _IDataCDnCr { CDnCr = 0U};
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vgba_top___024unit);  ///< Copying not allowed
  public:
    Vgba_top___024unit(const char* name="TOP");
    ~Vgba_top___024unit();
    
    // API METHODS
    
    // INTERNAL METHODS
    void __Vconfigure(Vgba_top__Syms* symsp, bool first);
  private:
    void _ctor_var_reset();
} VL_ATTR_ALIGNED(128);

#endif // guard
