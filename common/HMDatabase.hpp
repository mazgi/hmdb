//
//  HMDatabase.hpp
//  hmdb
//
//  Created by Matsuki Hidenori on 3/5/13.
//
//

#ifndef __hmdb__HMDatabase__
#define __hmdb__HMDatabase__

#include "hmdb-common.h"
#include <iostream>
#include <map>

namespace hmdb {
    class HMError;
    class HMResultSet;

#ifdef DOXYGEN_LANGUAGE_JAPANESE
    /*!
     @brief Databaseクラス

     ## 概要
     ファイルシステム上の1つのsqlite3ファイルへの操作を抽象化する.

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
        const int CloseRetryLimit = 5;
        const int ExecRetryLimit = 5;
        std::string databasePath_;
        sqlite3 *db_;
#if SQLITE_VERSION_NUMBER >= 3005000
        std::string vfsName_;
        OpenMode mode_;
#endif
        bool inTransaction_;
        bool executingStatement_;
        StatementMap cachedStatements_;
        bool buildStatement(HMError **outError, sqlite3_stmt **outStmt, const char *sql);
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
        HMDatabase(const char *dbPath, int mode = OpenCreate|OpenReadWrite, const char *vfsName = NULL);
#else
#ifdef DOXYGEN_LANGUAGE_JAPANESE
        /*!
         @brief コンストラクタ
         @param dbPath databaseファイルpath
         */
#else
#endif
        HMDatabase(const char *dbPath);
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

        template<class ... Args>
        bool executeQuery(HMError **outError, HMResultSet **outRet, const char *sql, const Args & ... args);

//        template<class ... Args>
//        bool executeQuery(HMError **outError, const char *sql, const Args & ... args)
//        {
//            bool result = executeQuery(outError, nullptr, sql, args ...);
//            return result;
//        }
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
            HMError *err = nullptr;
            bool success = executeQuery(&err, nullptr, "BEGIN EXCLUSIVE TRANSACTION");
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
            HMError *err = nullptr;
            bool success = executeQuery(&err, nullptr, "COMMIT TRANSACTION");
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
            HMError *err = nullptr;
            bool success = executeQuery(&err, nullptr, "ROLLBACK TRANSACTION");
            if (success) {
                inTransaction_ = false;
            }
            return success;
        }
    };
    typedef std::shared_ptr<HMDatabase> HMDatabaseRef;
} /* endof namespace */

#endif /* defined(__hmdb__HMDatabase__) */
