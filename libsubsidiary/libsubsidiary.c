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
 * Note that everything other than SubsidiaryGenericHookMethod has been redacted from this source.
*/

#include <objc/runtime.h>
#include "libsubsidiary.h"
#include <mach-o/dyld.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <unistd.h>

subsid_err SubsidiaryGenericHookMethodWithError(Class cls, SEL name, IMP imp, IMP *orig) {
 /* we shouldn't need to check cls or name since those should take us to Subsid_NoSel. This does mean that we would have a different error type, but in Unsigncuts we shouldn't care about that */
 if (!imp) {
  return Subsid_InvalidArgs;
 }
 Method hookMethod = class_getInstanceMethod(cls, name);
 if (!hookMethod) {
  return Subsid_NoSel;
 }
 unsigned int numberOfMethods = 0;
 Method *methods = class_copyMethodList(cls, &numberOfMethods);
 for (int i = 0; i < numberOfMethods; i++) {
  Method m = methods[i];
  if (method_getName(m) == name) {
   /* the method is in this class so we can safely replace the method */
   *orig = class_replaceMethod(cls, name, imp, method_getTypeEncoding(hookMethod));
   free(methods);
   return Subsid_Succeed;
  }
 }
 /* the method is in the superclass, add the method instead to not override superclass and get IMP of orig */
 free(methods);
 *orig = method_getImplementation(hookMethod);
 class_addMethod(cls, name, imp, method_getTypeEncoding(hookMethod));
 return Subsid_Succeed;
}
