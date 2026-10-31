/* Grounded continuation through the internal endpoint-plane wedge of two
 * qualified BASE edges. The existing selected-junction proof is required by
 * the caller. Both rays must start inside the contracted shared-node ball,
 * overlap both finite tubes, and enter the next tube within four updates.
 * No charge, position, axis, route, ratio or native-object writes. */
EXPORT const u32 lab_snaking_base_joint_gap_config[4]={1,2,4,0};

static u32 sbj_occupation(const void *physics,const void *route,void *course,
    void *native_base,u64 a,u64 z,u64 ba,u64 bz,const float *delta,
    float length2,float projection,float width,float speed,
    const HopVectors *v,float *debt){
    if(!finite(projection)||projection<=length2||!finite(speed)||speed<=2.f||
       speed>lab_snaking_config.maximum_speed)return 0;
    u64 following=scp_following(route,course,a,z);u32 key;
    if(!ptr(following)||following==a||following==z||
       !successor((void *)z,&key)||be_point(course,key)!=following||
       w((void *)following,0x8c)!=key)return 0;
    u64 bf=be_point(native_base,key);
    if(!bf||bf==ba||bf==bz||!be_edge((void *)bz,key))return 0;
    float sd[3],sd2,sp,nsd[3],nsd2,nsp,nd[3],nd2,np;
    if(!hf_intent(physics,(void *)a,(void *)z,v,0,sd,&sd2,&sp)||
       !hf_intent(physics,(void *)z,(void *)following,v,0,nsd,&nsd2,&nsp)||
       !hf_intent(physics,(void *)bz,(void *)bf,v,0,nd,&nd2,&np)||
       !(sp>sd2)||!(nsp<0.f)||!(np<0.f)||
       !hnb_future_edge(sd,sd2,sp,v)||!hf_edge(nsd,nsd2,v)||!hf_edge(nd,nd2,v)||
       !hnb_straight(sd,sd2,nsd,nsd2)||!hnb_straight(delta,length2,nd,nd2))return 0;
    float next_width=f((void *)bz,0x24),other=f((void *)bf,0x24);
    if(!finite(width)||!finite(next_width)||!finite(other)||
       width<lab_snaking_config.minimum_width||next_width<lab_snaking_config.minimum_width||
       other<lab_snaking_config.minimum_width||width>10000||next_width>10000||other>10000)return 0;
    if(other<next_width)next_width=other;
    float clearance=width-lab_snaking_config.margin-2.f*speed;
    float next_clearance=next_width-lab_snaking_config.margin-2.f*speed;
    float radius=clearance<next_clearance?clearance:next_clearance,travel=4.f*speed;
    if(!finite(radius)||radius<=0)return 0;
    float offset[3],next_offset[3],selected_offset[3],next_selected_offset[3];
    for(u32 i=0;i<3;i++){
        float p=f(physics,0x2c+4*i);
        offset[i]=p-f((void *)ba,0xc+4*i);
        next_offset[i]=p-f((void *)bz,0xc+4*i);
        selected_offset[i]=p-f((void *)a,0xc+4*i);
        next_selected_offset[i]=p-f((void *)z,0xc+4*i);
        if(!finite(offset[i])||!finite(next_offset[i])||
           !finite(selected_offset[i])||!finite(next_selected_offset[i]))return 0;
    }
    for(u32 mode=0;mode<2;mode++){
        const float *axis=mode?v->pending:v->motion;
        HnbInterval first,next,cap,selected,next_selected;
        if(!hnb_interval(delta,length2,projection,offset,axis,clearance,0.f,1,&first)||
           !hnb_interval(nd,nd2,np,next_offset,axis,next_clearance,0.f,1,&next)||
           !hnc_sphere(next_offset,axis,radius,&cap))return 0;
        /* Only a gap between closed longitudinal faces can be bridged.
         * Open radial exits never receive this continuation authority. */
        if(first.hi_open||next.lo_open||first.hi>=0.f||next.lo<=0.f||
           next.lo>=travel||next.hi<=travel||cap.lo>=0.f||cap.hi<=0.f||
           cap.lo>=first.hi||cap.hi<=next.lo)return 0;
        if(!hnb_interval(sd,sd2,sp,selected_offset,axis,0.f,0.f,0,&selected)||
           !hnb_interval(nsd,nsd2,nsp,next_selected_offset,axis,0.f,0.f,0,&next_selected)||
           !hnb_selected_join(sd,sd2,nsd,nsd2,next_selected_offset,axis,&selected,&next_selected)||
           !(hbs_contains(selected,travel)||hbs_contains(next_selected,travel)||
             hnb_cover(selected,next_selected,travel)))return 0;
    }
    /* The kart has not reached the next BASE segment's starting plane.
     * Credit no gap distance; the caller still walks its full charge horizon. */
    *debt=0.f;return 1;
}
