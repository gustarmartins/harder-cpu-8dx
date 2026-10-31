/* A past BASE endpoint may use the already-proved grounded node continuation.
 * This establishes no occupation by itself; the unchanged caller must still
 * prove the contracted shared-node ball and both complete motion forecasts. */
EXPORT const u32 lab_snaking_joint_turn_config[4]={1,2,4,0};
static u32 jtp_past(const void *physics,const void *a,const float *delta,
    float length2,float *projection){
    if(!finite(length2)||length2<64.f)return 0;
    float value=0;
    for(u32 i=0;i<3;i++){
        float offset=f(physics,0x2c+4*i)-f(a,0xc+4*i);
        if(!finite(offset)||!finite(delta[i]))return 0;
        value+=offset*delta[i];
    }
    if(!finite(value)||value<=length2)return 0;
    *projection=value;return 1;
}
