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

/* F_  : flags
 * FS_ : short flags
 * FP_ : flag prefix */

#define FP_NONE  ""
#define FP_SHORT "-"
#define FP_LONG  "--"

#define F_QUIET_W "quiet-warn"
#define F_QUIET_E "quiet-error"
#define F_QUIET   "quiet"
#define F_FATAL_W "fatal-warn"
#define F_FATAL_E "fatal-error"
#define F_FATAL   "fatal"
#define F_STDIN   "stdin"
#define F_OPT_END "\0"
/* Prefixes `-` and `--` is not used in comparation
 * between expected flags and received arguments.
 * OPT_END is `--`, so if `--` is removed only
 * `\0` will remain. */

#define FS_QUIET_W 'W'
#define FS_QUIET_E 'E'
#define FS_QUIET   'Q'
#define FS_FATAL_W 'w'
#define FS_FATAL_E 'e'
#define FS_FATAL   'f'

#endif
