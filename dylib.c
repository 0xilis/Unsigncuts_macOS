#include <stdio.h>
#include <objc/runtime.h>

typedef struct objc_selector *SEL;

static unsigned char hook_WFShortcutExtractor_allowsOldFormatFile(void) {
 return 0x1;
}

__attribute__((constructor)) static void init() {
 Class cls = objc_getClass("WFShortcutExtractor");
 SEL name = sel_getUid("allowsOldFormatFile");
 Method meth = class_getInstanceMethod(cls, name);
 if (!meth) {
  return;
 }
 IMP imp = (IMP)&hook_WFShortcutExtractor_allowsOldFormatFile;
 method_setImplementation(meth, imp);
}