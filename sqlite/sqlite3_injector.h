#ifndef sqlite3_injector_h
#define sqlite3_injector_h

#include "sqlite3.h"

struct KeyStorage
{
    unsigned char m_key;
    unsigned m_pageSize;
    unsigned char * m_page;
};

void sqlite3_activate_see(const char *info);
void sqlite3PagerFreeCodec(void *pCodec);
void sqlite3CodecSizeChange(void *pCodec, int pageSize, int nReserve);
void* sqlite3Codec(void *pCodec, void *data, unsigned nPageNum, int nMode);
void sqlite3CodecGetKey(sqlite3* db, int nDb, void **zKey, int *nKey);
int sqlite3CodecAttach(sqlite3 *db, int nDb, const void *zKey, int nKey);
int sqlite3_key(sqlite3 *db, const void *zKey, int nKey);
int sqlite3_rekey(sqlite3 *db, const void *zKey, int nKey);
int sqlite3_key_v2(sqlite3 *db, const char *zDbName, const void *pKey, int nKey);
int sqlite3_rekey_v2(sqlite3 *db, const char *zDbName, const void *pKey, int nKey);


#endif
