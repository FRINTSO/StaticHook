#ifndef STATICHOOK_DATATYPES_H_
#define STATICHOOK_DATATYPES_H_

namespace HookLibrary {

	typedef unsigned char		BYTE;
	typedef unsigned short		WORD;
	typedef unsigned long		DWORD;
#if _WIN64
	typedef unsigned __int64	QWORD;
#endif

	typedef char				INT8;
	typedef unsigned char		UINT8;
	typedef short				INT16;
	typedef unsigned short		UINT16;
	typedef int					INT32;
	typedef unsigned int		UINT32;
#if _WIN64
	typedef __int64				INT64;
	typedef unsigned __int64	UINT64;
#endif
	typedef float				FP32;
	typedef double				FP64;


	typedef wchar_t				WCHAR;
} // namespace HookLibrary

#endif // !STATICHOOK_DATATYPES_H_