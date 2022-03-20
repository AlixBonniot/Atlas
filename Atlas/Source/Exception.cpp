#include "Exception.h"

#include <sstream>

Exception::Exception(HRESULT exceptionCode, const char* file, int line)
: m_exceptionCode{ exceptionCode }
, m_exceptionMessage{}
{
    ConcatenateMessage(file, line);
}

char const* Exception::what() const
{
    // We return the exception type
    return "Atlas framework exception";
}

const char* Exception::GetExceptionMessage() const
{
    // We send the message
    return m_exceptionMessage.c_str();
}

std::string Exception::GetExceptionDescrition() const
{
    // We get the exception description thanks to the
    // format message function
    const int size{ 1024 };
    char buffer[size]{};

    FormatMessageA(
        FORMAT_MESSAGE_FROM_SYSTEM,
        nullptr,
        m_exceptionCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
        buffer,
        size,
        nullptr
    );

    std::ostringstream oss{};
    oss << buffer;
    return oss.str();
}

void Exception::ConcatenateMessage(const char* file, int line)
{
    // We concatenate the message with all the necessary informations
    // file - line: message description

    std::ostringstream oss{};
    oss << file << " - " << line << ":\n";
    oss << GetExceptionDescrition();

    // We override our exception message
    m_exceptionMessage = oss.str();
}

void Test(HRESULT exceptionCode)
{
    if (exceptionCode != S_OK)
    {
        THROW_FRAMEWORK_EXCEPTION(exceptionCode);
    }
}
