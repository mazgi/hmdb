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
        template<class T>
        const T& value(const char* fieldName)
        {
            return nullptr;
        }
        template<class T>
        const T& operator[](int fieldIndex)
        {
            return nullptr;
        }
    };
} /* endof namespace */

#endif /* defined(__hmdb__HMResultSet__) */
