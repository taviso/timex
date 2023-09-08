# timex

This is a "hello world" for the Timex m851 written in C.

I ported the official SDK to C, I wrote a brief article about it [here](https://lock.cmpxchg8b.com/timex.html).

I hope this can be a useful template for building your own WristApp!

![crown](https://github.com/taviso/timex/assets/123814/8b04b788-d304-48cf-8239-009a207597c9)

# Requirements

You need `wine`, `unshield` and `msitools`.

> Note that on fedora, you will need `wine.i686`.

# Usage

First, run `buildenv.sh` to download the toolchain and headers.

> Note: It doesn't install anything, it just places them in the build directory.

## Setup

You must create a `.app` file that describes where the code goes.

Here is a minimal example:

```ini
[WristApp]
Name=Hello World
Description=Test Application
Line1=
Line2=
Version Required=018
PAR=hello_par_018.bin
CODE=hello_code_018.bin
DB=
Password Support=
```

Now you need to create a base file for each of your states, name them
`state0.c`, `state1.c` and so on.

The first function in each `state?.c` file should be your event handler.

You can place variables wherever you like.

```c
#include <timex.h>

void banner_state_manager (void)
{
        switch (CORECurrentEvent) {
            case COREEVENT_STATEENTRY:
                coreSetPopDownState(COREDEFAULTSTATE);
                break;
            default:
                // Use the default handler for all other events.
                coreCommonBannerStateHandler();
                break;
        }

        return;
}
```

> Note: If you want your state to be written in assembly, you can do that too!
> Just call it `state3.asm` and the `Makefile` will understand.

Put your background event handler in `common.c`, this is also where you will
put any common code that all states need to access.

You will also need a `param.asm` file that contains the application control
block.

## Makefile

The simplest Makefile will just contain this:

```Makefile
include etc/rules.mk
```

This assumes you just have a few `state?.c` files and that's it!

If you want more `.c` files linked into a state, specify that you want them
compiled and linked in like this:

```Makefile
# Add any additional object dependencies here.
state1.out: banner.obj data.obj extra.obj
```

You can also adjust toolchain flags, for example to disable warnings or enable
debugging options:

```Makefile
C88FLAGS=-s -w123
```

If you want to append commands to a target, just use double colons.

For example:

```Makefile
clean::
	rm -f my_extra_file
```

### Databases

If you want to create a database, first add a `DB=` section to your `.app` file.

Create records called `*.rec` in the `db` directory.

You can call the records `00_foo.rec`, `02_bar.rec`, `03_baz.rec` and so on.
They will be added to the database in filename order.

> Note: Currently it will always be a random access, variable record size
> database.

Use code like this to access it:

```c
    dbOpenFile();
    dbReadRecordRandomVar(&rec, num, sizeof(rec));
    dbCloseFile();
```

### Pre-processing

The `c88` compiler is sometimes finicky. A recommended step is to pre-process
your files with the GNU C Pre-processor, this way you can use modern features
and workaround buggy macro syntax.

To enable this feature, just do this:

```Makefile
# You can optionally request that all your .c file be pre-processed with GNU
# cpp before being compiled with c88.
#
USE_GNU_CPP = 1
```

# Building

Once your `Makefile` is complete, just type `make`!

![make](https://github.com/taviso/timex/assets/123814/46cc947b-dbc6-4cb3-b0fa-e9dc412eab49)

You can upload your app to your watch using `libdlusb`.

## Windows

If you are using Windows, copy the `.app` and `.bin` files to your
`C:\Program Files (x86)\Timex\App` directory.

Alternatively, just run `bin/wristappdl.exe` for a simple upload tool.

> Note: I needed to run it with Administrator priviliges and in compatability mode.

## Errors

##### `lc88 E200 (0): Absolute address xyz occupied`

This means the locator couldn't find a way to fit your code into the available
space. You can try splitting your code into more states, or reducing the amount
of code in your common section to free up space.

If you're accessing lots of static data (strings, tables, etc), try putting that
data into a database instead, that will make more room for code.

## Debugging

There is an simulator with debugging support (breakpoints, disassembler, save states, etc).

It is Windows only, but very handy for development.

![datalink](https://github.com/taviso/timex/assets/123814/cdafffec-f685-462a-9ed6-cf3638000a62)

