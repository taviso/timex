// vim:ff=dos

#ifndef __TIMEX_ASMREGS
#define __TIMEX_ASMREGS

// This file contains a collection of macros for managing registers when
// calling inline assembly. This is very poorly supported in c88, so these
// macros were developed by carefully observing what c88 does.
//
// There are two macros you need, and a few caveats.
//
// 1. __spoils() lets c88 know that a function will clobber certain registers.
// 2. __uses() lets c88 know that a regparam must be loaded.
// 3. __useptr() lets c88 know a pointer might be written too.
//
// The caveats are that not all registers can be marked spoiled, if you touch
// IX, IY, etc, then you must push/pop it.
//
// You must also save files in dos format, or the asm parser goes crazy. vim
// users, just add vim:ff=dos to the top of the file.

typedef char     a_spoils_t;
typedef short    b_spoils_t;    // Implies A
typedef short   ab_spoils_t;
typedef long    hl_spoils_t;    // Implies AB

#define __spoils(a) a ## _spoils_t

#define __useptr(p) __fallthrough_iy(p)

// Can use these to trick c88 into thinking iy/ix are damaged.
// e.g. __fallthrough_iy(0)
extern void _asmfunc __fallthrough_iy(void _near *iy);
extern void _asmfunc __fallthrough_ix(void _near *iy, void _near *ix);

// extern void _asmfunc __fallthrough_a(char a);
// extern void _asmfunc __fallthrough_b(char a, char l);
// extern void _asmfunc __fallthrough_c(char a, char l, char yp);
// extern void _asmfunc __fallthrough_d(char a, char l, char yp, char xp);
// extern void _asmfunc __fallthrough_e(char a, char l, char yp, char xp, char h);
// extern void _asmfunc __fallthrough_t(char a, char l, char yp, char xp, char h, char b);
// extern void _asmfunc __fallthrough_f(char a, char l, char yp, char xp);
// extern void _asmfunc __fallthrough_g(int ba);
// extern void _asmfunc __fallthrough_h(int ba, int hl);
// extern void _asmfunc __fallthrough_i(int ba, int hl, int ix);
// extern void _asmfunc __fallthrough_j(int ba, int hl, int ix, int iy);
// extern void _asmfunc __fallthrough_k(long hlba);
// extern void _asmfunc __fallthrough_l(long hlba, long iyix);
// extern void _asmfunc __fallthrough_m(void _near *iy);
// extern void _asmfunc __fallthrough_n(void _near *iy, void _near *ix);
// extern void _asmfunc __fallthrough_o(void _near *iy, void _near *ix, void _near *hl);
// extern void _asmfunc __fallthrough_p(void _near *iy, void _near *ix, void _near *hl, void _near *ba);

#endif
