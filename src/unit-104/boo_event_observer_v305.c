/* Private passive Boo observation component. Not installed.
 * Entrypoints borrow objects from the exact current native planner/use calls.
 * Bounds and readbacks validate representation/coherence, not allocation leases.
 * No native-object writes, forced use, timer, role or driving changes. */
#include "boo_event_observer_v305.h"
BE_EXPORT const BooEventConfig lab_boo_event_config={
    0x3130454f4f424148ull,1,BE_RECORD_SIZE,BE_RACERS,BE_STAGES,0x42614,0x61ec0};
BE_EXPORT BooEventRecord lab_boo_event_records[BE_RACERS][BE_STAGES];
extern be_u32 lab_boo_defense_current(const void *,be_u64);

static be_u64 q(const void *p,be_u32 o){return *(const volatile be_u64 *)((const be_u8 *)p+o);}
static be_u32 w(const void *p,be_u32 o){return *(const volatile be_u32 *)((const be_u8 *)p+o);}
static be_u32 b(const void *p,be_u32 o){return *((const volatile be_u8 *)p+o);}
static be_u32 ptr(be_u64 p){return p>=0x10000&&!(p&7)&&p<(1ull<<39)-0x3000;}

static be_u32 collect(BooEventRecord *v,const void *inv,be_u32 slot_index,
                     const void *item,const void *planner,be_u64 base,be_u32 event){
    if(!base||(base&4095)||base>=(1ull<<39)-0x1400000||!ptr((be_u64)inv)||
       slot_index>=2||q(inv,0)!=base+0x11acb70)return 0;
    be_u32 racer=w(inv,0x40);
    be_u64 slot=q(inv,0x60+8*slot_index);
    if(racer>=BE_RACERS||!ptr(slot)||q((void *)slot,0x70)!=(be_u64)inv||
       w((void *)slot,0x9c)!=22||w((void *)slot,0xa0)!=1||b((void *)slot,0x41)!=3||
       b((void *)slot,0xc1)>1)return 0;
    be_u64 scene=((be_u64 (*)(void))(base+0x7f41fc))();
    if(!ptr(scene)||q((void *)scene,0)!=base+0x125e158||!(b((void *)scene,0x180)&4))return 0;
    be_u64 system=q((void *)scene,0x1b0);
    if(!ptr(system)||q((void *)system,0)!=base+0x125a060)return 0;
    be_u64 race=q((void *)system,0x238),manager=q((void *)system,0x240),clocks=q((void *)system,0x218);
    if(!ptr(race)||q((void *)race,0)!=base+0x11b4308||!ptr(manager)||
       q((void *)manager,0)!=base+0x11a7188||!b((void *)manager,0x170)||!ptr(clocks))return 0;
    be_u32 count=w((void *)manager,0xe0);
    be_u64 array=q((void *)manager,0xe8),clock=q((void *)clocks,0x50);
    if(count<=racer||count>BE_RACERS||!ptr(array)||q((void *)array,8*racer)!=(be_u64)inv||
       !ptr(clock)||w((void *)clock,0x38)!=6)return 0;
    be_u64 proxy=q((void *)race,0x50+8*racer);
    if(!ptr(proxy)||q((void *)proxy,0)!=base+0x11b44f8)return 0;
    be_u64 role=q((void *)proxy,0x48),physics=q((void *)proxy,0x50);
    if(!ptr(role)||!ptr(physics)||q((void *)role,0x28)!=physics||
       q((void *)physics,0xf8)!=role||w((void *)role,0xa8)!=racer||
       b((void *)role,0xe1)!=1||b((void *)role,0xe7))return 0;
    v->inventory=(be_u64)inv;v->slot=slot;v->role=role;v->physics=physics;
    v->scene=scene;v->system=system;v->clock=clock;
    v->tick=w((void *)clock,0x44);v->racer=racer;v->event=event;v->slot_index=slot_index;
    if(v->tick>=0x80000000u)return 0;
    v->selector=22;v->slot_state=3;v->stock=1;v->used=b((void *)slot,0xc1);
    v->role_bytes=w((void *)role,0xd0);v->flags=w((void *)role,0x1cc);
    v->active_remote=b((void *)role,0xe1)|(b((void *)role,0xe7)<<8);
    v->star_ticks=w((void *)role,0x1e4);v->boo_ticks=w((void *)role,0x1ec);
    v->origin=base+(event==BE_DEFENSE_REQUEST?0x61ec0:0x42614);
    v->item_token=v->item_lifecycle=v->protection_requested=~0u;
    v->planner_state=v->planner_counter=v->planner_output=~0u;
    if(event==BE_DEFENSE_REQUEST){
        if(!ptr((be_u64)planner)||q(planner,0xa8)!=(be_u64)inv||q(inv,0x58)!=slot)return 0;
        be_u64 driver=q(planner,0x90);
        if(!ptr(driver))return 0;
        be_u64 adapter=q((void *)driver,0x88);
        if(!ptr(adapter)||q((void *)adapter,0)!=base+0x11b44f8||
           q((void *)adapter,0x48)!=role||q((void *)adapter,0x50)!=physics)return 0;
        be_u64 state=q((void *)driver,0x50);
        if(!ptr(state)||q((void *)state,0x88)!=driver||q((void *)state,0xa8)!=(be_u64)planner)return 0;
        v->planner_state=b(planner,0x41);v->planner_counter=w(planner,0x44);
        v->planner_output=w(planner,0xc4);v->reason=1; /* Qualified policy returned true. */
    }else if(event==BE_NATIVE_USE){
        if(!ptr((be_u64)item)||q(item,0)!=base+0x11ac310||w(item,0x58)!=18||
           w(item,0x5c)!=racer||b(item,0x71)!=7||!v->used||b(item,0x38d)>1)return 0;
        v->item=(be_u64)item;v->item_token=*(const volatile unsigned short *)((const be_u8 *)item+0x274);
        v->item_lifecycle=7;v->protection_requested=b(item,0x38d);
    }else return 0;
    return 1;
}

