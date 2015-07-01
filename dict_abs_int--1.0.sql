-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION dict_int" to load this file. \quit

CREATE FUNCTION dabs_int_init(internal)
	RETURNS internal
	AS 'MODULE_PATHNAME'
	LANGUAGE C STRICT;

CREATE FUNCTION dabs_int_lexize(internal, internal, internal, internal)
	RETURNS internal
	AS 'MODULE_PATHNAME'
	LANGUAGE C STRICT;

CREATE TEXT SEARCH TEMPLATE abs_int_dict_template (
	LEXIZE = dabs_int_lexize,
	INIT   = dabs_int_init
);

CREATE TEXT SEARCH DICTIONARY abs_int_dict (
	TEMPLATE = abs_int_dict_template
);

COMMENT ON TEXT SEARCH DICTIONARY abs_int_dict IS 'dictionary that return absolute value for integers';