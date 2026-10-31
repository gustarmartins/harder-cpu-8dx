/* Contact-qualified forecast of the native hop permission, not extra charge.
 * Retail17D054 seeds progress0/increment.045. Retail17AB64 adds in binary32,
 * saturates at1, and17ACCC compares progress>=.6. Actual contact, input and
 * special-state gates still own the transition in17B4DC. An uncertain input
 * keeps the previous entry allowance; every route/clearance check still runs.
 */
EXPORT const struct {
    u32 abi,progress_offset,increment_offset,reserve_updates;
    float ready,increment;
} lab_snaking_native_hop_phase_config={1,0xc4,0xc8,2,.6f,.045f};

EXPORT u32 lab_snaking_native_hop_entry_updates(void *drift,u32 state,
                                               u32 elapsed,u32 original){
    if(state!=2||elapsed>=31||original<=3||!ptr((u64)drift)||w(drift,0x10)!=2)
        return original;
    u64 role=q(drift,8);
    if(!ptr(role))return original;
    u64 physics=q((void *)role,0x28);
    if(!ptr(physics)||q((void *)physics,0xf8)!=role||q((void *)physics,0x110)!=(u64)drift||
       b((void *)role,0xd2)!=1||b((void *)role,0xd3)!=1||!b((void *)role,0xe1)||
       b((void *)role,0xe7)||
       (w((void *)role,0x1cc)&(0x01204018u|0x20000u|0x800080u))||
       b((void *)physics,0x200)!=1||b((void *)physics,0x201)!=1||
       b((void *)physics,0x208)||w((void *)physics,0x5d4)||
       b(drift,0x14)!=1||b(drift,0x101)||b(drift,0x102)||
       (b((void *)role,0xe3)&&b(drift,0x100)))return original;
    float metric=f((void *)physics,0x22c),speed=f((void *)physics,0x380);
    float minimum=f(drift,0x64),axis=f((void *)role,0x17c),sum=f(drift,0x6c);
    if(!finite(metric)||metric<0.f||metric>=1.f||!finite(speed)||!finite(minimum)||
       minimum<0.f||speed<=minimum||speed<=.5f||!finite(axis)||axis< -1.f||axis>1.f||
       !finite(sum)||sum*axis<=0.f||!sch_inward((void *)role,axis<0.f?-axis:axis))
        return original;
    float progress=f(drift,0xc4),increment=f(drift,0xc8);
    if(!finite(progress)||progress<0.f||progress>1.f||!finite(increment)||
       (increment!=.045f&&!(increment==0.f&&progress>=.6f)))return original;
    u32 updates=0;
    do{
        progress+=increment;
        updates++;
    }while(progress<.6f&&updates<31);
    if(progress<.6f)return original;
    /* The transition itself earns no charge. Keep the caller's full strict
     * native charge/release/settling allowance, plus two entry reserve updates.
     * This is conditional on current full contact; it is not a KCL forecast.
     */
    updates+=lab_snaking_native_hop_phase_config.reserve_updates;
    return updates<original?updates:original;
}
