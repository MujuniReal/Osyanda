.code32


.text

.global _start
.global run_impala

_start:
    lea (sys_stack),%esp
	call run_impala

.bss
reserve: .fill 4096,1,0
sys_stack:

.data
section_id: .ascii "KERNEL DATA SECTION"
