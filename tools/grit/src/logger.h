//
// \file logging.h
//   Simple level-based logging functionality
// \date 20070223 - 20070223
// \author cearn
//
// === NOTES === 

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>

/*! \addtogroup grpLog
*	\{
*/

/*

Logging functionality.

N levels of logs: 
- 0 error: Things go bewm
- 1 warning: Internal conflict, but nothing fatal
- 2 stat: Regular output, to see what's been done.

Log levels work cumulatively: a higher one also outputs 
lower levels.

Functions:
- set log level
- get log level
- set output stream
- print log
- macro for log + return. Hmmm, probably a bad idea.
*/

enum ELogger
{
	LOG_NONE,	//!< No logging (default)
	LOG_ERROR,		//!< Fatal error
	LOG_WARNING,	//!< Non-fatal problem
	LOG_STATUS,		//!< General status message
	LOG_MAX
};

/*	// Commented out for now because you shouldn't be touching them :P
extern const char *log_strings[];

extern int __log_level;
extern FILE *__log_file;
*/

// --------------------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------------------


void log_init(int level, FILE *fp);
void log_exit();
void log_set_level(int level);
int log_get_level();
void log_set_stream(FILE *fp);

int lprintf(int level, const char *format, ...);

/*!	\}	*/


#endif	// __LOGGER_H__

// EOF
