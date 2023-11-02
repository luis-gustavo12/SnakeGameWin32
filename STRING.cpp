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


char* szFormatWideString(char* szString) {

	char szResult  [600];






	sprintf_s(szResult, "%s", szString);






	return szResult;
}
