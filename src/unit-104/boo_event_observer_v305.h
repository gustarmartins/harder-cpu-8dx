#ifndef HARDERAI_BOO_EVENT_OBSERVER_V305_H
#define HARDERAI_BOO_EVENT_OBSERVER_V305_H
typedef unsigned char be_u8;
typedef unsigned int be_u32;
typedef unsigned long long be_u64;
#define BE_EXPORT __attribute__((visibility("default")))
#define BE_RACERS 12u
#define BE_STAGES 2u
#define BE_RECORD_SIZE 192u
enum { BE_DEFENSE_REQUEST=1, BE_NATIVE_USE=2 };

/* Separate last-event streams prevent a use from erasing its preceding request.
 * Counts are module-lifetime lower bounds; readers need a current-epoch baseline.
 * A native use/protection observation does not establish a successful dodge. */
typedef struct {
    be_u32 lock,fault;
    be_u64 sequence,events,dropped;
    be_u64 inventory,slot,role,physics,scene,system,clock;
    be_u32 tick,racer,event,slot_index;
    be_u32 selector,slot_state,stock,used;
    be_u32 role_bytes,flags,active_remote,star_ticks;
    be_u32 boo_ticks,planner_state,planner_counter,planner_output;
    be_u32 item_token,item_lifecycle,protection_requested,reason;
    be_u64 item,origin,reserved;
} BooEventRecord;
typedef struct {be_u64 magic;be_u32 abi,size,racers,stages,use_site,request_site;} BooEventConfig;
_Static_assert(sizeof(BooEventRecord)==BE_RECORD_SIZE,"Boo event ABI1");
_Static_assert(__builtin_offsetof(BooEventRecord,inventory)==32,"Boo event owner offset");
_Static_assert(__builtin_offsetof(BooEventRecord,tick)==88,"Boo event payload offset");
_Static_assert(__builtin_offsetof(BooEventRecord,item)==168,"Boo event object offset");
_Static_assert(sizeof(BooEventConfig)==32,"Boo event config ABI1");
BE_EXPORT void lab_boo_event_request(const void *planner,be_u64 base);
BE_EXPORT void lab_boo_event_use(const void *inventory,be_u32 slot,const void *item,be_u64 base);
BE_EXPORT be_u32 lab_boo_defense_observed_current(const void *planner,be_u64 base);
#endif
