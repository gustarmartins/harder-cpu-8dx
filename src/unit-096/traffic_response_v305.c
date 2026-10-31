/* Private traffic-response prototype. The two call sites follow the native
 * probability draw; detection and all subsequent geometry/state vetoes remain
 * native. Preserve the random draw and its state even when upgrading a refusal.
 * This helper reads game objects and changes only the returned admission bit.
 */
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
static u64 q(const void *p,u32 o){return *(const u64 *)((const u8 *)p+o);}
static u32 w(const void *p,u32 o){return *(const u32 *)((const u8 *)p+o);}
static u8 b(const void *p,u32 o){return *((const u8 *)p+o);}
static u32 ptr(u64 p){return p>=0x10000&&!(p&7)&&p<(1ull<<39)-0x2000;}

__attribute__((visibility("default")))
u32 lab_traffic_response(const void *avoid,u32 native_result){
    if(native_result||!ptr((u64)avoid))return native_result;
    u64 driver=q(avoid,0x70);
    if(!ptr(driver))return native_result;
    u64 state=q((void *)driver,0x50),proxy=q((void *)driver,0x88);
    if(!ptr(state)||!ptr(proxy)||q((void *)state,0x88)!=driver)return native_result;
    u64 nav=q((void *)state,0xb0);
    if(!ptr(nav)||q((void *)nav,0x58)!=driver||q((void *)nav,0x68)!=(u64)avoid)return native_result;
    u64 role=q((void *)proxy,0x48),physics=q((void *)proxy,0x50);
    if(!ptr(role)||!ptr(physics)||q((void *)role,0x28)!=physics||q((void *)physics,0xf8)!=role||
       w((void *)role,0xa8)>=12||b((void *)role,0xd2)!=1||b((void *)role,0xd3)!=1||
       b((void *)role,0xe1)!=1||b((void *)role,0xe7)||
       (int)w((void *)role,0x1e4)>0||(int)w((void *)role,0x1e8)>0)return native_result;
    u64 wrapper=q(avoid,0xd8);
    if(!ptr(wrapper))return native_result;
    u32 reaction=w((void *)wrapper,0x10);
    if(reaction!=1&&reaction!=3)return native_result;
    u64 object=q((void *)wrapper,0);
    if(!ptr(object))return native_result;
    u64 definition=q((void *)object,0x140);
    if(!ptr(definition))return native_result;
    u32 kind=w((void *)definition,0);
    /* Verified Shroom Ridge placements: CarA, TruckA and Bus. Other objects,
     * including CarSurf's drivable ramp, retain their existing behavior. */
    return kind==0xbbc||kind==0xbbe||kind==0xbc0;
}
