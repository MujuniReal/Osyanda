/*
typedef struct{
    uint32 gs, fs, es, ds;
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32 interrupt_no, interrupt_errcode;
    uint32 eip, cs, eflags, oldesp, ss;

}GP_REGISTERS;
*/
GS_OFFSET = 4
FS_OFFSET = 8
ES_OFFSET = 12
DS_OFFSET = 16
EDI_OFFSET = 20
ESI_OFFSET = 24
EBP_OFFSET = 28
ESP_OFFSET = 32
EBX_OFFSET = 36
EDX_OFFSET = 40
ECX_OFFSET = 44
EAX_OFFSET = 48
INTRNO_OFFSET = 52
INTRERRCODE_OFFSET = 56
EIP_OFFSET = 60
CS_OFFSET = 64
EFLAGS_OFFSET = 68
OLDESP_OFFSET = 72
SS_OFFSET = 76




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
