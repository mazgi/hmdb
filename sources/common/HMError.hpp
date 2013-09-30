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
#ifdef DOXYGEN_LANGUAGE_JAPANESE
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
    class HMError {
        int code_;
        std::string description_;
        void code(int newCode) { code_ = newCode; }
        void description(std::string newDescription) { description_ = newDescription; }
    public:
#ifdef DOXYGEN_LANGUAGE_JAPANESE
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        int code() { return code_; }
#ifdef DOXYGEN_LANGUAGE_JAPANESE
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        const std::string description() { return description_; }
    };
} /* endof namespace */

#endif /* defined(__hmdb__HMError__) */
