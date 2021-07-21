/*


typedef struct {
    uint16 interrupthandler_lo;     Low 2bytes of location of interrupt handler 
    uint16 code_segment_selector;   Index of code segment descriptor in gdt 
    uint8  zero;                    Always set to zero 
    uint8  entry_attrib;             idt entry attributes; defines gate type, storage segment, privilleges, presence of idt entry 
    uint16 interrupthandler_hi;      High 2bytes of location of interrupt handler 
} __attribute__((packed)) IDTENTRY;


typedef struct {
    uint16 idt_size;                 size/limit of idt, ensure to subtract 1 when declaring this, to avoid +1 - errors
    uint32 idt_location;            base/location of idt in memory (absolute) 
}__attribute__((packed)) IDTPOINTER;
  


typedef struct{
    uint32 gs, fs, es, ds;
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32 interrupt_no, interrupt_errcode;
    uint32 eip, cs, eflags, oldesp, ss;

}GP_REGISTERS;
*/
R_GS = 0
R_FS = 4
R_ES = 8
R_DS = 12
R_EDI = 16
R_ESI = 20
R_EBP = 24
R_ESP = 28
R_EBX = 32
R_EDX = 36
R_ECX = 40
R_EAX = 44
INTRNO = 48
INTRERRCODE = 52
R_EIP = 56
R_CS = 60
R_EFLAGS = 64
R_OLDESP = 68
R_SS = 72




/*
.macro GP_REGISTERS regs_name
regs_name:
    gs_m: .int 0x0
    fs_m: .int 0x0
    es_m: .int 0x0
    ds_m: .int 0x0
    edi_m: .int 0x0
    esi_m: .int 0x0
    ebp_m: .int 0x0
    esp_m: .int 0x0
    ebx_m: .int 0x0
    edx_m: .int 0x0
    ecx_m: .int 0x0
    eax_m: .int 0x0
    interrupt_no_m: .int 0x0
    interrupt_errcode_m: .int 0x0
    eip_m: .int 0x0
    cs_m: .int 0x0
    eflags_m: .int 0x0
    oldesp_m: .int 0x0
    ss_m: .int 0x0

.endm
*/
