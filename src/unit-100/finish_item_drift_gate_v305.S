#include "register_context.inc"
.text
.balign 4
.global lab_finish_item_drift_hook
.type lab_finish_item_drift_hook,%function
lab_finish_item_drift_hook:
    tbz w0,#0,.Lfinish_item_drift_admit
    save_context
    mov x0,x19
    bl lab_finish_queued_bullet_drift_urgent
    cbz w0,.Lfinish_item_drift_keep
    restore_context
    b lab_finish_item_drift_continue
.Lfinish_item_drift_keep:
    restore_context
    b lab_finish_item_drift_block
.Lfinish_item_drift_admit:
    b lab_finish_item_drift_continue
.global lab_finish_item_drift_continue
lab_finish_item_drift_continue:
    b .
.global lab_finish_item_drift_block
lab_finish_item_drift_block:
    b .
.size lab_finish_item_drift_hook,.-lab_finish_item_drift_hook
