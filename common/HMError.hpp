//
//  HMError.h
//  hmdb
//
//  Created by Matsuki Hidenori on 3/14/13.
//
//

#ifndef __hmdb__HMError__
#define __hmdb__HMError__

#include <iostream>

namespace hmdb {
    class HMError {
        int code_;
        std::string description_;
        void code(int newCode) { code_ = newCode; }
        void description(std::string newDescription) { description_ = newDescription; }
    public:
        int code() { return code_; }
        const std::string description() { return description_; }
    };
} /* endof namespace */

#endif /* defined(__hmdb__HMError__) */
