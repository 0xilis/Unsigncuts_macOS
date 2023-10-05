#include <stdio.h>
#include <spawn.h>
#include <stdlib.h> /* malloc() */
#include <string.h> /* strlen() */

#include "libsubsidiary/libsubsidiary.h"

#include <objc/runtime.h>
#include <objc/message.h>

typedef void WFShortcutExtractor;

typedef struct objc_selector *SEL;

static unsigned char (*orig_WFShortcutExtractor_allowsOldFormatFile)(WFShortcutExtractor *self, SEL cmd);

static unsigned char hook_WFShortcutExtractor_allowsOldFormatFile(void) {
 return 0x1;
}

__attribute__((constructor)) static void init() {
 printf("hello from dylib.c!\n");
 subsid_err err = SubsidiaryGenericHookMethodWithError(objc_getClass("WFShortcutExtractor"), sel_getUid("allowsOldFormatFile"), (IMP)&hook_WFShortcutExtractor_allowsOldFormatFile, (IMP *)&orig_WFShortcutExtractor_allowsOldFormatFile);
 if (err) {
  printf("error hooking\n");
 } else {
  printf("hooked!!!!\n");
 }
}