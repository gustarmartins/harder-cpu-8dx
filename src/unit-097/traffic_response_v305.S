#include "register_context.inc"
.text
.balign 4
.global lab_traffic_response_state3_hook
.type lab_traffic_response_state3_hook,%function
lab_traffic_response_state3_hook:
    save_context
    mov w1,w0
    mov x0,x19
    bl lab_traffic_response
    str x0,[sp]
    restore_context
    tbz w0,#0,1f
.global lab_traffic_response_state3_accept
lab_traffic_response_state3_accept:
    b .
1:
.global lab_traffic_response_state3_refuse
lab_traffic_response_state3_refuse:
    b .
.size lab_traffic_response_state3_hook,.-lab_traffic_response_state3_hook

.balign 4
.global lab_traffic_response_state2_hook
.type lab_traffic_response_state2_hook,%function
lab_traffic_response_state2_hook:
    save_context
    mov w1,w0
    mov x0,x19
    bl lab_traffic_response
    str x0,[sp]
    restore_context
    mov w21,w0
.global lab_traffic_response_state2_return
lab_traffic_response_state2_return:
    b .
.size lab_traffic_response_state2_hook,.-lab_traffic_response_state2_hook
