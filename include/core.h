#pragma once
#include <common.h>
#include <loader.h>

/*
    The main core class to hold and manage all components.
*/

enum CoreStatus{
    CORE_CLOSED = 0,
    CORE_STANDBY = 1,
    CORE_RUNNING = 2,
    CORE_PAUSED = 3,
    CORE_HALTED = 4,
    CORE_FAILURE = -1
};

class Core{
public:
    //  constructor and destructor
    Core();

    //  core startup and shutdown
    CoreStatus init();
    CoreStatus start();
    CoreStatus stop();
    CoreStatus shutdown();

    //  context and helper funcs
    void set_core_status(CoreStatus status);
    CoreStatus get_core_status();

    void set_core_path(const std::filesystem::path& path);
    std::filesystem::path get_core_path();

private:
    //  private vars
    CoreStatus m_core_status;
    std::filesystem::path m_core_path;
};