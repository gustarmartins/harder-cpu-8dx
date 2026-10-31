/* Owned-hop base occupation can advance before the processed selected cache.
 * Qualify exactly its cached successor; never clamp or relocate the kart.
 * The selected union and contracted next-base tube cover the entire four-
 * update forecast. The caller continues its unchanged full horizon walk. */
EXPORT const struct {u32 abi,max_edges,prediction_updates,reserved;float alignment_squared;}
lab_snaking_hop_base_successor_config={1,2,4,0,.995f};

static u32 hbs_contains(HnbInterval interval,float travel){
    return (interval.lo<0||(interval.lo==0&&!interval.lo_open))&&interval.hi>travel;
}

EXPORT const u32 lab_snaking_base_successor_diag_config[4]={1,320,120,0x48420000u};
static u32 hbs_denied(u32 *reason,u32 why,u32 mode){
    if(reason)*reason=(why<<8)|mode;return 0;
}
static u32 hbs_occupation(const void *physics,const void *route,void *course,void *native_base,
    u64 a,u64 z,u64 ba,u64 bz,const float *delta,float length2,float projection,
    float speed,const HopVectors *v,float *debt,u32 *reason){
    if(!finite(projection)||projection<length2||!finite(speed)||speed<=2.f)return hbs_denied(reason,1,255);
    u64 following=scp_following(route,course,a,z);
    u32 key;
    if(!ptr(following)||following==a||following==z||
       !successor((void *)z,&key)||be_point(course,key)!=following||
       w((void *)following,0x8c)!=key)return hbs_denied(reason,2,255);
    u64 bf=be_point(native_base,key);
    if(!bf||bf==ba||bf==bz||!be_edge((void *)bz,key))return hbs_denied(reason,3,255);
    float sd[3],sd2,sp,nsd[3],nsd2,nsp,nd[3],nd2,np;
    if(!hf_intent(physics,(void *)a,(void *)z,v,1,sd,&sd2,&sp))return hbs_denied(reason,4,255);
    if(!hf_intent(physics,(void *)z,(void *)following,v,0,nsd,&nsd2,&nsp))return hbs_denied(reason,5,255);
    if(!hf_intent(physics,(void *)bz,(void *)bf,v,1,nd,&nd2,&np))return hbs_denied(reason,6,255);
    if(!hf_edge(sd,sd2,v))return hbs_denied(reason,7,255);
    if(!hnb_future_edge(nsd,nsd2,nsp,v))return hbs_denied(reason,8,255);
    if(!hf_edge(nd,nd2,v))return hbs_denied(reason,9,255);
    if(!hnb_straight(sd,sd2,nsd,nsd2))return hbs_denied(reason,10,255);
    if(!hnb_straight(delta,length2,nd,nd2))return hbs_denied(reason,11,255);
    float width=f((void *)bz,0x24),r=f((void *)bf,0x24);
    if(!finite(width)||!finite(r)||width<lab_snaking_config.minimum_width||
       r<lab_snaking_config.minimum_width||width>10000||r>10000)return hbs_denied(reason,12,255);
    if(r<width)width=r;
    float clearance=width-lab_snaking_config.margin-2.f*speed,travel=4.f*speed;
    if(clearance<=0)return hbs_denied(reason,13,255);
    float base_offset[3],selected_offset[3],next_selected_offset[3];
    for(u32 i=0;i<3;i++){
        float p=f(physics,0x2c+4*i);
        base_offset[i]=p-f((void *)bz,0xc+4*i);
        selected_offset[i]=p-f((void *)a,0xc+4*i);
        next_selected_offset[i]=p-f((void *)z,0xc+4*i);
        if(!finite(base_offset[i])||!finite(selected_offset[i])||!finite(next_selected_offset[i]))return hbs_denied(reason,14,255);
    }
    for(u32 mode=0;mode<2;mode++){
        const float *axis=mode?v->pending:v->motion;
        HnbInterval next_base,first_selected,next_selected;
        if(!hnb_interval(nd,nd2,np,base_offset,axis,clearance,0.f,1,&next_base))return hbs_denied(reason,15,mode);
        if(!hnb_interval(sd,sd2,sp,selected_offset,axis,0.f,0.f,0,&first_selected))return hbs_denied(reason,16,mode);
        if(!hnb_interval(nsd,nsd2,nsp,next_selected_offset,axis,0.f,0.f,0,&next_selected))return hbs_denied(reason,17,mode);
        if(!hnb_selected_join(sd,sd2,nsd,nsd2,next_selected_offset,axis,&first_selected,&next_selected))return hbs_denied(reason,18,mode);
        if(!hbs_contains(next_base,travel))return hbs_denied(reason,19,mode);
        if(!(hnb_cover(first_selected,next_selected,travel)||hbs_contains(next_selected,travel)))return hbs_denied(reason,20,mode);
    }
    /* The next loop edge adds its complete base length. Debit the already
     * occupied distance measured on that edge, rather than the old tangent. */
    float distance=np/root(nd2);
    if(!finite(distance)||distance<0)return hbs_denied(reason,21,255);
    *debt=distance;return 1;
}
