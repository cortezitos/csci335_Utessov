// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcounter.h for the primary calling header

#include "Vcounter__pch.h"
#include "Vcounter__Syms.h"
#include "Vcounter___024unit.h"

extern "C" void notify_counter_reached_nine();

VL_INLINE_OPT void Vcounter___024unit____Vdpiimwrap_notify_counter_reached_nine_TOP____024unit() {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vcounter___024unit____Vdpiimwrap_notify_counter_reached_nine_TOP____024unit\n"); );
    // Body
    notify_counter_reached_nine();
}
