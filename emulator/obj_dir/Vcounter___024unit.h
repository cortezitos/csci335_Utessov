// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vcounter.h for the primary calling header

#ifndef VERILATED_VCOUNTER___024UNIT_H_
#define VERILATED_VCOUNTER___024UNIT_H_  // guard

#include "verilated.h"


class Vcounter__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vcounter___024unit final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vcounter__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vcounter___024unit(Vcounter__Syms* symsp, const char* v__name);
    ~Vcounter___024unit();
    VL_UNCOPYABLE(Vcounter___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
