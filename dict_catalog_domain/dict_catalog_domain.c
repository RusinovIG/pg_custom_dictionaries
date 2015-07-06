/*
 * Text search dictionary that index domain parts
 */
#include "postgres.h"

#include <ctype.h>

#include "commands/defrem.h"
#include "tsearch/ts_locale.h"
#include "tsearch/ts_utils.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(dict_catalog_domain_init);
PG_FUNCTION_INFO_V1(dict_catalog_domain_lexize);

Datum
dict_catalog_domain_init(PG_FUNCTION_ARGS)
{
	PG_RETURN_POINTER(NULL);
}

static char * find_word(char *in, char **end)
{
	char *start;
	*end = NULL;
	while (*in && t_iseq(in, '.'))
		in += pg_mblen(in);

	if (!*in || *in == '#')
  		return NULL;

	start = in;

	while (*in && !t_iseq(in, '.'))
		in += pg_mblen(in);

	*end = in;

	return start;
}

Datum
dict_catalog_domain_lexize(PG_FUNCTION_ARGS)
{
	char *in = (char *) PG_GETARG_POINTER(1);
	int length = PG_GETARG_INT32(2);
	char *txt = pnstrdup(in, PG_GETARG_INT32(2));
	TSLexeme *res = NULL;

	if (!length || t_iseq(in, '.'))
  		PG_RETURN_POINTER(NULL);

	/* Parse string and return array of words */
	{
		char *part;
		char *pos;
		char *end;
		int ntokens;
		
		res = palloc(sizeof(TSLexeme));
		res[0].lexeme = txt;

		pos = txt;
		ntokens = 1;
		while ((part = find_word(pos, &end)) != NULL)
		{
			res = repalloc(res, sizeof(TSLexeme) * (ntokens + 2));

			/* Remove duplicates */
			if (end - part != length) {
				res[ntokens].lexeme = pnstrdup(part, end - part);
				ntokens++;
			}
			pos = end;
		}
		res[ntokens].lexeme = NULL;
	}

	PG_RETURN_POINTER(res);
}