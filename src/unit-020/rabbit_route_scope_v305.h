/* Private autonomous-reference admission for the existing paired route views.
 * Caller owns the native selector/store boundary. No game fields are written.
 * Storage/admission leases protect the current immutable identity descriptor.
 */
EXPORT u32 lab_rabbit_route_scope(void *driver,void *role,void *physics,u64 base){
    (void)driver;(void)role;(void)physics;(void)base;
    return 0;
}
