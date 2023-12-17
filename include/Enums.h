#pragma once
enum EWindowState {
    FULLSCREEN,
    MAXIMIZED,
    MINIMIZED,
};
enum ELogType {
    LOG = 0,
    STATUS = 1,
    LOG_WARNING = 2,
    LOG_ERROR = 3,
    SUBSTATUS = 4,
    ASYNC_TASK = 5,
    NON_ASYNC_TASK = 6,
    RESULT_VALID = 7,
    RESULT_ERROR = 8
};

