// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcounter.h for the primary calling header

#include "Vcounter__pch.h"
#include "Vcounter__Syms.h"
#include "Vcounter___024unit.h"

void Vcounter___024unit___ctor_var_reset(Vcounter___024unit* vlSelf);

Vcounter___024unit::Vcounter___024unit(Vcounter__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vcounter___024unit___ctor_var_reset(this);
}

void Vcounter___024unit::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vcounter___024unit::~Vcounter___024unit() {
}
