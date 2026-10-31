/* Future edges may follow their native route orientation. The occupied edge,
 * current ground admission and the full three-dimensional forecast stay intact.
 * Route normals describe course intent; they do not establish future KCL. */
EXPORT const u32 lab_corner_future_plane_config[4]={1,0x90,0x9c,12};
static u32 cfp_normal(const void *point,float *normal){
    u32 offset=0x90;float norm=0.f;
    for(u32 i=0;i<3;i++)normal[i]=f(point,offset+4*i);
    if(normal[0]==0.f&&normal[1]==0.f&&normal[2]==0.f){
        offset=0x9c;for(u32 i=0;i<3;i++)normal[i]=f(point,offset+4*i);
    }
    for(u32 i=0;i<3;i++){
        if(!finite(normal[i]))return 0;norm+=normal[i]*normal[i];
    }
    if(!finite(norm)||norm<.999f||norm>1.001f)return 0;
    norm=root_positive(norm);for(u32 i=0;i<3;i++)normal[i]/=norm;
    return 1;
}
static u32 cfp_edge(const ArcOwner *c,void *a,void *z,u32 occupied,u32 radial,
    ArcEdge *out,u32 stage,u32 *reason,u32 future){
    u32 original_reason=0;
    if(cp_edge(c,a,z,occupied,radial,out,stage,&original_reason)){
        if(reason)*reason=0;return 1;
    }
    if(reason)*reason=original_reason;
    if(!future||occupied||original_reason!=7)return 0;
    float ground[3],one[3],two[3];
    if(!cnr_up(c,ground)||!cfp_normal(a,one)||!cfp_normal(z,two))return 0;
    /* Same positive .95 squared normal agreement used by qualified snaking
     * future edges; no extension to a reversed or distant surface. */
    float agreement[5]={ca_dot(one,two),ca_dot(one,ground),ca_dot(two,ground),
                        ca_dot(one,c->up),ca_dot(two,c->up)};
    for(u32 i=0;i<5;i++)if(!finite(agreement[i])||agreement[i]<=0.f||
        agreement[i]*agreement[i]<.95f)return 0;
    ArcOwner local=*c;for(u32 i=0;i<3;i++)local.up[i]=one[i];
    u32 local_reason=0;
    if(!cp_edge(&local,a,z,occupied,radial,out,stage,&local_reason))return 0;
    float vertical=ca_dot(out->delta,two);
    if(!finite(vertical)||vertical*vertical>.0025f*out->length2)return 0;
    if(reason)*reason=0;return 1;
}
