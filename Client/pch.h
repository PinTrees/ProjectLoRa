#pragma once

#include <Windows.h>
#include <iostream>
#include <future>

#include <utility>
#include <typeinfo>

#include <vector>
#include <array>
using std::vector;
using std::array;

#include <map>	
using std::map;
using std::make_pair;

#include<unordered_map>
using std::unordered_map;

#include <list>
using std::list;

#include <string>
using std::wstring;
using std::string;

#include <sstream>
using std::wstringstream;

#include <fstream>
#include <tchar.h>

#include <math.h>
#include <cmath>
#include <assert.h>

#include <memory>		
#include <algorithm>	

#pragma comment(lib,"Msimg32.lib")


// Custom Define Header
#include "define.h"
#include "register.h"
#include "type_define.h"


// Custom [ Class, Struct ] Header
#include "Vec2.h"
#include "func.h"

// GDI+
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;


#include "CSystemMgr.h"
