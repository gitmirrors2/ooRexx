
// macOS doesn't support any of the sem_xxx functions
#if !defined __APPLE__
    INTERNAL_ROUTINE(SysCreateMutexSem,      SysCreateMutexSem)
    INTERNAL_ROUTINE(SysOpenMutexSem,        SysOpenMutexSem)
    INTERNAL_ROUTINE(SysCloseMutexSem,       SysCloseMutexSem)
    INTERNAL_ROUTINE(SysRequestMutexSem,     SysRequestMutexSem)
    INTERNAL_ROUTINE(SysReleaseMutexSem,     SysReleaseMutexSem)
    INTERNAL_ROUTINE(SysCreateEventSem,      SysCreateEventSem)
    INTERNAL_ROUTINE(SysOpenEventSem,        SysOpenEventSem)
    INTERNAL_ROUTINE(SysCloseEventSem,       SysCloseEventSem)
    INTERNAL_ROUTINE(SysResetEventSem,       SysResetEventSem)
    INTERNAL_ROUTINE(SysPostEventSem,        SysPostEventSem)
    INTERNAL_ROUTINE(SysWaitEventSem,        SysWaitEventSem)
#endif
    INTERNAL_ROUTINE(SysSetPriority,         SysSetPriority)
    INTERNAL_ROUTINE(SysFork,                SysFork)
    INTERNAL_ROUTINE(SysWait,                SysWait)
    INTERNAL_ROUTINE(SysCreatePipe,          SysCreatePipe)
    INTERNAL_ROUTINE(SysCls,                 SysCls)
    INTERNAL_ROUTINE(SysGetKey,              SysGetKey)
    INTERNAL_ROUTINE(SysGetMessage,          SysGetMessage)
    INTERNAL_ROUTINE(SysGetMessageX,         SysGetMessageX)
    INTERNAL_ROUTINE(SysMkDir,               SysMkDir)
#ifdef LINUX
    INTERNAL_ROUTINE(SysLinVer,              SysVersion)
#endif
    INTERNAL_ROUTINE(SysVersion,             SysVersion)
    INTERNAL_ROUTINE(SysSetFileDateTime,     SysSetFileDateTime)
    INTERNAL_ROUTINE(SysGetFileDateTime,     SysGetFileDateTime)
    INTERNAL_ROUTINE(SysQueryProcess,        SysQueryProcess)
    INTERNAL_ROUTINE(SysGetErrorText,        SysGetErrorText)