static void publish(const void *inv,be_u32 slot,const void *item,const void *planner,be_u64 base,be_u32 event){
    BooEventRecord next={0},again={0};
    if(!collect(&next,inv,slot,item,planner,base,event))return;
    BooEventRecord *s=&lab_boo_event_records[next.racer][event-1];be_u32 unlocked=0;
    if(!__atomic_compare_exchange_n(&s->lock,&unlocked,1,1,__ATOMIC_ACQUIRE,__ATOMIC_RELAXED)){
        be_u64 d=__atomic_load_n(&s->dropped,__ATOMIC_RELAXED);
        if(d!=~0ull)__atomic_compare_exchange_n(&s->dropped,&d,d+1,1,__ATOMIC_RELAXED,__ATOMIC_RELAXED);
        return;
    }
    if(s->fault)goto done;
    if((s->sequence&1)||s->sequence>~0ull-2||s->events==~0ull){s->fault=1;goto done;}
    if(!collect(&again,inv,slot,item,planner,base,event))goto done;
    const be_u64 *a=(const be_u64 *)&next.inventory,*z=(const be_u64 *)&again.inventory;
    for(be_u32 i=0;i<(sizeof(next)-32)/8;i++)if(a[i]!=z[i])goto done;
    __atomic_add_fetch(&s->sequence,1,__ATOMIC_ACQ_REL);s->events++;
    volatile be_u64 *to=(volatile be_u64 *)&s->inventory;
    for(be_u32 i=0;i<(sizeof(next)-32)/8;i++)to[i]=a[i];
    __atomic_add_fetch(&s->sequence,1,__ATOMIC_RELEASE);
done:
    __atomic_store_n(&s->lock,0,__ATOMIC_RELEASE);
}

BE_EXPORT void lab_boo_event_request(const void *planner,be_u64 base){
    if(!ptr((be_u64)planner))return;
    be_u64 inv=q(planner,0xa8);if(!ptr(inv))return;
    be_u64 held=q((void *)inv,0x58);be_u32 slot=2;
    if(held==q((void *)inv,0x60))slot=0;
    else if(held==q((void *)inv,0x68))slot=1;
    publish((void *)inv,slot,0,planner,base,BE_DEFENSE_REQUEST);
}
BE_EXPORT void lab_boo_event_use(const void *inv,be_u32 slot,const void *item,be_u64 base){
    publish(inv,slot,item,0,base,BE_NATIVE_USE);
}
BE_EXPORT be_u32 lab_boo_defense_observed_current(const void *planner,be_u64 base){
    be_u32 result=lab_boo_defense_current(planner,base);
    if(result)lab_boo_event_request(planner,base);
    return result;
}
