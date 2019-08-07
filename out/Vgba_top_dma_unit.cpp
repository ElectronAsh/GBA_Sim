// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vgba_top.h for the primary calling header

#include "Vgba_top_dma_unit.h" // For This
#include "Vgba_top__Syms.h"


//--------------------
// STATIC VARIABLES


//--------------------

VL_CTOR_IMP(Vgba_top_dma_unit) {
    // Reset internal values
    // Reset structure values
    _ctor_var_reset();
}

void Vgba_top_dma_unit::__Vconfigure(Vgba_top__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vgba_top_dma_unit::~Vgba_top_dma_unit() {
}

//--------------------
// Internal Methods

void Vgba_top_dma_unit::_initial__TOP__gba_top__DOT__dma__DOT__dma0__1(Vgba_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vgba_top_dma_unit::_initial__TOP__gba_top__DOT__dma__DOT__dma0__1\n"); );
    Vgba_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // INITIAL at dma/register.sv:8
    this->datapath__DOT__sad__DOT__clear = 0U;
    // INITIAL at dma/register.sv:8
    this->datapath__DOT__dad__DOT__clear = 0U;
    // INITIAL at dma/register.sv:8
    this->datapath__DOT__data_reg__DOT__clear = 0U;
    // INITIAL at dma/counter.sv:4
    this->datapath__DOT__xferCnt__DOT__d = 0U;
    // INITIAL at dma/counter.sv:5
    this->datapath__DOT__xferCnt__DOT__load = 0U;
    // INITIAL at dma/counter.sv:5
    this->datapath__DOT__xferCnt__DOT__up = 1U;
    // INITIAL at dma/register.sv:8
    this->datapath__DOT__oldsad__DOT__clear = 0U;
    // INITIAL at dma/register.sv:8
    this->datapath__DOT__oldsad__DOT__enable = 1U;
    // INITIAL at dma/register.sv:8
    this->datapath__DOT__olddad__DOT__clear = 0U;
    // INITIAL at dma/register.sv:8
    this->datapath__DOT__olddad__DOT__enable = 1U;
    // INITIAL at dma/register.sv:8
    this->datapath__DOT__oldctl__DOT__clear = 0U;
    // INITIAL at dma/register.sv:8
    this->datapath__DOT__oldctl__DOT__enable = 1U;
}

void Vgba_top_dma_unit::_settle__TOP__gba_top__DOT__dma__DOT__dma0__5(Vgba_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vgba_top_dma_unit::_settle__TOP__gba_top__DOT__dma__DOT__dma0__5\n"); );
    Vgba_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    this->starter__DOT__rst_b = this->rst_b;
    this->fsm__DOT__rst_b = this->rst_b;
    this->datapath__DOT__rst_b = this->rst_b;
    this->datapath__DOT__sad__DOT__q = this->datapath__DOT__sAddrRaw;
    this->datapath__DOT__dad__DOT__q = this->datapath__DOT__dAddrRaw;
    this->datapath__DOT__data_reg__DOT__q = this->datapath__DOT__data;
    this->datapath__DOT__xferCnt__DOT__q = this->datapath__DOT__xfers;
    this->datapath__DOT__oldsad__DOT__q = this->datapath__DOT__old_SAD_reg;
    this->datapath__DOT__olddad__DOT__q = this->datapath__DOT__old_DAD_reg;
    this->datapath__DOT__oldctl__DOT__q = this->datapath__DOT__old_CTL_reg;
    // ALWAYS at dma/dma_top.sv:27
    this->set_wdata = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			this->set_wdata = 1U;
		    }
		}
	    }
	}
    }
    this->datapath__DOT__destGamePak = this->destGamePak;
    this->datapath__DOT__dAddr = ((0xf8000000U & (((IData)(this->destGamePak) 
						   << 0x1bU) 
						  & this->datapath__DOT__dAddrRaw)) 
				  | (0x7ffffffU & this->datapath__DOT__dAddrRaw));
    this->datapath__DOT__srcGamePak = this->srcGamePak;
    this->datapath__DOT__sAddr = ((0xf8000000U & (((IData)(this->srcGamePak) 
						   << 0x1bU) 
						  & this->datapath__DOT__sAddrRaw)) 
				  | (0x7ffffffU & this->datapath__DOT__sAddrRaw));
    this->starter__DOT__sound = this->sound;
    this->datapath__DOT__sound = this->sound;
    this->starter__DOT__clk = this->clk;
    this->fsm__DOT__clk = this->clk;
    this->datapath__DOT__clk = this->clk;
    this->starter__DOT__sound_req = this->sound_req;
    this->fsm__DOT__mem_wait = this->mem_wait;
    this->fsm__DOT__preempted = this->preempted;
    this->datapath__DOT__srcAddrL = this->srcAddrL;
    this->datapath__DOT__srcAddrH = this->srcAddrH;
    this->datapath__DOT____Vcellinp__oldsad__d = (((IData)(this->srcAddrH) 
						   << 0x10U) 
						  | (IData)(this->srcAddrL));
    this->datapath__DOT____Vcellinp__srcAddrMux__i1 
	= (((IData)(this->srcAddrH) << 0x10U) | (IData)(this->srcAddrL));
    this->datapath__DOT__destAddrL = this->destAddrL;
    this->datapath__DOT__destAddrH = this->destAddrH;
    this->datapath__DOT____Vcellinp__olddad__d = (((IData)(this->destAddrH) 
						   << 0x10U) 
						  | (IData)(this->destAddrL));
    this->datapath__DOT__controlL = this->controlL;
    this->datapath__DOT__words_to_transfer = (0x3fffU 
					      & ((IData)(this->sound)
						  ? 4U
						  : (IData)(this->controlL)));
    this->starter__DOT__hcount = this->hcount;
    this->starter__DOT__vcount = this->vcount;
    this->starter__DOT__controlH = this->controlH;
    this->fsm__DOT__dma_repeat = (1U & ((IData)(this->controlH) 
					>> 9U));
    this->fsm__DOT__enable = (1U & ((IData)(this->controlH) 
				    >> 0xfU));
    this->fsm__DOT__genIRQ = (1U & ((IData)(this->controlH) 
				    >> 0xeU));
    this->datapath__DOT__controlH = this->controlH;
    this->datapath__DOT____Vcellinp__oldctl__d = (((IData)(this->controlH) 
						   << 0x10U) 
						  | (IData)(this->controlL));
    // ALWAYS at dma/dma_top.sv:27
    this->storeRData = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->storeRData = 1U;
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:222
    this->datapath__DOT__targetAddr = (((IData)(this->destAddrH) 
					<< 0x10U) | (IData)(this->destAddrL));
    if ((3U == (3U & ((IData)(this->controlH) >> 0xcU)))) {
	if ((1U & (~ (IData)(this->sound)))) {
	    this->datapath__DOT__targetAddr = 0x6000000U;
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->stepSRC = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->stepSRC = 1U;
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:222
    this->datapath__DOT__sCnt = (3U & ((IData)(this->controlH) 
				       >> 7U));
    // ALWAYS at dma/dma_top.sv:222
    this->datapath__DOT__dCnt = (3U & ((IData)(this->controlH) 
				       >> 5U));
    if ((3U == (3U & ((IData)(this->controlH) >> 0xcU)))) {
	if (this->sound) {
	    this->datapath__DOT__dCnt = 2U;
	}
    }
    this->new_transfer = (((this->datapath__DOT__old_SAD_reg 
			    != (((IData)(this->srcAddrH) 
				 << 0x10U) | (IData)(this->srcAddrL))) 
			   | (this->datapath__DOT__old_DAD_reg 
			      != (((IData)(this->destAddrH) 
				   << 0x10U) | (IData)(this->destAddrL)))) 
			  | (this->datapath__DOT__old_CTL_reg 
			     != (((IData)(this->controlH) 
				  << 0x10U) | (IData)(this->controlL))));
    this->datapath__DOT__xferWord = (1U & ((IData)(this->controlH) 
					   >> 0xaU));
    // ALWAYS at dma/dma_top.sv:27
    this->write = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->write = 1U;
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->others_cant_preempt = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->others_cant_preempt = 1U;
			}
		    }
		}
	    }
	}
    }
    this->starter__DOT__cpu_preemptable = this->cpu_preemptable;
    // ALWAYS at dma/dma_top.sv:303
    this->starter__DOT__hold_sound = 0U;
    if ((0x2000U & (IData)(this->controlH))) {
	if ((0x1000U & (IData)(this->controlH))) {
	    if (this->sound) {
		if (this->starter__DOT__sound_req_delay) {
		    if ((1U & (~ (IData)(this->cpu_preemptable)))) {
			this->starter__DOT__hold_sound = 1U;
		    }
		} else {
		    this->starter__DOT__hold_sound = 0U;
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:303
    this->starter__DOT__passed_go = this->starter__DOT__display_sync_startable;
    if ((0x2000U & (IData)(this->controlH))) {
	if ((0x1000U & (IData)(this->controlH))) {
	    if ((1U & (~ (IData)(this->sound)))) {
		if ((1U & (~ (((2U == (0xffU & (IData)(this->vcount))) 
			       & (IData)(this->starter__DOT__display_sync_startable)) 
			      & (IData)(this->cpu_preemptable))))) {
		    if (((0xa2U == (0xffU & (IData)(this->vcount))) 
			 & (IData)(this->cpu_preemptable))) {
			this->starter__DOT__passed_go 
			    = (1U & ((IData)(this->controlH) 
				     >> 0xfU));
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:303
    this->dma_stop = 0U;
    if ((0x2000U & (IData)(this->controlH))) {
	if ((0x1000U & (IData)(this->controlH))) {
	    if ((1U & (~ (IData)(this->sound)))) {
		if ((1U & (~ (((2U == (0xffU & (IData)(this->vcount))) 
			       & (IData)(this->starter__DOT__display_sync_startable)) 
			      & (IData)(this->cpu_preemptable))))) {
		    if (((0xa2U == (0xffU & (IData)(this->vcount))) 
			 & (IData)(this->cpu_preemptable))) {
			this->dma_stop = 1U;
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:303
    this->start = ((0x2000U & (IData)(this->controlH))
		    ? ((0x1000U & (IData)(this->controlH))
		        ? ((IData)(this->sound) ? ((IData)(this->starter__DOT__sound_req_delay) 
						   & (IData)(this->cpu_preemptable))
			    : (((2U == (0xffU & (IData)(this->vcount))) 
				& (IData)(this->starter__DOT__display_sync_startable)) 
			       & (IData)(this->cpu_preemptable)))
		        : ((0xf0U == (0xffU & (IData)(this->hcount))) 
			   & (IData)(this->cpu_preemptable)))
		    : ((0x1000U & (IData)(this->controlH))
		        ? ((0xa0U == (0xffU & (IData)(this->vcount))) 
			   & (IData)(this->cpu_preemptable))
		        : (IData)(this->cpu_preemptable)));
    this->datapath__DOT__sad__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__dad__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__data_reg__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__xferCnt__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__oldsad__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__olddad__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__oldctl__DOT__rst_b = this->datapath__DOT__rst_b;
    this->fsm__DOT__set_wdata = this->set_wdata;
    this->datapath__DOT__set_wdata = this->set_wdata;
    this->datapath__DOT__addrMux__DOT__i1 = this->datapath__DOT__dAddr;
    this->datapath__DOT__addrMux__DOT__i0 = this->datapath__DOT__sAddr;
    this->datapath__DOT__sad__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__dad__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__data_reg__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__xferCnt__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__oldsad__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__olddad__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__oldctl__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__oldsad__DOT__d = this->datapath__DOT____Vcellinp__oldsad__d;
    this->datapath__DOT__srcAddrMux__DOT__i1 = this->datapath__DOT____Vcellinp__srcAddrMux__i1;
    this->datapath__DOT__olddad__DOT__d = this->datapath__DOT____Vcellinp__olddad__d;
    this->xferDone = ((IData)(this->datapath__DOT__xfers) 
		      == (IData)(this->datapath__DOT__words_to_transfer));
    this->datapath__DOT__oldctl__DOT__d = this->datapath__DOT____Vcellinp__oldctl__d;
    this->fsm__DOT__storeRData = this->storeRData;
    this->datapath__DOT__storeRData = this->storeRData;
    this->datapath__DOT__destAddrMux__DOT__i1 = this->datapath__DOT__targetAddr;
    this->fsm__DOT__stepSRC = this->stepSRC;
    this->datapath__DOT__stepSRC = this->stepSRC;
    // ALWAYS at dma/dma_top.sv:204
    this->datapath__DOT__reloadDad = (3U == (IData)(this->datapath__DOT__dCnt));
    this->fsm__DOT__new_transfer = this->new_transfer;
    this->datapath__DOT__new_transfer = this->new_transfer;
    // ALWAYS at dma/dma_top.sv:27
    this->loadSAD = 0U;
    if ((0U == (IData)(this->fsm__DOT__cs))) {
	if ((((IData)(this->controlH) >> 0xfU) & (IData)(this->new_transfer))) {
	    this->loadSAD = 1U;
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->loadDAD = 0U;
    if ((0U == (IData)(this->fsm__DOT__cs))) {
	if ((((IData)(this->controlH) >> 0xfU) & (IData)(this->new_transfer))) {
	    this->loadDAD = 1U;
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->loadCNT = 0U;
    if ((0U == (IData)(this->fsm__DOT__cs))) {
	if ((((IData)(this->controlH) >> 0xfU) & (IData)(this->new_transfer))) {
	    this->loadCNT = 1U;
	}
    }
    // ALWAYS at dma/dma_top.sv:204
    this->datapath__DOT__addrStep = ((IData)(this->datapath__DOT__xferWord)
				      ? 4U : 2U);
    this->datapath__DOT__steppedSAddr = ((2U & (IData)(this->datapath__DOT__sCnt))
					  ? ((1U & (IData)(this->datapath__DOT__sCnt))
					      ? (this->datapath__DOT__sAddr 
						 + this->datapath__DOT__addrStep)
					      : this->datapath__DOT__sAddr)
					  : ((1U & (IData)(this->datapath__DOT__sCnt))
					      ? (this->datapath__DOT__sAddr 
						 - this->datapath__DOT__addrStep)
					      : (this->datapath__DOT__sAddr 
						 + this->datapath__DOT__addrStep)));
    this->datapath__DOT__steppedDAddr = ((2U & (IData)(this->datapath__DOT__dCnt))
					  ? ((1U & (IData)(this->datapath__DOT__dCnt))
					      ? (this->datapath__DOT__dAddr 
						 + this->datapath__DOT__addrStep)
					      : this->datapath__DOT__dAddr)
					  : ((1U & (IData)(this->datapath__DOT__dCnt))
					      ? (this->datapath__DOT__dAddr 
						 - this->datapath__DOT__addrStep)
					      : (this->datapath__DOT__dAddr 
						 + this->datapath__DOT__addrStep)));
    this->datapath__DOT__size_mem_transfer = ((IData)(this->datapath__DOT__xferWord)
					       ? 2U
					       : 1U);
    this->fsm__DOT__write = this->write;
    this->datapath__DOT__write = this->write;
    this->datapath__DOT__desiredAddr = ((IData)(this->write)
					 ? this->datapath__DOT__dAddr
					 : this->datapath__DOT__sAddr);
    this->fsm__DOT__others_cant_preempt = this->others_cant_preempt;
    this->starter__DOT__dma_stop = this->dma_stop;
    this->starter__DOT__start = this->start;
    this->fsm__DOT__start = this->start;
    this->fsm__DOT__xferDone = this->xferDone;
    this->datapath__DOT__xferDone = this->xferDone;
    // ALWAYS at dma/dma_top.sv:27
    this->reload_xfers = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if (((IData)(this->xferDone) 
				     & ((IData)(this->controlH) 
					>> 9U))) {
				    this->reload_xfers = 1U;
				} else {
				    if (this->xferDone) {
					this->reload_xfers = 1U;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->stepDEST = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if ((1U & (~ ((IData)(this->xferDone) 
					      & ((IData)(this->controlH) 
						 >> 9U))))) {
				    if ((1U & (~ (IData)(this->xferDone)))) {
					this->stepDEST = 1U;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->fsm_disable = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if ((1U & (~ ((IData)(this->xferDone) 
					      & ((IData)(this->controlH) 
						 >> 9U))))) {
				    if (this->xferDone) {
					this->fsm_disable = 1U;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->irq = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if (((IData)(this->xferDone) 
				     & ((IData)(this->controlH) 
					>> 9U))) {
				    this->irq = (1U 
						 & ((IData)(this->controlH) 
						    >> 0xeU));
				} else {
				    if (this->xferDone) {
					this->irq = 
					    (1U & ((IData)(this->controlH) 
						   >> 0xeU));
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    this->datapath__DOT__data_reg__DOT__enable = this->datapath__DOT__storeRData;
    this->datapath__DOT__xferCnt__DOT__enable = this->datapath__DOT__stepSRC;
    this->fsm__DOT__loadSAD = this->loadSAD;
    this->datapath__DOT__loadSAD = this->loadSAD;
    this->datapath__DOT__sadEnable = ((IData)(this->loadSAD) 
				      | (IData)(this->stepSRC));
    this->fsm__DOT__loadDAD = this->loadDAD;
    this->datapath__DOT__loadDAD = this->loadDAD;
    this->fsm__DOT__loadCNT = this->loadCNT;
    this->datapath__DOT__loadCNT = this->loadCNT;
    this->datapath__DOT____Vcellinp__destAddrMux__s 
	= ((IData)(this->loadDAD) | ((IData)(this->loadCNT) 
				     & (IData)(this->datapath__DOT__reloadDad)));
    this->datapath__DOT__srcAddrMux__DOT__i0 = this->datapath__DOT__steppedSAddr;
    this->datapath__DOT__nextSAddr = ((IData)(this->loadSAD)
				       ? this->datapath__DOT____Vcellinp__srcAddrMux__i1
				       : this->datapath__DOT__steppedSAddr);
    this->datapath__DOT__destAddrMux__DOT__i0 = this->datapath__DOT__steppedDAddr;
    this->datapath__DOT__addrMux__DOT__s = this->datapath__DOT__write;
    this->datapath__DOT__addrMux__DOT__y = this->datapath__DOT__desiredAddr;
    // ALWAYS at dma/dma_top.sv:245
    this->datapath__DOT__wdata_size = this->datapath__DOT__data;
    if (((1U == (IData)(this->datapath__DOT__size_mem_transfer)) 
	 & (this->datapath__DOT__desiredAddr >> 1U))) {
	this->datapath__DOT__wdata_size = ((0xffffU 
					    & this->datapath__DOT__wdata_size) 
					   | (0xffff0000U 
					      & (this->datapath__DOT__data 
						 << 0x10U)));
    }
    this->fsm__DOT__reload_xfers = this->reload_xfers;
    // ALWAYS at dma/counter.sv:15
    this->datapath__DOT__xferCnt__DOT__ns = (0x3fffU 
					     & ((IData)(this->reload_xfers)
						 ? 0U
						 : 
						((IData)(this->stepSRC)
						  ? 
						 ((IData)(1U) 
						  + (IData)(this->datapath__DOT__xfers))
						  : (IData)(this->datapath__DOT__xfers))));
    this->datapath__DOT__reload_xfers = this->reload_xfers;
    this->fsm__DOT__stepDEST = this->stepDEST;
    this->datapath__DOT__stepDEST = this->stepDEST;
    this->datapath__DOT__dadEnable = (((IData)(this->loadDAD) 
				       | (IData)(this->stepDEST)) 
				      | ((IData)(this->loadCNT) 
					 & (IData)(this->datapath__DOT__reloadDad)));
    this->fsm__DOT__disable_dma = this->fsm_disable;
    this->disable_dma = ((IData)(this->fsm_disable) 
			 | (IData)(this->dma_stop));
    this->fsm__DOT__irq = this->irq;
    this->datapath__DOT__srcAddrMux__DOT__s = this->datapath__DOT__loadSAD;
    this->datapath__DOT__sad__DOT__enable = this->datapath__DOT__sadEnable;
    this->datapath__DOT__destAddrMux__DOT__s = this->datapath__DOT____Vcellinp__destAddrMux__s;
    this->datapath__DOT__nextDAddr = ((IData)(this->datapath__DOT____Vcellinp__destAddrMux__s)
				       ? this->datapath__DOT__targetAddr
				       : this->datapath__DOT__steppedDAddr);
    this->datapath__DOT__srcAddrMux__DOT__y = this->datapath__DOT__nextSAddr;
    this->datapath__DOT__sad__DOT__d = this->datapath__DOT__nextSAddr;
    this->datapath__DOT__xferCnt__DOT__clear = this->datapath__DOT__reload_xfers;
    this->datapath__DOT__dad__DOT__enable = this->datapath__DOT__dadEnable;
    this->datapath__DOT__destAddrMux__DOT__y = this->datapath__DOT__nextDAddr;
    this->datapath__DOT__dad__DOT__d = this->datapath__DOT__nextDAddr;
}

VL_INLINE_OPT void Vgba_top_dma_unit::_settle__TOP__gba_top__DOT__dma__DOT__dma0__9(Vgba_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vgba_top_dma_unit::_settle__TOP__gba_top__DOT__dma__DOT__dma0__9\n"); );
    Vgba_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    this->fsm__DOT__allowed_to_begin = this->allowed_to_begin;
    // ALWAYS at dma/dma_top.sv:27
    this->fsm__DOT__ns = 0U;
    if ((0U == (IData)(this->fsm__DOT__cs))) {
	if ((((IData)(this->controlH) >> 0xfU) & (IData)(this->new_transfer))) {
	    this->fsm__DOT__ns = 1U;
	}
    } else {
	if ((1U == (IData)(this->fsm__DOT__cs))) {
	    if ((0x8000U & (IData)(this->controlH))) {
		this->fsm__DOT__ns = ((IData)(this->start)
				       ? (((IData)(this->preempted) 
					   | (IData)(this->mem_wait))
					   ? 2U : ((IData)(this->allowed_to_begin)
						    ? 3U
						    : 1U))
				       : 1U);
	    }
	} else {
	    if ((2U == (IData)(this->fsm__DOT__cs))) {
		if ((0x8000U & (IData)(this->controlH))) {
		    this->fsm__DOT__ns = (((IData)(this->preempted) 
					   | (IData)(this->mem_wait))
					   ? 2U : ((IData)(this->allowed_to_begin)
						    ? 3U
						    : 2U));
		}
	    } else {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if (this->mem_wait) {
			this->fsm__DOT__ns = 3U;
		    } else {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->fsm__DOT__ns = 4U;
			}
		    }
		} else {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if (this->mem_wait) {
			    this->fsm__DOT__ns = 4U;
			} else {
			    if ((0x8000U & (IData)(this->controlH))) {
				this->fsm__DOT__ns 
				    = (((IData)(this->xferDone) 
					& ((IData)(this->controlH) 
					   >> 9U)) ? 1U
				        : ((IData)(this->xferDone)
					    ? 0U : 
					   ((IData)(this->preempted)
					     ? 5U : 3U)));
			    }
			}
		    } else {
			if ((5U == (IData)(this->fsm__DOT__cs))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				this->fsm__DOT__ns 
				    = (((IData)(this->preempted) 
					| (IData)(this->mem_wait))
				        ? 5U : ((IData)(this->allowed_to_begin)
						 ? 3U
						 : 5U));
			    }
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->active = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U == (IData)(this->fsm__DOT__cs))) {
	    if ((0x8000U & (IData)(this->controlH))) {
		if (this->start) {
		    if ((1U & (~ ((IData)(this->preempted) 
				  | (IData)(this->mem_wait))))) {
			if (this->allowed_to_begin) {
			    this->active = 1U;
			}
		    }
		}
	    }
	} else {
	    if ((2U == (IData)(this->fsm__DOT__cs))) {
		if ((0x8000U & (IData)(this->controlH))) {
		    if ((1U & (~ ((IData)(this->preempted) 
				  | (IData)(this->mem_wait))))) {
			if (this->allowed_to_begin) {
			    this->active = 1U;
			}
		    }
		}
	    } else {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if (this->mem_wait) {
			this->active = 1U;
		    } else {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->active = 1U;
			}
		    }
		} else {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if (this->mem_wait) {
			    this->active = 1U;
			} else {
			    if ((0x8000U & (IData)(this->controlH))) {
				if ((1U & (~ ((IData)(this->xferDone) 
					      & ((IData)(this->controlH) 
						 >> 9U))))) {
				    this->active = 1U;
				}
			    }
			}
		    } else {
			if ((5U == (IData)(this->fsm__DOT__cs))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if ((1U & (~ ((IData)(this->preempted) 
					      | (IData)(this->mem_wait))))) {
				    if (this->allowed_to_begin) {
					this->active = 1U;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    this->fsm__DOT__active = this->active;
    this->datapath__DOT__active = this->active;
    this->datapath__DOT__wdata__out__en1 = (((IData)(this->active) 
					     & (IData)(this->set_wdata))
					     ? 0xffffffffU
					     : 0U);
}

VL_INLINE_OPT void Vgba_top_dma_unit::_settle__TOP__gba_top__DOT__dma__DOT__dma0__13(Vgba_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vgba_top_dma_unit::_settle__TOP__gba_top__DOT__dma__DOT__dma0__13\n"); );
    Vgba_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    this->datapath__DOT__size = this->size;
    this->datapath__DOT__wen = this->wen;
    this->datapath__DOT__wdata = this->wdata;
    this->datapath__DOT__addr = this->addr;
    this->datapath__DOT__rdata = this->rdata;
    this->datapath__DOT__data_reg__DOT__d = this->datapath__DOT__rdata;
}

VL_INLINE_OPT void Vgba_top_dma_unit::_combo__TOP__gba_top__DOT__dma__DOT__dma0__17(Vgba_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vgba_top_dma_unit::_combo__TOP__gba_top__DOT__dma__DOT__dma0__17\n"); );
    Vgba_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    this->starter__DOT__rst_b = this->rst_b;
    this->fsm__DOT__rst_b = this->rst_b;
    this->datapath__DOT__rst_b = this->rst_b;
    this->starter__DOT__sound = this->sound;
    this->datapath__DOT__srcGamePak = this->srcGamePak;
    this->datapath__DOT__destGamePak = this->destGamePak;
    this->datapath__DOT__sound = this->sound;
    this->starter__DOT__sound_req = this->sound_req;
    this->datapath__DOT__sad__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__dad__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__data_reg__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__xferCnt__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__oldsad__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__olddad__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__oldctl__DOT__rst_b = this->datapath__DOT__rst_b;
}

VL_INLINE_OPT void Vgba_top_dma_unit::_combo__TOP__gba_top__DOT__dma__DOT__dma0__21(Vgba_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vgba_top_dma_unit::_combo__TOP__gba_top__DOT__dma__DOT__dma0__21\n"); );
    Vgba_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    this->starter__DOT__clk = this->clk;
    this->fsm__DOT__clk = this->clk;
    this->datapath__DOT__clk = this->clk;
    this->fsm__DOT__preempted = this->preempted;
    this->datapath__DOT__sad__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__dad__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__data_reg__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__xferCnt__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__oldsad__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__olddad__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__oldctl__DOT__clk = this->datapath__DOT__clk;
}

VL_INLINE_OPT void Vgba_top_dma_unit::_sequent__TOP__gba_top__DOT__dma__DOT__dma0__25(Vgba_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vgba_top_dma_unit::_sequent__TOP__gba_top__DOT__dma__DOT__dma0__25\n"); );
    Vgba_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at dma/register.sv:10
    if (this->rst_b) {
	if (this->storeRData) {
	    this->datapath__DOT__data = this->rdata;
	}
    } else {
	this->datapath__DOT__data = 0U;
    }
    // ALWAYS at dma/register.sv:10
    this->datapath__DOT__old_CTL_reg = ((IData)(this->rst_b)
					 ? this->datapath__DOT____Vcellinp__oldctl__d
					 : 0U);
    // ALWAYS at dma/register.sv:10
    this->datapath__DOT__old_DAD_reg = ((IData)(this->rst_b)
					 ? this->datapath__DOT____Vcellinp__olddad__d
					 : 0U);
    // ALWAYS at dma/register.sv:10
    this->datapath__DOT__old_SAD_reg = ((IData)(this->rst_b)
					 ? this->datapath__DOT____Vcellinp__oldsad__d
					 : 0U);
    // ALWAYS at dma/register.sv:10
    if (this->rst_b) {
	if (this->datapath__DOT__sadEnable) {
	    this->datapath__DOT__sAddrRaw = this->datapath__DOT__nextSAddr;
	}
    } else {
	this->datapath__DOT__sAddrRaw = 0U;
    }
    // ALWAYS at dma/register.sv:10
    if (this->rst_b) {
	if (this->datapath__DOT__dadEnable) {
	    this->datapath__DOT__dAddrRaw = this->datapath__DOT__nextDAddr;
	}
    } else {
	this->datapath__DOT__dAddrRaw = 0U;
    }
    // ALWAYS at dma/dma_top.sv:284
    this->starter__DOT__display_sync_startable = ((IData)(this->rst_b) 
						  & (IData)(this->starter__DOT__passed_go));
    // ALWAYS at dma/counter.sv:9
    this->datapath__DOT__xfers = ((IData)(this->rst_b)
				   ? (IData)(this->datapath__DOT__xferCnt__DOT__ns)
				   : 0U);
    // ALWAYS at dma/dma_top.sv:291
    this->starter__DOT__sound_req_delay = ((IData)(this->rst_b) 
					   & ((IData)(this->starter__DOT__hold_sound)
					       ? (IData)(this->starter__DOT__sound_req_delay)
					       : (IData)(this->sound_req)));
    // ALWAYS at dma/dma_top.sv:20
    this->fsm__DOT__cs = ((IData)(this->rst_b) ? (IData)(this->fsm__DOT__ns)
			   : 0U);
    this->datapath__DOT__data_reg__DOT__q = this->datapath__DOT__data;
    this->datapath__DOT__oldctl__DOT__q = this->datapath__DOT__old_CTL_reg;
    this->datapath__DOT__olddad__DOT__q = this->datapath__DOT__old_DAD_reg;
    this->datapath__DOT__oldsad__DOT__q = this->datapath__DOT__old_SAD_reg;
    this->datapath__DOT__sad__DOT__q = this->datapath__DOT__sAddrRaw;
    this->datapath__DOT__dad__DOT__q = this->datapath__DOT__dAddrRaw;
    this->datapath__DOT__xferCnt__DOT__q = this->datapath__DOT__xfers;
    // ALWAYS at dma/dma_top.sv:27
    this->set_wdata = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			this->set_wdata = 1U;
		    }
		}
	    }
	}
    }
    this->fsm__DOT__set_wdata = this->set_wdata;
    this->datapath__DOT__set_wdata = this->set_wdata;
}

VL_INLINE_OPT void Vgba_top_dma_unit::_combo__TOP__gba_top__DOT__dma__DOT__dma0__29(Vgba_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vgba_top_dma_unit::_combo__TOP__gba_top__DOT__dma__DOT__dma0__29\n"); );
    Vgba_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    this->fsm__DOT__mem_wait = this->mem_wait;
    this->datapath__DOT__srcAddrL = this->srcAddrL;
    this->datapath__DOT__srcAddrH = this->srcAddrH;
    this->datapath__DOT____Vcellinp__srcAddrMux__i1 
	= (((IData)(this->srcAddrH) << 0x10U) | (IData)(this->srcAddrL));
    this->datapath__DOT__destAddrL = this->destAddrL;
    this->datapath__DOT__destAddrH = this->destAddrH;
    this->datapath__DOT__controlL = this->controlL;
    this->datapath__DOT__words_to_transfer = (0x3fffU 
					      & ((IData)(this->sound)
						  ? 4U
						  : (IData)(this->controlL)));
    this->starter__DOT__hcount = this->hcount;
    this->starter__DOT__vcount = this->vcount;
    this->starter__DOT__controlH = this->controlH;
    this->fsm__DOT__dma_repeat = (1U & ((IData)(this->controlH) 
					>> 9U));
    this->fsm__DOT__enable = (1U & ((IData)(this->controlH) 
				    >> 0xfU));
    this->fsm__DOT__genIRQ = (1U & ((IData)(this->controlH) 
				    >> 0xeU));
    this->datapath__DOT__controlH = this->controlH;
    // ALWAYS at dma/dma_top.sv:222
    this->datapath__DOT__targetAddr = (((IData)(this->destAddrH) 
					<< 0x10U) | (IData)(this->destAddrL));
    if ((3U == (3U & ((IData)(this->controlH) >> 0xcU)))) {
	if ((1U & (~ (IData)(this->sound)))) {
	    this->datapath__DOT__targetAddr = 0x6000000U;
	}
    }
    // ALWAYS at dma/dma_top.sv:222
    this->datapath__DOT__sCnt = (3U & ((IData)(this->controlH) 
				       >> 7U));
    // ALWAYS at dma/dma_top.sv:222
    this->datapath__DOT__dCnt = (3U & ((IData)(this->controlH) 
				       >> 5U));
    if ((3U == (3U & ((IData)(this->controlH) >> 0xcU)))) {
	if (this->sound) {
	    this->datapath__DOT__dCnt = 2U;
	}
    }
    this->datapath__DOT__xferWord = (1U & ((IData)(this->controlH) 
					   >> 0xaU));
    this->starter__DOT__cpu_preemptable = this->cpu_preemptable;
    this->datapath__DOT____Vcellinp__oldctl__d = (((IData)(this->controlH) 
						   << 0x10U) 
						  | (IData)(this->controlL));
    this->datapath__DOT____Vcellinp__olddad__d = (((IData)(this->destAddrH) 
						   << 0x10U) 
						  | (IData)(this->destAddrL));
    this->datapath__DOT____Vcellinp__oldsad__d = (((IData)(this->srcAddrH) 
						   << 0x10U) 
						  | (IData)(this->srcAddrL));
    this->new_transfer = (((this->datapath__DOT__old_SAD_reg 
			    != (((IData)(this->srcAddrH) 
				 << 0x10U) | (IData)(this->srcAddrL))) 
			   | (this->datapath__DOT__old_DAD_reg 
			      != (((IData)(this->destAddrH) 
				   << 0x10U) | (IData)(this->destAddrL)))) 
			  | (this->datapath__DOT__old_CTL_reg 
			     != (((IData)(this->controlH) 
				  << 0x10U) | (IData)(this->controlL))));
    this->datapath__DOT__sAddr = ((0xf8000000U & (((IData)(this->srcGamePak) 
						   << 0x1bU) 
						  & this->datapath__DOT__sAddrRaw)) 
				  | (0x7ffffffU & this->datapath__DOT__sAddrRaw));
    this->datapath__DOT__dAddr = ((0xf8000000U & (((IData)(this->destGamePak) 
						   << 0x1bU) 
						  & this->datapath__DOT__dAddrRaw)) 
				  | (0x7ffffffU & this->datapath__DOT__dAddrRaw));
    // ALWAYS at dma/dma_top.sv:303
    this->starter__DOT__passed_go = this->starter__DOT__display_sync_startable;
    if ((0x2000U & (IData)(this->controlH))) {
	if ((0x1000U & (IData)(this->controlH))) {
	    if ((1U & (~ (IData)(this->sound)))) {
		if ((1U & (~ (((2U == (0xffU & (IData)(this->vcount))) 
			       & (IData)(this->starter__DOT__display_sync_startable)) 
			      & (IData)(this->cpu_preemptable))))) {
		    if (((0xa2U == (0xffU & (IData)(this->vcount))) 
			 & (IData)(this->cpu_preemptable))) {
			this->starter__DOT__passed_go 
			    = (1U & ((IData)(this->controlH) 
				     >> 0xfU));
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:303
    this->dma_stop = 0U;
    if ((0x2000U & (IData)(this->controlH))) {
	if ((0x1000U & (IData)(this->controlH))) {
	    if ((1U & (~ (IData)(this->sound)))) {
		if ((1U & (~ (((2U == (0xffU & (IData)(this->vcount))) 
			       & (IData)(this->starter__DOT__display_sync_startable)) 
			      & (IData)(this->cpu_preemptable))))) {
		    if (((0xa2U == (0xffU & (IData)(this->vcount))) 
			 & (IData)(this->cpu_preemptable))) {
			this->dma_stop = 1U;
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:303
    this->starter__DOT__hold_sound = 0U;
    if ((0x2000U & (IData)(this->controlH))) {
	if ((0x1000U & (IData)(this->controlH))) {
	    if (this->sound) {
		if (this->starter__DOT__sound_req_delay) {
		    if ((1U & (~ (IData)(this->cpu_preemptable)))) {
			this->starter__DOT__hold_sound = 1U;
		    }
		} else {
		    this->starter__DOT__hold_sound = 0U;
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:303
    this->start = ((0x2000U & (IData)(this->controlH))
		    ? ((0x1000U & (IData)(this->controlH))
		        ? ((IData)(this->sound) ? ((IData)(this->starter__DOT__sound_req_delay) 
						   & (IData)(this->cpu_preemptable))
			    : (((2U == (0xffU & (IData)(this->vcount))) 
				& (IData)(this->starter__DOT__display_sync_startable)) 
			       & (IData)(this->cpu_preemptable)))
		        : ((0xf0U == (0xffU & (IData)(this->hcount))) 
			   & (IData)(this->cpu_preemptable)))
		    : ((0x1000U & (IData)(this->controlH))
		        ? ((0xa0U == (0xffU & (IData)(this->vcount))) 
			   & (IData)(this->cpu_preemptable))
		        : (IData)(this->cpu_preemptable)));
    // ALWAYS at dma/dma_top.sv:27
    this->storeRData = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->storeRData = 1U;
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->stepSRC = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->stepSRC = 1U;
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->write = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->write = 1U;
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->others_cant_preempt = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->others_cant_preempt = 1U;
			}
		    }
		}
	    }
	}
    }
    this->datapath__DOT__srcAddrMux__DOT__i1 = this->datapath__DOT____Vcellinp__srcAddrMux__i1;
    this->xferDone = ((IData)(this->datapath__DOT__xfers) 
		      == (IData)(this->datapath__DOT__words_to_transfer));
    this->datapath__DOT__destAddrMux__DOT__i1 = this->datapath__DOT__targetAddr;
    // ALWAYS at dma/dma_top.sv:204
    this->datapath__DOT__reloadDad = (3U == (IData)(this->datapath__DOT__dCnt));
    this->datapath__DOT__size_mem_transfer = ((IData)(this->datapath__DOT__xferWord)
					       ? 2U
					       : 1U);
    this->datapath__DOT__oldctl__DOT__d = this->datapath__DOT____Vcellinp__oldctl__d;
    this->datapath__DOT__olddad__DOT__d = this->datapath__DOT____Vcellinp__olddad__d;
    this->datapath__DOT__oldsad__DOT__d = this->datapath__DOT____Vcellinp__oldsad__d;
    this->fsm__DOT__new_transfer = this->new_transfer;
    this->datapath__DOT__new_transfer = this->new_transfer;
    // ALWAYS at dma/dma_top.sv:27
    this->loadSAD = 0U;
    if ((0U == (IData)(this->fsm__DOT__cs))) {
	if ((((IData)(this->controlH) >> 0xfU) & (IData)(this->new_transfer))) {
	    this->loadSAD = 1U;
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->loadDAD = 0U;
    if ((0U == (IData)(this->fsm__DOT__cs))) {
	if ((((IData)(this->controlH) >> 0xfU) & (IData)(this->new_transfer))) {
	    this->loadDAD = 1U;
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->loadCNT = 0U;
    if ((0U == (IData)(this->fsm__DOT__cs))) {
	if ((((IData)(this->controlH) >> 0xfU) & (IData)(this->new_transfer))) {
	    this->loadCNT = 1U;
	}
    }
    this->datapath__DOT__addrMux__DOT__i0 = this->datapath__DOT__sAddr;
    this->datapath__DOT__addrMux__DOT__i1 = this->datapath__DOT__dAddr;
    // ALWAYS at dma/dma_top.sv:204
    this->datapath__DOT__addrStep = ((IData)(this->datapath__DOT__xferWord)
				      ? 4U : 2U);
    this->datapath__DOT__steppedSAddr = ((2U & (IData)(this->datapath__DOT__sCnt))
					  ? ((1U & (IData)(this->datapath__DOT__sCnt))
					      ? (this->datapath__DOT__sAddr 
						 + this->datapath__DOT__addrStep)
					      : this->datapath__DOT__sAddr)
					  : ((1U & (IData)(this->datapath__DOT__sCnt))
					      ? (this->datapath__DOT__sAddr 
						 - this->datapath__DOT__addrStep)
					      : (this->datapath__DOT__sAddr 
						 + this->datapath__DOT__addrStep)));
    this->datapath__DOT__steppedDAddr = ((2U & (IData)(this->datapath__DOT__dCnt))
					  ? ((1U & (IData)(this->datapath__DOT__dCnt))
					      ? (this->datapath__DOT__dAddr 
						 + this->datapath__DOT__addrStep)
					      : this->datapath__DOT__dAddr)
					  : ((1U & (IData)(this->datapath__DOT__dCnt))
					      ? (this->datapath__DOT__dAddr 
						 - this->datapath__DOT__addrStep)
					      : (this->datapath__DOT__dAddr 
						 + this->datapath__DOT__addrStep)));
    this->starter__DOT__dma_stop = this->dma_stop;
    this->starter__DOT__start = this->start;
    this->fsm__DOT__start = this->start;
    this->fsm__DOT__storeRData = this->storeRData;
    this->datapath__DOT__storeRData = this->storeRData;
    this->fsm__DOT__stepSRC = this->stepSRC;
    this->datapath__DOT__stepSRC = this->stepSRC;
    this->fsm__DOT__write = this->write;
    this->datapath__DOT__write = this->write;
    this->datapath__DOT__desiredAddr = ((IData)(this->write)
					 ? this->datapath__DOT__dAddr
					 : this->datapath__DOT__sAddr);
    this->fsm__DOT__others_cant_preempt = this->others_cant_preempt;
    this->fsm__DOT__xferDone = this->xferDone;
    this->datapath__DOT__xferDone = this->xferDone;
    // ALWAYS at dma/dma_top.sv:27
    this->reload_xfers = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if (((IData)(this->xferDone) 
				     & ((IData)(this->controlH) 
					>> 9U))) {
				    this->reload_xfers = 1U;
				} else {
				    if (this->xferDone) {
					this->reload_xfers = 1U;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->stepDEST = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if ((1U & (~ ((IData)(this->xferDone) 
					      & ((IData)(this->controlH) 
						 >> 9U))))) {
				    if ((1U & (~ (IData)(this->xferDone)))) {
					this->stepDEST = 1U;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->fsm_disable = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if ((1U & (~ ((IData)(this->xferDone) 
					      & ((IData)(this->controlH) 
						 >> 9U))))) {
				    if (this->xferDone) {
					this->fsm_disable = 1U;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->irq = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if (((IData)(this->xferDone) 
				     & ((IData)(this->controlH) 
					>> 9U))) {
				    this->irq = (1U 
						 & ((IData)(this->controlH) 
						    >> 0xeU));
				} else {
				    if (this->xferDone) {
					this->irq = 
					    (1U & ((IData)(this->controlH) 
						   >> 0xeU));
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    this->fsm__DOT__loadSAD = this->loadSAD;
    this->datapath__DOT__loadSAD = this->loadSAD;
    this->datapath__DOT__sadEnable = ((IData)(this->loadSAD) 
				      | (IData)(this->stepSRC));
    this->fsm__DOT__loadDAD = this->loadDAD;
    this->datapath__DOT__loadDAD = this->loadDAD;
    this->fsm__DOT__loadCNT = this->loadCNT;
    this->datapath__DOT__loadCNT = this->loadCNT;
    this->datapath__DOT____Vcellinp__destAddrMux__s 
	= ((IData)(this->loadDAD) | ((IData)(this->loadCNT) 
				     & (IData)(this->datapath__DOT__reloadDad)));
    this->datapath__DOT__srcAddrMux__DOT__i0 = this->datapath__DOT__steppedSAddr;
    this->datapath__DOT__nextSAddr = ((IData)(this->loadSAD)
				       ? this->datapath__DOT____Vcellinp__srcAddrMux__i1
				       : this->datapath__DOT__steppedSAddr);
    this->datapath__DOT__destAddrMux__DOT__i0 = this->datapath__DOT__steppedDAddr;
    this->datapath__DOT__data_reg__DOT__enable = this->datapath__DOT__storeRData;
    this->datapath__DOT__xferCnt__DOT__enable = this->datapath__DOT__stepSRC;
    this->datapath__DOT__addrMux__DOT__s = this->datapath__DOT__write;
    this->datapath__DOT__addrMux__DOT__y = this->datapath__DOT__desiredAddr;
    // ALWAYS at dma/dma_top.sv:245
    this->datapath__DOT__wdata_size = this->datapath__DOT__data;
    if (((1U == (IData)(this->datapath__DOT__size_mem_transfer)) 
	 & (this->datapath__DOT__desiredAddr >> 1U))) {
	this->datapath__DOT__wdata_size = ((0xffffU 
					    & this->datapath__DOT__wdata_size) 
					   | (0xffff0000U 
					      & (this->datapath__DOT__data 
						 << 0x10U)));
    }
    this->fsm__DOT__reload_xfers = this->reload_xfers;
    // ALWAYS at dma/counter.sv:15
    this->datapath__DOT__xferCnt__DOT__ns = (0x3fffU 
					     & ((IData)(this->reload_xfers)
						 ? 0U
						 : 
						((IData)(this->stepSRC)
						  ? 
						 ((IData)(1U) 
						  + (IData)(this->datapath__DOT__xfers))
						  : (IData)(this->datapath__DOT__xfers))));
    this->datapath__DOT__reload_xfers = this->reload_xfers;
    this->fsm__DOT__stepDEST = this->stepDEST;
    this->datapath__DOT__stepDEST = this->stepDEST;
    this->datapath__DOT__dadEnable = (((IData)(this->loadDAD) 
				       | (IData)(this->stepDEST)) 
				      | ((IData)(this->loadCNT) 
					 & (IData)(this->datapath__DOT__reloadDad)));
    this->fsm__DOT__disable_dma = this->fsm_disable;
    this->disable_dma = ((IData)(this->fsm_disable) 
			 | (IData)(this->dma_stop));
    this->fsm__DOT__irq = this->irq;
    this->datapath__DOT__srcAddrMux__DOT__s = this->datapath__DOT__loadSAD;
    this->datapath__DOT__sad__DOT__enable = this->datapath__DOT__sadEnable;
    this->datapath__DOT__destAddrMux__DOT__s = this->datapath__DOT____Vcellinp__destAddrMux__s;
    this->datapath__DOT__nextDAddr = ((IData)(this->datapath__DOT____Vcellinp__destAddrMux__s)
				       ? this->datapath__DOT__targetAddr
				       : this->datapath__DOT__steppedDAddr);
    this->datapath__DOT__srcAddrMux__DOT__y = this->datapath__DOT__nextSAddr;
    this->datapath__DOT__sad__DOT__d = this->datapath__DOT__nextSAddr;
    this->datapath__DOT__xferCnt__DOT__clear = this->datapath__DOT__reload_xfers;
    this->datapath__DOT__dad__DOT__enable = this->datapath__DOT__dadEnable;
    this->datapath__DOT__destAddrMux__DOT__y = this->datapath__DOT__nextDAddr;
    this->datapath__DOT__dad__DOT__d = this->datapath__DOT__nextDAddr;
}

void Vgba_top_dma_unit::_settle__TOP__gba_top__DOT__dma__DOT__dma1__6(Vgba_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vgba_top_dma_unit::_settle__TOP__gba_top__DOT__dma__DOT__dma1__6\n"); );
    Vgba_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    this->starter__DOT__rst_b = this->rst_b;
    this->fsm__DOT__rst_b = this->rst_b;
    this->datapath__DOT__rst_b = this->rst_b;
    this->datapath__DOT__sad__DOT__q = this->datapath__DOT__sAddrRaw;
    this->datapath__DOT__dad__DOT__q = this->datapath__DOT__dAddrRaw;
    this->datapath__DOT__data_reg__DOT__q = this->datapath__DOT__data;
    this->datapath__DOT__xferCnt__DOT__q = this->datapath__DOT__xfers;
    this->datapath__DOT__oldsad__DOT__q = this->datapath__DOT__old_SAD_reg;
    this->datapath__DOT__olddad__DOT__q = this->datapath__DOT__old_DAD_reg;
    this->datapath__DOT__oldctl__DOT__q = this->datapath__DOT__old_CTL_reg;
    // ALWAYS at dma/dma_top.sv:27
    this->set_wdata = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			this->set_wdata = 1U;
		    }
		}
	    }
	}
    }
    this->datapath__DOT__destGamePak = this->destGamePak;
    this->datapath__DOT__dAddr = ((0xf8000000U & (((IData)(this->destGamePak) 
						   << 0x1bU) 
						  & this->datapath__DOT__dAddrRaw)) 
				  | (0x7ffffffU & this->datapath__DOT__dAddrRaw));
    this->datapath__DOT__srcGamePak = this->srcGamePak;
    this->datapath__DOT__sAddr = ((0xf8000000U & (((IData)(this->srcGamePak) 
						   << 0x1bU) 
						  & this->datapath__DOT__sAddrRaw)) 
				  | (0x7ffffffU & this->datapath__DOT__sAddrRaw));
    this->starter__DOT__sound = this->sound;
    this->datapath__DOT__sound = this->sound;
    this->starter__DOT__clk = this->clk;
    this->fsm__DOT__clk = this->clk;
    this->datapath__DOT__clk = this->clk;
    this->fsm__DOT__mem_wait = this->mem_wait;
    this->fsm__DOT__preempted = this->preempted;
    this->datapath__DOT__srcAddrL = this->srcAddrL;
    this->datapath__DOT__srcAddrH = this->srcAddrH;
    this->datapath__DOT____Vcellinp__oldsad__d = (((IData)(this->srcAddrH) 
						   << 0x10U) 
						  | (IData)(this->srcAddrL));
    this->datapath__DOT____Vcellinp__srcAddrMux__i1 
	= (((IData)(this->srcAddrH) << 0x10U) | (IData)(this->srcAddrL));
    this->datapath__DOT__destAddrL = this->destAddrL;
    this->datapath__DOT__destAddrH = this->destAddrH;
    this->datapath__DOT____Vcellinp__olddad__d = (((IData)(this->destAddrH) 
						   << 0x10U) 
						  | (IData)(this->destAddrL));
    this->datapath__DOT__controlL = this->controlL;
    this->datapath__DOT__words_to_transfer = (0x3fffU 
					      & ((IData)(this->sound)
						  ? 4U
						  : (IData)(this->controlL)));
    this->starter__DOT__hcount = this->hcount;
    this->starter__DOT__vcount = this->vcount;
    this->starter__DOT__controlH = this->controlH;
    this->fsm__DOT__dma_repeat = (1U & ((IData)(this->controlH) 
					>> 9U));
    this->fsm__DOT__enable = (1U & ((IData)(this->controlH) 
				    >> 0xfU));
    this->fsm__DOT__genIRQ = (1U & ((IData)(this->controlH) 
				    >> 0xeU));
    this->datapath__DOT__controlH = this->controlH;
    this->datapath__DOT____Vcellinp__oldctl__d = (((IData)(this->controlH) 
						   << 0x10U) 
						  | (IData)(this->controlL));
    // ALWAYS at dma/dma_top.sv:27
    this->storeRData = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->storeRData = 1U;
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:222
    this->datapath__DOT__targetAddr = (((IData)(this->destAddrH) 
					<< 0x10U) | (IData)(this->destAddrL));
    if ((3U == (3U & ((IData)(this->controlH) >> 0xcU)))) {
	if ((1U & (~ (IData)(this->sound)))) {
	    this->datapath__DOT__targetAddr = 0x6000000U;
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->stepSRC = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->stepSRC = 1U;
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:222
    this->datapath__DOT__sCnt = (3U & ((IData)(this->controlH) 
				       >> 7U));
    // ALWAYS at dma/dma_top.sv:222
    this->datapath__DOT__dCnt = (3U & ((IData)(this->controlH) 
				       >> 5U));
    if ((3U == (3U & ((IData)(this->controlH) >> 0xcU)))) {
	if (this->sound) {
	    this->datapath__DOT__dCnt = 2U;
	}
    }
    this->new_transfer = (((this->datapath__DOT__old_SAD_reg 
			    != (((IData)(this->srcAddrH) 
				 << 0x10U) | (IData)(this->srcAddrL))) 
			   | (this->datapath__DOT__old_DAD_reg 
			      != (((IData)(this->destAddrH) 
				   << 0x10U) | (IData)(this->destAddrL)))) 
			  | (this->datapath__DOT__old_CTL_reg 
			     != (((IData)(this->controlH) 
				  << 0x10U) | (IData)(this->controlL))));
    this->datapath__DOT__xferWord = (1U & ((IData)(this->controlH) 
					   >> 0xaU));
    // ALWAYS at dma/dma_top.sv:27
    this->write = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->write = 1U;
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->others_cant_preempt = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->others_cant_preempt = 1U;
			}
		    }
		}
	    }
	}
    }
    this->starter__DOT__sound_req = this->sound_req;
    this->starter__DOT__cpu_preemptable = this->cpu_preemptable;
    // ALWAYS at dma/dma_top.sv:303
    this->starter__DOT__hold_sound = 0U;
    if ((0x2000U & (IData)(this->controlH))) {
	if ((0x1000U & (IData)(this->controlH))) {
	    if (this->sound) {
		if (this->starter__DOT__sound_req_delay) {
		    if ((1U & (~ (IData)(this->cpu_preemptable)))) {
			this->starter__DOT__hold_sound = 1U;
		    }
		} else {
		    this->starter__DOT__hold_sound = 0U;
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:303
    this->starter__DOT__passed_go = this->starter__DOT__display_sync_startable;
    if ((0x2000U & (IData)(this->controlH))) {
	if ((0x1000U & (IData)(this->controlH))) {
	    if ((1U & (~ (IData)(this->sound)))) {
		if ((1U & (~ (((2U == (0xffU & (IData)(this->vcount))) 
			       & (IData)(this->starter__DOT__display_sync_startable)) 
			      & (IData)(this->cpu_preemptable))))) {
		    if (((0xa2U == (0xffU & (IData)(this->vcount))) 
			 & (IData)(this->cpu_preemptable))) {
			this->starter__DOT__passed_go 
			    = (1U & ((IData)(this->controlH) 
				     >> 0xfU));
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:303
    this->dma_stop = 0U;
    if ((0x2000U & (IData)(this->controlH))) {
	if ((0x1000U & (IData)(this->controlH))) {
	    if ((1U & (~ (IData)(this->sound)))) {
		if ((1U & (~ (((2U == (0xffU & (IData)(this->vcount))) 
			       & (IData)(this->starter__DOT__display_sync_startable)) 
			      & (IData)(this->cpu_preemptable))))) {
		    if (((0xa2U == (0xffU & (IData)(this->vcount))) 
			 & (IData)(this->cpu_preemptable))) {
			this->dma_stop = 1U;
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:303
    this->start = ((0x2000U & (IData)(this->controlH))
		    ? ((0x1000U & (IData)(this->controlH))
		        ? ((IData)(this->sound) ? ((IData)(this->starter__DOT__sound_req_delay) 
						   & (IData)(this->cpu_preemptable))
			    : (((2U == (0xffU & (IData)(this->vcount))) 
				& (IData)(this->starter__DOT__display_sync_startable)) 
			       & (IData)(this->cpu_preemptable)))
		        : ((0xf0U == (0xffU & (IData)(this->hcount))) 
			   & (IData)(this->cpu_preemptable)))
		    : ((0x1000U & (IData)(this->controlH))
		        ? ((0xa0U == (0xffU & (IData)(this->vcount))) 
			   & (IData)(this->cpu_preemptable))
		        : (IData)(this->cpu_preemptable)));
    this->datapath__DOT__sad__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__dad__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__data_reg__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__xferCnt__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__oldsad__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__olddad__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__oldctl__DOT__rst_b = this->datapath__DOT__rst_b;
    this->fsm__DOT__set_wdata = this->set_wdata;
    this->datapath__DOT__set_wdata = this->set_wdata;
    this->datapath__DOT__addrMux__DOT__i1 = this->datapath__DOT__dAddr;
    this->datapath__DOT__addrMux__DOT__i0 = this->datapath__DOT__sAddr;
    this->datapath__DOT__sad__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__dad__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__data_reg__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__xferCnt__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__oldsad__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__olddad__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__oldctl__DOT__clk = this->datapath__DOT__clk;
    this->datapath__DOT__oldsad__DOT__d = this->datapath__DOT____Vcellinp__oldsad__d;
    this->datapath__DOT__srcAddrMux__DOT__i1 = this->datapath__DOT____Vcellinp__srcAddrMux__i1;
    this->datapath__DOT__olddad__DOT__d = this->datapath__DOT____Vcellinp__olddad__d;
    this->xferDone = ((IData)(this->datapath__DOT__xfers) 
		      == (IData)(this->datapath__DOT__words_to_transfer));
    this->datapath__DOT__oldctl__DOT__d = this->datapath__DOT____Vcellinp__oldctl__d;
    this->fsm__DOT__storeRData = this->storeRData;
    this->datapath__DOT__storeRData = this->storeRData;
    this->datapath__DOT__destAddrMux__DOT__i1 = this->datapath__DOT__targetAddr;
    this->fsm__DOT__stepSRC = this->stepSRC;
    this->datapath__DOT__stepSRC = this->stepSRC;
    // ALWAYS at dma/dma_top.sv:204
    this->datapath__DOT__reloadDad = (3U == (IData)(this->datapath__DOT__dCnt));
    this->fsm__DOT__new_transfer = this->new_transfer;
    this->datapath__DOT__new_transfer = this->new_transfer;
    // ALWAYS at dma/dma_top.sv:27
    this->loadSAD = 0U;
    if ((0U == (IData)(this->fsm__DOT__cs))) {
	if ((((IData)(this->controlH) >> 0xfU) & (IData)(this->new_transfer))) {
	    this->loadSAD = 1U;
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->loadDAD = 0U;
    if ((0U == (IData)(this->fsm__DOT__cs))) {
	if ((((IData)(this->controlH) >> 0xfU) & (IData)(this->new_transfer))) {
	    this->loadDAD = 1U;
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->loadCNT = 0U;
    if ((0U == (IData)(this->fsm__DOT__cs))) {
	if ((((IData)(this->controlH) >> 0xfU) & (IData)(this->new_transfer))) {
	    this->loadCNT = 1U;
	}
    }
    // ALWAYS at dma/dma_top.sv:204
    this->datapath__DOT__addrStep = ((IData)(this->datapath__DOT__xferWord)
				      ? 4U : 2U);
    this->datapath__DOT__steppedSAddr = ((2U & (IData)(this->datapath__DOT__sCnt))
					  ? ((1U & (IData)(this->datapath__DOT__sCnt))
					      ? (this->datapath__DOT__sAddr 
						 + this->datapath__DOT__addrStep)
					      : this->datapath__DOT__sAddr)
					  : ((1U & (IData)(this->datapath__DOT__sCnt))
					      ? (this->datapath__DOT__sAddr 
						 - this->datapath__DOT__addrStep)
					      : (this->datapath__DOT__sAddr 
						 + this->datapath__DOT__addrStep)));
    this->datapath__DOT__steppedDAddr = ((2U & (IData)(this->datapath__DOT__dCnt))
					  ? ((1U & (IData)(this->datapath__DOT__dCnt))
					      ? (this->datapath__DOT__dAddr 
						 + this->datapath__DOT__addrStep)
					      : this->datapath__DOT__dAddr)
					  : ((1U & (IData)(this->datapath__DOT__dCnt))
					      ? (this->datapath__DOT__dAddr 
						 - this->datapath__DOT__addrStep)
					      : (this->datapath__DOT__dAddr 
						 + this->datapath__DOT__addrStep)));
    this->datapath__DOT__size_mem_transfer = ((IData)(this->datapath__DOT__xferWord)
					       ? 2U
					       : 1U);
    this->fsm__DOT__write = this->write;
    this->datapath__DOT__write = this->write;
    this->datapath__DOT__desiredAddr = ((IData)(this->write)
					 ? this->datapath__DOT__dAddr
					 : this->datapath__DOT__sAddr);
    this->fsm__DOT__others_cant_preempt = this->others_cant_preempt;
    this->starter__DOT__dma_stop = this->dma_stop;
    this->starter__DOT__start = this->start;
    this->fsm__DOT__start = this->start;
    this->fsm__DOT__xferDone = this->xferDone;
    this->datapath__DOT__xferDone = this->xferDone;
    // ALWAYS at dma/dma_top.sv:27
    this->reload_xfers = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if (((IData)(this->xferDone) 
				     & ((IData)(this->controlH) 
					>> 9U))) {
				    this->reload_xfers = 1U;
				} else {
				    if (this->xferDone) {
					this->reload_xfers = 1U;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->stepDEST = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if ((1U & (~ ((IData)(this->xferDone) 
					      & ((IData)(this->controlH) 
						 >> 9U))))) {
				    if ((1U & (~ (IData)(this->xferDone)))) {
					this->stepDEST = 1U;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->fsm_disable = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if ((1U & (~ ((IData)(this->xferDone) 
					      & ((IData)(this->controlH) 
						 >> 9U))))) {
				    if (this->xferDone) {
					this->fsm_disable = 1U;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->irq = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if (((IData)(this->xferDone) 
				     & ((IData)(this->controlH) 
					>> 9U))) {
				    this->irq = (1U 
						 & ((IData)(this->controlH) 
						    >> 0xeU));
				} else {
				    if (this->xferDone) {
					this->irq = 
					    (1U & ((IData)(this->controlH) 
						   >> 0xeU));
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    this->datapath__DOT__data_reg__DOT__enable = this->datapath__DOT__storeRData;
    this->datapath__DOT__xferCnt__DOT__enable = this->datapath__DOT__stepSRC;
    this->fsm__DOT__loadSAD = this->loadSAD;
    this->datapath__DOT__loadSAD = this->loadSAD;
    this->datapath__DOT__sadEnable = ((IData)(this->loadSAD) 
				      | (IData)(this->stepSRC));
    this->fsm__DOT__loadDAD = this->loadDAD;
    this->datapath__DOT__loadDAD = this->loadDAD;
    this->fsm__DOT__loadCNT = this->loadCNT;
    this->datapath__DOT__loadCNT = this->loadCNT;
    this->datapath__DOT____Vcellinp__destAddrMux__s 
	= ((IData)(this->loadDAD) | ((IData)(this->loadCNT) 
				     & (IData)(this->datapath__DOT__reloadDad)));
    this->datapath__DOT__srcAddrMux__DOT__i0 = this->datapath__DOT__steppedSAddr;
    this->datapath__DOT__nextSAddr = ((IData)(this->loadSAD)
				       ? this->datapath__DOT____Vcellinp__srcAddrMux__i1
				       : this->datapath__DOT__steppedSAddr);
    this->datapath__DOT__destAddrMux__DOT__i0 = this->datapath__DOT__steppedDAddr;
    this->datapath__DOT__addrMux__DOT__s = this->datapath__DOT__write;
    this->datapath__DOT__addrMux__DOT__y = this->datapath__DOT__desiredAddr;
    // ALWAYS at dma/dma_top.sv:245
    this->datapath__DOT__wdata_size = this->datapath__DOT__data;
    if (((1U == (IData)(this->datapath__DOT__size_mem_transfer)) 
	 & (this->datapath__DOT__desiredAddr >> 1U))) {
	this->datapath__DOT__wdata_size = ((0xffffU 
					    & this->datapath__DOT__wdata_size) 
					   | (0xffff0000U 
					      & (this->datapath__DOT__data 
						 << 0x10U)));
    }
    this->fsm__DOT__reload_xfers = this->reload_xfers;
    // ALWAYS at dma/counter.sv:15
    this->datapath__DOT__xferCnt__DOT__ns = (0x3fffU 
					     & ((IData)(this->reload_xfers)
						 ? 0U
						 : 
						((IData)(this->stepSRC)
						  ? 
						 ((IData)(1U) 
						  + (IData)(this->datapath__DOT__xfers))
						  : (IData)(this->datapath__DOT__xfers))));
    this->datapath__DOT__reload_xfers = this->reload_xfers;
    this->fsm__DOT__stepDEST = this->stepDEST;
    this->datapath__DOT__stepDEST = this->stepDEST;
    this->datapath__DOT__dadEnable = (((IData)(this->loadDAD) 
				       | (IData)(this->stepDEST)) 
				      | ((IData)(this->loadCNT) 
					 & (IData)(this->datapath__DOT__reloadDad)));
    this->fsm__DOT__disable_dma = this->fsm_disable;
    this->disable_dma = ((IData)(this->fsm_disable) 
			 | (IData)(this->dma_stop));
    this->fsm__DOT__irq = this->irq;
    this->datapath__DOT__srcAddrMux__DOT__s = this->datapath__DOT__loadSAD;
    this->datapath__DOT__sad__DOT__enable = this->datapath__DOT__sadEnable;
    this->datapath__DOT__destAddrMux__DOT__s = this->datapath__DOT____Vcellinp__destAddrMux__s;
    this->datapath__DOT__nextDAddr = ((IData)(this->datapath__DOT____Vcellinp__destAddrMux__s)
				       ? this->datapath__DOT__targetAddr
				       : this->datapath__DOT__steppedDAddr);
    this->datapath__DOT__srcAddrMux__DOT__y = this->datapath__DOT__nextSAddr;
    this->datapath__DOT__sad__DOT__d = this->datapath__DOT__nextSAddr;
    this->datapath__DOT__xferCnt__DOT__clear = this->datapath__DOT__reload_xfers;
    this->datapath__DOT__dad__DOT__enable = this->datapath__DOT__dadEnable;
    this->datapath__DOT__destAddrMux__DOT__y = this->datapath__DOT__nextDAddr;
    this->datapath__DOT__dad__DOT__d = this->datapath__DOT__nextDAddr;
}

VL_INLINE_OPT void Vgba_top_dma_unit::_combo__TOP__gba_top__DOT__dma__DOT__dma1__18(Vgba_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vgba_top_dma_unit::_combo__TOP__gba_top__DOT__dma__DOT__dma1__18\n"); );
    Vgba_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    this->starter__DOT__rst_b = this->rst_b;
    this->fsm__DOT__rst_b = this->rst_b;
    this->datapath__DOT__rst_b = this->rst_b;
    this->starter__DOT__sound = this->sound;
    this->datapath__DOT__srcGamePak = this->srcGamePak;
    this->datapath__DOT__destGamePak = this->destGamePak;
    this->datapath__DOT__sound = this->sound;
    this->datapath__DOT__sad__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__dad__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__data_reg__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__xferCnt__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__oldsad__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__olddad__DOT__rst_b = this->datapath__DOT__rst_b;
    this->datapath__DOT__oldctl__DOT__rst_b = this->datapath__DOT__rst_b;
}

VL_INLINE_OPT void Vgba_top_dma_unit::_combo__TOP__gba_top__DOT__dma__DOT__dma1__41(Vgba_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vgba_top_dma_unit::_combo__TOP__gba_top__DOT__dma__DOT__dma1__41\n"); );
    Vgba_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    this->starter__DOT__sound_req = this->sound_req;
}

VL_INLINE_OPT void Vgba_top_dma_unit::_combo__TOP__gba_top__DOT__dma__DOT__dma2__31(Vgba_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vgba_top_dma_unit::_combo__TOP__gba_top__DOT__dma__DOT__dma2__31\n"); );
    Vgba_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    this->fsm__DOT__mem_wait = this->mem_wait;
    this->datapath__DOT__srcAddrL = this->srcAddrL;
    this->datapath__DOT__srcAddrH = this->srcAddrH;
    this->datapath__DOT____Vcellinp__srcAddrMux__i1 
	= (((IData)(this->srcAddrH) << 0x10U) | (IData)(this->srcAddrL));
    this->datapath__DOT__destAddrH = this->destAddrH;
    this->datapath__DOT__destAddrL = this->destAddrL;
    this->datapath__DOT__controlL = this->controlL;
    this->datapath__DOT__words_to_transfer = (0x3fffU 
					      & ((IData)(this->sound)
						  ? 4U
						  : (IData)(this->controlL)));
    this->starter__DOT__hcount = this->hcount;
    this->starter__DOT__vcount = this->vcount;
    this->starter__DOT__controlH = this->controlH;
    this->fsm__DOT__dma_repeat = (1U & ((IData)(this->controlH) 
					>> 9U));
    this->fsm__DOT__enable = (1U & ((IData)(this->controlH) 
				    >> 0xfU));
    this->fsm__DOT__genIRQ = (1U & ((IData)(this->controlH) 
				    >> 0xeU));
    this->datapath__DOT__controlH = this->controlH;
    // ALWAYS at dma/dma_top.sv:222
    this->datapath__DOT__targetAddr = (((IData)(this->destAddrH) 
					<< 0x10U) | (IData)(this->destAddrL));
    if ((3U == (3U & ((IData)(this->controlH) >> 0xcU)))) {
	if ((1U & (~ (IData)(this->sound)))) {
	    this->datapath__DOT__targetAddr = 0x6000000U;
	}
    }
    // ALWAYS at dma/dma_top.sv:222
    this->datapath__DOT__sCnt = (3U & ((IData)(this->controlH) 
				       >> 7U));
    // ALWAYS at dma/dma_top.sv:222
    this->datapath__DOT__dCnt = (3U & ((IData)(this->controlH) 
				       >> 5U));
    if ((3U == (3U & ((IData)(this->controlH) >> 0xcU)))) {
	if (this->sound) {
	    this->datapath__DOT__dCnt = 2U;
	}
    }
    this->datapath__DOT__xferWord = (1U & ((IData)(this->controlH) 
					   >> 0xaU));
    this->starter__DOT__cpu_preemptable = this->cpu_preemptable;
    this->datapath__DOT____Vcellinp__oldctl__d = (((IData)(this->controlH) 
						   << 0x10U) 
						  | (IData)(this->controlL));
    this->datapath__DOT____Vcellinp__olddad__d = (((IData)(this->destAddrH) 
						   << 0x10U) 
						  | (IData)(this->destAddrL));
    this->datapath__DOT____Vcellinp__oldsad__d = (((IData)(this->srcAddrH) 
						   << 0x10U) 
						  | (IData)(this->srcAddrL));
    this->new_transfer = (((this->datapath__DOT__old_SAD_reg 
			    != (((IData)(this->srcAddrH) 
				 << 0x10U) | (IData)(this->srcAddrL))) 
			   | (this->datapath__DOT__old_DAD_reg 
			      != (((IData)(this->destAddrH) 
				   << 0x10U) | (IData)(this->destAddrL)))) 
			  | (this->datapath__DOT__old_CTL_reg 
			     != (((IData)(this->controlH) 
				  << 0x10U) | (IData)(this->controlL))));
    this->datapath__DOT__sAddr = ((0xf8000000U & (((IData)(this->srcGamePak) 
						   << 0x1bU) 
						  & this->datapath__DOT__sAddrRaw)) 
				  | (0x7ffffffU & this->datapath__DOT__sAddrRaw));
    this->datapath__DOT__dAddr = ((0xf8000000U & (((IData)(this->destGamePak) 
						   << 0x1bU) 
						  & this->datapath__DOT__dAddrRaw)) 
				  | (0x7ffffffU & this->datapath__DOT__dAddrRaw));
    // ALWAYS at dma/dma_top.sv:303
    this->starter__DOT__passed_go = this->starter__DOT__display_sync_startable;
    if ((0x2000U & (IData)(this->controlH))) {
	if ((0x1000U & (IData)(this->controlH))) {
	    if ((1U & (~ (IData)(this->sound)))) {
		if ((1U & (~ (((2U == (0xffU & (IData)(this->vcount))) 
			       & (IData)(this->starter__DOT__display_sync_startable)) 
			      & (IData)(this->cpu_preemptable))))) {
		    if (((0xa2U == (0xffU & (IData)(this->vcount))) 
			 & (IData)(this->cpu_preemptable))) {
			this->starter__DOT__passed_go 
			    = (1U & ((IData)(this->controlH) 
				     >> 0xfU));
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:303
    this->dma_stop = 0U;
    if ((0x2000U & (IData)(this->controlH))) {
	if ((0x1000U & (IData)(this->controlH))) {
	    if ((1U & (~ (IData)(this->sound)))) {
		if ((1U & (~ (((2U == (0xffU & (IData)(this->vcount))) 
			       & (IData)(this->starter__DOT__display_sync_startable)) 
			      & (IData)(this->cpu_preemptable))))) {
		    if (((0xa2U == (0xffU & (IData)(this->vcount))) 
			 & (IData)(this->cpu_preemptable))) {
			this->dma_stop = 1U;
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:303
    this->starter__DOT__hold_sound = 0U;
    if ((0x2000U & (IData)(this->controlH))) {
	if ((0x1000U & (IData)(this->controlH))) {
	    if (this->sound) {
		if (this->starter__DOT__sound_req_delay) {
		    if ((1U & (~ (IData)(this->cpu_preemptable)))) {
			this->starter__DOT__hold_sound = 1U;
		    }
		} else {
		    this->starter__DOT__hold_sound = 0U;
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:303
    this->start = ((0x2000U & (IData)(this->controlH))
		    ? ((0x1000U & (IData)(this->controlH))
		        ? ((IData)(this->sound) ? ((IData)(this->starter__DOT__sound_req_delay) 
						   & (IData)(this->cpu_preemptable))
			    : (((2U == (0xffU & (IData)(this->vcount))) 
				& (IData)(this->starter__DOT__display_sync_startable)) 
			       & (IData)(this->cpu_preemptable)))
		        : ((0xf0U == (0xffU & (IData)(this->hcount))) 
			   & (IData)(this->cpu_preemptable)))
		    : ((0x1000U & (IData)(this->controlH))
		        ? ((0xa0U == (0xffU & (IData)(this->vcount))) 
			   & (IData)(this->cpu_preemptable))
		        : (IData)(this->cpu_preemptable)));
    // ALWAYS at dma/dma_top.sv:27
    this->storeRData = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->storeRData = 1U;
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->stepSRC = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->stepSRC = 1U;
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->write = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->write = 1U;
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->others_cant_preempt = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->others_cant_preempt = 1U;
			}
		    }
		}
	    }
	}
    }
    this->datapath__DOT__srcAddrMux__DOT__i1 = this->datapath__DOT____Vcellinp__srcAddrMux__i1;
    this->xferDone = ((IData)(this->datapath__DOT__xfers) 
		      == (IData)(this->datapath__DOT__words_to_transfer));
    this->datapath__DOT__destAddrMux__DOT__i1 = this->datapath__DOT__targetAddr;
    // ALWAYS at dma/dma_top.sv:204
    this->datapath__DOT__reloadDad = (3U == (IData)(this->datapath__DOT__dCnt));
    this->datapath__DOT__size_mem_transfer = ((IData)(this->datapath__DOT__xferWord)
					       ? 2U
					       : 1U);
    this->datapath__DOT__oldctl__DOT__d = this->datapath__DOT____Vcellinp__oldctl__d;
    this->datapath__DOT__olddad__DOT__d = this->datapath__DOT____Vcellinp__olddad__d;
    this->datapath__DOT__oldsad__DOT__d = this->datapath__DOT____Vcellinp__oldsad__d;
    this->fsm__DOT__new_transfer = this->new_transfer;
    this->datapath__DOT__new_transfer = this->new_transfer;
    // ALWAYS at dma/dma_top.sv:27
    this->loadSAD = 0U;
    if ((0U == (IData)(this->fsm__DOT__cs))) {
	if ((((IData)(this->controlH) >> 0xfU) & (IData)(this->new_transfer))) {
	    this->loadSAD = 1U;
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->loadDAD = 0U;
    if ((0U == (IData)(this->fsm__DOT__cs))) {
	if ((((IData)(this->controlH) >> 0xfU) & (IData)(this->new_transfer))) {
	    this->loadDAD = 1U;
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->loadCNT = 0U;
    if ((0U == (IData)(this->fsm__DOT__cs))) {
	if ((((IData)(this->controlH) >> 0xfU) & (IData)(this->new_transfer))) {
	    this->loadCNT = 1U;
	}
    }
    this->datapath__DOT__addrMux__DOT__i0 = this->datapath__DOT__sAddr;
    this->datapath__DOT__addrMux__DOT__i1 = this->datapath__DOT__dAddr;
    // ALWAYS at dma/dma_top.sv:204
    this->datapath__DOT__addrStep = ((IData)(this->datapath__DOT__xferWord)
				      ? 4U : 2U);
    this->datapath__DOT__steppedSAddr = ((2U & (IData)(this->datapath__DOT__sCnt))
					  ? ((1U & (IData)(this->datapath__DOT__sCnt))
					      ? (this->datapath__DOT__sAddr 
						 + this->datapath__DOT__addrStep)
					      : this->datapath__DOT__sAddr)
					  : ((1U & (IData)(this->datapath__DOT__sCnt))
					      ? (this->datapath__DOT__sAddr 
						 - this->datapath__DOT__addrStep)
					      : (this->datapath__DOT__sAddr 
						 + this->datapath__DOT__addrStep)));
    this->datapath__DOT__steppedDAddr = ((2U & (IData)(this->datapath__DOT__dCnt))
					  ? ((1U & (IData)(this->datapath__DOT__dCnt))
					      ? (this->datapath__DOT__dAddr 
						 + this->datapath__DOT__addrStep)
					      : this->datapath__DOT__dAddr)
					  : ((1U & (IData)(this->datapath__DOT__dCnt))
					      ? (this->datapath__DOT__dAddr 
						 - this->datapath__DOT__addrStep)
					      : (this->datapath__DOT__dAddr 
						 + this->datapath__DOT__addrStep)));
    this->starter__DOT__dma_stop = this->dma_stop;
    this->starter__DOT__start = this->start;
    this->fsm__DOT__start = this->start;
    this->fsm__DOT__storeRData = this->storeRData;
    this->datapath__DOT__storeRData = this->storeRData;
    this->fsm__DOT__stepSRC = this->stepSRC;
    this->datapath__DOT__stepSRC = this->stepSRC;
    this->fsm__DOT__write = this->write;
    this->datapath__DOT__write = this->write;
    this->datapath__DOT__desiredAddr = ((IData)(this->write)
					 ? this->datapath__DOT__dAddr
					 : this->datapath__DOT__sAddr);
    this->fsm__DOT__others_cant_preempt = this->others_cant_preempt;
    this->fsm__DOT__xferDone = this->xferDone;
    this->datapath__DOT__xferDone = this->xferDone;
    // ALWAYS at dma/dma_top.sv:27
    this->reload_xfers = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if (((IData)(this->xferDone) 
				     & ((IData)(this->controlH) 
					>> 9U))) {
				    this->reload_xfers = 1U;
				} else {
				    if (this->xferDone) {
					this->reload_xfers = 1U;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->stepDEST = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if ((1U & (~ ((IData)(this->xferDone) 
					      & ((IData)(this->controlH) 
						 >> 9U))))) {
				    if ((1U & (~ (IData)(this->xferDone)))) {
					this->stepDEST = 1U;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->fsm_disable = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if ((1U & (~ ((IData)(this->xferDone) 
					      & ((IData)(this->controlH) 
						 >> 9U))))) {
				    if (this->xferDone) {
					this->fsm_disable = 1U;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->irq = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if (((IData)(this->xferDone) 
				     & ((IData)(this->controlH) 
					>> 9U))) {
				    this->irq = (1U 
						 & ((IData)(this->controlH) 
						    >> 0xeU));
				} else {
				    if (this->xferDone) {
					this->irq = 
					    (1U & ((IData)(this->controlH) 
						   >> 0xeU));
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    this->fsm__DOT__loadSAD = this->loadSAD;
    this->datapath__DOT__loadSAD = this->loadSAD;
    this->datapath__DOT__sadEnable = ((IData)(this->loadSAD) 
				      | (IData)(this->stepSRC));
    this->fsm__DOT__loadDAD = this->loadDAD;
    this->datapath__DOT__loadDAD = this->loadDAD;
    this->fsm__DOT__loadCNT = this->loadCNT;
    this->datapath__DOT__loadCNT = this->loadCNT;
    this->datapath__DOT____Vcellinp__destAddrMux__s 
	= ((IData)(this->loadDAD) | ((IData)(this->loadCNT) 
				     & (IData)(this->datapath__DOT__reloadDad)));
    this->datapath__DOT__srcAddrMux__DOT__i0 = this->datapath__DOT__steppedSAddr;
    this->datapath__DOT__nextSAddr = ((IData)(this->loadSAD)
				       ? this->datapath__DOT____Vcellinp__srcAddrMux__i1
				       : this->datapath__DOT__steppedSAddr);
    this->datapath__DOT__destAddrMux__DOT__i0 = this->datapath__DOT__steppedDAddr;
    this->datapath__DOT__data_reg__DOT__enable = this->datapath__DOT__storeRData;
    this->datapath__DOT__xferCnt__DOT__enable = this->datapath__DOT__stepSRC;
    this->datapath__DOT__addrMux__DOT__s = this->datapath__DOT__write;
    this->datapath__DOT__addrMux__DOT__y = this->datapath__DOT__desiredAddr;
    // ALWAYS at dma/dma_top.sv:245
    this->datapath__DOT__wdata_size = this->datapath__DOT__data;
    if (((1U == (IData)(this->datapath__DOT__size_mem_transfer)) 
	 & (this->datapath__DOT__desiredAddr >> 1U))) {
	this->datapath__DOT__wdata_size = ((0xffffU 
					    & this->datapath__DOT__wdata_size) 
					   | (0xffff0000U 
					      & (this->datapath__DOT__data 
						 << 0x10U)));
    }
    this->fsm__DOT__reload_xfers = this->reload_xfers;
    // ALWAYS at dma/counter.sv:15
    this->datapath__DOT__xferCnt__DOT__ns = (0x3fffU 
					     & ((IData)(this->reload_xfers)
						 ? 0U
						 : 
						((IData)(this->stepSRC)
						  ? 
						 ((IData)(1U) 
						  + (IData)(this->datapath__DOT__xfers))
						  : (IData)(this->datapath__DOT__xfers))));
    this->datapath__DOT__reload_xfers = this->reload_xfers;
    this->fsm__DOT__stepDEST = this->stepDEST;
    this->datapath__DOT__stepDEST = this->stepDEST;
    this->datapath__DOT__dadEnable = (((IData)(this->loadDAD) 
				       | (IData)(this->stepDEST)) 
				      | ((IData)(this->loadCNT) 
					 & (IData)(this->datapath__DOT__reloadDad)));
    this->fsm__DOT__disable_dma = this->fsm_disable;
    this->disable_dma = ((IData)(this->fsm_disable) 
			 | (IData)(this->dma_stop));
    this->fsm__DOT__irq = this->irq;
    this->datapath__DOT__srcAddrMux__DOT__s = this->datapath__DOT__loadSAD;
    this->datapath__DOT__sad__DOT__enable = this->datapath__DOT__sadEnable;
    this->datapath__DOT__destAddrMux__DOT__s = this->datapath__DOT____Vcellinp__destAddrMux__s;
    this->datapath__DOT__nextDAddr = ((IData)(this->datapath__DOT____Vcellinp__destAddrMux__s)
				       ? this->datapath__DOT__targetAddr
				       : this->datapath__DOT__steppedDAddr);
    this->datapath__DOT__srcAddrMux__DOT__y = this->datapath__DOT__nextSAddr;
    this->datapath__DOT__sad__DOT__d = this->datapath__DOT__nextSAddr;
    this->datapath__DOT__xferCnt__DOT__clear = this->datapath__DOT__reload_xfers;
    this->datapath__DOT__dad__DOT__enable = this->datapath__DOT__dadEnable;
    this->datapath__DOT__destAddrMux__DOT__y = this->datapath__DOT__nextDAddr;
    this->datapath__DOT__dad__DOT__d = this->datapath__DOT__nextDAddr;
}

VL_INLINE_OPT void Vgba_top_dma_unit::_combo__TOP__gba_top__DOT__dma__DOT__dma3__32(Vgba_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vgba_top_dma_unit::_combo__TOP__gba_top__DOT__dma__DOT__dma3__32\n"); );
    Vgba_top* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    this->fsm__DOT__mem_wait = this->mem_wait;
    this->datapath__DOT__srcAddrH = this->srcAddrH;
    this->datapath__DOT__srcAddrL = this->srcAddrL;
    this->datapath__DOT____Vcellinp__srcAddrMux__i1 
	= (((IData)(this->srcAddrH) << 0x10U) | (IData)(this->srcAddrL));
    this->datapath__DOT__destAddrL = this->destAddrL;
    this->datapath__DOT__destAddrH = this->destAddrH;
    this->datapath__DOT__controlL = this->controlL;
    this->datapath__DOT__words_to_transfer = (0x3fffU 
					      & ((IData)(this->sound)
						  ? 4U
						  : (IData)(this->controlL)));
    this->starter__DOT__hcount = this->hcount;
    this->starter__DOT__vcount = this->vcount;
    this->starter__DOT__controlH = this->controlH;
    this->fsm__DOT__dma_repeat = (1U & ((IData)(this->controlH) 
					>> 9U));
    this->fsm__DOT__enable = (1U & ((IData)(this->controlH) 
				    >> 0xfU));
    this->fsm__DOT__genIRQ = (1U & ((IData)(this->controlH) 
				    >> 0xeU));
    this->datapath__DOT__controlH = this->controlH;
    // ALWAYS at dma/dma_top.sv:222
    this->datapath__DOT__targetAddr = (((IData)(this->destAddrH) 
					<< 0x10U) | (IData)(this->destAddrL));
    if ((3U == (3U & ((IData)(this->controlH) >> 0xcU)))) {
	if ((1U & (~ (IData)(this->sound)))) {
	    this->datapath__DOT__targetAddr = 0x6000000U;
	}
    }
    // ALWAYS at dma/dma_top.sv:222
    this->datapath__DOT__sCnt = (3U & ((IData)(this->controlH) 
				       >> 7U));
    // ALWAYS at dma/dma_top.sv:222
    this->datapath__DOT__dCnt = (3U & ((IData)(this->controlH) 
				       >> 5U));
    if ((3U == (3U & ((IData)(this->controlH) >> 0xcU)))) {
	if (this->sound) {
	    this->datapath__DOT__dCnt = 2U;
	}
    }
    this->datapath__DOT__xferWord = (1U & ((IData)(this->controlH) 
					   >> 0xaU));
    this->starter__DOT__cpu_preemptable = this->cpu_preemptable;
    this->datapath__DOT____Vcellinp__oldctl__d = (((IData)(this->controlH) 
						   << 0x10U) 
						  | (IData)(this->controlL));
    this->datapath__DOT____Vcellinp__olddad__d = (((IData)(this->destAddrH) 
						   << 0x10U) 
						  | (IData)(this->destAddrL));
    this->datapath__DOT____Vcellinp__oldsad__d = (((IData)(this->srcAddrH) 
						   << 0x10U) 
						  | (IData)(this->srcAddrL));
    this->new_transfer = (((this->datapath__DOT__old_SAD_reg 
			    != (((IData)(this->srcAddrH) 
				 << 0x10U) | (IData)(this->srcAddrL))) 
			   | (this->datapath__DOT__old_DAD_reg 
			      != (((IData)(this->destAddrH) 
				   << 0x10U) | (IData)(this->destAddrL)))) 
			  | (this->datapath__DOT__old_CTL_reg 
			     != (((IData)(this->controlH) 
				  << 0x10U) | (IData)(this->controlL))));
    this->datapath__DOT__sAddr = ((0xf8000000U & (((IData)(this->srcGamePak) 
						   << 0x1bU) 
						  & this->datapath__DOT__sAddrRaw)) 
				  | (0x7ffffffU & this->datapath__DOT__sAddrRaw));
    this->datapath__DOT__dAddr = ((0xf8000000U & (((IData)(this->destGamePak) 
						   << 0x1bU) 
						  & this->datapath__DOT__dAddrRaw)) 
				  | (0x7ffffffU & this->datapath__DOT__dAddrRaw));
    // ALWAYS at dma/dma_top.sv:303
    this->starter__DOT__passed_go = this->starter__DOT__display_sync_startable;
    if ((0x2000U & (IData)(this->controlH))) {
	if ((0x1000U & (IData)(this->controlH))) {
	    if ((1U & (~ (IData)(this->sound)))) {
		if ((1U & (~ (((2U == (0xffU & (IData)(this->vcount))) 
			       & (IData)(this->starter__DOT__display_sync_startable)) 
			      & (IData)(this->cpu_preemptable))))) {
		    if (((0xa2U == (0xffU & (IData)(this->vcount))) 
			 & (IData)(this->cpu_preemptable))) {
			this->starter__DOT__passed_go 
			    = (1U & ((IData)(this->controlH) 
				     >> 0xfU));
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:303
    this->dma_stop = 0U;
    if ((0x2000U & (IData)(this->controlH))) {
	if ((0x1000U & (IData)(this->controlH))) {
	    if ((1U & (~ (IData)(this->sound)))) {
		if ((1U & (~ (((2U == (0xffU & (IData)(this->vcount))) 
			       & (IData)(this->starter__DOT__display_sync_startable)) 
			      & (IData)(this->cpu_preemptable))))) {
		    if (((0xa2U == (0xffU & (IData)(this->vcount))) 
			 & (IData)(this->cpu_preemptable))) {
			this->dma_stop = 1U;
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:303
    this->starter__DOT__hold_sound = 0U;
    if ((0x2000U & (IData)(this->controlH))) {
	if ((0x1000U & (IData)(this->controlH))) {
	    if (this->sound) {
		if (this->starter__DOT__sound_req_delay) {
		    if ((1U & (~ (IData)(this->cpu_preemptable)))) {
			this->starter__DOT__hold_sound = 1U;
		    }
		} else {
		    this->starter__DOT__hold_sound = 0U;
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:303
    this->start = ((0x2000U & (IData)(this->controlH))
		    ? ((0x1000U & (IData)(this->controlH))
		        ? ((IData)(this->sound) ? ((IData)(this->starter__DOT__sound_req_delay) 
						   & (IData)(this->cpu_preemptable))
			    : (((2U == (0xffU & (IData)(this->vcount))) 
				& (IData)(this->starter__DOT__display_sync_startable)) 
			       & (IData)(this->cpu_preemptable)))
		        : ((0xf0U == (0xffU & (IData)(this->hcount))) 
			   & (IData)(this->cpu_preemptable)))
		    : ((0x1000U & (IData)(this->controlH))
		        ? ((0xa0U == (0xffU & (IData)(this->vcount))) 
			   & (IData)(this->cpu_preemptable))
		        : (IData)(this->cpu_preemptable)));
    // ALWAYS at dma/dma_top.sv:27
    this->storeRData = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->storeRData = 1U;
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->stepSRC = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->stepSRC = 1U;
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->write = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->write = 1U;
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->others_cant_preempt = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U == (IData)(this->fsm__DOT__cs))) {
		    if ((1U & (~ (IData)(this->mem_wait)))) {
			if ((0x8000U & (IData)(this->controlH))) {
			    this->others_cant_preempt = 1U;
			}
		    }
		}
	    }
	}
    }
    this->datapath__DOT__srcAddrMux__DOT__i1 = this->datapath__DOT____Vcellinp__srcAddrMux__i1;
    this->xferDone = ((IData)(this->datapath__DOT__xfers) 
		      == (IData)(this->datapath__DOT__words_to_transfer));
    this->datapath__DOT__destAddrMux__DOT__i1 = this->datapath__DOT__targetAddr;
    // ALWAYS at dma/dma_top.sv:204
    this->datapath__DOT__reloadDad = (3U == (IData)(this->datapath__DOT__dCnt));
    this->datapath__DOT__size_mem_transfer = ((IData)(this->datapath__DOT__xferWord)
					       ? 2U
					       : 1U);
    this->datapath__DOT__oldctl__DOT__d = this->datapath__DOT____Vcellinp__oldctl__d;
    this->datapath__DOT__olddad__DOT__d = this->datapath__DOT____Vcellinp__olddad__d;
    this->datapath__DOT__oldsad__DOT__d = this->datapath__DOT____Vcellinp__oldsad__d;
    this->fsm__DOT__new_transfer = this->new_transfer;
    this->datapath__DOT__new_transfer = this->new_transfer;
    // ALWAYS at dma/dma_top.sv:27
    this->loadSAD = 0U;
    if ((0U == (IData)(this->fsm__DOT__cs))) {
	if ((((IData)(this->controlH) >> 0xfU) & (IData)(this->new_transfer))) {
	    this->loadSAD = 1U;
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->loadDAD = 0U;
    if ((0U == (IData)(this->fsm__DOT__cs))) {
	if ((((IData)(this->controlH) >> 0xfU) & (IData)(this->new_transfer))) {
	    this->loadDAD = 1U;
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->loadCNT = 0U;
    if ((0U == (IData)(this->fsm__DOT__cs))) {
	if ((((IData)(this->controlH) >> 0xfU) & (IData)(this->new_transfer))) {
	    this->loadCNT = 1U;
	}
    }
    this->datapath__DOT__addrMux__DOT__i0 = this->datapath__DOT__sAddr;
    this->datapath__DOT__addrMux__DOT__i1 = this->datapath__DOT__dAddr;
    // ALWAYS at dma/dma_top.sv:204
    this->datapath__DOT__addrStep = ((IData)(this->datapath__DOT__xferWord)
				      ? 4U : 2U);
    this->datapath__DOT__steppedSAddr = ((2U & (IData)(this->datapath__DOT__sCnt))
					  ? ((1U & (IData)(this->datapath__DOT__sCnt))
					      ? (this->datapath__DOT__sAddr 
						 + this->datapath__DOT__addrStep)
					      : this->datapath__DOT__sAddr)
					  : ((1U & (IData)(this->datapath__DOT__sCnt))
					      ? (this->datapath__DOT__sAddr 
						 - this->datapath__DOT__addrStep)
					      : (this->datapath__DOT__sAddr 
						 + this->datapath__DOT__addrStep)));
    this->datapath__DOT__steppedDAddr = ((2U & (IData)(this->datapath__DOT__dCnt))
					  ? ((1U & (IData)(this->datapath__DOT__dCnt))
					      ? (this->datapath__DOT__dAddr 
						 + this->datapath__DOT__addrStep)
					      : this->datapath__DOT__dAddr)
					  : ((1U & (IData)(this->datapath__DOT__dCnt))
					      ? (this->datapath__DOT__dAddr 
						 - this->datapath__DOT__addrStep)
					      : (this->datapath__DOT__dAddr 
						 + this->datapath__DOT__addrStep)));
    this->starter__DOT__dma_stop = this->dma_stop;
    this->starter__DOT__start = this->start;
    this->fsm__DOT__start = this->start;
    this->fsm__DOT__storeRData = this->storeRData;
    this->datapath__DOT__storeRData = this->storeRData;
    this->fsm__DOT__stepSRC = this->stepSRC;
    this->datapath__DOT__stepSRC = this->stepSRC;
    this->fsm__DOT__write = this->write;
    this->datapath__DOT__write = this->write;
    this->datapath__DOT__desiredAddr = ((IData)(this->write)
					 ? this->datapath__DOT__dAddr
					 : this->datapath__DOT__sAddr);
    this->fsm__DOT__others_cant_preempt = this->others_cant_preempt;
    this->fsm__DOT__xferDone = this->xferDone;
    this->datapath__DOT__xferDone = this->xferDone;
    // ALWAYS at dma/dma_top.sv:27
    this->reload_xfers = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if (((IData)(this->xferDone) 
				     & ((IData)(this->controlH) 
					>> 9U))) {
				    this->reload_xfers = 1U;
				} else {
				    if (this->xferDone) {
					this->reload_xfers = 1U;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->stepDEST = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if ((1U & (~ ((IData)(this->xferDone) 
					      & ((IData)(this->controlH) 
						 >> 9U))))) {
				    if ((1U & (~ (IData)(this->xferDone)))) {
					this->stepDEST = 1U;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->fsm_disable = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if ((1U & (~ ((IData)(this->xferDone) 
					      & ((IData)(this->controlH) 
						 >> 9U))))) {
				    if (this->xferDone) {
					this->fsm_disable = 1U;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    // ALWAYS at dma/dma_top.sv:27
    this->irq = 0U;
    if ((0U != (IData)(this->fsm__DOT__cs))) {
	if ((1U != (IData)(this->fsm__DOT__cs))) {
	    if ((2U != (IData)(this->fsm__DOT__cs))) {
		if ((3U != (IData)(this->fsm__DOT__cs))) {
		    if ((4U == (IData)(this->fsm__DOT__cs))) {
			if ((1U & (~ (IData)(this->mem_wait)))) {
			    if ((0x8000U & (IData)(this->controlH))) {
				if (((IData)(this->xferDone) 
				     & ((IData)(this->controlH) 
					>> 9U))) {
				    this->irq = (1U 
						 & ((IData)(this->controlH) 
						    >> 0xeU));
				} else {
				    if (this->xferDone) {
					this->irq = 
					    (1U & ((IData)(this->controlH) 
						   >> 0xeU));
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    this->fsm__DOT__loadSAD = this->loadSAD;
    this->datapath__DOT__loadSAD = this->loadSAD;
    this->datapath__DOT__sadEnable = ((IData)(this->loadSAD) 
				      | (IData)(this->stepSRC));
    this->fsm__DOT__loadDAD = this->loadDAD;
    this->datapath__DOT__loadDAD = this->loadDAD;
    this->fsm__DOT__loadCNT = this->loadCNT;
    this->datapath__DOT__loadCNT = this->loadCNT;
    this->datapath__DOT____Vcellinp__destAddrMux__s 
	= ((IData)(this->loadDAD) | ((IData)(this->loadCNT) 
				     & (IData)(this->datapath__DOT__reloadDad)));
    this->datapath__DOT__srcAddrMux__DOT__i0 = this->datapath__DOT__steppedSAddr;
    this->datapath__DOT__nextSAddr = ((IData)(this->loadSAD)
				       ? this->datapath__DOT____Vcellinp__srcAddrMux__i1
				       : this->datapath__DOT__steppedSAddr);
    this->datapath__DOT__destAddrMux__DOT__i0 = this->datapath__DOT__steppedDAddr;
    this->datapath__DOT__data_reg__DOT__enable = this->datapath__DOT__storeRData;
    this->datapath__DOT__xferCnt__DOT__enable = this->datapath__DOT__stepSRC;
    this->datapath__DOT__addrMux__DOT__s = this->datapath__DOT__write;
    this->datapath__DOT__addrMux__DOT__y = this->datapath__DOT__desiredAddr;
    // ALWAYS at dma/dma_top.sv:245
    this->datapath__DOT__wdata_size = this->datapath__DOT__data;
    if (((1U == (IData)(this->datapath__DOT__size_mem_transfer)) 
	 & (this->datapath__DOT__desiredAddr >> 1U))) {
	this->datapath__DOT__wdata_size = ((0xffffU 
					    & this->datapath__DOT__wdata_size) 
					   | (0xffff0000U 
					      & (this->datapath__DOT__data 
						 << 0x10U)));
    }
    this->fsm__DOT__reload_xfers = this->reload_xfers;
    // ALWAYS at dma/counter.sv:15
    this->datapath__DOT__xferCnt__DOT__ns = (0x3fffU 
					     & ((IData)(this->reload_xfers)
						 ? 0U
						 : 
						((IData)(this->stepSRC)
						  ? 
						 ((IData)(1U) 
						  + (IData)(this->datapath__DOT__xfers))
						  : (IData)(this->datapath__DOT__xfers))));
    this->datapath__DOT__reload_xfers = this->reload_xfers;
    this->fsm__DOT__stepDEST = this->stepDEST;
    this->datapath__DOT__stepDEST = this->stepDEST;
    this->datapath__DOT__dadEnable = (((IData)(this->loadDAD) 
				       | (IData)(this->stepDEST)) 
				      | ((IData)(this->loadCNT) 
					 & (IData)(this->datapath__DOT__reloadDad)));
    this->fsm__DOT__disable_dma = this->fsm_disable;
    this->disable_dma = ((IData)(this->fsm_disable) 
			 | (IData)(this->dma_stop));
    this->fsm__DOT__irq = this->irq;
    this->datapath__DOT__srcAddrMux__DOT__s = this->datapath__DOT__loadSAD;
    this->datapath__DOT__sad__DOT__enable = this->datapath__DOT__sadEnable;
    this->datapath__DOT__destAddrMux__DOT__s = this->datapath__DOT____Vcellinp__destAddrMux__s;
    this->datapath__DOT__nextDAddr = ((IData)(this->datapath__DOT____Vcellinp__destAddrMux__s)
				       ? this->datapath__DOT__targetAddr
				       : this->datapath__DOT__steppedDAddr);
    this->datapath__DOT__srcAddrMux__DOT__y = this->datapath__DOT__nextSAddr;
    this->datapath__DOT__sad__DOT__d = this->datapath__DOT__nextSAddr;
    this->datapath__DOT__xferCnt__DOT__clear = this->datapath__DOT__reload_xfers;
    this->datapath__DOT__dad__DOT__enable = this->datapath__DOT__dadEnable;
    this->datapath__DOT__destAddrMux__DOT__y = this->datapath__DOT__nextDAddr;
    this->datapath__DOT__dad__DOT__d = this->datapath__DOT__nextDAddr;
}

void Vgba_top_dma_unit::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vgba_top_dma_unit::_ctor_var_reset\n"); );
    // Body
    controlL = VL_RAND_RESET_I(16);
    controlH = VL_RAND_RESET_I(16);
    srcAddrL = VL_RAND_RESET_I(16);
    srcAddrH = VL_RAND_RESET_I(16);
    destAddrL = VL_RAND_RESET_I(16);
    destAddrH = VL_RAND_RESET_I(16);
    mem_wait = VL_RAND_RESET_I(1);
    preempted = VL_RAND_RESET_I(1);
    srcGamePak = VL_RAND_RESET_I(1);
    destGamePak = VL_RAND_RESET_I(1);
    allowed_to_begin = VL_RAND_RESET_I(1);
    cpu_preemptable = VL_RAND_RESET_I(1);
    disable_dma = VL_RAND_RESET_I(1);
    active = VL_RAND_RESET_I(1);
    irq = VL_RAND_RESET_I(1);
    others_cant_preempt = VL_RAND_RESET_I(1);
    rdata = VL_RAND_RESET_I(32);
    addr = VL_RAND_RESET_I(32);
    wdata = VL_RAND_RESET_I(32);
    size = VL_RAND_RESET_I(2);
    wen = VL_RAND_RESET_I(1);
    vcount = VL_RAND_RESET_I(16);
    hcount = VL_RAND_RESET_I(16);
    sound = VL_RAND_RESET_I(1);
    sound_req = VL_RAND_RESET_I(1);
    clk = VL_RAND_RESET_I(1);
    rst_b = VL_RAND_RESET_I(1);
    fsm_disable = VL_RAND_RESET_I(1);
    xferDone = VL_RAND_RESET_I(1);
    loadCNT = VL_RAND_RESET_I(1);
    loadSAD = VL_RAND_RESET_I(1);
    loadDAD = VL_RAND_RESET_I(1);
    stepSRC = VL_RAND_RESET_I(1);
    stepDEST = VL_RAND_RESET_I(1);
    storeRData = VL_RAND_RESET_I(1);
    write = VL_RAND_RESET_I(1);
    dma_stop = VL_RAND_RESET_I(1);
    start = VL_RAND_RESET_I(1);
    set_wdata = VL_RAND_RESET_I(1);
    new_transfer = VL_RAND_RESET_I(1);
    reload_xfers = VL_RAND_RESET_I(1);
    addr__out = VL_RAND_RESET_I(32);
    addr__en = VL_RAND_RESET_I(32);
    wdata__out = VL_RAND_RESET_I(32);
    wdata__en = VL_RAND_RESET_I(32);
    size__out = VL_RAND_RESET_I(2);
    size__en = VL_RAND_RESET_I(2);
    wen__out = VL_RAND_RESET_I(1);
    wen__en = VL_RAND_RESET_I(1);
    starter__DOT__controlH = VL_RAND_RESET_I(16);
    starter__DOT__vcount = VL_RAND_RESET_I(16);
    starter__DOT__hcount = VL_RAND_RESET_I(16);
    starter__DOT__sound = VL_RAND_RESET_I(1);
    starter__DOT__sound_req = VL_RAND_RESET_I(1);
    starter__DOT__cpu_preemptable = VL_RAND_RESET_I(1);
    starter__DOT__start = VL_RAND_RESET_I(1);
    starter__DOT__dma_stop = VL_RAND_RESET_I(1);
    starter__DOT__clk = VL_RAND_RESET_I(1);
    starter__DOT__rst_b = VL_RAND_RESET_I(1);
    starter__DOT__display_sync_startable = VL_RAND_RESET_I(1);
    starter__DOT__passed_go = VL_RAND_RESET_I(1);
    starter__DOT__hold_sound = VL_RAND_RESET_I(1);
    starter__DOT__sound_req_delay = VL_RAND_RESET_I(1);
    fsm__DOT__mem_wait = VL_RAND_RESET_I(1);
    fsm__DOT__dma_repeat = VL_RAND_RESET_I(1);
    fsm__DOT__enable = VL_RAND_RESET_I(1);
    fsm__DOT__start = VL_RAND_RESET_I(1);
    fsm__DOT__new_transfer = VL_RAND_RESET_I(1);
    fsm__DOT__preempted = VL_RAND_RESET_I(1);
    fsm__DOT__genIRQ = VL_RAND_RESET_I(1);
    fsm__DOT__allowed_to_begin = VL_RAND_RESET_I(1);
    fsm__DOT__xferDone = VL_RAND_RESET_I(1);
    fsm__DOT__loadCNT = VL_RAND_RESET_I(1);
    fsm__DOT__loadSAD = VL_RAND_RESET_I(1);
    fsm__DOT__loadDAD = VL_RAND_RESET_I(1);
    fsm__DOT__stepSRC = VL_RAND_RESET_I(1);
    fsm__DOT__stepDEST = VL_RAND_RESET_I(1);
    fsm__DOT__storeRData = VL_RAND_RESET_I(1);
    fsm__DOT__active = VL_RAND_RESET_I(1);
    fsm__DOT__write = VL_RAND_RESET_I(1);
    fsm__DOT__disable_dma = VL_RAND_RESET_I(1);
    fsm__DOT__set_wdata = VL_RAND_RESET_I(1);
    fsm__DOT__irq = VL_RAND_RESET_I(1);
    fsm__DOT__others_cant_preempt = VL_RAND_RESET_I(1);
    fsm__DOT__reload_xfers = VL_RAND_RESET_I(1);
    fsm__DOT__clk = VL_RAND_RESET_I(1);
    fsm__DOT__rst_b = VL_RAND_RESET_I(1);
    fsm__DOT__cs = VL_RAND_RESET_I(3);
    fsm__DOT__ns = VL_RAND_RESET_I(3);
    datapath__DOT__loadCNT = VL_RAND_RESET_I(1);
    datapath__DOT__loadSAD = VL_RAND_RESET_I(1);
    datapath__DOT__loadDAD = VL_RAND_RESET_I(1);
    datapath__DOT__stepSRC = VL_RAND_RESET_I(1);
    datapath__DOT__stepDEST = VL_RAND_RESET_I(1);
    datapath__DOT__storeRData = VL_RAND_RESET_I(1);
    datapath__DOT__active = VL_RAND_RESET_I(1);
    datapath__DOT__write = VL_RAND_RESET_I(1);
    datapath__DOT__set_wdata = VL_RAND_RESET_I(1);
    datapath__DOT__srcGamePak = VL_RAND_RESET_I(1);
    datapath__DOT__destGamePak = VL_RAND_RESET_I(1);
    datapath__DOT__xferDone = VL_RAND_RESET_I(1);
    datapath__DOT__new_transfer = VL_RAND_RESET_I(1);
    datapath__DOT__srcAddrL = VL_RAND_RESET_I(16);
    datapath__DOT__srcAddrH = VL_RAND_RESET_I(16);
    datapath__DOT__destAddrL = VL_RAND_RESET_I(16);
    datapath__DOT__destAddrH = VL_RAND_RESET_I(16);
    datapath__DOT__controlL = VL_RAND_RESET_I(16);
    datapath__DOT__controlH = VL_RAND_RESET_I(16);
    datapath__DOT__sound = VL_RAND_RESET_I(1);
    datapath__DOT__reload_xfers = VL_RAND_RESET_I(1);
    datapath__DOT__rdata = VL_RAND_RESET_I(32);
    datapath__DOT__addr = VL_RAND_RESET_I(32);
    datapath__DOT__wdata = VL_RAND_RESET_I(32);
    datapath__DOT__size = VL_RAND_RESET_I(2);
    datapath__DOT__wen = VL_RAND_RESET_I(1);
    datapath__DOT__clk = VL_RAND_RESET_I(1);
    datapath__DOT__rst_b = VL_RAND_RESET_I(1);
    datapath__DOT__old_SAD_reg = VL_RAND_RESET_I(32);
    datapath__DOT__old_DAD_reg = VL_RAND_RESET_I(32);
    datapath__DOT__old_CTL_reg = VL_RAND_RESET_I(32);
    datapath__DOT__sAddr = VL_RAND_RESET_I(32);
    datapath__DOT__dAddr = VL_RAND_RESET_I(32);
    datapath__DOT__steppedSAddr = VL_RAND_RESET_I(32);
    datapath__DOT__steppedDAddr = VL_RAND_RESET_I(32);
    datapath__DOT__nextSAddr = VL_RAND_RESET_I(32);
    datapath__DOT__nextDAddr = VL_RAND_RESET_I(32);
    datapath__DOT__desiredAddr = VL_RAND_RESET_I(32);
    datapath__DOT__sAddrRaw = VL_RAND_RESET_I(32);
    datapath__DOT__dAddrRaw = VL_RAND_RESET_I(32);
    datapath__DOT__data = VL_RAND_RESET_I(32);
    datapath__DOT__xfers = VL_RAND_RESET_I(14);
    datapath__DOT__wordCount = VL_RAND_RESET_I(14);
    datapath__DOT__xferWord = VL_RAND_RESET_I(1);
    datapath__DOT__addrStep = VL_RAND_RESET_I(32);
    datapath__DOT__targetAddr = VL_RAND_RESET_I(32);
    datapath__DOT__sCnt = VL_RAND_RESET_I(2);
    datapath__DOT__dCnt = VL_RAND_RESET_I(2);
    datapath__DOT__reloadDad = VL_RAND_RESET_I(1);
    datapath__DOT__sadEnable = VL_RAND_RESET_I(1);
    datapath__DOT__dadEnable = VL_RAND_RESET_I(1);
    datapath__DOT__size_mem_transfer = VL_RAND_RESET_I(2);
    datapath__DOT__wdata_size = VL_RAND_RESET_I(32);
    datapath__DOT____Vcellinp__srcAddrMux__i1 = VL_RAND_RESET_I(32);
    datapath__DOT____Vcellinp__destAddrMux__s = VL_RAND_RESET_I(1);
    datapath__DOT__words_to_transfer = VL_RAND_RESET_I(14);
    datapath__DOT____Vcellinp__oldsad__d = VL_RAND_RESET_I(32);
    datapath__DOT____Vcellinp__olddad__d = VL_RAND_RESET_I(32);
    datapath__DOT____Vcellinp__oldctl__d = VL_RAND_RESET_I(32);
    datapath__DOT__wdata__out__en1 = VL_RAND_RESET_I(32);
    datapath__DOT__srcAddrMux__DOT__y = VL_RAND_RESET_I(32);
    datapath__DOT__srcAddrMux__DOT__i0 = VL_RAND_RESET_I(32);
    datapath__DOT__srcAddrMux__DOT__i1 = VL_RAND_RESET_I(32);
    datapath__DOT__srcAddrMux__DOT__s = VL_RAND_RESET_I(1);
    datapath__DOT__destAddrMux__DOT__y = VL_RAND_RESET_I(32);
    datapath__DOT__destAddrMux__DOT__i0 = VL_RAND_RESET_I(32);
    datapath__DOT__destAddrMux__DOT__i1 = VL_RAND_RESET_I(32);
    datapath__DOT__destAddrMux__DOT__s = VL_RAND_RESET_I(1);
    datapath__DOT__addrMux__DOT__y = VL_RAND_RESET_I(32);
    datapath__DOT__addrMux__DOT__i0 = VL_RAND_RESET_I(32);
    datapath__DOT__addrMux__DOT__i1 = VL_RAND_RESET_I(32);
    datapath__DOT__addrMux__DOT__s = VL_RAND_RESET_I(1);
    datapath__DOT__sad__DOT__q = VL_RAND_RESET_I(32);
    datapath__DOT__sad__DOT__d = VL_RAND_RESET_I(32);
    datapath__DOT__sad__DOT__clk = VL_RAND_RESET_I(1);
    datapath__DOT__sad__DOT__clear = VL_RAND_RESET_I(1);
    datapath__DOT__sad__DOT__enable = VL_RAND_RESET_I(1);
    datapath__DOT__sad__DOT__rst_b = VL_RAND_RESET_I(1);
    datapath__DOT__dad__DOT__q = VL_RAND_RESET_I(32);
    datapath__DOT__dad__DOT__d = VL_RAND_RESET_I(32);
    datapath__DOT__dad__DOT__clk = VL_RAND_RESET_I(1);
    datapath__DOT__dad__DOT__clear = VL_RAND_RESET_I(1);
    datapath__DOT__dad__DOT__enable = VL_RAND_RESET_I(1);
    datapath__DOT__dad__DOT__rst_b = VL_RAND_RESET_I(1);
    datapath__DOT__data_reg__DOT__q = VL_RAND_RESET_I(32);
    datapath__DOT__data_reg__DOT__d = VL_RAND_RESET_I(32);
    datapath__DOT__data_reg__DOT__clk = VL_RAND_RESET_I(1);
    datapath__DOT__data_reg__DOT__clear = VL_RAND_RESET_I(1);
    datapath__DOT__data_reg__DOT__enable = VL_RAND_RESET_I(1);
    datapath__DOT__data_reg__DOT__rst_b = VL_RAND_RESET_I(1);
    datapath__DOT__xferCnt__DOT__q = VL_RAND_RESET_I(14);
    datapath__DOT__xferCnt__DOT__d = VL_RAND_RESET_I(14);
    datapath__DOT__xferCnt__DOT__clk = VL_RAND_RESET_I(1);
    datapath__DOT__xferCnt__DOT__enable = VL_RAND_RESET_I(1);
    datapath__DOT__xferCnt__DOT__clear = VL_RAND_RESET_I(1);
    datapath__DOT__xferCnt__DOT__load = VL_RAND_RESET_I(1);
    datapath__DOT__xferCnt__DOT__up = VL_RAND_RESET_I(1);
    datapath__DOT__xferCnt__DOT__rst_b = VL_RAND_RESET_I(1);
    datapath__DOT__xferCnt__DOT__ns = VL_RAND_RESET_I(14);
    datapath__DOT__oldsad__DOT__q = VL_RAND_RESET_I(32);
    datapath__DOT__oldsad__DOT__d = VL_RAND_RESET_I(32);
    datapath__DOT__oldsad__DOT__clk = VL_RAND_RESET_I(1);
    datapath__DOT__oldsad__DOT__clear = VL_RAND_RESET_I(1);
    datapath__DOT__oldsad__DOT__enable = VL_RAND_RESET_I(1);
    datapath__DOT__oldsad__DOT__rst_b = VL_RAND_RESET_I(1);
    datapath__DOT__olddad__DOT__q = VL_RAND_RESET_I(32);
    datapath__DOT__olddad__DOT__d = VL_RAND_RESET_I(32);
    datapath__DOT__olddad__DOT__clk = VL_RAND_RESET_I(1);
    datapath__DOT__olddad__DOT__clear = VL_RAND_RESET_I(1);
    datapath__DOT__olddad__DOT__enable = VL_RAND_RESET_I(1);
    datapath__DOT__olddad__DOT__rst_b = VL_RAND_RESET_I(1);
    datapath__DOT__oldctl__DOT__q = VL_RAND_RESET_I(32);
    datapath__DOT__oldctl__DOT__d = VL_RAND_RESET_I(32);
    datapath__DOT__oldctl__DOT__clk = VL_RAND_RESET_I(1);
    datapath__DOT__oldctl__DOT__clear = VL_RAND_RESET_I(1);
    datapath__DOT__oldctl__DOT__enable = VL_RAND_RESET_I(1);
    datapath__DOT__oldctl__DOT__rst_b = VL_RAND_RESET_I(1);
}
