/* A current native query may retain its orientation target while publishing
 * a different road normal. Qualify that exact query under the existing actor
 * and race lease; never substitute a near-equality tolerance for provenance.
 * All original grounded corner/motion/route predicates still run afterward. */
#include "native_accepted_ground_target_v305.h"
extern u32 lab_native_ground_target_retained(const void *,u64,u32,u32);
EXPORT const u32 lab_corner_ground_provenance_config[4]={1,1,0x189020,0x32c};
static u32 cgp_word(const void *p,u32 off){
    return *(const volatile u32 *)((const u8 *)p+off);
}
static u32 cgp_query_current(const ArcOwner *c){
    if(!c->counter||c->counter>c->now)return 0;
    const void *p=(void *)c->physics;
    u32 words[9];float road[3],target[3],rn=0.f,tn=0.f;
    for(u32 i=0;i<3;i++){
        union {u32 u;float f;} r={.u=cgp_word(p,0x17c+4*i)};
        union {u32 u;float f;} t={.u=cgp_word(p,0x32c+4*i)};
        words[i]=r.u;words[3+i]=t.u;words[6+i]=cgp_word(p,0x188+4*i);
        if(!finite(r.f)||!finite(t.f))return 0;
        road[i]=r.f;target[i]=t.f;rn+=r.f*r.f;tn+=t.f*t.f;
    }
    if(!finite(rn)||!finite(tn)||rn<.999f||rn>1.001f||tn<.999f||tn>1.001f)return 0;
    float agreement=ca_dot(road,target);
    if(!finite(agreement)||agreement<=0.f||agreement*agreement<.9801f*rn*tn)return 0;
    NativeAcceptedGroundTarget query;
    u32 start=c->now-c->counter;
    if(!lab_native_ground_target_accepted(p,c->clock,start,c->now,&query)&&
       !lab_native_ground_target_retained(p,c->clock,start,c->now))return 0;
    if(cgp_word((void *)c->clock,0x38)!=6||cgp_word((void *)c->clock,0x44)!=c->now)return 0;
    for(u32 i=0;i<3;i++)if(cgp_word(p,0x17c+4*i)!=words[i]||
        cgp_word(p,0x32c+4*i)!=words[3+i]||cgp_word(p,0x188+4*i)!=words[6+i])return 0;
    return 1;
}
