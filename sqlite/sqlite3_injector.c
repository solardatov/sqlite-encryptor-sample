#include "sqlite3_injector.h"

#ifdef SQLITE_HAS_CODEC

void sqlite3_activate_see(const char *info)
{
     // TBD
}

void sqlite3PagerFreeCodec(void *pCodec)
{
    if (pCodec)
    {
        struct KeyStorage *ks = (struct KeyStorage *)pCodec;

        if (ks->m_page)
        {
            free(ks->m_page);
        }

        free(pCodec);
    }
}

void sqlite3CodecSizeChange(void *pCodec, int pageSize, int nReserve)
{
    if (pCodec)
    {
        struct KeyStorage *ks = (struct KeyStorage *)pCodec;
        ks->m_pageSize = pageSize;

        if (ks->m_page)
            free(ks->m_page);

        ks->m_page = malloc(pageSize);
        if (ks->m_page)
            memset(ks->m_page, 0, pageSize);
    }
}

void* sqlite3Codec(void *pCodec, void *data, unsigned nPageNum, int nMode)
{
    if (pCodec == NULL)
        return data;

    struct KeyStorage *ks = (struct KeyStorage *)pCodec;
    unsigned char *p = (unsigned char *)data;
    
    switch(nMode)
    {
        case 0: // Undo a "case 7" journal file encryption
        case 2: // Reload a page
        case 3: // Load a page
            for (int i=0; i < ks->m_pageSize; i++)
            {
                p[i] ^= 1;//ks->m_key;
            }
            return data;
        case 6: // Encrypt a page for the main database file
            for (int i=0; i < ks->m_pageSize; i++)
            {
                ks->m_page[i] = p[i] ^ 1;//ks->m_key;
            }
            return ks->m_page;

        case 7: // Encrypt a page for the journal file
            for (int i=0; i < ks->m_pageSize; i++)
            {
                ks->m_page[i] = p[i] ^ 1;//ks->m_key;
            }
            return ks->m_page;            
    }

    return NULL;
}

int sqlite3CodecAttach(sqlite3 *db, int nDb, const void *zKey, int nKey)
{
    
    struct KeyStorage *ks = (struct KeyStorage *)malloc(sizeof(struct KeyStorage));
    if (NULL != ks)
    {
        ks->m_key = ((unsigned char*)(zKey))[0];
        ks->m_pageSize = 0;
        ks->m_page = NULL;
        
        sqlite3PagerSetCodec(sqlite3BtreePager(db->aDb[nDb].pBt),
                                    sqlite3Codec,
                                    sqlite3CodecSizeChange,
                                    sqlite3PagerFreeCodec, (void *)ks);

        return SQLITE_OK;
    }
    else
    {
        return SQLITE_FAIL;
    }
}

void sqlite3CodecGetKey(sqlite3* db, int nDb, void **zKey, int *nKey)
{
    // TBD
    *zKey = NULL;
    *nKey = -1;
}


int sqlite3_key(sqlite3 *db, const void *zKey, int nKey)
{
    return sqlite3CodecAttach(db, 0, zKey, nKey);
}

int sqlite3_rekey(sqlite3 *db, const void *zKey, int nKey)
{
    // TBD
    return SQLITE_FAIL;
}

int sqlite3_key_v2(sqlite3 *db, const char *zDbName, const void *pKey, int nKey)
{
    // TBD
    return SQLITE_FAIL;
}


int sqlite3_rekey_v2(sqlite3 *db, const char *zDbName, const void *pKey, int nKey)
{
    // TBD
    return SQLITE_FAIL;
}

#endif
