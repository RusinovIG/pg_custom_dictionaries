MODULE_big = dict_catalog_domain
OBJS = dict_catalog_domain.o $(WIN32RES)

EXTENSION = dict_catalog_domain
DATA = dict_catalog_domain--1.0.sql
PGFILEDESC = "dict_catalog_domain - add-on dictionary template for full-text search"

REGRESS = dict_catalog_domain

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)