#gcc-inline-assembly
sub_str.c : simple routine(asm_sub_str) that gives sub-string in a given string implemented using gcc inline assembly.
On x86_64 systems, compile using -m32 switch else it will give a 'segmentation fault' error due to difference in the size of memory addresses.
Ref: http://ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html
