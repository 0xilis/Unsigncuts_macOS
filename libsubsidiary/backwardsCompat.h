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

#ifndef BACKWARDS_COMPAT_H
#define BACKWARDS_COMPAT_H

#include <stdio.h>
#include <objc/runtime.h>
#include "libsubsidiary.h"

void MSHookMessageEx(Class _class, SEL message, IMP hook, IMP *old);
void SubHookMessageEx(Class class, SEL selector, void *replacement, void *old_ptr, bool *created_imp_ptr);
libh_err LBHookMessage(Class objcClass, SEL selector, void *replacement, void *old_ptr);

#endif /* BACKWARDS_COMPAT */