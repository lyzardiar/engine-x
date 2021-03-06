cmake_minimum_required(VERSION 3.6)

set(APP_NAME FiveWar)

project(${APP_NAME})

if(NOT DEFINED BUILD_ENGINE_DONE)
    set(ENGINEX_ROOT "$ENV{ENGINEX_ROOT}")
    if(ENGINEX_ROOT STREQUAL "")
        set(ENGINEX_ROOT "$ENV{COCOS2DX_ROOT}")
    endif()

    if(NOT (ENGINEX_ROOT STREQUAL ""))
        set(COCOS2DX_ROOT_PATH "${ENGINEX_ROOT}")
        file(TO_CMAKE_PATH ${COCOS2DX_ROOT_PATH} COCOS2DX_ROOT_PATH) # string(REPLACE "\\" "/" COCOS2DX_ROOT_PATH ${COCOS2DX_ROOT_PATH})
        message(STATUS "Using system env var ENGINEX_ROOT=${ENGINEX_ROOT}")
    else()
        set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
    endif()

    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    include(CocosBuildSet)
    set(BUILD_LUA_LIBS ON)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
endif()

set(res_res_folders
    "${CMAKE_CURRENT_SOURCE_DIR}/../res"
    )
set(res_src_folders
    "${CMAKE_CURRENT_SOURCE_DIR}/../src"
    )
set(res_script_folders
    "${COCOS2DX_ROOT_PATH}/extensions/scripting/lua-bindings/script"
    )
if(APPLE OR VS)
#    cocos_mark_multi_resources(res_res RES_TO "Resources/res" FOLDERS ${res_res_folders})
#    cocos_mark_multi_resources(res_src RES_TO "Resources/src" FOLDERS ${res_src_folders})
#    cocos_mark_multi_resources(res_script RES_TO "Resources/src/cocos" FOLDERS ${res_script_folders})

#    set(cc_common_res ${res_res} ${res_src} ${res_script})
    set(cc_common_res ${res_res_folders} ${res_src_folders})
endif()

# record sources, headers...
set(GAME_SOURCE
    Classes/AppDelegate.cpp
    Classes/lua_assetsmanager_test_sample.cpp
    Classes/lua_test_bindings.cpp
    Classes/gameai/maths/Double.cpp
    )
set(GAME_HEADER
    Classes/AppDelegate.h
    Classes/lua_test_bindings.h
    Classes/lua_assetsmanager_test_sample.h
    Classes/gameai/maths/Double.hpp
    Classes/gameai/maths/Vector2D.hpp
    Classes/gameai/World.hpp
    Classes/gameai/entities/Vehicle.hpp
    Classes/gameai/maths/Triangulator.hpp
    Classes/gameai/maths/Transformations.hpp
    Classes/gameai/fsm/Telegram.hpp
    Classes/gameai/entities/MovingEntity.hpp
    Classes/gameai/maths/Matrix2D.hpp
    Classes/gameai/entityshapes/ps/Hints.hpp
    Classes/gameai/graph/Graph.hpp
    Classes/gameai/maths/Geometry2D.hpp
    Classes/gameai/maths/FastMath.hpp
    Classes/gameai/Domain.hpp
    Classes/gameai/entityshapes/ps/BitmapPic.hpp
    Classes/gameai/steering/AutoPilot.hpp
    Classes/gameai/base/Serializable.hpp
    Classes/gameai/utils/StopWatch.hpp
    Classes/gameai/utils/ForceRecorder.hpp
    Classes/gameai/steering/SBF.hpp
    Classes/gameai/graph/GraphSearch_BFS.hpp
    Classes/gameai/entityshapes/ps/WallPic.hpp
    Classes/gameai/entityshapes/ps/ObstaclePic.hpp
    Classes/gameai/entityshapes/ps/BuildingPic.hpp
    Classes/gameai/entities/Wall.hpp
    Classes/gameai/entities/Building.hpp
    Classes/gameai/utils/ObstacleSAXParser.hpp
    Classes/gameai/utils/EntitySAXParser.hpp
    Classes/gameai/utils/VehicleSAXParser.hpp
    Classes/gameai/utils/Message.hpp
    Classes/gameai/utils/GraphSAXParser.hpp
    Classes/gameai/steering/SmootherVector2D.hpp
    Classes/gameai/utils/BuildingSAXParser.hpp
    Classes/gameai/maths/MathUtils.hpp
    Classes/gameai/graph/IGraphSearch.hpp
    Classes/gameai/graph/GraphSearch_Astar.hpp
    Classes/gameai/graph/AstarHeuristic.hpp
    Classes/gameai/fsm/State.hpp
    Classes/gameai/entityshapes/ps/Umbrella.hpp
    Classes/gameai/graph/GraphSearch_DFS.hpp
    Classes/gameai/graph/GraphEdge.hpp
    Classes/gameai/graph/AshCrowFlight.hpp
    Classes/gameai/graph/GraphSearch_Dijkstra.hpp
    Classes/gameai/graph/GraphNode.hpp
    Classes/gameai/graph/AshManhattan.hpp
    Classes/gameai/fsm/Dispatcher.hpp
    Classes/gameai/fsm/FiniteStateMachine.hpp
    Classes/gameai/entityshapes/ps/ImageBank.hpp
    Classes/gameai/entityshapes/ps/PersonPic.hpp
    Classes/gameai/entityshapes/ps/PicturePS.hpp
    Classes/gameai/entityshapes/ps/CirclePic.hpp
    Classes/gameai/entityshapes/Picture.hpp
    Classes/gameai/entities/BaseEntity.hpp
    Classes/gameai/entityshapes/ps/ArrowPic.hpp
    Classes/gameai/entities/Obstacle.hpp
    Classes/gameai/entities/Artefact.hpp
    )

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME lua_empty_test)
    list(APPEND GAME_SOURCE proj.android/app/jni/main.cpp)
