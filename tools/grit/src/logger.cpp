//
// \file logger.cpp
//   Simple, level-based logging functionality
// \date 20070223 - 20070223
// \author cearn
//
// === NOTES === 

#include <stdio.h>
#include <stdarg.h>

#include "logger.h"

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


inline int clamp(int x, int mn, int mx)
{	return x >= mx ? mx : ( x < mn ? mn : x);	}


// --------------------------------------------------------------------
// GLOBALS
// --------------------------------------------------------------------


//! Logging level. Only messages of equal or higher importance are printed.
int __log_level = 0;	

//! Stream to output to.		
FILE *__log_fp = stderr;

//! Status prefixes.
const char *__log_prefix[LOG_MAX+1]= 
{
	"", 
	"ERROR: ",
	"WARNING: ", 
	"STATUS: ", 
	""
};


// --------------------------------------------------------------------
// FUNCTIONS
// --------------------------------------------------------------------


//! Set logging level
void log_set_level(int level)
{
	__log_level = clamp(level, LOG_NONE, LOG_MAX);
}

//! Get logging level
int log_get_level()
{	
	return __log_level;
}

//! Set log stream
void log_set_stream(FILE *fp)
{
	__log_fp = fp ? fp : stderr;
}

//! Get log stream
FILE *log_get_stream()
{
	return __log_fp;
}

//! Initialize logging system.
/*! \param level	Sets level of output. Clamped to allowable range.
*	\param fp		Output stream. If NULL, \a stderr is used.
*/
void log_init(int level, FILE *fp)
{
	log_set_level(level);
	log_set_stream(fp);
}

//! Close the logging system.
void log_exit()
{
	log_set_stream(NULL);
	log_set_level(LOG_NONE);
}


//! Print a logging message to \a __log_fp.
/*! Works the same as printf(), except the \a level parameter
*	  that determines whether anything is printed at all. Output is 
*	  written to the log stream.
*	\param level	Message level. Message is only output if 
*	  it's lower or equal to the log level.
*	\param format	Format string
*	\return Number of characters printed.
*/
int lprintf(int level, const char *format, ...)
{

	if(level > __log_level || __log_fp == NULL)
		return 0;

	// Log prefix
	fputs(__log_prefix[clamp(level, 0, LOG_MAX)], __log_fp);

	va_list	args;
	va_start(args, format);

	return vfprintf(__log_fp, format, args);
}
