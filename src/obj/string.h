//
// Created by 曹顺 on 2019/2/13.
//

#ifndef HYPERMIND_STRING_H
#define HYPERMIND_STRING_H

#include <hypermind.h>
#include "vm.h"
#include "object.h"
#include "utils.h"

namespace hypermind {
    HM_OBJECT(String) {
        HMHash hashCode;
        HMUINT32 length;
        HMChar *charSequence{nullptr};
        HM_OBJ_CONSTRUCTOR(String, const HMChar *str, HMUINT32 len), length(len) {
            charSequence = vm->Allocate<HMChar>(length + 1);
            // 计算文本hash
            if (charSequence != nullptr) {
                hm_memcpy(charSequence, str, length);
                hashCode = hashString(charSequence, length);
                charSequence[length] = '\0';
            } else {
                MEMRY_ERROR("文本对象申请内存失败");
            }
        }
        HM_OBJ_CONSTRUCTOR(String, const HMChar *str), length(hm_strlen(str)) {
            // 计算文本hash
            charSequence = vm->Allocate<HMChar>(length + 1);
            if (charSequence != nullptr) {
                hm_memcpy(charSequence, str, length);
                hashCode = hashString(charSequence, length);
                charSequence[length] = '\0';
            } else {
                MEMRY_ERROR("文本对象申请内存失败");
            }
        }
        HM_OBJ_DECL();

        HMBool equals(HMObject *object) override {
            if (object->type != ObjectType::String)
                return false;
            if (this == object) {
                return true;
            }
            auto *str = (HMString *)object;
            if (length == 0 && str->length == 0) {
                return true;
            }
            if (str->length == length && hm_memcmp(str->charSequence, charSequence, length) == 0) {
                return true;
            }
            return HMObject::equals(object);
        }
    };

}

#endif //HYPERMIND_STRING_H
