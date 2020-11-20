#ifndef _ERROR_HPP
#define _ERROR_HPP

/**
 * Logs the error id and its description
 * 
 * @param[in] error an integer representing the error id
 * @param[in] description a string representing the error description
 */
void ErrorCallback(int error, const char* description);

#endif