/**************************************************************************
**
**	FILE        :  @(#)s1c88349.dsc	1.2
**
**	VERSION     :  01/05/31
**
**	DESCRIPTION :  software description for S1C88349 
**
**	COPYRIGHT   :  2000 SEIKO EPSON CORPORATION
**
**************************************************************************/

#define coreCodeOverlayBaseAddress 0x00f31a
#ifdef _common
# include "common.inc"
#else
# define __lc_ub_asm coreCodeOverlayBaseAddress
#endif

software {
	// define program start label
	// program start label is the start of the code
	// reset vector should point to this label 
	load_mod start=__START;

	// define software layout
	layout {
		// define the preferred locating order of sections
		// in the memory space 
		// (the range is defined in the s1c88316.cpu file)
		space SMC88_space {
			// define for each sub-area in the space 
			// the locating order of sections
			block total_range {
				// define a cluster for read-only sections
				// containing:
				//  - program code
				//  - romdata sections
				//       * vectors
				//       * strings
				//       * constant data
				//  - copy table (used by startup code)
				//  - initialization data 
				//    (copied to ram by startup code)
				cluster rom {
					attribute r; 
					amode code_short {
						// system reserved 
						// (exception vector)
						reserved length=0x2 addr=0x26;
						// reserved length=0x100 addr=0x00;
					}
					amode code_short {
						// allocate short program code 
						// before short romdata
						section selection=x;
						section selection=r;
					}
					amode code {
						section .text_COMMON addr = coreCodeOverlayBaseAddress;
						section .rtcode;
						// Now space for the states.
						label asm; // AppStateManager
						section .text addr = __lc_ub_asm;
						section selection=x;
						section selection=r;
						// allocate program code, 
						// then allocate romdata,
						// initialization data,  
						copy;
						table;
					}
					amode data_short {
						// allocate short romdata
						section selection=r; 
					}
					amode data {
						// allocate far romdata
						// copy table
						section selection=r;
					}
				}
				// define a cluster for ram sections
				// containing:
				//  - uninitialized data
				//  - initialized data
				//      * zeroed by startup code 
				//        (clean attribute)
				//      * copied from initialization data 
				//        by startup code (init attribute)
				//  - heap (only when used)
				//  - stack
				//  - buffer needed by debugger
				cluster ram {
					attribute w;
					amode data_tiny {
						// allocate tiny memory code
						// before short romdata
						section selection=w;
					}
					amode data_short {
						// allocate short data
						section selection=w;
						heap;
					}
					amode data {
						// allocate far data,
						// heap (growing upwards)
						// stack (growing downwards)
						// reservation for CrossView debugger
						// (only when using '-g')
						section selection=w;
						reserved label=xvwbuffer length=0x10;
						stack;
					}
				}
			}
		}
	}
}

cpu etc\S1c88349.cpu
memory etc\S1c88349.mem

