#ifndef ENGINE
#define ENGINE

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// OAM sprite
// see http://wiki.nesdev.com/w/index.php/PPU_OAM
typedef struct sprite {
    uint8_t y;          // y pixel coordinate
    uint8_t tile_index; // index into pattern table
    uint8_t attributes; // attribute flags
    uint8_t x;          // x pixel coordinate
} sprite_t;

typedef enum {
	S_NONE = 0x00,
	S_TITLE = (1<<0),
	S_CREDIT = (1<<1),
	S_THE_END = (1<<2),
	S_LEVEL = (1<<3),
	S_LEVEL_BACK = (1<<4),
	S_LEVEL_FRONT = (1<<5),
	S_LEVEL_000 = (1<<6),
	S_LEVEL_128 = (1<<7),
	S_ALL = (1<<8),
} ScreenId;


typedef enum {
	C_NONE = 16,
	C_POS_X_MIN = 17,
	C_POS_X_MAX = 18,
	C_POS_Y_MIN = 19,
	C_POS_Y_MAX = 20,
	C_LEVEL = 21
} Collision;

typedef struct {
	uint8_t x;
	uint8_t y;
} Position;

typedef struct {
	uint16_t score;
	char* nickname;
} HighScore;

typedef struct {
	uint8_t games_count;
	HighScore highscores[];
} HighScores;

typedef struct {
	uint8_t coins;
	uint8_t health;
	char* name;
	bool active;
	bool dead;  
	Position position;
	Collision collision;
} Player;

typedef struct {
	void (*collide)(sprite_t*, Player*);
	sprite_t sprites[];
} Graphic;

typedef struct {
	ScreenId id;
	uint8_t inputCode;
	void (*callback)(Player*);
} Action;

typedef struct {
    void (* const exec)();
    uint8_t *active;
    uint8_t *remainingExecutions;
} Anim;

typedef struct {
	ScreenId id;
	uint8_t *initialized;
	void (* const update)();
	void (* const init)();
	Graphic graphics[];
} Screen;

typedef struct {
	ScreenId screen;
	Action* actions[];
} ActionProvider;

typedef struct {
	Player player1;
	Player player2;
	HighScores highscores;
	ScreenId screen;
    uint8_t screenIndex;
} GameState;


void engine_handleInput(void);
void engine_detectCollisions(void);
void engine_detectCollisionWithPlayer(Player*, sprite_t*, Graphic*);
void engine_start(void);
void engine_frame_update(void);

//#pragma bss-name(push, "OAM")

GameState engine = {{0,0,"Player1",false,true,{0,0},C_NONE},{0,0,"Player2",false,true,{0,0},C_NONE}};
Screen* engine_screens[] = {};
ActionProvider* engine_actions[32] = {};

//uint8_t oam_tmp1 = 1;
//uint8_t oam_tmp2 = 2;
//uint8_t oam_tmp3 = 3;

unsigned char SPRITES[1];
//#pragma bss-name(pop)

#endif;