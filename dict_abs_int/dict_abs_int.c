/*
 * Text search dictionary that return absolute value for integers
 */
#include "postgres.h"

#include <ctype.h>

#include "commands/defrem.h"
#include "tsearch/ts_locale.h"
#include "tsearch/ts_utils.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(dabs_int_init);
PG_FUNCTION_INFO_V1(dabs_int_lexize);

Datum
dabs_int_init(PG_FUNCTION_ARGS)
{
	PG_RETURN_POINTER(NULL);
}

Datum
dabs_int_lexize(PG_FUNCTION_ARGS)
{
	char *in = (char *) PG_GETARG_POINTER(1);
	char *out = pnstrdup(in, PG_GETARG_INT32(2));
	char *start;
	char *end;
	TSLexeme *res = palloc0(sizeof(TSLexeme) * 2);

	res[1].lexeme = NULL;

	while (*out && t_iseq(out, '-'))
  		out += pg_mblen(out);

	start = out;

	while (*out)
    		out += pg_mblen(out);

	end = out;
	*out = pnstrdup(start, end - start);

  res[0].lexeme = out;

	PG_RETURN_POINTER(res);
}