

#ifndef _CLI_PARSER_H_
#define _CLI_PARSER_H_


#include <vector>

typedef std::vector<char*> strvec;

#define CLI_BOOL(_key) cli_bool(_key, args)
#define CLI_INT(_key, _dflt) cli_int(_key, args, _dflt)
#define CLI_STR(_key, _dflt) cli_str(_key, args, _dflt)

int cli_find_key(const char *key, const strvec &args);
int cli_int(const char *key, const strvec &args, int dflt);
bool cli_bool(const char *key, const strvec &args);
char *cli_str(const char *key, const strvec &args, const char *dflt);


/*
int cli_find_key(const char *key, int argc, char **argv);
int cli_int(const char *key, int argc, char **argv, int dflt);
bool cli_bool(const char *key, int argc, char **argv);
char *cli_str(const char *key, int argc, char **argv, char *dflt);
*/

#endif

// EOF
