#include <core.h>

//  constructor and destructor
Core::Core(){
    m_core_status = CORE_CLOSED;
}

//  core startup and shutdown
CoreStatus Core::init(){
    //initialise core components, set core status on success/failure

    m_core_status = CORE_STANDBY;
    return m_core_status;
}
CoreStatus Core::start(){
    //start emulator instance

    m_core_status = CORE_RUNNING;
    return m_core_status;
}
CoreStatus Core::stop(){
    //stop emulator instance

    m_core_status = CORE_STANDBY;
    return m_core_status;
}
CoreStatus Core::shutdown(){
    //shutdown core components, set core status on success/failure

    m_core_status = CORE_CLOSED;
    return m_core_status;
}

//  context and helper funcs
void Core::set_core_status(CoreStatus status){
    m_core_status = status;
}
CoreStatus Core::get_core_status(){
    return m_core_status;
}

void Core::set_core_path(const std::filesystem::path& path){
    m_core_path = path;
}
std::filesystem::path Core::get_core_path(){
    return m_core_path;
}