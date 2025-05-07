// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

// taf's Sofle RGB
// Based on Dan Evans' rgb_v3 keymap
// compile using: qmk compile -e CONVERT_TO=promicro_rp2040 -kb sofle -km rgb_v3_taf

#include <stdio.h>

#include QMK_KEYBOARD_H

#define INDICATOR_BRIGHTNESS 30

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)

// Light combinations
#define SET_INDICATORS(hsv) \
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {36+0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}
#define SET_UNDERGLOW(hsv) \
	{1, 6, hsv}, \
    {36+1, 6,hsv}
#define SET_NUMPAD(hsv)     \
	{36+15, 5, hsv},\
	{36+22, 3, hsv},\
	{36+27, 3, hsv}
#define SET_NUMROW(hsv) \
	{11, 2, hsv}, \
	{21, 2, hsv}, \
	{31, 2, hsv}, \
	{36+ 11, 2, hsv}, \
	{36+ 21, 2, hsv}, \
	{36+ 31, 2, hsv}
#define SET_INNER_COL(hsv)	\
	{32, 4, hsv}, \
    {36+ 32, 4, hsv}

#define SET_OUTER_COL(hsv) \
	{8, 4, hsv}, \
    {36+ 8, 4, hsv}
#define SET_THUMB_CLUSTER(hsv) 	\
	{26, 2, hsv}, \
	{36+ 26, 2, hsv}
