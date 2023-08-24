#include "scr_menu.h"


/*****************************************************************************/
/* Variable and Struct Declaration - Menu game */
/*****************************************************************************/
// Screen 
#define STEP_MENU_CHOSSE				(22)
#define NUMBER_MENU_ITEMS				(11)
#define	SCREEN_MENU_H					(64)

#define FRAMES_AXIS_Y() \
do { \
	frame_white.axis_y =frame[screen_menu.location-screen_menu.screen].axis_y; \
	frame[0].axis_y = 0; \
	frame[1].axis_y = 22; \
	frame[2].axis_y = 44; \
} while(0);

#define MENU_ITEMS_ICON_COLOR() \
do { \
	menu_items_icon_color[0] = !menu_chosse.items.is_archery_game; \
	menu_items_icon_color[1] = !menu_chosse.items.is_setting; \
	menu_items_icon_color[2] = !menu_chosse.items.is_charts; \
	menu_items_icon_color[3] = !menu_chosse.items.is_exit_0; \
	menu_items_icon_color[4] = !menu_chosse.items.is_exit_1; \
	menu_items_icon_color[5] = !menu_chosse.items.is_exit_2; \
	menu_items_icon_color[6] = !menu_chosse.items.is_exit_3; \
	menu_items_icon_color[7] = !menu_chosse.items.is_exit_4; \
	menu_items_icon_color[8] = !menu_chosse.items.is_exit_5; \
	menu_items_icon_color[9] = !menu_chosse.items.is_exit_6; \
	menu_items_icon_color[10] = !menu_chosse.items.is_exit_7; \
} while(0);

struct menu_items{
// menu items
	unsigned int is_archery_game : 1;
	unsigned int is_setting : 1;
	unsigned int is_charts : 1;
	unsigned int is_exit_0 : 1;
	unsigned int is_exit_1 : 1;
	unsigned int is_exit_2 : 1;
	unsigned int is_exit_3 : 1;
	unsigned int is_exit_4 : 1;
	unsigned int is_exit_5 : 1;
	unsigned int is_exit_6 : 1;
	unsigned int is_exit_7 : 1;
	unsigned int is_exit_9 : 1;
	unsigned int is_exit_10 : 1;
	unsigned int is_exit_11 : 1;
};
// Menu items icon
static const uint8_t *menu_items_icon[NUMBER_MENU_ITEMS] = {
	archery_icon, \
	setting_icon, \
	chart_icon, \
	exit_icon, \
	archery_icon, \
	archery_icon, \
	archery_icon, \
	archery_icon, \
	archery_icon, \
	archery_icon, \
	archery_icon, \
};

// Menu items color
uint8_t menu_items_icon_color[NUMBER_MENU_ITEMS];
uint8_t menu_items_icon_size_w[NUMBER_MENU_ITEMS] = {
	15, \
	16, \
	16, \
	15, \
	15, \
	15, \
	15, \
	15, \
	15, \
	15, \
	15, \
};
uint8_t menu_items_icon_size_h[NUMBER_MENU_ITEMS] = {
	15, \
	16, \
	16, \
	15, \
	15, \
	15, \
	15, \
	15, \
	15, \
	15, \
	15, \
};
uint8_t menu_items_icon_axis_y[3] = {2, 24,	46};

// Menu items name
static char menu_items_name[NUMBER_MENU_ITEMS][20] = {
	"   Archery Game1  ", 
	"   Archery Game2  ", 
	"   Archery Game3  ", 
	"   Archery Game4  ",
	"   Archery Game5  ",
	"   Archery Game6  ",
	"   Archery Game7  ",
	"   Archery Game8  ",
	"   Archery Game9  ",
	"   Archery Game10 ",
	"   Archery Game11 ",
};

typedef struct {
	int screen;
	int location;
} Screen;

Screen screen_menu;

// Menu items

union scr_menu_t {
	uint32_t _id = 1;		// if items >> => uint8_t -> uint16_t ->uint32_t
	menu_items items;
};

scr_menu_t menu_chosse;

// Scroll bar
typedef struct {
	uint8_t axis_x = 126;
	uint8_t axis_y = 0;
	uint8_t size_W = 3;
	uint8_t size_h = SCREEN_MENU_H / NUMBER_MENU_ITEMS;
} scr_menu_scroll_bar_t;

scr_menu_scroll_bar_t scroll_bar;

// Frames
typedef struct {
	uint8_t axis_x = 0;
	uint8_t axis_y = 0;
	uint8_t size_w = 123;
	uint8_t size_h = 20;
	uint8_t size_r = 3;
} scr_menu_frames_t;

scr_menu_frames_t frame_white;
scr_menu_frames_t frame[3];

/*****************************************************************************/
/* View - Menu game */
/*****************************************************************************/
static void view_scr_menu();

view_dynamic_t dyn_view_menu = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_menu
};

