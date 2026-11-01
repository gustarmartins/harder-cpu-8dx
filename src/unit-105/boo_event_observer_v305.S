/* Private observation at42614, after native use-marker publication. */
#include "register_context.inc"
.text
.balign 4
.global lab_boo_event_use_hook
.type lab_boo_event_use_hook,%function
lab_boo_event_use_hook:
    save_context
    mov x0,x19
    mov w1,w20
    mov x2,x22
    adrp x3,lab_module_start
    add x3,x3,:lo12:lab_module_start
    movz x9,#(LAB_MAIN_TO_MODULE & 0xffff)
    movk x9,#((LAB_MAIN_TO_MODULE >> 16) & 0xffff),lsl #16
    sub x3,x3,x9
    bl lab_boo_event_use
    restore_context
    ldrb w8,[x0,#0x2a]
.global lab_boo_event_use_return
lab_boo_event_use_return:
    b .
.size lab_boo_event_use_hook,.-lab_boo_event_use_hook
