/*
 * Copyright (c) 2021 Alibaba Group. All rights reserved.
 * License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
/*!
 * \file 
 * \brief This section defines DSP shared strcut for CPU&DSP&APP.
 *
 * General  properties:
 * 1. Post porcess define data and strcut, visiable for APP
 * 2. user define data shared bedtween DSP ans host
 */

#ifndef _CSI_DSP_TASK_DEFS_H
#define _CSI_DSP_TASK_DEFS_H

#include <string.h>
#include <stdint.h>
#include "csi_dsp_post_process_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define  MAX_REPORT_SIZE  256

#define  CSI_DSP_HW_TASK_EXTRA_BUF_START_INDEX  2
typedef struct _sisp_config_par{
	uint16_t id;
	uint16_t hor;
	uint16_t ver;
	uint16_t data_fmt;
	uint16_t line_in_entry;
	uint16_t line_stride;
	uint32_t buffer_size;
	uint64_t buffer_addr;
}sisp_config_par;

typedef   sisp_config_par spost_isp_config_par;
// typedef   sisp_config_par svipre_config_par;
typedef  struct vipre_config_par{
    uint8_t  id;
	uint8_t  act_channel;
	uint8_t  data_fmt;
	uint8_t  buffer_num;
	uint16_t line_num;
	uint16_t hor;
	uint16_t ver;
	uint16_t line_stride;
	uint32_t buffer_size;
	uint64_t buffer_addr[12];
}vipre_config_par_t;

typedef enum csi_dsp_report{
  CSI_DSP_REPORT_NORMAL,
  CSI_DSP_REPORT_RESULT,
  CSI_DSP_REPORT_RESULT_WITH_EXRA_PARAM,
  CSI_DSP_REPORT_ALGO_ERR,
  CSI_DSP_REPORT_PS_ERR,
  CSI_DSP_REPORT_ISP_ERR,
  CSI_DSP_REPORT_RY_ERR,
  CSI_DSP_REPORT_VI_PRE_ERR,
  CSI_DSP_REPORT_NO_BUF,
  CSI_DSP_REPORT_HEARTBEAT_ERR,
  CSI_DSP_HW_FRAME_DROP,
  CSI_DSP_REPORT_EXRA_PARAM,
  CSI_DSP_REPORT_HW_ERROR,
  CSI_DSP_REPORT_HW_VIPRE_NM_OVERFLOW_FLOW,
  CSI_DSP_REPORT_HW_VIPRE_FIFO_ERROR,
  CSI_DSP_REPORT_HW_VIPRE_BUS_ERROR,
  CSI_DSP_REPORT_HW_ERROR_END,
  CSI_DSP_REPORT_MAX
}csi_dsp_report_e;

typedef struct csi_dsp_report_item{
    csi_dsp_report_e type;
    union{
        char data[MAX_REPORT_SIZE];
        struct csi_dsp_buffer buf;
    };
}csi_dsp_report_item_t;
typedef enum csi_dsp_task_mode{
    CSI_DSP_TASK_SW_TO_SW =0x1<<0,  /*SW Queue to handle in / data/exception  */
    CSI_DSP_TASK_SW_TO_HW =0x1<<1,  /*SW Queue to handle in and exception / Report handlere exception,HW handl out*/
    CSI_DSP_TASK_HW_TO_SW =0x1<<2,  /* HW send handle in, Report handler  out and exception*/
    CSI_DSP_TASK_HW_TO_HW =0x01<<3, /* Hw handler in&out Report handler exception*/
    CSI_DSP_TASK_SW = (CSI_DSP_TASK_SW_TO_HW|CSI_DSP_TASK_SW_TO_SW),
    CSI_DSP_TASK_HW = (CSI_DSP_TASK_HW_TO_SW|CSI_DSP_TASK_HW_TO_HW),
}csi_dsp_task_mode_e;

//#define  CSI_DSP_TASK_SW  (CSI_DSP_TASK_SW_TO_HW|CSI_DSP_TASK_SW_TO_SW)
//#define  CSI_DSP_TASK_HW  (CSI_DSP_TASK_HW_TO_SW|CSI_DSP_TASK_HW_TO_HW)

enum csi_dsp_fe_type{
    CSI_DSP_FE_TYPE_CPU,
    CSI_DSP_FE_TYPE_ISP,
    CSI_DSP_FE_TYPE_VIPRE,
    CSI_DSP_FE_TYPE_INVALID,
};

enum csi_dsp_be_type{
    CSI_DSP_BE_TYPE_HOST,
    CSI_DSP_BE_TYPE_POST_ISP,
    CSI_DSP_BE_TYPE_INVALID,
};

enum csi_dsp_task_cfg{
    CSI_DSP_TASK_IDLE,
    CSI_DSP_TASK_START,
    CSI_DSP_TASK_STOP,

};

typedef struct csi_dsp_task_fe_para{
    enum csi_dsp_fe_type frontend_type;
    int task_id;
    union{
            sisp_config_par isp_param;
            vipre_config_par_t vipre_param;
    };
}csi_dsp_task_fe_para_t;
typedef struct _sw_be_config_par{
    int num_buf;
    struct csi_dsp_buffer bufs[1];

}sw_be_config_par;

typedef struct csi_dsp_task_be_para{
    enum csi_dsp_be_type backend_type;
    int task_id;
    union{
            sisp_config_par post_isp_param;
            sw_be_config_par sw_param;
    };

}csi_dsp_task_be_para_t;


typedef struct csi_dsp_algo_load_req{
	uint16_t  algo_id;
    int task_id;
    uint64_t  algo_ptr;
}csi_dsp_algo_load_req_t;


#ifdef __cplusplus
}
#endif

#endif
