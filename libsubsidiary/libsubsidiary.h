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

#ifndef LIBSUBSIDIARY_H
#define LIBSUBSIDIARY_H

#include <stdio.h>
#include <objc/runtime.h>

enum LIBHOOKER_ERR {
 LIBHOOKER_OK = 0,
 LIBHOOKER_ERR_SELECTOR_NOT_FOUND = 1,
 LIBHOOKER_ERR_SHORT_FUNC = 2,
 LIBHOOKER_ERR_BAD_INSN_AT_START = 3,
 LIBHOOKER_ERR_VM = 4,
 LIBHOOKER_ERR_NO_SYMBOL = 5,
};

typedef enum LIBHOOKER_ERR libh_err;

enum SubsidiaryMsgHookError {
 Subsid_Succeed = 0x0,
 Subsid_NoSel = 0x1,
 Subsid_InvalidArgs = 0x1000, /* 8 */
};

typedef enum SubsidiaryMsgHookError subsid_err;

void SubsidiaryGenericHookMethod(Class cls, SEL name, IMP imp, IMP *orig);
#if 0
void SubsidiaryHookFunction(const char *functionName, void *hook, void **origFunc);
void *SubsidiaryGetGenericIvar(void *obj, const char *ivarName);
void SubsidiaryGetGenericIvar(void *obj, const char *ivarName, void *data);
#endif
subsid_err SubsidiaryGenericHookMethodWithError(Class cls, SEL name, IMP imp, IMP *orig);

#endif /* LIBSUBSIDIARY_H */
