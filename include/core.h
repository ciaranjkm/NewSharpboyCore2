#pragma once

/*
    The main core class to hold and manage all components.
*/

enum CoreStatus{
    CORE_RUNNING,
    CORE_PAUSED,
    CORE_CLOSED,
    CORE_HALTED
};

class Core{
public:
    Core();

    //  context and helper funcs
    void set_core_status(CoreStatus status);
    CoreStatus get_core_status();

private:
    CoreStatus m_core_status;
};