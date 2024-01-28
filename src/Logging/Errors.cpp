#include "Errors.hpp"
#include <etl/error_handler.h>

void LogErrors(const etl::exception e) {
    Log<ELSF_LOG_MAX_MESSAGE_LENGTH>::instance().Error("%s:%s| %s", e.file_name(), e.line_number ,e.what());
}

etl::error_handler::set_callback<LogErrors>();