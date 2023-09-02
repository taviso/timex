# You can optionally request that all your .c file be pre-processed with GNU
# cpp before being compiled with c88.
# The benefit of this is that GNU cpp is more consistent, has less bugs and
# supports more features (variadic macros, counters, etc).
#
USE_GNU_CPP = 1

# If you want to debug compiler output, this will intermix source and assembly.
# You can use `make test.s` to generate the assembly.
#
#C88FLAGS=-s

include etc/rules.mk

# Add any additional object dependencies here.
state1.out: banner.obj

# These are compiler runtime libraries.
common.out: lib/mulxi.obj lib/blcps.obj
