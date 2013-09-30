//
//  HMDatabase.hpp
//  hmdb
//
//  Created by Matsuki Hidenori on 3/5/13.
//
//

#ifndef __hmdb__HMDatabase__
#define __hmdb__HMDatabase__

#include "hmdb-common.hpp"
#include <iostream>
#include <bitset>
#include <map>
#include <utility>
#include "HMRecordSet.hpp"

namespace hmdb {
#if HMDB_CXX_DIALECT_CXX11
    typedef std::shared_ptr<HMDatabase> HMDatabaseRef;
    typedef std::shared_ptr<HMError> HMErrorRef;
    typedef std::shared_ptr<HMRecordReader> HMRecordReaderRef;
#endif
    class HMError;
    class HMRecordReader;

#ifdef DOXYGEN_LANGUAGE_JAPANESE
    /*!
     @brief Databaseクラス

     ## 概要
     ファイルシステム上の1つのsqlite3ファイルへの操作を抽象化する.
     
     ### ライフサイクルと所有権
     - このクラスはアクティブなステートメントリストを所有する
     - このクラスは結果セットのReaderを所有しない

     ## 機能

     ### このクラスが扱うこと
     - クエリ発行
     - データベースのオープン／クローズ
     - トランザクションの開始／コミット／ロールバック

     ### このクラスが扱わないこと
     - エラーコード／エラーメッセージの管理
     - クエリ実行結果の操作
     
     */
#else /* } DOXYGEN_LANGUAGE { */
    /*!
     @brief Database class

     ## About

     ## Features

     */
#endif /* } DOXYGEN_LANGUAGE */
    class HMDatabase {
    public:
#pragma mark - public members
#ifdef DOXYGEN_LANGUAGE_JAPANESE
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        typedef enum {
            OpenReadOnly,
            OpenReadWrite,
            OpenCreate,
            
            OpenModeKeyAll
        } OpenModeKey;
#ifdef DOXYGEN_LANGUAGE_JAPANESE
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        typedef std::bitset<OpenModeKeyAll> OpenMode;
    private:
#pragma mark - private members
        typedef std::map<std::string, sqlite3_stmt*> StatementMap;
        std::string databasePath_;
        sqlite3* db_;
#if SQLITE_VERSION_NUMBER >= 3005000
        std::string vfsName_;
        OpenMode mode_;
#endif /* } SQLITE_VERSION_NUMBER */
        bool inTransaction_;
        bool executingStatement_;
        StatementMap cachedStatements_;
        bool buildStatement(HMError* &outError, sqlite3_stmt* &outStmt, const char* sql);
        bool bindParameterValue(HMError* &outError, sqlite3_stmt *&stmt, const int replacementCount, int &index)
        {
            /* do nothing */
            return true;
        }

        //TODO: map<class, func*>でいけない？
        bool bindParameterValue(HMError* &outError, sqlite3_stmt *&stmt, const int replacementCount, int &index, const double value)
        {
            int result = sqlite3_bind_double(stmt, ++index, value);
            if (result != SQLITE_OK) {
                //TODO: err
                return false;
            }
            return true;
        }

        bool bindParameterValue(HMError* &outError, sqlite3_stmt *&stmt, const int replacementCount, int &index, const int value)
        {
            int result = sqlite3_bind_int(stmt, ++index, value);
            if (result != SQLITE_OK) {
                //TODO: err
                return false;
            }
            return true;
        }

        bool bindParameterValue(HMError* &outError, sqlite3_stmt *&stmt, const int replacementCount, int &index, const char* value)
        {
            //If the fourth parameter to sqlite3_bind_text() or sqlite3_bind_text16() is negative, then the length of the string is the number of bytes up to the first zero terminator.
            //The fifth argument to sqlite3_bind_blob(), sqlite3_bind_text(), and sqlite3_bind_text16() is a destructor used to dispose of the BLOB or string after SQLite has finished with it. The destructor is called to dispose of the BLOB or string even if the call to sqlite3_bind_blob(), sqlite3_bind_text(), or sqlite3_bind_text16() fails. If the fifth argument is the special value SQLITE_STATIC, then SQLite assumes that the information is in static, unmanaged space and does not need to be freed. If the fifth argument has the value SQLITE_TRANSIENT, then SQLite makes its own private copy of the data immediately, before the sqlite3_bind_*() routine returns.
            //These are special values for the destructor that is passed in as the final argument to routines like sqlite3_result_blob(). If the destructor argument is SQLITE_STATIC, it means that the content pointer is constant and will never change. It does not need to be destroyed. The SQLITE_TRANSIENT value means that the content will likely change in the near future and that SQLite should make its own private copy of the content before returning.
            int result = sqlite3_bind_text(stmt, ++index, value, -1, SQLITE_TRANSIENT);
            if (result != SQLITE_OK) {
                //TODO: err
                return false;
            }
            return true;
        }

