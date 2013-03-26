//
//  testHMDatabase.cpp
//  hmdb
//
//  Created by matsuki hidenori on 3/26/13.
//
//

#include "gtest/gtest.h"
#include "hmdb.hpp"

TEST(DBTest, test1)
{
    hmdb::HMDatabase* db = new hmdb::HMDatabase("/cannotaccess/null");
    ASSERT_FALSE(db->open());
}
