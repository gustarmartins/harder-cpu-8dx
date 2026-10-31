/* Locate a canonical cached edge before testing the occupied corridor.
 * An out-of-plane edge outside the kart's longitudinal projection may locate
 * its predecessor/successor; it cannot qualify as the occupied driving edge. */
EXPORT const u32 lab_corner_edge_location_config[4]={1,7,9,16};
static u32 cel_locate(const ArcOwner *c,const void *a,const void *z,
    float *delta,float *length2,float *projection,u32 stage,u32 radial){
    u32 reason=0;
    if(cp_intent(c,a,z,1.f,.0025f,0,delta,length2,projection,stage,radial,&reason))return 1;
    if(reason!=7)return 0;
    float ground[3];
    if(!cnr_up(c,ground)||!simple_point(a)||!simple_point(z))return 0;
    u64 course=radial?c->base_course:c->course;
    u32 ka=w(a,0x8c),kz=w(z,0x8c);
    if(be_point((void *)course,ka)!=(u64)a||be_point((void *)course,kz)!=(u64)z||
       !be_edge((void *)a,kz))return 0;
    float n=0.f,p=0.f;
    for(u32 i=0;i<3;i++){
        float start=f(a,0xc+4*i),end=f(z,0xc+4*i),position=f((void *)c->physics,0x2c+4*i);
        if(!finite(start)||!finite(end)||!finite(position))return 0;
        delta[i]=end-start;n+=delta[i]*delta[i];p+=(position-start)*delta[i];
    }
    if(!finite(n)||n<64.f||!finite(p)||(p>=0.f&&p<=n))return 0;
    *length2=n;*projection=p;return 1;
}
