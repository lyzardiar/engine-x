/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "cocos2d.h"
#include "AppDelegate.h"
#include "base/CCScriptSupport.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "lua_assetsmanager_test_sample.h"
#include "scripting/lua-bindings/manual/lua_module_register.h"
#include "lua_test_bindings.h"

#include "gameai/maths/Double.hpp"

USING_NS_CC;

AppDelegate::AppDelegate()
{
    // fixed me
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
}

AppDelegate::~AppDelegate()
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};
    
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // register lua engine
    LuaEngine* engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    lua_State* L = engine->getLuaStack()->getLuaState();
    lua_module_register(L);

    lua_getglobal(L, "_G");
    if (lua_istable(L,-1))//stack:...,_G,
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ||CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        register_assetsmanager_test_sample(L);
#endif
        register_test_binding(L);
    }
    lua_pop(L, 1);
	
    //The call was commented because it will lead to ZeroBrane Studio can't find correct context when debugging
    //engine->executeScriptFile("src/hello.lua");
    
    CCLOG("4.9406564584124654E-324: 0x%llx   0x0000000000000001", Double.doubleToLongBits(4.9406564584124654E-324));

    CCLOG("1.2345678901234569E+150: 0x%llx   0x5F182344CD3CDF9F", Double.doubleToLongBits(1.2345678901234569E+150));
    CCLOG("1.2345678901234569E+300: 0x%llx   0x7E3D7EE8BCBBD352", Double.doubleToLongBits(1.2345678901234569E+300));

    CCLOG("                    NaN: 0x%llx  0xFFF8000000000000", Double.doubleToLongBits(NAN));
    CCLOG("              -Infinity: 0x%llx  0xFFF0000000000000", Double.doubleToLongBits(-INFINITY));
    CCLOG("               Infinity: 0x%llx  0x7FF0000000000000", Double.doubleToLongBits(INFINITY));

    CCLOG("0x41EFFFFFFFE00000: %f   4.2949672950000000E+009", Double.longBitsToDouble(0x41EFFFFFFFE00000LL));
    CCLOG("0xFFFFFFFFFFFFFFFF: %f  NaN", Double.longBitsToDouble(0xFFFFFFFFFFFFFFFFLL));
    CCLOG("0xFFF0000000000000: %f  -Infinity", Double.longBitsToDouble(0xFFF0000000000000LL));
    CCLOG("0x7FF0000000000000: %f  Infinity", Double.longBitsToDouble(0x7FF0000000000000LL));


    CCLOG("MAX_VALUE: %f", Double.MAX_VALUE);
    CCLOG("MIN_VALUE: %f", Double.MIN_VALUE);

#if CC_64BITS
    FileUtils::getInstance()->addSearchPath("tools/64bit");
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
    FileUtils::getInstance()->setPopupNotify(false);

    FileUtils::getInstance()->addSearchPath("../src");
    FileUtils::getInstance()->addSearchPath("../res");
#elif 
    FileUtils::getInstance()->addSearchPath("src");
    FileUtils::getInstance()->addSearchPath("res");
#endif

    engine->executeString("require 'main.lua'");

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
}
