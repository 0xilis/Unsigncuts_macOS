/*
 * Copyright (C) 2023 Snoolie K / 0xilis. All rights reserved.
 *
 * This document is the property of Snoolie K / 0xilis.
 * It is considered confidential and proprietary.
 *
 * This document may not be reproduced or transmitted in any form,
 * in whole or in part, without the express written permission of
 * Snoolie K / 0xilis.
*/

/*
 * TODO:
 *
 * Basically everything regarding backwards compatibility.
 * A lot of tweaks only hook methods (and SubsidiaryGenericHookMethod should
 * be identical to other hooking libraries) so this will be fine for some.
 * But a lot of tweaks do other stuff, ex hooking using substrate to hook ivars.
 * Ex, MSHookIvar. This is a lot harder to implement backwards compatibility for as
 * the functionality of how Subsidiary handles Ivars is quite different then how
 * Substrate does this, so this can't just be a simple wrapper around the old function.
 * With that being said, pretty much everything from other hooking libraries should
 * be able to be backwards compatible with libsubsidiary, even if some stuff will
 * require more jank than others :P.
*/

#include "libsubsidiary.h"

void MSHookMessageEx(Class _class, SEL message, IMP hook, IMP *old) {
 SubsidiaryGenericHookMethod(_class, message, hook, old);
}

void SubHookMessageEx(Class class, SEL selector, void *replacement, void *old_ptr, bool *created_imp_ptr) {
 SubsidiaryGenericHookMethod(class, selector, replacement, old_ptr);
}

/* Notice that error handling may not behave the same, ex LIBHOOKER_ERR does not have a ret for invalid args, but I'm guessing almost no tweaks that use the api will rely on the return value, and the few that do likely only check if it's LIBHOOKER_OK, 0x0 (which Subsid_Succeed should suffice for) so the 0x100 of Subsid_InvalidArgs hopefully shouldn't impact it */
libh_err LBHookMessage(Class objcClass, SEL selector, void *replacement, void *old_ptr) {
 return (libh_err)SubsidiaryGenericHookMethodWithError(objcClass, selector, replacement, old_ptr);
}