#include "STRING.h"
/**
 * @file   HELP.cpp
 * @brief  This section contain functions that will be used for dealing with strings (of any kind).
 * 
 * @author Luís Silva
 * @date   30/10/2023
 */













/**
 * @brief This function is inteded to be used inside Windows API Message Box functions (but can be used by others that require
 * a WCSTR or LPWCSTR string types) as parameters, since it's annoying to be everytime creating variables that only makes sense
 * for formatting this kind of string. Why not creating a function for this kind of situation.
 * 
 * @param szString
 * @return 
 */


wchar_t* wchszFormatWideString(char* szString) {

	wchar_t* wchszResult;



	if ( (wchszResult = (wchar_t*)malloc( (sizeof(szString) + 1) * sizeof(wchar_t)  )  ) == NULL) {
		return nullptr;
	}


	wsprintf(wchszResult, L"%s", szString);






	return wchszResult;
}
