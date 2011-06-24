/*
 * Copyright (c) 2010 Cisco Systems, Inc.  All rights reserved.
 * Copyright © 2010-2011 UT-Battelle, LLC. All rights reserved.
 * Copyright © 2010-2011 Oak Ridge National Labs.  All rights reserved.
 *
 * See COPYING in top-level directory
 *
 * $COPYRIGHT$
 *
 */

#include "cci/config.h"

#include <stdio.h>

#include "cci.h"
#include "plugins/core/core.h"


int cci_get_opt(cci_opt_handle_t *handle, cci_opt_level_t level, 
                cci_opt_name_t name, void** val, int *len)
{
    int             ret     = CCI_SUCCESS;
    cci__ep_t       *ep     = NULL;
    cci__conn_t     *conn   = NULL;

    if (NULL == handle ||
        NULL == val ||
        NULL == len) {
        return CCI_EINVAL;
    }

    CCI_ENTER;

    if (CCI_OPT_LEVEL_ENDPOINT == level) {
        if (handle->endpoint == NULL || name == CCI_OPT_CONN_SEND_TIMEOUT)
            return CCI_EINVAL;
        ep = container_of(handle->endpoint, cci__ep_t, endpoint);
    } else {
        if (handle->connection == NULL || name != CCI_OPT_CONN_SEND_TIMEOUT)
            return CCI_EINVAL;
        conn = container_of(handle->connection, cci__conn_t, connection);
    }

    switch (name) {
    case CCI_OPT_ENDPT_MAX_HEADER_SIZE:
    {
        uint8_t *size = calloc(1, sizeof(*size));
        if (!size)
            return CCI_ENOMEM;

        *size = ep->max_hdr_size;
        *len = sizeof(*size);
        *val = size;
        break;
    }
    case CCI_OPT_ENDPT_SEND_TIMEOUT:
    {
        uint32_t *timeout = calloc(1, sizeof(*timeout));
        if (!timeout)
            return CCI_ENOMEM;

        *timeout = ep->tx_timeout;
        *len = sizeof(*timeout);
        *val = timeout;
        break;
    }
    case CCI_OPT_ENDPT_RECV_BUF_COUNT:
    {
        uint32_t *count = calloc(1, sizeof(*count));
        if (!count)
            return CCI_ENOMEM;

        *count = ep->rx_buf_cnt;
        *len = sizeof(*count);
        *val = count;
        break;
    }
    case CCI_OPT_ENDPT_SEND_BUF_COUNT:
    {
        uint32_t *count = calloc(1, sizeof(*count));
        if (!count)
            return CCI_ENOMEM;

        *count = ep->tx_buf_cnt;
        *len = sizeof(*count);
        *val = count;
        break;
    }
    case CCI_OPT_ENDPT_KEEPALIVE_TIMEOUT:
    {
        uint32_t *timeout = calloc(1, sizeof(*timeout));
        if (!timeout)
            return CCI_ENOMEM;

        *timeout = ep->keepalive_timeout;
        *len = sizeof(*timeout);
        *val = timeout;
        break;
    }
    case CCI_OPT_CONN_SEND_TIMEOUT:
    {
        uint32_t *timeout = calloc(1, sizeof(*timeout));
        if (!timeout)
            return CCI_ENOMEM;

        *timeout = conn->tx_timeout;
        *len = sizeof(*timeout);
        *val = timeout;
        break;
    }
    default:
        debug(CCI_DB_INFO, "unknown option %d", name);
        ret = CCI_EINVAL;
    }

#if 0
    ret = cci_core->get_opt(handle, level, name, val, len);
#endif

    CCI_EXIT;

    return ret;
}
