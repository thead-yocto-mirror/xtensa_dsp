/*
 * Copyright (c) 2017 Cadence Design Systems Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Alternatively you can use and distribute this file under the terms of
 * the GNU General Public License version 2 or later.
 */

#ifndef XRP_KERNEL_REPORT_H
#define XRP_KERNEL_REPORT_H

// #include "xrp_alloc.h"
#include <linux/interrupt.h>
#include "xrp_kernel_defs.h"

#define REPORT_QUEUE_NUM   8

struct xrp_report_ring_buffer{
    volatile __u32 WR;
    volatile __u32 RD;
    volatile bool is_full;
    __u32  max_item;
    __u8   data[1];
};

struct xrp_reporter {

    struct fasync_struct *fasync;
	struct tasklet_struct  report_task;
	__u64 buffer_virt; 
	phys_addr_t buffer_phys;
	size_t buffer_size;
    struct xrp_report_ring_buffer  *buffer_list;

};

#endif
