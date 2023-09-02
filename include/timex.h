#ifndef __TIMEX_H
#define __TIMEX_H

#include <stdint.h>
#include <stdbool.h>

#include "timex/asmregs.h"

// This is a hack to force the compiler to load inline parameters into
// registers. If you remove this, then the parameter loads will be optimnized
// away if they're only referenced in an asm section.
// Yes, I know about #pragma optimize... it doesn't help.
#define JOIN(x, y) JOIN1(x, y)
#define JOIN1(x,  y) x ## y
#define __use(t, n) do {                            \
    void _asmfunc JOIN(__fallthrough_, __LINE__) t; \
                  JOIN(__fallthrough_, __LINE__) n; \
} while (false)

#include "timex/core.h"
#include "timex/lcdchar.h"
#include "timex/events.h"
#include "timex/coremac.h"
#include "timex/lcdmac.h"
#include "timex/hwmac.h"
#include "timex/utlmac.h"

#endif
