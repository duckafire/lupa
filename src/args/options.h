#ifndef __ARGS_FLAGS__
#define __ARGS_FLAGS__

/*
 * -W --quiet-warn  : hide warnings during parsing process.
 * -E --quiet-error : hide errors during parsing process.
 * -Q --quiet       : hide warnings, and errors during parsing process.
 * -w --fatal-warn  : first parsing warning will stop the process.
 * -e --fatal-error : first parsing error will stop the process.
 * -f --fatal       : first parsing warning, or error will stop the process.
 *    --stdin       : read content from stdin.
 *    --            : end of options list.
 */

/* OPT_   : option
 * OPT_S_ : short option
 * OPT_P_ : option prefix */

#define OPT_P_NONE  ""
#define OPT_P_SHORT "-"
#define OPT_P_LONG  "--"

#define OPT_QUIET_W "quiet-warn"
#define OPT_QUIET_E "quiet-error"
#define OPT_QUIET   "quiet"
#define OPT_FATAL_W "fatal-warn"
#define OPT_FATAL_E "fatal-error"
#define OPT_FATAL   "fatal"
#define OPT_STDIN   "stdin"
#define OPT_END     "\0"
/* Prefixes `-` and `--` is not used in comparation
 * between expected option and received arguments.
 * OPT_END is `--`, so if `--` is removed only
 * `\0` will remain. */

#define OPT_S_QUIET_W 'W'
#define OPT_S_QUIET_E 'E'
#define OPT_S_QUIET   'Q'
#define OPT_S_FATAL_W 'w'
#define OPT_S_FATAL_E 'e'
#define OPT_S_FATAL   'f'

#endif
