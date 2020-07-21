#pragma once

#include <string>
#include "binaryninjaapi.h"
extern "C" {
    #include "xedInc/xed-interface.h"
}


// The difference between DF_INTEL and DF_BN_INTEL is
//   DF_INTEL is more verbose (states size more often, and some more subtle things)
//   DF_INTEL uses some different opcodes (jz and jnz vs je and jne)
enum DISASSEMBLY_FLAVOR_ENUM
{
    DF_INTEL,
    DF_BN_INTEL,
    DF_ATT,
    DF_XED
};

struct DISASSEMBLY_OPTIONS
{
    DISASSEMBLY_FLAVOR_ENUM df;

    bool lowerCase;
    std::string separator;

    DISASSEMBLY_OPTIONS(DISASSEMBLY_FLAVOR_ENUM df = DF_BN_INTEL, bool lowerCase = true, std::string separator = ", ")
     : df(df), lowerCase(lowerCase), separator(separator) { };
};

#define IL_FLAG_C 0
#define IL_FLAG_P 2
#define IL_FLAG_A 4
#define IL_FLAG_Z 6
#define IL_FLAG_S 7
#define IL_FLAG_D 10
#define IL_FLAG_O 11
#define IL_FLAG_C0 32
#define IL_FLAG_C1 33
#define IL_FLAG_C2 34
#define IL_FLAG_C3 35

#define IL_FLAGWRITE_ALL     1
#define IL_FLAGWRITE_NOCARRY 2
#define IL_FLAGWRITE_CO      3
#define IL_FLAGWRITE_X87COM  4
#define IL_FLAGWRITE_X87COMI 5
#define IL_FLAGWRITE_X87C1Z  6
#define IL_FLAGWRITE_X87RND  7

#define IL_FLAG_CLASS_INT     0 // Default
#define IL_FLAG_CLASS_X87COM  1
#define IL_FLAG_CLASS_X87COMI 2

#define IL_FLAG_GROUP_E  0
#define IL_FLAG_GROUP_NE 1
#define IL_FLAG_GROUP_LT 2
#define IL_FLAG_GROUP_LE 3
#define IL_FLAG_GROUP_GE 4
#define IL_FLAG_GROUP_GT 5
#define IL_FLAG_GROUP_PE 6
#define IL_FLAG_GROUP_PO 7

#define TRAP_DIV       0
#define TRAP_ICEBP     1
#define TRAP_NMI       2
#define TRAP_BP        3
#define TRAP_OVERFLOW  4
#define TRAP_BOUND     5
#define TRAP_ILL       6
#define TRAP_NOT_AVAIL 7
#define TRAP_DOUBLE    8
#define TRAP_TSS       10
#define TRAP_NO_SEG    11
#define TRAP_STACK     12
#define TRAP_GPF       13
#define TRAP_PAGE      14
#define TRAP_FPU       16
#define TRAP_ALIGN     17
#define TRAP_MCE       18
#define TRAP_SIMD      19

#define REG_STACK_X87   0x999
#define REG_X87_r(n)   (0x1000 + (n))             // The fake "real" (physical) register
#define REG_X87_TOP     0x1008

#define INTRINSIC_F2XM1   0
#define INTRINSIC_FBLD    1
#define INTRINSIC_FBST    2
#define INTRINSIC_FSIN    3
#define INTRINSIC_FCOS    4
#define INTRINSIC_FSINCOS 5
#define INTRINSIC_FPATAN  6
#define INTRINSIC_FPREM   7
#define INTRINSIC_FPREM1  8
#define INTRINSIC_FPTAN   9
#define INTRINSIC_FSCALE  10
#define INTRINSIC_FXAM    11
#define INTRINSIC_FXTRACT 12
#define INTRINSIC_FYL2X   13
#define INTRINSIC_FYL2XP1 14

bool GetLowLevelILForInstruction(BinaryNinja::Architecture* arch, const uint64_t addr, BinaryNinja::LowLevelILFunction& il, const xed_decoded_inst_t* const xedd);
