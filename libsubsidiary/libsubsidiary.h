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

enum SubsidiaryMsgHookError {
 Subsid_Succeed = 0x0,
 Subsid_NoSel = 0x1,
 Subsid_InvalidArgs = 0x1000, /* 8 */
};

typedef enum SubsidiaryMsgHookError subsid_err;

subsid_err SubsidiaryGenericHookMethodWithError(Class cls, SEL name, IMP imp, IMP *orig);

#endif /* LIBSUBSIDIARY_H */
