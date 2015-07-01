/*
 * Text search dictionary that return absolute value for integers
 */
#include "postgres.h"

#include "commands/defrem.h"
#include "tsearch/ts_public.h"

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
	char	   *in = (char *) PG_GETARG_POINTER(1);
	char	   *txt = pnstrdup(in, PG_GETARG_INT32(2));
	TSLexeme   *res = palloc0(sizeof(TSLexeme) * 2);

	res[1].lexeme = NULL;
	if ('-' == txt[0])
	{
		// crop "-" symbol
		*txt = pnstrdup(in + 1, PG_GETARG_INT32(2) - 1);
	}
  res[0].lexeme = txt;

	PG_RETURN_POINTER(res);
}