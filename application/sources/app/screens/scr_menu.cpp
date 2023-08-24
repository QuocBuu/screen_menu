#include "scr_menu.h"

/*****************************************************************************/
/* Variable and Struct Declaration - Menu game */
/*****************************************************************************/
#define STEP_MENU_CHOSSE				(22)
#define NUMBER_MENU_ITEMS				(4)
#define	SCREEN_MENU_H					(64)

#define MENU_ITEM_ARRDESS_1				(STEP_MENU_CHOSSE)
#define MENU_ITEM_ARRDESS_2				(STEP_MENU_CHOSSE*2)
#define MENU_ITEM_ARRDESS_3				(STEP_MENU_CHOSSE*3)
#define MENU_ITEM_ARRDESS_4				(STEP_MENU_CHOSSE*4)

int k;
struct menu_items{
// menu items
	unsigned int is_archery_game : 1;
	unsigned int is_setting : 1;
	unsigned int is_charts : 1;
	unsigned int is_exit_0 : 1;
	unsigned int is_exit_1 : 1;
};
	
union scr_menu_t {
	uint8_t _id=1;		// if items >> => uint8_t -> uint16_t ->uint32_t
	menu_items items;
};

scr_menu_t menu_chosse;

// Screen menu
typedef struct {
	uint8_t screen;
	uint8_t location;
	uint8_t axis_y = location * STEP_MENU_CHOSSE;
	uint8_t items;
	// uint8_t frames_items[3] = {
	// 	screen,
	// 	screen + 1,
	// 	screen + 2
	// };

	// void update() {
	// 	if (items < frames_items[0]) {
	// 		screen--;
	// 	} 
	// 	else if (items > frames_items[2]) {
	// 		screen++;
	// 	}
	// }
	// constrain(items, 0, NUMBER_MENU_ITEMS);
} Screen;

Screen scr;

// Scroll bar
typedef struct {
#define AR_GAME_MENU_SCROLL_BAR_AXIS_X		(126)
#define AR_GAME_MENU_SCROLL_BAR_AXIS_Y		(0)
#define AR_GAME_MENU_SCROLL_BAR_SIZE_W		(3)
#define AR_GAME_MENU_SCROLL_BAR_SIZE_H		(SCREEN_MENU_H / NUMBER_MENU_ITEMS)
	uint8_t axis_x = AR_GAME_MENU_SCROLL_BAR_AXIS_X;
	uint8_t axis_y = AR_GAME_MENU_SCROLL_BAR_SIZE_H*k;
	uint8_t size_W = AR_GAME_MENU_SCROLL_BAR_SIZE_W;
	uint8_t size_h = AR_GAME_MENU_SCROLL_BAR_SIZE_H;
} scr_menu_scroll_bar_t;

scr_menu_scroll_bar_t scroll_bar;

// Frames
typedef struct {
#define AR_GAME_MENU_FRAMES_AXIS_X			(0)
#define AR_GAME_MENU_FRAMES_AXIS_Y			(STEP_MENU_CHOSSE + menu_location.screen)
#define AR_GAME_MENU_FRAMES_SIZE_W			(123)
#define AR_GAME_MENU_FRAMES_SIZE_H			(20)
#define AR_GAME_MENU_FRAMES_SIZE_R			(3)

	uint8_t axis_x = AR_GAME_MENU_FRAMES_AXIS_X;
	uint8_t axis_y;
	uint8_t size_w = AR_GAME_MENU_FRAMES_SIZE_W;
	uint8_t size_h = AR_GAME_MENU_FRAMES_SIZE_H;
	uint8_t size_r = AR_GAME_MENU_FRAMES_SIZE_R;
} scr_menu_frames_t;

scr_menu_frames_t frame_white;
scr_menu_frames_t frame[3];

#define FRAMES_AXIS_Y() \
do { \
	frame_white.axis_y = k*22; \
	frame[0].axis_y = 0; \
	frame[1].axis_y = 22; \
	frame[2].axis_y = 44; \
} while(0);

