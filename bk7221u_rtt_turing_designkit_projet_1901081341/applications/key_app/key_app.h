#ifndef _KEY_APP_H_
#define _KEY_APP_H_
#include"rtconfig.h"

#define KEY_BUTTON_DEBUG                    0
#define KEY_BUTTION_TABLE_CFG               0
#define SD_CHECK_SCAN_INTERVAL_MS		    (20)
#define LONG_PRESS_HOLD_FILTERS_TIMES       (60)

#define MAP_KEY_PLAY_PAUSE_PIN				4 //P4 
#define MAP_KEY_VOLUME_ADD_NEXT 			5 //P3 
#define MAP_KEY_VOLUME_REDUCE_PREV			3 //P2 
#define MAP_KEY_VOICE						2//P7 
#define MAP_WECHAT							7 //P6 


//#define MAP_KEY_PLAY_PAUSE_PIN				4 //P4 
//#define MAP_KEY_VOLUME_ADD_NEXT 			7 //P3 
//#define MAP_KEY_VOLUME_REDUCE_PREV			2 //P2 
//#define MAP_KEY_VOICE						3//P7 
//#define MAP_WECHAT							5 //P6 


enum{
#if (USING_DEMO_BOARD == 1)
	_KEY_PLAY_PAUSE_SHORT_PRESS = 0,
	_KEY_PLAY_PAUSE_LONG_PRESS,
	_KEY_VOLUME_ADD_NEXT_SHORT_PRESS,
	_KEY_VOLUME_ADD_NEXT_LONG_PRESS,
	_KEY_VOLUME_ADD_NEXT_LONG_START_PRESS,
	_KEY_VOLUME_ADD_NEXT_DOUBLE_PRESS,

	_KEY_VOLUME_REDUCE_PREV_SHORT_PRESS,
	_KEY_VOLUME_REDUCE_PREV_LONG_PRESS,
	_KEY_VOLUME_REDUCE_PREV_LONG_START_PRESS,
	_KEY_VOLUME_REDUCE_PREV_DOUBLE_PRESS,
	
	_KEY_PLAY_VOICE_SHORT_PRESS,
	_KEY_PLAY_VOICE_LONG_PRESS,
	
	_KEY_PLAY_WECHAT_SHORT_PRESS,
	_KEY_PLAY_WECHAT_LONG_PRESS,
	_KEY_PLAY_WECHAT_LONG_START_PRESS,
	_KEY_PLAY_WECHAT_DOUBLE_PRESS,

	_KEY_CONFIG_NET_LONG_PRESS,
	_KEY_MUSIC_COLLECT_SHORT_PRESS,
#else
	_KEY_NEXT_SHORT_PRESS = 0,
	_KEY_NEXT_LONG_PRESS,
	_KEY_PREV_SHORT_PRESS,
	_KEY_PREV_LONG_PRESS,
	_KEY_COLLECT_SHORT_PRESS,
	_KEY_COLLECT_LONG_PRESS,
	_KEY_WECHAT_SHORT_PRESS,
	_KEY_WECHAT_LONG_PRESS,
	_KEY_VOICE_SHORT_PRESS,
	_KEY_VOICE_LONG_PRESS,
	_KEY_CONFIG_NET_LONG_PRESS,
#endif
};

#define SD_STATUS_CHECK_PIN				        12
#define SD_DEBOUNCE_COUNT 			            10
#define SD_INSTER_STATUS_CHECK_PIN_LEVEL        (0)

#define LINEIN_STATUS_CHECK_PIN	                8
#define LINEIN_DEBOUNCE_COUNT 			        10
#define LINEIN_INSTER_STATUS_CHECK_PIN_LEVEL    (0)

typedef enum{
	OFFLINE_STATUS = 0x00,
	ONLINE_STATUS,
}CHECK_STATUS_E;

void key_button_app_init(void);
void adc_button_app_init(void);
int sd_is_online(void);
void sd_check_init(void);
void send_keymode_2_offline(void);
void send_keymode_2_turing(void);
#endif  /*_KEY_APP_H_*/
