cmake_minimum_required (VERSION 3.0)
project (berk185)

include_directories (include)

add_library (berk185 STATIC
  hash/hash.c
  hash/hash_bigkey.c
  hash/hash_buf.c
  hash/hash_func.c
  hash/hash_log2.c
  hash/hash_page.c
  hash/hsearch.c
  hash/ndbm.c

  btree/bt_close.c
  btree/bt_conv.c
  btree/bt_debug.c
  btree/bt_delete.c
  btree/bt_get.c
  btree/bt_open.c
  btree/bt_overflow.c
  btree/bt_page.c
  btree/bt_put.c
  btree/bt_search.c
  btree/bt_seq.c
  btree/bt_split.c
  btree/bt_utils.c

  db/db.c

  mpool/mpool.c

  recno/rec_close.c
  recno/rec_delete.c
  recno/rec_get.c
  recno/rec_open.c
  recno/rec_put.c
  recno/rec_search.c
  recno/rec_seq.c
  recno/rec_utils.c
)
set_target_properties (berk185 PROPERTIES COMPILE_DEFINITIONS
  __DBINTERFACE_PRIVATE
)

add_executable (berk185_dump
  util/berk185_dump.c
)
target_link_libraries (berk185_dump berk185)
