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
#include <algorithm>

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
#else /* } DOXYGEN_LANGUAGE { */
    /*!
     @brief Records reader class

     ## About

     ## Features
     
     */
#endif /* } DOXYGEN_LANGUAGE */
    class HMRecordReader {
        sqlite3_stmt* stmt_;
        std::vector<std::string> fieldNames;
    public:
#ifdef DOXYGEN_LANGUAGE_JAPANESE
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        HMRecordReader(sqlite3_stmt* &stmt);
#ifdef DOXYGEN_LANGUAGE_JAPANESE
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        bool next(HMError* &outError);
#ifdef DOXYGEN_LANGUAGE_JAPANESE
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        inline bool next()
        {
            HMError *err = HMDB_NULL;
            return next(err);
        }
#ifdef DOXYGEN_LANGUAGE_JAPANESE
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        bool isNull(const int index)
        {
            return sqlite3_column_type(stmt_, index) == SQLITE_NULL;
        }
#ifdef DOXYGEN_LANGUAGE_JAPANESE
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        bool isNull(const char* fieldName)
        {
            std::vector<std::string>::iterator it = std::find(fieldNames.begin(), fieldNames.end(), fieldName);
            size_t index = std::distance(fieldNames.begin(), it);
            if (index >= fieldNames.size()) {
                return (double)NULL;
            }
            return sqlite3_column_type(stmt_, (int)index) == SQLITE_NULL;
        }
#ifdef DOXYGEN_LANGUAGE_JAPANESE
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        double doubleValue(const int index)
        {
            return sqlite3_column_double(stmt_, index);
        }
#ifdef DOXYGEN_LANGUAGE_JAPANESE
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        double doubleValue(const char* fieldName)
        {
            std::vector<std::string>::iterator it = std::find(fieldNames.begin(), fieldNames.end(), fieldName);
            size_t index = std::distance(fieldNames.begin(), it);
            if (index >= fieldNames.size()) {
                return (double)NULL;
            }
            return doubleValue((int)index);
        }
#ifdef DOXYGEN_LANGUAGE_JAPANESE
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        int intValue(const int index)
        {
            return sqlite3_column_int(stmt_, index);
        }
#ifdef DOXYGEN_LANGUAGE_JAPANESE
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        int intValue(const char* fieldName)
        {
            std::vector<std::string>::iterator it = std::find(fieldNames.begin(), fieldNames.end(), fieldName);
            size_t index = std::distance(fieldNames.begin(), it);
            if (index >= fieldNames.size()) {
                return (int)NULL;
            }
            return intValue((int)index);
        }
#ifdef DOXYGEN_LANGUAGE_JAPANESE
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        const char* textValue(const int index)
        {
            return reinterpret_cast<const char*>(sqlite3_column_text(stmt_, index));
        }
#ifdef DOXYGEN_LANGUAGE_JAPANESE
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
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
