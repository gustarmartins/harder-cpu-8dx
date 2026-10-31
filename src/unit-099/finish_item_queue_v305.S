#include "register_context.inc"
.text
.balign 4
.global lab_finish_bullet_wait_hook
.type lab_finish_bullet_wait_hook,%function
.global lab_boo_defense_hook
lab_boo_defense_hook:
lab_finish_bullet_wait_hook:
    save_context
    mov x0,x19
    adrp x1,lab_module_start
    add x1,x1,:lo12:lab_module_start
    movz x9,#(LAB_MAIN_TO_MODULE & 0xffff)
    movk x9,#((LAB_MAIN_TO_MODULE >> 16) & 0xffff),lsl #16
    sub x1,x1,x9
    bl lab_boo_defense_current
    cbnz w0,.Lboo_shared_use
    mov x0,x19
    bl lab_finish_bullet_urgent
    cbz w0,.Lfinish_bullet_native
    restore_context
    str wzr,[x19,#0xec]
    ldr w8,[x19,#0xec]
    b lab_finish_bullet_wait_return
.Lfinish_bullet_native:
    restore_context
    ldr w8,[x19,#0xec]
.global lab_finish_bullet_wait_return
.global lab_boo_defense_return
lab_boo_defense_return:
lab_finish_bullet_wait_return:
    b .
.Lboo_shared_use:
    restore_context
.global lab_boo_defense_use
lab_boo_defense_use:
    b .
.size lab_finish_bullet_wait_hook,.-lab_finish_bullet_wait_hook