void frame_white_location() {
	if (frame_white.axis_y == frame[1].axis_y) {
		// button [UP]
		/* sua lai location sceen */
		/* frame khong doi */
		/* icon thay doi - ip doi >> 1*/
		// Button [Down]
		/* frame_white.axis_y == frame[2].axis_y*/
		// Button [Mode]
		/* screen_tran()*/
	}

	if (frame_white.axis_y == frame[2].axis_y) {
		// button [UP]
		/* frame_white.axis_y == frame[1].axis_y*/
		// Button [Down]
		/* frame_white.axis_y == frame[2].axis_y*/
		// Button [Mode]
		/* screen_tran()*/
	}

	if (frame_white.axis_y == frame[3].axis_y) {
		// button [Down]
		/* sua lai location sceen */
		/* frame khong doi */
		/* icon thay doi - ip doi << 1*/
		// Button [Up]
		/* frame_white.axis_y == frame[2].axis_y*/
		// Button [Mode]
		/* screen_tran()*/
	}
}

// items addrees
static uint8_t menu_items_addr[NUMBER_MENU_ITEMS];
#define MENU_ITEMS_ADDR() \
do { \
	for (uint8_t i = 1; i <= NUMBER_MENU_ITEMS; i++) { \
		menu_items_addr[i] = STEP_MENU_CHOSSE*i; \
	} \
} while(0);

// Menu items icon
static const uint8_t *menu_items_icon[NUMBER_MENU_ITEMS] = {
	archery_icon, \
	setting_icon, \
	chart_icon, \
	exit_icon \
};

uint8_t menu_items_icon_color[NUMBER_MENU_ITEMS] = {
	!menu_chosse.items.is_archery_game, \
	!menu_chosse.items.is_setting, \
	!menu_chosse.items.is_charts, \
	!menu_chosse.items.is_exit_0, \
};
#define MENU_ITEMS_ICON_COLOR() \
do { \
	menu_items_icon_color[0] = !menu_chosse.items.is_archery_game; \
	menu_items_icon_color[1] = !menu_chosse.items.is_setting; \
	menu_items_icon_color[2] = !menu_chosse.items.is_charts; \
	menu_items_icon_color[3] = !menu_chosse.items.is_exit_0; \
} while(0);

uint8_t menu_items_icon_size_w[NUMBER_MENU_ITEMS] = {
	15, \
	16, \
	16, \
	15, \
};
uint8_t menu_items_icon_size_h[NUMBER_MENU_ITEMS] = {
	15, \
	16, \
	16, \
	15, \
};
uint8_t menu_items_icon_axis_y[3] = {
	2,
	24,
	46,
};

// Menu items name
static char menu_items_name[NUMBER_MENU_ITEMS][20] = {
	"   Archery Game1  ", 
	"   Archery Game2  ", 
	"   Archery Game3  ", 
	"   Archery Game4  " 
};

// typedef struct {
// 	// menu object location
// 	uint8_t chosse;
// 	uint8_t scroll_bar;
// 	uint8_t screen;
// } scr_menu_game_location_t;

// static scr_menu_game_location_t menu_location;


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
								menu_items_icon[scr.screen + i], \
								menu_items_icon_size_w[scr.screen + i], \
								menu_items_icon_size_h[scr.screen + i], \
								menu_items_icon_color[scr.screen + i]);
	}
	// Text Menu
	view_render.setTextSize(1);
	for (uint8_t i = 0; i < 3; i++) {
		view_render.setTextColor(menu_items_icon_color[scr.screen + i]);
		view_render.setCursor(AR_GAME_MENU_TEXT_AXIS_X, menu_items_icon_axis_y[i]+5);
		// view_render.print("   Archery Game  ");
		view_render.print(menu_items_name[scr.screen + i]);
	}
}

