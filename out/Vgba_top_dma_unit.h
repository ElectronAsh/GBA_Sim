// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vgba_top.h for the primary calling header

#ifndef _Vgba_top_dma_unit_H_
#define _Vgba_top_dma_unit_H_

#include "verilated.h"

class Vgba_top__Syms;

//----------

VL_MODULE(Vgba_top_dma_unit) {
  public:
    
    // PORTS
    // Begin mtask footprint  all: 
    VL_IN8(clk,0,0);
    VL_IN8(rst_b,0,0);
    VL_IN8(mem_wait,0,0);
    VL_IN8(preempted,0,0);
    VL_IN8(srcGamePak,0,0);
    VL_IN8(destGamePak,0,0);
    VL_IN8(allowed_to_begin,0,0);
    VL_IN8(cpu_preemptable,0,0);
    VL_OUT8(disable_dma,0,0);
    VL_OUT8(active,0,0);
    VL_OUT8(irq,0,0);
    VL_OUT8(others_cant_preempt,0,0);
    VL_IN8(size,1,0);
    VL_IN8(wen,0,0);
    VL_IN8(sound,0,0);
    VL_IN8(sound_req,0,0);
    VL_OUT8(size__out,1,0);
    VL_OUT8(size__en,1,0);
    VL_OUT8(wen__out,0,0);
    VL_OUT8(wen__en,0,0);
    VL_IN16(controlL,15,0);
    VL_IN16(controlH,15,0);
    VL_IN16(srcAddrL,15,0);
    VL_IN16(srcAddrH,15,0);
    VL_IN16(destAddrL,15,0);
    VL_IN16(destAddrH,15,0);
    VL_IN16(vcount,15,0);
    VL_IN16(hcount,15,0);
    VL_IN(rdata,31,0);
    VL_IN(addr,31,0);
    VL_IN(wdata,31,0);
    VL_OUT(addr__out,31,0);
    VL_OUT(addr__en,31,0);
    VL_OUT(wdata__out,31,0);
    VL_OUT(wdata__en,31,0);
    
    // LOCAL SIGNALS
    // Begin mtask footprint  all: 
    VL_SIG8(fsm_disable,0,0);
    VL_SIG8(xferDone,0,0);
    VL_SIG8(loadCNT,0,0);
    VL_SIG8(loadSAD,0,0);
    VL_SIG8(loadDAD,0,0);
    VL_SIG8(stepSRC,0,0);
    VL_SIG8(stepDEST,0,0);
    VL_SIG8(storeRData,0,0);
    VL_SIG8(write,0,0);
    VL_SIG8(dma_stop,0,0);
    VL_SIG8(start,0,0);
    VL_SIG8(set_wdata,0,0);
    VL_SIG8(new_transfer,0,0);
    VL_SIG8(reload_xfers,0,0);
    VL_SIG8(starter__DOT__sound,0,0);
    VL_SIG8(starter__DOT__sound_req,0,0);
    VL_SIG8(starter__DOT__cpu_preemptable,0,0);
    VL_SIG8(starter__DOT__start,0,0);
    VL_SIG8(starter__DOT__dma_stop,0,0);
    VL_SIG8(starter__DOT__clk,0,0);
    VL_SIG8(starter__DOT__rst_b,0,0);
    VL_SIG8(starter__DOT__display_sync_startable,0,0);
    VL_SIG8(starter__DOT__passed_go,0,0);
    VL_SIG8(starter__DOT__hold_sound,0,0);
    VL_SIG8(starter__DOT__sound_req_delay,0,0);
    VL_SIG8(fsm__DOT__mem_wait,0,0);
    VL_SIG8(fsm__DOT__dma_repeat,0,0);
    VL_SIG8(fsm__DOT__enable,0,0);
    VL_SIG8(fsm__DOT__start,0,0);
    VL_SIG8(fsm__DOT__new_transfer,0,0);
    VL_SIG8(fsm__DOT__preempted,0,0);
    VL_SIG8(fsm__DOT__genIRQ,0,0);
    VL_SIG8(fsm__DOT__allowed_to_begin,0,0);
    VL_SIG8(fsm__DOT__xferDone,0,0);
    VL_SIG8(fsm__DOT__loadCNT,0,0);
    VL_SIG8(fsm__DOT__loadSAD,0,0);
    VL_SIG8(fsm__DOT__loadDAD,0,0);
    VL_SIG8(fsm__DOT__stepSRC,0,0);
    VL_SIG8(fsm__DOT__stepDEST,0,0);
    VL_SIG8(fsm__DOT__storeRData,0,0);
    VL_SIG8(fsm__DOT__active,0,0);
    VL_SIG8(fsm__DOT__write,0,0);
    VL_SIG8(fsm__DOT__disable_dma,0,0);
    VL_SIG8(fsm__DOT__set_wdata,0,0);
    VL_SIG8(fsm__DOT__irq,0,0);
    VL_SIG8(fsm__DOT__others_cant_preempt,0,0);
    VL_SIG8(fsm__DOT__reload_xfers,0,0);
    VL_SIG8(fsm__DOT__clk,0,0);
    VL_SIG8(fsm__DOT__rst_b,0,0);
    VL_SIG8(fsm__DOT__cs,2,0);
    VL_SIG8(fsm__DOT__ns,2,0);
    VL_SIG8(datapath__DOT__loadCNT,0,0);
    VL_SIG8(datapath__DOT__loadSAD,0,0);
    VL_SIG8(datapath__DOT__loadDAD,0,0);
    VL_SIG8(datapath__DOT__stepSRC,0,0);
    VL_SIG8(datapath__DOT__stepDEST,0,0);
    VL_SIG8(datapath__DOT__storeRData,0,0);
    VL_SIG8(datapath__DOT__active,0,0);
    VL_SIG8(datapath__DOT__write,0,0);
    VL_SIG8(datapath__DOT__set_wdata,0,0);
    VL_SIG8(datapath__DOT__srcGamePak,0,0);
    VL_SIG8(datapath__DOT__destGamePak,0,0);
    VL_SIG8(datapath__DOT__xferDone,0,0);
    VL_SIG8(datapath__DOT__new_transfer,0,0);
    VL_SIG8(datapath__DOT__sound,0,0);
    VL_SIG8(datapath__DOT__reload_xfers,0,0);
    VL_SIG8(datapath__DOT__size,1,0);
    VL_SIG8(datapath__DOT__wen,0,0);
    VL_SIG8(datapath__DOT__clk,0,0);
    VL_SIG8(datapath__DOT__rst_b,0,0);
    VL_SIG8(datapath__DOT__xferWord,0,0);
    VL_SIG8(datapath__DOT__sCnt,1,0);
    VL_SIG8(datapath__DOT__dCnt,1,0);
    VL_SIG8(datapath__DOT__reloadDad,0,0);
    VL_SIG8(datapath__DOT__sadEnable,0,0);
    VL_SIG8(datapath__DOT__dadEnable,0,0);
    VL_SIG8(datapath__DOT__size_mem_transfer,1,0);
    VL_SIG8(datapath__DOT__srcAddrMux__DOT__s,0,0);
    VL_SIG8(datapath__DOT__destAddrMux__DOT__s,0,0);
    VL_SIG8(datapath__DOT__addrMux__DOT__s,0,0);
    VL_SIG8(datapath__DOT__sad__DOT__clk,0,0);
    VL_SIG8(datapath__DOT__sad__DOT__clear,0,0);
    VL_SIG8(datapath__DOT__sad__DOT__enable,0,0);
    VL_SIG8(datapath__DOT__sad__DOT__rst_b,0,0);
    VL_SIG8(datapath__DOT__dad__DOT__clk,0,0);
    VL_SIG8(datapath__DOT__dad__DOT__clear,0,0);
    VL_SIG8(datapath__DOT__dad__DOT__enable,0,0);
    VL_SIG8(datapath__DOT__dad__DOT__rst_b,0,0);
    VL_SIG8(datapath__DOT__data_reg__DOT__clk,0,0);
    VL_SIG8(datapath__DOT__data_reg__DOT__clear,0,0);
    VL_SIG8(datapath__DOT__data_reg__DOT__enable,0,0);
    VL_SIG8(datapath__DOT__data_reg__DOT__rst_b,0,0);
    VL_SIG8(datapath__DOT__xferCnt__DOT__clk,0,0);
    VL_SIG8(datapath__DOT__xferCnt__DOT__enable,0,0);
    VL_SIG8(datapath__DOT__xferCnt__DOT__clear,0,0);
    VL_SIG8(datapath__DOT__xferCnt__DOT__load,0,0);
    VL_SIG8(datapath__DOT__xferCnt__DOT__up,0,0);
    VL_SIG8(datapath__DOT__xferCnt__DOT__rst_b,0,0);
    VL_SIG8(datapath__DOT__oldsad__DOT__clk,0,0);
    VL_SIG8(datapath__DOT__oldsad__DOT__clear,0,0);
    VL_SIG8(datapath__DOT__oldsad__DOT__enable,0,0);
    VL_SIG8(datapath__DOT__oldsad__DOT__rst_b,0,0);
    VL_SIG8(datapath__DOT__olddad__DOT__clk,0,0);
    VL_SIG8(datapath__DOT__olddad__DOT__clear,0,0);
    VL_SIG8(datapath__DOT__olddad__DOT__enable,0,0);
    VL_SIG8(datapath__DOT__olddad__DOT__rst_b,0,0);
    VL_SIG8(datapath__DOT__oldctl__DOT__clk,0,0);
    VL_SIG8(datapath__DOT__oldctl__DOT__clear,0,0);
    VL_SIG8(datapath__DOT__oldctl__DOT__enable,0,0);
    VL_SIG8(datapath__DOT__oldctl__DOT__rst_b,0,0);
    VL_SIG16(starter__DOT__controlH,15,0);
    VL_SIG16(starter__DOT__vcount,15,0);
    VL_SIG16(starter__DOT__hcount,15,0);
    VL_SIG16(datapath__DOT__srcAddrL,15,0);
    VL_SIG16(datapath__DOT__srcAddrH,15,0);
    VL_SIG16(datapath__DOT__destAddrL,15,0);
    VL_SIG16(datapath__DOT__destAddrH,15,0);
    VL_SIG16(datapath__DOT__controlL,15,0);
    VL_SIG16(datapath__DOT__controlH,15,0);
    VL_SIG16(datapath__DOT__xfers,13,0);
    VL_SIG16(datapath__DOT__wordCount,13,0);
    VL_SIG16(datapath__DOT__words_to_transfer,13,0);
    VL_SIG16(datapath__DOT__xferCnt__DOT__q,13,0);
    VL_SIG16(datapath__DOT__xferCnt__DOT__d,13,0);
    VL_SIG16(datapath__DOT__xferCnt__DOT__ns,13,0);
    VL_SIG(datapath__DOT__rdata,31,0);
    VL_SIG(datapath__DOT__addr,31,0);
    VL_SIG(datapath__DOT__wdata,31,0);
    VL_SIG(datapath__DOT__old_SAD_reg,31,0);
    VL_SIG(datapath__DOT__old_DAD_reg,31,0);
    VL_SIG(datapath__DOT__old_CTL_reg,31,0);
    VL_SIG(datapath__DOT__sAddr,31,0);
    VL_SIG(datapath__DOT__dAddr,31,0);
    VL_SIG(datapath__DOT__steppedSAddr,31,0);
    VL_SIG(datapath__DOT__steppedDAddr,31,0);
    VL_SIG(datapath__DOT__nextSAddr,31,0);
    VL_SIG(datapath__DOT__nextDAddr,31,0);
    VL_SIG(datapath__DOT__desiredAddr,31,0);
    VL_SIG(datapath__DOT__sAddrRaw,31,0);
    VL_SIG(datapath__DOT__dAddrRaw,31,0);
    VL_SIG(datapath__DOT__data,31,0);
    VL_SIG(datapath__DOT__addrStep,31,0);
    VL_SIG(datapath__DOT__targetAddr,31,0);
    VL_SIG(datapath__DOT__wdata_size,31,0);
    VL_SIG(datapath__DOT__srcAddrMux__DOT__y,31,0);
    VL_SIG(datapath__DOT__srcAddrMux__DOT__i0,31,0);
    VL_SIG(datapath__DOT__srcAddrMux__DOT__i1,31,0);
    VL_SIG(datapath__DOT__destAddrMux__DOT__y,31,0);
    VL_SIG(datapath__DOT__destAddrMux__DOT__i0,31,0);
    VL_SIG(datapath__DOT__destAddrMux__DOT__i1,31,0);
    VL_SIG(datapath__DOT__addrMux__DOT__y,31,0);
    VL_SIG(datapath__DOT__addrMux__DOT__i0,31,0);
    VL_SIG(datapath__DOT__addrMux__DOT__i1,31,0);
    VL_SIG(datapath__DOT__sad__DOT__q,31,0);
    VL_SIG(datapath__DOT__sad__DOT__d,31,0);
    VL_SIG(datapath__DOT__dad__DOT__q,31,0);
    VL_SIG(datapath__DOT__dad__DOT__d,31,0);
    VL_SIG(datapath__DOT__data_reg__DOT__q,31,0);
    VL_SIG(datapath__DOT__data_reg__DOT__d,31,0);
    VL_SIG(datapath__DOT__oldsad__DOT__q,31,0);
    VL_SIG(datapath__DOT__oldsad__DOT__d,31,0);
    VL_SIG(datapath__DOT__olddad__DOT__q,31,0);
    VL_SIG(datapath__DOT__olddad__DOT__d,31,0);
    VL_SIG(datapath__DOT__oldctl__DOT__q,31,0);
    VL_SIG(datapath__DOT__oldctl__DOT__d,31,0);
    
    // LOCAL VARIABLES
    // Begin mtask footprint  all: 
    VL_SIG8(datapath__DOT____Vcellinp__destAddrMux__s,0,0);
    VL_SIG(datapath__DOT____Vcellinp__srcAddrMux__i1,31,0);
    VL_SIG(datapath__DOT____Vcellinp__oldsad__d,31,0);
    VL_SIG(datapath__DOT____Vcellinp__olddad__d,31,0);
    VL_SIG(datapath__DOT____Vcellinp__oldctl__d,31,0);
    VL_SIG(datapath__DOT__wdata__out__en1,31,0);
    
    // INTERNAL VARIABLES
  private:
    Vgba_top__Syms* __VlSymsp;  // Symbol table
  public:
    
    // PARAMETERS
    enum _IDatadatapath__DOT__srcAddrMux__DOT__width { datapath__DOT__srcAddrMux__DOT__width = 0x20U};
    enum _IDatadatapath__DOT__destAddrMux__DOT__width { datapath__DOT__destAddrMux__DOT__width = 0x20U};
    enum _IDatadatapath__DOT__addrMux__DOT__width { datapath__DOT__addrMux__DOT__width = 0x20U};
    enum _IDatadatapath__DOT__sad__DOT__width { datapath__DOT__sad__DOT__width = 0x20U};
    enum _IDatadatapath__DOT__dad__DOT__width { datapath__DOT__dad__DOT__width = 0x20U};
    enum _IDatadatapath__DOT__data_reg__DOT__width { datapath__DOT__data_reg__DOT__width = 0x20U};
    enum _IDatadatapath__DOT__xferCnt__DOT__width { datapath__DOT__xferCnt__DOT__width = 0xeU};
    enum _IDatadatapath__DOT__oldsad__DOT__width { datapath__DOT__oldsad__DOT__width = 0x20U};
    enum _IDatadatapath__DOT__olddad__DOT__width { datapath__DOT__olddad__DOT__width = 0x20U};
    enum _IDatadatapath__DOT__oldctl__DOT__width { datapath__DOT__oldctl__DOT__width = 0x20U};
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vgba_top_dma_unit);  ///< Copying not allowed
  public:
    Vgba_top_dma_unit(const char* name="TOP");
    ~Vgba_top_dma_unit();
    
    // API METHODS
    
    // INTERNAL METHODS
    void __Vconfigure(Vgba_top__Syms* symsp, bool first);
    void _combo__TOP__gba_top__DOT__dma__DOT__dma0__17(Vgba_top__Syms* __restrict vlSymsp);
    void _combo__TOP__gba_top__DOT__dma__DOT__dma0__21(Vgba_top__Syms* __restrict vlSymsp);
    void _combo__TOP__gba_top__DOT__dma__DOT__dma0__29(Vgba_top__Syms* __restrict vlSymsp);
    void _combo__TOP__gba_top__DOT__dma__DOT__dma1__18(Vgba_top__Syms* __restrict vlSymsp);
    void _combo__TOP__gba_top__DOT__dma__DOT__dma1__41(Vgba_top__Syms* __restrict vlSymsp);
    void _combo__TOP__gba_top__DOT__dma__DOT__dma2__31(Vgba_top__Syms* __restrict vlSymsp);
    void _combo__TOP__gba_top__DOT__dma__DOT__dma3__32(Vgba_top__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset();
  public:
    void _initial__TOP__gba_top__DOT__dma__DOT__dma0__1(Vgba_top__Syms* __restrict vlSymsp);
    void _sequent__TOP__gba_top__DOT__dma__DOT__dma0__25(Vgba_top__Syms* __restrict vlSymsp);
    void _settle__TOP__gba_top__DOT__dma__DOT__dma0__13(Vgba_top__Syms* __restrict vlSymsp);
    void _settle__TOP__gba_top__DOT__dma__DOT__dma0__5(Vgba_top__Syms* __restrict vlSymsp);
    void _settle__TOP__gba_top__DOT__dma__DOT__dma0__9(Vgba_top__Syms* __restrict vlSymsp);
    void _settle__TOP__gba_top__DOT__dma__DOT__dma1__6(Vgba_top__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(128);

#endif // guard