view_screen_t scr_menu = {
	&dyn_view_menu,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void view_scr_menu() {
// ICON	
#define AR_GAME_MENU_ICON_AXIS_X			(7)
#define AR_GAME_MENU_ICON_AXIS_Y			(AR_GAME_MENU_FRAMES_AXIS_Y - 2)
#define AR_GAME_MENU_ICON_SIZE_W			(15)
#define AR_GAME_MENU_ICON_SIZE_H			(15)
// Text
#define AR_GAME_MENU_TEXT_AXIS_X			(20)
#define AR_GAME_MENU_TEXT_AXIS_Y			(AR_GAME_MENU_ICON_AXIS_Y - 5)
	// Scroll bar
	view_render.fillRect(	scroll_bar.axis_x - 1, \
							scroll_bar.axis_y, \
							scroll_bar.size_W, \
							scroll_bar.size_h, \
							WHITE);
	view_render.drawBitmap(	scroll_bar.axis_x, \
							0, \
							dot_icon, \
							1, \
							SCREEN_MENU_H, \
							WHITE);
	// Frame White
	view_render.fillRoundRect(	frame_white.axis_x, \
								frame_white.axis_y, \
								frame_white.size_w, \
								frame_white.size_h, \
								frame_white.size_r, \
								WHITE);
	for (uint8_t i = 0; i < 3; i++) {
	// Frames
		view_render.drawRoundRect(	frame[i].axis_x, \
									frame[i].axis_y, \
									frame[i].size_w, \
									frame[i].size_h, \
									frame[i].size_r, \
									WHITE);
	// Icon
		view_render.drawBitmap(	AR_GAME_MENU_ICON_AXIS_X, \
								menu_items_icon_axis_y[i], \
								menu_items_icon[screen_menu.screen + i], \
								menu_items_icon_size_w[screen_menu.screen + i], \
								menu_items_icon_size_h[screen_menu.screen + i], \
								menu_items_icon_color[screen_menu.screen + i]);
	}
	// Text Menu
	view_render.setTextSize(1);
	for (uint8_t i = 0; i < 3; i++) {
		view_render.setTextColor(menu_items_icon_color[screen_menu.screen + i]);
		view_render.setCursor(AR_GAME_MENU_TEXT_AXIS_X, menu_items_icon_axis_y[i]+5);
		view_render.print(menu_items_name[screen_menu.screen + i]);
	}
}

/*****************************************************************************/
/* Handle - Menu game */
/*****************************************************************************/
void update_menu_screen_chosse() {
	constrain(screen_menu.location, 1, NUMBER_MENU_ITEMS-1);
	menu_chosse._id = 1<<screen_menu.location;
	FRAMES_AXIS_Y();
	MENU_ITEMS_ICON_COLOR();
	scroll_bar.axis_y = (SCREEN_MENU_H*screen_menu.location / NUMBER_MENU_ITEMS);
	constrain(screen_menu.screen, 1, NUMBER_MENU_ITEMS-3);	
}

void scr_menu_handle(ak_msg_t* msg) {
	switch (msg->sig) {
	case AC_DISPLAY_INITIAL: {
		APP_DBG_SIG("AC_DISPLAY_INITIAL\n");
		view_render.initialize();
		view_render_display_on();
		update_menu_screen_chosse();
	}
		break;

	case AC_DISPLAY_BUTTON_MODE_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_MODE_RELEASED\n");
		switch (screen_menu.location) {
		case 1:
			/* code */
			break;
		
		default:
			break;
		}

	}
		break;

	case AC_DISPLAY_BUTTON_UP_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_UP_RELEASED\n");
		if (screen_menu.location > 0) {screen_menu.location--;}
		if (frame_white.axis_y == frame[0].axis_y) {
			if (screen_menu.screen > 0) {screen_menu.screen--;}
		}
		else if (frame_white.axis_y == frame[1].axis_y) {
			frame_white.axis_y = frame[0].axis_y;
		}
		else if (frame_white.axis_y == frame[2].axis_y) {
			frame_white.axis_y = frame[1].axis_y;
		}
		update_menu_screen_chosse();
	}
		break;

	case AC_DISPLAY_BUTTON_DOWN_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_DOWN_RELEASED\n");
		if (screen_menu.location < NUMBER_MENU_ITEMS-1) {screen_menu.location++;}
		if (frame_white.axis_y == frame[0].axis_y) {
			frame_white.axis_y = frame[1].axis_y;
		}
		else if (frame_white.axis_y == frame[1].axis_y) {
			frame_white.axis_y = frame[2].axis_y;
		}
		else if (frame_white.axis_y == frame[2].axis_y) {
			if (screen_menu.screen < NUMBER_MENU_ITEMS-3) {screen_menu.screen++;}
		}
		update_menu_screen_chosse();
	}
		break;

	default:
		break;
	}
}
