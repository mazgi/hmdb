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
#else
    /*!
     @brief Database class

     ## About

     ## Features

     */
#endif
    class HMDatabase {
    public:
        typedef enum {
            OpenReadOnly,
            OpenReadWrite,
            OpenCreate,
            
            OpenModeKeyAll
        } OpenModeKey;
        typedef std::bitset<OpenModeKeyAll> OpenMode;
    private:
        typedef std::map<std::string, sqlite3_stmt*> StatementMap;
        std::string databasePath_;
        sqlite3* db_;
#if SQLITE_VERSION_NUMBER >= 3005000
        std::string vfsName_;
        OpenMode mode_;
#endif
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
#if SQLITE_VERSION_NUMBER >= 3005000
#ifdef DOXYGEN_LANGUAGE_JAPANESE
        /*!
         @brief コンストラクタ
         @param dbPath databaseファイルpath
         @param mode モード
         @param vfsName VFS名
         */
#else
#endif
        HMDatabase(const char* dbPath, int mode = OpenCreate|OpenReadWrite, const char* vfsName = NULL);
#else
#ifdef DOXYGEN_LANGUAGE_JAPANESE
        /*!
         @brief コンストラクタ
         @param dbPath databaseファイルpath
         */
#else
#endif
        HMDatabase(const char* dbPath);
#endif
#ifdef DOXYGEN_LANGUAGE_JAPANESE
        /*!
         @brief デストラクタ
         */
#else
#endif
        ~HMDatabase();
#ifdef DOXYGEN_LANGUAGE_JAPANESE
        /*!
         @brief databaseファイルを開く
         @result 成功すればtrue
         */
#else
#endif
        bool open();
#ifdef DOXYGEN_LANGUAGE_JAPANESE
        /*!
         @brief databaseファイルを閉じる
         @result 成功すればtrue
         */
#else
#endif
        bool close();
#if !HMDB_CXX_FEATURE_CXX_VARIADIC_TEMPLATES
        bool executeQuery(HMError* &outError, const char* sql)
        {
#pragma warning Impl.
            return false;
        }
#endif
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
#endif
#if HMDB_CXX_FEATURE_CXX_VARIADIC_TEMPLATES
        template<class ... Args>
        bool executeQuery(HMError* &outError, const char* sql, const Args & ... args)
        {
            HMRecordReader *outRet = nullptr;
            bool result = executeQueryForRead(outError, outRet, sql, args ...);
            if (!result) {
                return result;
            }
            while (outRet->next(outError)) {
                //TODO: log
            }
            return result;
        }
#endif
#ifdef DOXYGEN_LANGUAGE_JAPANESE
        /*!
         @brief トランザクションを開始する
         @result 成功すればtrue
         */
#else
#endif
        bool beginTransaction()
        {
            if (inTransaction_) {
                return false;
            }
            HMError* err = HMDB_NULL;
            bool success = executeQuery(err, "BEGIN EXCLUSIVE TRANSACTION");
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
#else
#endif
        bool commitTransaction()
        {
            if (!inTransaction_) {
                return false;
            }
            HMError* err = HMDB_NULL;
            bool success = executeQuery(err, "COMMIT TRANSACTION");
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
#else
#endif
        bool rollbackTransaction()
        {
            if (!inTransaction_) {
                return false;
            }
            HMError* err = HMDB_NULL;
            bool success = executeQuery(err, "ROLLBACK TRANSACTION");
            if (success) {
                inTransaction_ = false;
            }
            return success;
        }
    };
} /* endof namespace */

#endif /* defined(__hmdb__HMDatabase__) */
