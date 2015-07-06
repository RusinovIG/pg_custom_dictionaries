-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION dict_catalog_domain" to load this file. \quit

CREATE FUNCTION dict_catalog_domain_init(internal)
	RETURNS internal
	AS 'MODULE_PATHNAME'
	LANGUAGE C STRICT;

CREATE FUNCTION dict_catalog_domain_lexize(internal, internal, internal, internal)
	RETURNS internal
	AS 'MODULE_PATHNAME'
	LANGUAGE C STRICT;

CREATE TEXT SEARCH TEMPLATE catalog_domain_dict_template (
	LEXIZE = dict_catalog_domain_lexize,
	INIT   = dict_catalog_domain_init
);

CREATE TEXT SEARCH DICTIONARY catalog_domain_dict (
	TEMPLATE = catalog_domain_dict_template
);

COMMENT ON TEXT SEARCH DICTIONARY catalog_domain_dict IS 'dictionary that index domain parts';