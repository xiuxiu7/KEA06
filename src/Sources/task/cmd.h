/*
 * cmd.h
 *
 *  Created on: 2017年11月7日
 *      Author: xiuxiu
 */

#ifndef SOURCES_TASK_CMD_H_
#define SOURCES_TASK_CMD_H_

#include "stdint.h"


typedef struct {
     char const *cmd_name;                         //命令字符串
     int32_t max_args;                             //最大参数数目
     void (*handle)(int argc, void * cmd_arg);     //命令回调函数
     char  *help;                                  //帮助信息
}cmd_list_struct;


#define ARG_NUM     9          //命令中允许的参数个数
#define CMD_LEN     15         //命令名占用的最大字符长度
#define CMD_BUF_LEN 60         //命令缓存的最大长度

typedef struct {
    char rec_buf[CMD_BUF_LEN];            //接收命令缓冲区
    char processed_buf[CMD_BUF_LEN];      //存储加工后的命令(去除控制字符)
    int32_t cmd_arg[ARG_NUM];             //保存命令的参数
}cmd_analyze_struct;


void fill_rec_buf(char data);
void tCmd(void);


#endif /* SOURCES_TASK_CMD_H_ */
