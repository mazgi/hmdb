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
     @brief Database class

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
        bool hasNext(HMError* &outError);
        inline bool hasNext()
        {
            HMError *err = nullptr;
            return hasNext(err);
        }
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

    class HMRecordSet_ {
        HMDatabase *db_;
        sqlite3_stmt *stmt_;
    public:
        bool nextRow(HMError* &outError);
        template<class T>
        const T& valueForColumnName(const char* name);
        template<class T>
        const T& valueForColumnIndex(const int index);

        
        int intForColumn(const char* columnName);
        int intForColumn(const int columnIndex);
        double doubleForColumn(const char* columnName);
        double doubleForColumn(const int columnIndex);
        long longForColumn(const char* columnName);
        long longForColumn(const int columnIndex);
        std::string stringForColumn(const char* columnName);
        std::string stringForColumn(const int columnIndex);
        blob blobForColumn(const char* columnName);
        blob blobForColumn(const int columnIndex);
    };
} /* endof namespace */

#endif /* defined(__hmdb__HMResultSet__) */
