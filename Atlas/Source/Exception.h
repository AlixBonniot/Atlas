#ifndef EXCEPTION_H
#define EXCEPTION_H

// The exception class will be used to detect errors related
// to Direct3D API library

#include "appinc.h"

#include <exception>
#include <string>

class Exception : public std::exception
{
public:
	Exception(HRESULT exceptionCode, const char* file, int line);

	// Tell what kind of error it is
	virtual const char* what() const override;
	const char* GetExceptionMessage() const;

private:
	std::string GetExceptionDescrition() const;
	void ConcatenateMessage(const char* file, int line);

private:
	HRESULT m_exceptionCode;
	std::string m_exceptionMessage;
};

// Utiliy function that test an HRESULT before throwing the exception
void Test(HRESULT exceptionCode);

#define THROW_FRAMEWORK_EXCEPTION(exceptionCode) throw Exception{ exceptionCode, __FILE__, __LINE__ }

#endif