/*
 *  hmdbosx.cp
 *  hmdbosx
 *
 *  Created by matsuki hidenori on 3/27/13.
 *
 *
 */

#include <iostream>
#include "hmdbosx.h"
#include "hmdbosxPriv.h"

void hmdbosx::HelloWorld(const char * s)
{
	 hmdbosxPriv *theObj = new hmdbosxPriv;
	 theObj->HelloWorldPriv(s);
	 delete theObj;
};

void hmdbosxPriv::HelloWorldPriv(const char * s) 
{
	std::cout << s << std::endl;
};

