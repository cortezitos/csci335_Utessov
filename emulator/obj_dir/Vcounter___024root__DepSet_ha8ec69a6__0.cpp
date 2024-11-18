// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcounter.h for the primary calling header

#include "Vcounter__pch.h"
#include "Vcounter__Syms.h"
#include "Vcounter___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcounter___024root___dump_triggers__act(Vcounter___024root* vlSelf);
#endif  // VL_DEBUG

void Vcounter___024root___eval_triggers__act(Vcounter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcounter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.set(0U, (((IData)(vlSelf->clk) 
                                      & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__clk__0))) 
                                     | ((IData)(vlSelf->reset) 
                                        & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__reset__0)))));
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
    vlSelf->__Vtrigprevexpr___TOP__reset__0 = vlSelf->reset;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vcounter___024root___dump_triggers__act(vlSelf);
    }
#endif
}

void Vcounter___024unit____Vdpiimwrap_notify_counter_reached_nine_TOP____024unit();

VL_INLINE_OPT void Vcounter___024root___nba_sequent__TOP__0(Vcounter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcounter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*3:0*/ __Vdly__counter__DOT__count;
    __Vdly__counter__DOT__count = 0;
    // Body
    __Vdly__counter__DOT__count = vlSelf->counter__DOT__count;
    if (vlSelf->reset) {
        __Vdly__counter__DOT__count = 0U;
    } else {
        __Vdly__counter__DOT__count = (0xfU & ((IData)(1U) 
                                               + (IData)(vlSelf->counter__DOT__count)));
        if ((9U == (IData)(vlSelf->counter__DOT__count))) {
            Vcounter___024unit____Vdpiimwrap_notify_counter_reached_nine_TOP____024unit();
        }
    }
    vlSelf->counter__DOT__count = __Vdly__counter__DOT__count;
}
