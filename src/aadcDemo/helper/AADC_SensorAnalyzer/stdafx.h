/**
Copyright (c)
Audi Autonomous Driving Cup. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
3.  All advertising materials mentioning features or use of this software must display the following acknowledgement: �This product includes software developed by the Audi AG and its contributors for Audi Autonomous Driving Cup.�
4.  Neither the name of Audi nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY AUDI AG AND CONTRIBUTORS �AS IS� AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL AUDI AG OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


**********************************************************************
* $Author:: spiesra $  $Date:: 2017-05-12 09:39:39#$ $Rev:: 63110   $
**********************************************************************/

#ifndef __STD_INCLUDES_HEADER
#define __STD_INCLUDES_HEADER

//fix gcc 5 error, using c++11 for std ABI. see:http://stackoverflow.com/questions/33394934/converting-std-cxx11string-to-stdstring/33395489
#define _GLIBCXX_USE_CXX11_ABI 0

#include <adtf_platform_inc.h>
#include <adtf_plugin_sdk.h>
using namespace adtf;

#include <adtf_graphics.h>
using namespace adtf_graphics;

#include "aadc_geometrics.h"

#include <QtGui/QtGui>
#include <QtCore/QtCore>

#ifdef WIN32
#ifdef _DEBUG
#pragma comment(lib, "qtmaind.lib")
#pragma comment(lib, "qtcored4.lib")
#pragma comment(lib, "qtguid4.lib")
#else // _DEBUG
#pragma comment(lib, "qtmain.lib")
#pragma comment(lib, "qtcore4.lib")
#pragma comment(lib, "qtgui4.lib")
#endif
#endif

#endif // __STD_INCLUDES_HEADER


