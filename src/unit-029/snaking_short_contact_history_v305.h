/* Retain a qualified landed normal through the existing three-update contact
 * allowance. Only owned history and local forecast vectors are affected.
 * Native contact, axes, charge, motion and route checks remain authoritative. */
EXPORT const u32 lab_snaking_short_contact_history_config[4]={1,3,4,5};

static u32 sch_matching(const GroundNativeAxis *r,u32 ds){
    return r&&r->ready&&r->predicted&&r->expected_valid&&!r->poison&&
        r->landing==1&&!r->expected_world&&(ds==4||ds==5)&&r->ds==ds;
}

static u32 sch_air(const void *physics,const SnakeHopFrame *frame,
                   const GroundNativeAxis *r,u32 ds){
    u32 air=w(physics,0x26c);
    if(!sch_matching(r,ds)||!df_contact(physics,frame)||
       b(physics,0x200)!=1||b(physics,0x201)!=0||air<1||air>3)return 0;
    if(!((r->contact==3&&r->air==0&&air==1)||
         (r->contact==1&&r->air>=1&&r->air<3&&air==r->air+1)))return 0;
    for(u32 i=0;i<3;i++)if(nga_bits(r->road[i])!=nga_bits(r->target[i])||
        nga_bits(r->road[i])!=w(physics,0x32c+4*i))return 0;
    return 1;
}

static u32 sch_resume(const void *physics,const GroundNativeAxis *r,u32 ds){
    return sch_matching(r,ds)&&r->contact==1&&r->air>=1&&r->air<=3&&
        b(physics,0x200)==1&&b(physics,0x201)==1&&
        w(physics,0x26c)==0&&f(physics,0x274)==0.f;
}

/* Called only after the exact per-update history and ownership validation. */
static u32 sch_current(const void *physics,const SnakeHopFrame *frame,
                       const GroundNativeAxis *r){
    if(!ptr(frame->drift)||!sch_matching(r,w((void *)frame->drift,0x10))||
       !df_contact(physics,frame)||r->contact!=1||r->air<1||r->air>3||
       b(physics,0x200)!=1||b(physics,0x201)!=0||w(physics,0x26c)!=r->air)return 0;
    for(u32 i=0;i<3;i++)if(nga_bits(r->road[i])!=nga_bits(r->target[i])||
        nga_bits(r->road[i])!=w(physics,0x32c+4*i))return 0;
    return 1;
}