/*****************************************************************************/
/* Handle - Menu game */
/*****************************************************************************/
void update_menu_screen_chosse() {
	// switch (menu_location.chosse) {
	// case MENU_ITEM_ARRDESS_1: {
	// 	// menu_chosse.item.archery_game = BLACK;
	// 	// menu_chosse.item.setting = WHITE;
	// 	// menu_chosse.item.charts = WHITE;
	// 	// menu_chosse.item.exit = WHITE;
	// 	// menu_location.scroll_bar = 0;
	// 	// menu_location.screen = 0;
	// }
	// 	break;

	// case MENU_ITEM_ARRDESS_2: {
	// 	// menu_chosse.item.archery_game = WHITE;
	// 	// menu_chosse.item.setting = BLACK;
	// 	// menu_chosse.item.charts = WHITE;
	// 	// menu_chosse.item.exit = WHITE;
	// 	// menu_location.scroll_bar = AR_GAME_MENU_SCROLL_BAR_SIZE_H;
	// }
	// 	break;

	// case MENU_ITEM_ARRDESS_3: {
	// 	// menu_chosse.item.archery_game = WHITE;
	// 	// menu_chosse.item.setting = WHITE;
	// 	// menu_chosse.item.charts = BLACK;
	// 	// menu_chosse.item.exit = WHITE;
	// 	// menu_location.scroll_bar = AR_GAME_MENU_SCROLL_BAR_SIZE_H*2;
	// }
	// 	break;

	// case MENU_ITEM_ARRDESS_4: {
	// 	// menu_chosse.item.archery_game = WHITE;
	// 	// menu_chosse.item.setting = WHITE;
	// 	// menu_chosse.item.charts = WHITE;
	// 	// menu_chosse.item.exit = BLACK;
	// 	// menu_location.scroll_bar = AR_GAME_MENU_SCROLL_BAR_SIZE_H*3;
	// 	// menu_location.screen = STEP_MENU_CHOSSE;
	// }
	// 	break;

	// default:
	// 	break;
	// }
}

void scr_menu_handle(ak_msg_t* msg) {
	switch (msg->sig) {
	case AC_DISPLAY_INITIAL: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
		view_render.initialize();
		view_render_display_on();
		FRAMES_AXIS_Y();
		MENU_ITEMS_ADDR();
		// setup one shot
		// if(1) {
		// 	// menu_chosse.item.archery_game = BLACK;
		// 	// menu_chosse.item.setting = WHITE;
		// 	// menu_chosse.item.charts = WHITE;
		// 	// menu_chosse.item.exit_0 = WHITE;
		// 	// menu_location.chosse = MENU_ITEM_ARRDESS_1;
		// }
	}
		break;
	
	// case AC_DISPLAY_SHOW_IDLE: {
		// SCREEN_TRAN(scr_idle_handle,&scr_idle);
	// }
	// 	break;

	case AC_DISPLAY_BUTTON_MODE_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_MODE_RELEASED\n");
		// Screen transition
		// switch (menu_location.chosse) {
		// case MENU_ITEM_ARRDESS_1: {
		// 	// SCREEN_TRAN(scr_archery_game_handle,	&scr_archery_game	);
		// }
		// 	break;

		// case MENU_ITEM_ARRDESS_2: {
		// 	// SCREEN_TRAN(scr_game_setting_handle,	&scr_game_setting	);
		// }
		// 	break;

		// case MENU_ITEM_ARRDESS_3: {
		// 	// SCREEN_TRAN(scr_charts_game_handle, 	&scr_charts_game	);
		// }
		// 	break;

		// case MENU_ITEM_ARRDESS_4: {
		// 	// SCREEN_TRAN(scr_idle_handle, 			&scr_idle			);
		// }
		// 	break;

		// default:
		// 	break;
		// }
	}
		// BUZZER_PlayTones(tones_cc);
		break;

	case AC_DISPLAY_BUTTON_UP_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_UP_RELEASED\n");
		// Move up
		// menu_location.chosse -= STEP_MENU_CHOSSE;
		// if (menu_location.chosse < MENU_ITEM_ARRDESS_1) { 
		// 	menu_location.chosse = MENU_ITEM_ARRDESS_4; 
		// }
		// Update menu screen
		k--;
		frame_white.axis_y = k*22;
		menu_chosse._id = 1>>k;
		scroll_bar.axis_y = AR_GAME_MENU_SCROLL_BAR_SIZE_H*k;
		// update_menu_screen_chosse();
		}
		break;

	case AC_DISPLAY_BUTTON_DOWN_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_DOWN_RELEASED\n");
		// Move down
		// menu_location.chosse += STEP_MENU_CHOSSE;
		// if (menu_location.chosse > MENU_ITEM_ARRDESS_4) { 
		// 	menu_location.chosse = MENU_ITEM_ARRDESS_1;
		// }
		// Update menu screen
		k++;
		frame_white.axis_y = k*22;
		menu_chosse._id = 2;
		scroll_bar.axis_y = AR_GAME_MENU_SCROLL_BAR_SIZE_H*k;
		// update_menu_screen_chosse();
	}
		break;

	default:
		break;
	}
}
