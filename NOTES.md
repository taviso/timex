# State Index

|  Index | Kernel Definition          | Description |
| ------ | -------------------------- | ----------- |
|  0x00  | COREBANNERSTATE            | The state to proceed to on a mode entry.
|  0x01  | COREDEFAULTSTATE           | The state to proceed to after a mode banner state and for any mode change requests that bypasses the mode banner state.
|  0x02  | CORESET1BANNERSTATE        | Using the common crown handler, this is the state that will be active when the crown is placed in the SET 1 position.
|  0x03  | CORESET1STATE              | Handles the application SET 1 processing.
|  0x04  | COREPOPUPSTATE             | The state to proceed on an application popup request through the kernel.
|  0x05  | COREPASSWORDDEFAULTSTATE   | Password entry default state handler
|  0x06  | COREPASSWORDSETBANNERSTATE | Password entry set banner state handler
|  0x07  | COREPASSWORDSETSTATE       | Password entry set state handler
|  0x08… | General Purpose            | These states have no kernel restrictions on its usage.


# Project Ideas

- Scan firmware for instructions we can borrow to compress our code?
- LD EP, #0 should be unescessary - remove in cleancc.
- Can I detect tail recursion and `s/carl;ret/jrl/g` easily?

I'm not 100% certain my tricks to force consistent calling convention is working.

# Notes
## Print Section Summary

- `pr88.exe -s -v2 filename.obj`


