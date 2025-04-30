//
//! \file cli.cpp
//!  Command line interface
//! \date 20050823 - 20080130
//! \author gauauu, cearn
/* === NOTES ===
*/

#include "cli.h"
#include <string.h>
#include <stdlib.h>

//! Find a key in a string array.
/*!	\return key index or length of array if not found.
*/
int cli_find_key(const char *key, const strvec &args)
{
	int ii, count = args.size();
	for(ii = 1; ii<count; ii++)
		if(strncmp(key, args[ii], strlen(key)) == 0)
			break;

	return ii;
}

//! Return whether \a key is present in \a args.
bool cli_bool(const char *key, const strvec &args)
{
	return cli_find_key(key, args) < (int)args.size();
}

//! Return the integer following \a key, or \a dflt if \a key not found.
int cli_int(const char *key, const strvec &args, int dflt)
{
	int pos = cli_find_key(key, args), count = args.size();
	if(pos >= count)
		return dflt;

	char *str = &args[pos][strlen(key)];

	if(*str != '\0')					// attached field
		return strtoul(str, NULL, 0);

	if(pos == count-1)			// separate field, but OOB
		return dflt;

	return strtoul(args[pos+1], NULL, 0);
}

//! Return the string following \a key, or \a dflt if \a key not found.
char *cli_str(const char *key, const strvec &args, const char *dflt)
{
	int pos = cli_find_key(key, args), count = args.size();
	if(pos >= count)
		return (char *)dflt;

	char *str = &args[pos][strlen(key)];
	if(*str != '\0')					// attached field
		return str;

	if(pos == count-1)			// separate field, but OOB
		return (char *)dflt;

	return args[pos+1];
}

// TODO cli_range ... somehow :P

// EOF
