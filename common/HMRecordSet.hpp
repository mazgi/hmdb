//
//  HMResultSet.h
//  hmdb
//
//  Created by Matsuki Hidenori on 3/5/13.
//
//

#ifndef __hmdb__HMResultSet__
#define __hmdb__HMResultSet__

#include <iostream>
#include <vector>
#include <map>
#include <typeinfo>

namespace hmdb {
    class HMError;
    class HMDatabase;
    
    typedef std::basic_string<u_int8_t> blob;

#ifdef DOXYGEN_LANGUAGE_JAPANESE
    /*!
     @brief Recordの集合を表すクラス

     ## 概要
     複数の結果レコードへの操作を抽象化する.

     ## 機能

     ### このクラスが扱うこと
     - レコードを進める
     - レコードオブジェクトの取得

     ### このクラスが扱わないこと
     - エラーコード／エラーメッセージの管理
     - レコードを戻す
     - レコードへの値の書き込み
     - レコードフィールドの操作

     */
#else
    /*!
     @brief Records reader class

     ## About

     ## Features
     
     */
#endif
    class HMRecordReader {
        const int ExecRetryLimit = 5;
        sqlite3_stmt* stmt_;
        std::vector<std::string> fieldNames;
    public:
        HMRecordReader(sqlite3_stmt* &stmt);
        bool next(HMError* &outError);
        inline bool next()
        {
            HMError *err = nullptr;
            return next(err);
        }
        const double doubleValue(const int index)
        {
            return sqlite3_column_double(stmt_, index);
        }
        const double doubleValue(const char* fieldName)
        {
            std::vector<std::string>::iterator it = std::find(fieldNames.begin(), fieldNames.end(), fieldName);
            size_t index = std::distance(fieldNames.begin(), it);
            if (index >= fieldNames.size()) {
                return NULL;
            }
            return doubleValue((int)index);
        }
        const int intValue(const int index)
        {
            return sqlite3_column_int(stmt_, index);
        }
        const int intValue(const char* fieldName)
        {
            std::vector<std::string>::iterator it = std::find(fieldNames.begin(), fieldNames.end(), fieldName);
            size_t index = std::distance(fieldNames.begin(), it);
            if (index >= fieldNames.size()) {
                return NULL;
            }
            return intValue((int)index);
        }
        const char* textValue(const int index)
        {
            return reinterpret_cast<const char*>(sqlite3_column_text(stmt_, index));
        }
        const char* textValue(const char* fieldName)
        {
            std::vector<std::string>::iterator it = std::find(fieldNames.begin(), fieldNames.end(), fieldName);
            size_t index = std::distance(fieldNames.begin(), it);
            if (index >= fieldNames.size()) {
                return NULL;
            }
            return textValue((int)index);
        }
    };
} /* endof namespace */

#endif /* defined(__hmdb__HMResultSet__) */
