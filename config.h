#pragma once

#define SRC_DIRECTORY "D:/GithubRepositories/Element/src/"
#define INCLUDE_DIRECTORY "D:/GithubRepositories/Element/include/"
#define WINDOW_DLL "D:/GithubRepositories/Element/Modules/Windows/Release/Window.dll"
#define TARGET_PLATFORM "Windows"

#define FUNCTION_SUCCESS static_cast<int8_t>(1)
#define FUNCTION_RESULT_UNDEFINED static_cast<int8_t>(0)
#define FUNCTION_FAILURE static_cast<int8_t>(-1)

#define WINDOW_PROCESS 0
#define APP_PROCESS 1
#define RENDER_PROCESS 2
#define EVENT_PROCESS 3
#define MAIN_PROCESS 65535
