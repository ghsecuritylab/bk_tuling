#pragma once

#include <cJSON.h>
#include <rtthread.h>
#include <rtservice.h>

/*
 * Ƶ��
 * ����Ƶ�����ƶ˴����������ӣ��豸���������������ӻ�ø����б�Ҳ�����л���ͬ������ʵ�ֲ�ͬ��Ƶ���л�
 * (�����ϣ�Ƶ��Ҳ�����Ǳ��صĸ���)
 */

struct player_channel_plugin
{
    char *name;
    int(*play)(cJSON *channel);

    rt_list_t list;
};

 /* ��ʼ��Ƶ����������Ƶ���б� */
int player_channel_init(void);
int player_channel_register_plugin(struct player_channel_plugin* plugin);

/* ��һ��Ƶ�� */
void player_channel_next(void);
/* ��һ��Ƶ�� */
void player_channel_prev(void);
