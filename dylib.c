#include <objc/runtime.h>

typedef struct objc_selector *SEL;

static unsigned char hook_WFShortcutExtractor_allowsOldFormatFile(void) {
 return 0x1;
}

__attribute__((constructor)) static void init() {
 Class cls = objc_getClass("WFShortcutExtractor"); /* wrapper around look_up_class */
 SEL name = sel_getUid("allowsOldFormatFile"); /* perhaps this can be done via dyld_get_objc_selector ? */
 Method meth = class_getInstanceMethod(cls, name);
 IMP imp = (IMP)&hook_WFShortcutExtractor_allowsOldFormatFile;
 method_setImplementation(meth, imp); /* this function already checks meth for nil so this is safe */
}