        bool bindParameterValue(HMError* &outError, sqlite3_stmt *&stmt, const int replacementCount, int &index, const std::string &value)
        {
            int result = sqlite3_bind_text(stmt, ++index, value.c_str(), -1, SQLITE_TRANSIENT);
            if (result != SQLITE_OK) {
                //TODO: err
                return false;
            }
            return true;
        }

        template<class First>
        bool bindParameterValue(HMError* &outError, sqlite3_stmt *&stmt, const int replacementCount, int &index, const First &value)
        {
            int result = SQLITE_OK;
            if (typeid(value) == typeid(HMDB_NULL)) {
                sqlite3_bind_null(stmt, ++index);
            } else {
                //undefined value (or blob or int64)
                sqlite3_bind_null(stmt, ++index);
            }
            if (result != SQLITE_OK) {
                //TODO: err
                return false;
            }
            return true;
        }
#if HMDB_CXX_FEATURE_CXX_VARIADIC_TEMPLATES
        template<class First, class ... Rest>
        bool bindParameterValue(HMError* &outError, sqlite3_stmt *&stmt, const int replacementCount, int &index, const First &first, const Rest & ... rest)
        {
            return bindParameterValue(outError, stmt, replacementCount, index, first)
            && bindParameterValue(outError, stmt, replacementCount, index, rest ...);
        }
#endif
    public:
#pragma mark - public members
#if SQLITE_VERSION_NUMBER >= 3005000
#ifdef DOXYGEN_LANGUAGE_JAPANESE
        /*!
         @brief コンストラクタ
         @param dbPath databaseファイルpath
         @param mode モード
         @param vfsName VFS名
         */
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        HMDatabase(const char* dbPath, int mode = OpenCreate|OpenReadWrite, const char* vfsName = NULL);
#else /* } SQLITE_VERSION_NUMBER { */
#ifdef DOXYGEN_LANGUAGE_JAPANESE
        /*!
         @brief コンストラクタ
         @param dbPath databaseファイルpath
         */
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        HMDatabase(const char* dbPath);
#endif /* } SQLITE_VERSION_NUMBER */
#ifdef DOXYGEN_LANGUAGE_JAPANESE
        /*!
         @brief デストラクタ
         */
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        ~HMDatabase();
#ifdef DOXYGEN_LANGUAGE_JAPANESE
        /*!
         @brief databaseファイルを開く
         @result 成功すればtrue
         */
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        bool open();
#ifdef DOXYGEN_LANGUAGE_JAPANESE
        /*!
         @brief databaseファイルを閉じる
         @result 成功すればtrue
         */
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        bool close();
#if HMDB_CXX_FEATURE_CXX_VARIADIC_TEMPLATES
        template<class ... Args>
        bool executeQueryForRead(HMError* &outError, HMRecordReader* &outRet, const char* sql, const Args & ... args)
        {
            if (executingStatement_) {
                //TODO: err
                return false;
            }
            //TODO: semaphore
            executingStatement_ = true;

            // load/build statement
            HMError *buildStmtErr = nullptr;
            sqlite3_stmt *stmt = NULL;
            bool buildStmtSuccess = buildStatement(buildStmtErr, stmt, sql);
            if (!buildStmtSuccess) {
                //TODO: err
                return false;
            }

            // bind parameter values to statement
            const int replacementCount = sqlite3_bind_parameter_count(stmt);
            int replacementIndex = 0;
            bool bindParameterSuccess = bindParameterValue(outError, stmt, replacementCount, replacementIndex, args ...);
            if (!bindParameterSuccess) {
                //TODO: err
                return false;
            }

            // execute statement
            outRet = new HMRecordReader(stmt);

//            sqlite3_finalize(stmt);

            executingStatement_ = false;
            return true;
        }
        template<class ... Args>
        bool executeQuery(HMError* &outError, const char* sql, const Args & ... args)
        {
            HMRecordReader *outRet = HMDB_NULL;
            bool result = executeQueryForRead(outError, outRet, sql, args ...);
            if (!result) {
                return result;
            }
            while (outRet->next(outError)) {
                //TODO: log
            }
            return result;
        }
#endif /* } HMDB_CXX_FEATURE_CXX_VARIADIC_TEMPLATES */

#ifdef DOXYGEN_LANGUAGE_JAPANESE
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        bool executeFormattedQueryForRead(HMError* &outError, HMRecordReader* &outRet, const char* format, va_list args);
        
#ifdef DOXYGEN_LANGUAGE_JAPANESE
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        bool executeFormattedQueryForRead(HMError* &outError, HMRecordReader* &outRet, const char* format, ...)
        {
            va_list args;
            va_start(args, format);
            bool result = executeFormattedQueryForRead(outError, outRet, format, args);
            va_end(args);
            return result;
        }

#ifdef DOXYGEN_LANGUAGE_JAPANESE
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        bool executeFormattedQuery(HMError* &outError, const char* format, ...)
        {
            HMRecordReader *outRet = HMDB_NULL;
            va_list args;
            va_start(args, format);
            bool result = executeFormattedQueryForRead(outError, outRet, format, args);
            va_end(args);
            if (!result) {
                return result;
            }
            while (outRet->next(outError)) {
                //TODO: log
            }
            return result;
        }

#ifdef DOXYGEN_LANGUAGE_JAPANESE
        /*!
         @brief トランザクションを開始する
         @result 成功すればtrue
         */
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        bool beginTransaction()
        {
            if (inTransaction_) {
                return false;
            }
            HMError* err = HMDB_NULL;
            bool success = false;
#if HMDB_CXX_FEATURE_CXX_VARIADIC_TEMPLATES
            success = executeQuery(err, "BEGIN EXCLUSIVE TRANSACTION");
#else /* } HMDB_CXX_FEATURE_CXX_VARIADIC_TEMPLATES { */
            success = executeFormattedQuery(err, "BEGIN EXCLUSIVE TRANSACTION");
#endif /* } HMDB_CXX_FEATURE_CXX_VARIADIC_TEMPLATES */
            if (success) {
                inTransaction_ = true;
            }
            return success;
        }
#ifdef DOXYGEN_LANGUAGE_JAPANESE
        /*!
         @brief トランザクションをコミットする
         @result 成功すればtrue
         */
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        bool commitTransaction()
        {
            if (!inTransaction_) {
                return false;
            }
            HMError* err = HMDB_NULL;
            bool success = false;
#if HMDB_CXX_FEATURE_CXX_VARIADIC_TEMPLATES
            success = executeQuery(err, "COMMIT TRANSACTION");
#else /* } HMDB_CXX_FEATURE_CXX_VARIADIC_TEMPLATES { */
            success = executeFormattedQuery(err, "COMMIT TRANSACTION");
#endif /* } HMDB_CXX_FEATURE_CXX_VARIADIC_TEMPLATES */
            if (success) {
                inTransaction_ = false;
            }
            return success;
        }
#ifdef DOXYGEN_LANGUAGE_JAPANESE
        /*!
         @brief トランザクションをロールバックする
         @result 成功すればtrue
         */
#else /* } DOXYGEN_LANGUAGE { */
#endif /* } DOXYGEN_LANGUAGE */
        bool rollbackTransaction()
        {
            if (!inTransaction_) {
                return false;
            }
            HMError* err = HMDB_NULL;
            bool success = false;
#if HMDB_CXX_FEATURE_CXX_VARIADIC_TEMPLATES
            success = executeQuery(err, "ROLLBACK TRANSACTION");
#else /* } HMDB_CXX_FEATURE_CXX_VARIADIC_TEMPLATES { */
            success = executeFormattedQuery(err, "ROLLBACK TRANSACTION");
#endif /* } HMDB_CXX_FEATURE_CXX_VARIADIC_TEMPLATES */
            if (success) {
                inTransaction_ = false;
            }
            return success;
        }
    };
} /* endof namespace */

#endif /* defined(__hmdb__HMDatabase__) */