#define SET_LAYER_ID(hsv) 	\
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {36+0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
	{1, 6, hsv}, \
    {36+1, 6, hsv}, \
	{8, 4, hsv}, \
	{36+ 8, 4, hsv}, \
	{26, 2, hsv}, \
	{36+ 26, 2, hsv}


enum sofle_layers {
    _QWERTY,
    _QWERTYCZ,
    _WINDOWS,
    _RAISE,
    _LOWER,
    _ADJUST,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_QWERTYCZ,
    KC_WINDOWS,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
};

enum {
    TD_HACEK_CARKA,
    TD_NEXT_PREV,
    TD_F_ELEVENTWELVE,
};

tap_dance_action_t tap_dance_actions[] = {
  [TD_HACEK_CARKA]  = ACTION_TAP_DANCE_DOUBLE(LALT(KC_E), LALT(KC_V)),
  [TD_NEXT_PREV]  = ACTION_TAP_DANCE_DOUBLE(KC_MPRV, KC_MNXT),
  [TD_F_ELEVENTWELVE]  = ACTION_TAP_DANCE_DOUBLE(KC_F11, KC_F12),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| Play  |    | Prev/Next  --+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Ctrl | Opt  | Cmd  | Raise| /Space  /       \Enter \  |Lower | Cmd  | Opt  | Ctrl |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_QWERTY] = LAYOUT(
    //,------------------------------------------------.                    ,---------------------------------------------------.
    KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_NO,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    KC_CAPS, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
    KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_MPLY,    TD(TD_NEXT_PREV)  ,KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                    KC_LCTL, KC_LALT, KC_LGUI, KC_RAISE, KC_SPC,     KC_ENT, KC_LOWER, KC_RGUI, KC_RALT, KC_RCTL
    //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),

/*
 * QWERTYCZ
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |Hacek |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ů  |  '   |
 * |------+------+------+------+------+------| Play  |    | Prev/Next  --+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Ctrl | Opt  | Cmd  | Raise| /Space  /       \Enter \  |Lower | Cmd  | Opt  | Ctrl |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_QWERTYCZ] = LAYOUT( // layer made with a custom abc extended layout in mind
    //,------------------------------------------------.                    ,---------------------------------------------------.
    KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    TD(TD_HACEK_CARKA),
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    KC_CAPS,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,   KC_K,    KC_L,    A(KC_SCLN), KC_QUOT,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
    KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_MPLY,    TD(TD_NEXT_PREV)  ,KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                    KC_LCTL, KC_LALT, KC_LGUI, KC_RAISE, KC_SPC,     KC_ENT, KC_LOWER ,KC_RGUI, KC_RALT, KC_RCTL
    //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),

/*
 * WINDOWS
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| Play  |    | Prev/Next  --+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Alt  | Win  | Ctrl |Raise | /Space  /       \Enter \  |Lower | Ctrl | Menu |AltGr |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_WINDOWS] = LAYOUT( // not yet tested
    //,------------------------------------------------.                    ,---------------------------------------------------.
    KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_NO,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    KC_CAPS, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
    KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_MPLY,    TD(TD_NEXT_PREV)  ,KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                    KC_LALT, KC_LGUI, KC_LCTL, KC_RAISE, KC_SPC,     KC_ENT, KC_LOWER, KC_RCTL, KC_APP, KC_RALT
    //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),

/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Esc  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11/F12|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Back |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   (  |   )  |   *  |   |  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   `  |   {  |   }  |   +  |   =  |-------|    |-------|   _  |   -  |   [  |   ]  |   \  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  _______,  KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  TD(TD_F_ELEVENTWELVE),
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  _______,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_BSPC,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  _______,  S(KC_1),S(KC_2), S(KC_3), S(KC_4), S(KC_5),                   S(KC_6), S(KC_7), S(KC_9), S(KC_0),S(KC_8), S(KC_BSLS),
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  _______,  KC_GRV, S(KC_LBRC),S(KC_RBRC),S(KC_EQL),KC_EQL,_______,_______,KC_MINS, S(KC_MINS), KC_LBRC, KC_RBRC,KC_BSLS,_______,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
/* LOWER
 * ,----------------------------------------.                     ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |RCLick|  MUp |LCLick|      |      |                    |      | PWrd |  Up  | NWrd |      | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |MLeft |MDown |MRight|      |      |-------.    ,-------|      | Left | Down | Right|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|      |      |      |      |      |-------|    |-------|      |      |      |      |      |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_LOWER] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,                      KC_NO,    KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_NO,   KC_NO,   KC_BTN2,KC_MS_U, KC_BTN1, KC_NO,                      KC_NO,   A(KC_LEFT),KC_UP,A(KC_RGHT),KC_NO,  _______,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_NO,   KC_NO,   KC_MS_L,KC_MS_D, KC_MS_R, KC_NO,                      KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,      KC_NO  ,KC_NO,    KC_NO,   KC_NO,  KC_NO,   KC_NO,   _______,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                 _______, _______, _______, _______,  _______   ,     _______, _______ ,  _______, _______, _______
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |EE_CLE|      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |QKBOOT|      |      |      |Win   |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |QWRT  |      |-------.    ,-------|      |QWRTCZ|      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-------i----------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  [_ADJUST] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  EE_CLR,  XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  QK_BOOT, XXXXXXX,XXXXXXX, XXXXXXX,KC_WINDOWS,XXXXXXX,                   XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  XXXXXXX, XXXXXXX,XXXXXXX, XXXXXXX,KC_QWERTY,XXXXXXX,                    XXXXXXX,KC_QWERTYCZ,XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  XXXXXXX, XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
};

// #ifdef RGBLIGHT_ENABLE
// char layer_state_str[70];
// // Now define the array of layers. Later layers take precedence

// // QWERTY,
// // Light on inner column and underglow
// const rgblight_segment_t PROGMEM layer_qwerty_lights[] = RGBLIGHT_LAYER_SEGMENTS(
//   SET_LAYER_ID(HSV_RED)

// );
// const rgblight_segment_t PROGMEM layer_colemakdh_lights[] = RGBLIGHT_LAYER_SEGMENTS(
//   SET_LAYER_ID(HSV_PINK)
// );

// // _NUM,
// // Light on outer column and underglow
// const rgblight_segment_t PROGMEM layer_num_lights[] = RGBLIGHT_LAYER_SEGMENTS(
// 	SET_LAYER_ID(HSV_TEAL)

// );
// // _SYMBOL,
// // Light on inner column and underglow
// const rgblight_segment_t PROGMEM layer_symbol_lights[] = RGBLIGHT_LAYER_SEGMENTS(
// 	SET_LAYER_ID(HSV_BLUE)

//     );
// // _COMMAND,
// // Light on inner column and underglow
// const rgblight_segment_t PROGMEM layer_command_lights[] = RGBLIGHT_LAYER_SEGMENTS(
//   SET_LAYER_ID(HSV_PURPLE)
// );

// //_NUMPAD
// const rgblight_segment_t PROGMEM layer_numpad_lights[] = RGBLIGHT_LAYER_SEGMENTS(
// 	SET_INDICATORS(HSV_ORANGE),
//     SET_UNDERGLOW(HSV_ORANGE),
// 	SET_NUMPAD(HSV_BLUE),
//     {7, 4, HSV_ORANGE},
//     {25, 2, HSV_ORANGE},
//     {36+6, 4, HSV_ORANGE},
//     {36+25, 2, HSV_ORANGE}
//     );
// // _SWITCHER   // light up top row
// const rgblight_segment_t PROGMEM layer_switcher_lights[] = RGBLIGHT_LAYER_SEGMENTS(
// 	SET_LAYER_ID(HSV_GREEN),
// 	SET_NUMROW(HSV_GREEN)
// );

// const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(

//     layer_qwerty_lights,
// 	layer_num_lights,// overrides layer 1
// 	layer_symbol_lights,
//     layer_command_lights,
// 	layer_numpad_lights,
// 	layer_switcher_lights,  // Overrides other layers
// 	layer_colemakdh_lights
// );

// layer_state_t layer_state_set_user(layer_state_t state) {
// 	rgblight_set_layer_state(0, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state,_QWERTY));
// 	rgblight_set_layer_state(7, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state,_COLEMAKDH));


// 	rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
// 	rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
// 	rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
// 	rgblight_set_layer_state(4, layer_state_cmp(state, _NUMPAD));
// 	rgblight_set_layer_state(5, layer_state_cmp(state, _SWITCH));
//     return state;
// }
// void keyboard_post_init_user(void) {
//     // Enable the LED layers
//     rgblight_layers = my_rgb_layers;

// 	rgblight_mode(10);// haven't found a way to set this in a more useful way

// }
// #endif

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
// 'qmklogo', 32x128px3
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0x60, 0x60, 0x6c, 0x6e, 
0x7e, 0x7c, 0x78, 0x70, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x19, 0x09, 0x0c, 0x04, 0x04, 0x06, 0x02, 0x02, 0x02, 
0x02, 0x02, 0x02, 0x04, 0x04, 0x04, 0x09, 0x09, 0x12, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 
0xc0, 0xbc, 0x83, 0x81, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0xc0, 0x40, 0x80, 0x80, 0x80, 
0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x83, 0x9c, 0xe0, 0x00, 
0x01, 0x1e, 0x60, 0x81, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x81, 0x60, 0x38, 0x07, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x04, 0x48, 0x88, 0x90, 0x90, 0x20, 0x20, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20, 0x20, 0x10, 0x90, 0x98, 0xc8, 0x04, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x07, 0x07, 0x07, 0x37, 0x37, 
0x3f, 0x1f, 0x0f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x70, 0x60, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 
0x80, 0xc0, 0xe0, 0xe0, 0x70, 0x60, 0x60, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x38, 0x70, 0x60, 0x60, 0x60, 0x70, 0x7c, 0x3f, 
0x0f, 0x03, 0x01, 0x00, 0x20, 0x20, 0x60, 0x70, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x38, 0x1c, 0x1c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
0x1c, 0x18, 0x38, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0c, 0x1c, 0x18, 0x38, 0x38, 0x38, 0x38, 0x38, 
0x18, 0x1c, 0x0e, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 
0x0e, 0x0e, 0x3f, 0x7f, 0x0e, 0x0e, 0x0c, 0x8c, 0x9c, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 
0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x39, 0x3d, 0x3d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0x1c, 0x0c, 0x0e, 0x0e, 0xfe, 0xfe, 0x0e, 
0x0c, 0x0c, 0x18, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x0e, 
0x0e, 0x06, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(qmk_logo, sizeof(qmk_logo));;
}

static void print_status_narrow(void) {
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("taf's\nSofle"), false);
    oled_write_ln_P(PSTR(""), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR(" Mac"), false);
            break;
        case _QWERTYCZ:
            oled_write_P(PSTR("MacCZ"), false);
            break;
        case _WINDOWS:
            oled_write_ln_P(PSTR(" Win"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjst"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    led_t led_state = host_keyboard_led_state();
    oled_write_ln_P(led_state.caps_lock ? PSTR("CapsL") : PSTR("     "), false);

    oled_write_ln_P(PSTR(""), false);
    oled_write_P(PSTR(" "), false);
    oled_write_ln(get_u8_str(get_current_wpm(), '0'), false);
    oled_write_ln_P(PSTR(" WPM"), false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                layer_move(_QWERTY);
            }
            return false;
        case KC_QWERTYCZ:
            if (record->event.pressed) {
                layer_move(_QWERTYCZ);
            }
            return false;
        case KC_WINDOWS:
            if (record->event.pressed) {
                layer_move(_WINDOWS);
            }
            return false;
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_WH_D);
        } else {
            tap_code(KC_WH_U);
        }
    }
    return false;
}

#endif
