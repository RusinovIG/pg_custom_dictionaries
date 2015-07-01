MODULE_big = dict_abs_int
OBJS = dict_abs_int.o $(WIN32RES)

EXTENSION = dict_abs_int
DATA = dict_abs_int--1.0.sql
PGFILEDESC = "dict_abs_int - add-on dictionary template for full-text search"

REGRESS = dict_abs_int

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)