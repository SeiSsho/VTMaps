########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(stb_COMPONENT_NAMES "")
set(stb_FIND_DEPENDENCY_NAMES "")

########### VARIABLES #######################################################################
#############################################################################################
set(stb_PACKAGE_FOLDER_RELEASE "C:/Users/tts/.conan2/p/stbf6cb8d59f52a8/p")
set(stb_BUILD_MODULES_PATHS_RELEASE )


set(stb_INCLUDE_DIRS_RELEASE "${stb_PACKAGE_FOLDER_RELEASE}/include")
set(stb_RES_DIRS_RELEASE )
set(stb_DEFINITIONS_RELEASE "-DSTB_TEXTEDIT_KEYTYPE=unsigned")
set(stb_SHARED_LINK_FLAGS_RELEASE )
set(stb_EXE_LINK_FLAGS_RELEASE )
set(stb_OBJECTS_RELEASE )
set(stb_COMPILE_DEFINITIONS_RELEASE "STB_TEXTEDIT_KEYTYPE=unsigned")
set(stb_COMPILE_OPTIONS_C_RELEASE )
set(stb_COMPILE_OPTIONS_CXX_RELEASE )
set(stb_LIB_DIRS_RELEASE )
set(stb_BIN_DIRS_RELEASE )
set(stb_LIBRARY_TYPE_RELEASE UNKNOWN)
set(stb_IS_HOST_WINDOWS_RELEASE 0)
set(stb_LIBS_RELEASE )
set(stb_SYSTEM_LIBS_RELEASE )
set(stb_FRAMEWORK_DIRS_RELEASE )
set(stb_FRAMEWORKS_RELEASE )
set(stb_BUILD_DIRS_RELEASE )
set(stb_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(stb_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${stb_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${stb_COMPILE_OPTIONS_C_RELEASE}>")
set(stb_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${stb_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${stb_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${stb_EXE_LINK_FLAGS_RELEASE}>")


set(stb_COMPONENTS_RELEASE )