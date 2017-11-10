/*
* cmd.c
*
*  Created on: 2017年11月7日
*      Author: xiuxiu
*/

#include "cmd.h"
#include "print.h"
#include "string.h"
#include "mqx_tasks.h"
#include <ctype.h>
#include "uart2can.h"

LWSEM_STRUCT sem_cmd;
cmd_analyze_struct cmd_analyze;

static uint32_t get_true_char_stream(char *dest, const char *src);
static int32_t cmd_arg_analyze(char *rec_buf, unsigned int len);
static int32_t string_to_dec(uint8_t *buf, uint32_t len);
void show_cmd_list(int32_t argc, void *cmd_arg);


void fill_rec_buf(char data)
{
	static uint32_t rec_count = 0;
	cmd_analyze.rec_buf[rec_count] = data;
	if( 0x0D == cmd_analyze.rec_buf[rec_count])
	{
		rec_count = 0;
		_lwsem_post(&sem_cmd);
	}
	else
	{
		rec_count++;
		if(rec_count >= CMD_BUF_LEN)
		{
			rec_count = 0;
		}
	}
}


static uint32_t get_true_char_stream(char *dest, const char *src)
{
	uint32_t dest_count=0;
	uint32_t src_count=0;

//while(src[src_count] != 0x0D && src[src_count+1] != 0x0A)
	while(src[src_count] != 0x0D)
	{
		if(isprint((int)src[src_count]))
		{
			dest[dest_count++]=src[src_count++];
		}
		else
		{
			switch(src[src_count])
			{
				case    0x08:   
				{
					if(dest_count>0)
					{
						dest_count --;
					}
					src_count ++;
				}break;
				case    0x1B:
				{
					if(src[src_count+1]==0x5B)
					{
						if(src[src_count+2]==0x41 || src[src_count+2]==0x42)
						{
							src_count +=3;   
						}
						else if(src[src_count+2]==0x43)
						{
							dest_count++;       
							src_count+=3;
						}
						else if(src[src_count+2]==0x44)
						{
							if(dest_count >0)  
							{
								dest_count --;
							}
							src_count +=3;
						}
						else
						{
							src_count +=3;
						}
					}
					else
					{
						src_count ++;
					}
				}break;
				default:
				{
					src_count++;
				}break;
			}
		}
	}
	dest[dest_count++]=src[src_count++];
	dest[dest_count++]=src[src_count++];
	return dest_count;
}

/**
* 命令参数分析函数,以空格作为一个参数结束,支持输入十六进制数(如:0x15),支持输入负数(如-15)
* @param rec_buf   命令参数缓存区
* @param len       命令的最大可能长度
* @return -1:       参数个数过多,其它:参数个数
*/
static int32_t cmd_arg_analyze(char *rec_buf, unsigned int len)
{
	uint32_t i;
	uint32_t blank_space_flag=0;
	uint32_t arg_num=0;  
	uint32_t index[ARG_NUM];  

	for(i=0;i<len;i++)
	{
		if(rec_buf[i]==0x20) 
		{
			blank_space_flag=1;
			continue;
		}
		else if(rec_buf[i]==0x0D)
		{
			break;
		}
		else
		{
			if(blank_space_flag==1)
			{
				blank_space_flag=0;
				if(arg_num < ARG_NUM)
				{
					index[arg_num]=i;
					arg_num++;
				}
				else
				{
					return -1;
				}
			}
		}
	}

	for(i=0;i<arg_num;i++)
	{
		cmd_analyze.cmd_arg[i]=string_to_dec((unsigned char *)(rec_buf+index[i]),len-index[i]);
	}
	return arg_num;
}

static int32_t string_to_dec(uint8_t *buf, uint32_t len)
{
	uint32_t i=0;
	uint32_t base=10; 
	int32_t  neg=1; 
	int32_t  result=0;

	if((buf[0]=='0')&&(buf[1]=='x'))
	{
		base=16;
		neg=1;
		i=2;
	}
	else if(buf[0]=='-')
	{
		base=10;
		neg=-1;
		i=1;
	}
	for(;i<len;i++)
	{
		if(buf[i]==0x20 || buf[i]==0x0D)
		{
			break;
		}

		result *= base;
		if(isdigit(buf[i])) 
		{
			result += buf[i]-'0';
		}
		else if(isxdigit(buf[i])) 
		{
			result+=tolower(buf[i])-87;
		}
		else
		{
			result += buf[i]-'0';
		}
	}
	result *= neg;
	return result;
}

void handle_software_reset(int32_t argc, void *cmd_arg)
{
	(void)argc;
	(void)cmd_arg;
	Cpu_SystemReset();
}


const cmd_list_struct cmd_list[]={
/*命令    			参数数目        			处理函数 				帮助信息                 */
	{" ",				0,			(void *)show_cmd_list,			"Show CMD list"},
	{"reset",			0,			(void *)handle_software_reset,		"reset s32k"},
	{"s",				0,			(void*)handle_show_rx_buf,		"show rx buffer"}
};

void show_cmd_list(int32_t argc, void *cmd_arg)
{
	(void)argc;
	(void)cmd_arg;
	uint32_t len = sizeof(cmd_list)/sizeof(cmd_list[0]);
	uint8_t i;
	MY_DEBUGF(((uint8_t *)&"cmd number:%d\r\n", len));
	for(i = 0; i < len; i++)
	{
		MY_DEBUGF(((uint8_t *)&"args: %d cmd: %s,                info: %s.\r\n", cmd_list[i].max_args, cmd_list[i].cmd_name, cmd_list[i].help));
	}
}

//***********************************************************************************//

void tCmd(void)
{
	uint32_t i;
	int32_t rec_arg_num;
	char cmd_buf[CMD_LEN];
	uint32_t rec_num;
	_lwsem_create(&sem_cmd, 0);
	UART_DEBUG_ClearRxBuf();
	UART_DEBUG_EnableEvent();
	for(;;)
	{
		_lwsem_wait(&sem_cmd);
		rec_num = get_true_char_stream(cmd_analyze.processed_buf, cmd_analyze.rec_buf);

		for(i=0;i<CMD_LEN;i++)
		{
			if((i>0)&&((cmd_analyze.processed_buf[i]==' ')||(cmd_analyze.processed_buf[i]==0x0D)))
			{
				cmd_buf[i]='\0'; 
				break;
			}
			else
			{
				cmd_buf[i]=cmd_analyze.processed_buf[i];
			}
		}

		rec_arg_num = cmd_arg_analyze(&cmd_analyze.processed_buf[i],rec_num);

		for(i=0;i<sizeof(cmd_list)/sizeof(cmd_list[0]);i++)
		{
			if(!strcmp(cmd_buf,cmd_list[i].cmd_name)) 
			{
				if(rec_arg_num<0 || rec_arg_num>cmd_list[i].max_args)
				{
					MY_DEBUGF(((uint8_t *)&"too many parameters!\r\n"));
				}
				else
				{
					cmd_list[i].handle( rec_arg_num, (void *)cmd_analyze.cmd_arg );
				}
				break;
			}

		}
		if(i >= sizeof(cmd_list)/sizeof(cmd_list[0]))
		{
			if(rec_num == 2)
			{
				MY_DEBUGF(((uint8_t *)&">>\r\n"));
			}else
			{
				MY_DEBUGF(((uint8_t *)&"not support cmd!\r\n"));
			}
		}
	}
}