elseif(LINUX)
    list(APPEND GAME_SOURCE proj.linux/main.cpp)
elseif(WINDOWS)
    list(APPEND GAME_HEADER proj.win32/main.h)
    list(APPEND GAME_SOURCE proj.win32/main.cpp)
    list(APPEND GAME_SOURCE proj.win32/main.cpp ${cc_common_res})
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios/AppController.h
             proj.ios/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios/LaunchScreen.storyboard
            proj.ios/LaunchScreenBackground.png
            proj.ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios/main.m
             proj.ios/AppController.mm
             proj.ios/RootViewController.mm
             proj.ios/HelloLua_Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        set(APP_UI_RES
            proj.mac/Icon.icns
            proj.mac/Info.plist
            proj.mac/en.lproj/InfoPlist.strings
            )
        list(APPEND GAME_SOURCE
             proj.mac/main.cpp
             proj.mac/HelloLua_Prefix.pch
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${cc_common_res})
endif()

set(APP_SRC ${GAME_HEADER} ${GAME_SOURCE})

if(NOT ANDROID)
    add_executable(${APP_NAME} ${APP_SRC})
else()
    add_library(${APP_NAME} SHARED ${APP_SRC})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/cpp-android)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/extensions/scripting/lua-bindings/proj.android ${ENGINE_BINARY_PATH}/cocos/lua-android)
    if(${CMAKE_ANDROID_ARCH_ABI} STREQUAL "x86")
        #add `-Wl,--no-warn-shared-textrel` to fix warning "shared library text segment is not shareable clang"
        target_link_libraries(${APP_NAME} -Wl,--whole-archive lua_android_spec -Wl,--no-whole-archive -Wl,--no-warn-shared-textrel)
    else()
        target_link_libraries(${APP_NAME} -Wl,--whole-archive lua_android_spec -Wl,--no-whole-archive)
    endif()

    config_android_shared_libs("org.cocos2dx.lib" "${CMAKE_CURRENT_SOURCE_DIR}/proj.android/app/src")
endif()
target_link_libraries(${APP_NAME} luacocos2d)
target_include_directories(${APP_NAME} PRIVATE Classes)

# mark app resources
setup_cocos_app_config(${APP_NAME})
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
    set_xcode_property(${APP_NAME} INSTALL_PATH "\$(LOCAL_APPS_DIR)")

    if(MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.mac/Info.plist")
        set_target_properties(${APP_NAME} PROPERTIES
            LINK_FLAGS "-pagezero_size 10000 -image_base 100000000"
        )
    elseif(IOS)
        set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios/Info.plist")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon-${APP_NAME}")
    endif()

    # For code-signing, set the DEVELOPMENT_TEAM:
    #set_xcode_property(${APP_NAME} DEVELOPMENT_TEAM "GRLXXXX2K9")
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME})
endif()

if(LINUX OR WINDOWS)
    # cocos_get_resource_path(APP_RES_DIR ${APP_NAME})
    # cocos_copy_target_res(${APP_NAME} LINK_TO ${APP_RES_DIR}/res FOLDERS ${res_res_folders})
    # cocos_copy_lua_scripts(${APP_NAME} ${res_src_folders} ${APP_RES_DIR}/src )
    # cocos_copy_lua_scripts(${APP_NAME} ${res_script_folders} ${APP_RES_DIR}/src/cocos)
endif()
