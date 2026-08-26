#include <core.h>

Core::Core(){
    m_core_status = CORE_CLOSED;
}

//  context and helper funcs
void Core::set_core_status(CoreStatus status){
    m_core_status = status;
}
CoreStatus Core::get_core_status(){
    return m_core_status;
}