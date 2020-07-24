#pragma once

#include "KeyModifiers.h"

//values from glfw3.h

namespace input
{
	/* The unknown key */
	constexpr int KEY_UNKNOWN = -1;
								   
	/* Printable keys */			   
	constexpr int KEY_SPACE            = 32;
	constexpr int KEY_APOSTROPHE       = 39; /* ' */
	constexpr int KEY_COMMA            = 44; /* , */
	constexpr int KEY_MINUS            = 45; /* - */
	constexpr int KEY_PERIOD           = 46; /* . */
	constexpr int KEY_SLASH            = 47; /* / */
	constexpr int KEY_0                = 48;
	constexpr int KEY_1                = 49;
	constexpr int KEY_2                = 50;
	constexpr int KEY_3                = 51;
	constexpr int KEY_4                = 52;
	constexpr int KEY_5                = 53;
	constexpr int KEY_6                = 54;
	constexpr int KEY_7                = 55;
	constexpr int KEY_8                = 56;
	constexpr int KEY_9                = 57;
	constexpr int KEY_SEMICOLON        = 59; /* ; */
	constexpr int KEY_EQUAL            = 61; /* = */
	constexpr int KEY_A                = 65;
	constexpr int KEY_B                = 66;
	constexpr int KEY_C                = 67;
	constexpr int KEY_D                = 68;
	constexpr int KEY_E                = 69;
	constexpr int KEY_F                = 70;
	constexpr int KEY_G                = 71;
	constexpr int KEY_H                = 72;
	constexpr int KEY_I                = 73;
	constexpr int KEY_J                = 74;
	constexpr int KEY_K                = 75;
	constexpr int KEY_L                = 76;
	constexpr int KEY_M                = 77;
	constexpr int KEY_N                = 78;
	constexpr int KEY_O                = 79;
	constexpr int KEY_P                = 80;
	constexpr int KEY_Q                = 81;
	constexpr int KEY_R                = 82;
	constexpr int KEY_S                = 83;
	constexpr int KEY_T                = 84;
	constexpr int KEY_U                = 85;
	constexpr int KEY_V                = 86;
	constexpr int KEY_W                = 87;
	constexpr int KEY_X                = 88;
	constexpr int KEY_Y                = 89;
	constexpr int KEY_Z                = 90;
	constexpr int KEY_LEFT_BRACKET     = 91; /* [ */
	constexpr int KEY_BACKSLASH        = 92; /* \ */
	constexpr int KEY_RIGHT_BRACKET    = 93; /* ] */
	constexpr int KEY_GRAVE_ACCENT     = 96; /* ` */
	constexpr int KEY_WORLD_1          = 161; /* non-US #1 */
	constexpr int KEY_WORLD_2          = 162; /* non-US #2 */

	/* Function keys */
	constexpr int KEY_ESCAPE           = 256;
	constexpr int KEY_ENTER            = 257;
	constexpr int KEY_TAB              = 258;
	constexpr int KEY_BACKSPACE        = 259;
	constexpr int KEY_INSERT           = 260;
	constexpr int KEY_DELETE           = 261;
	constexpr int KEY_RIGHT            = 262;
	constexpr int KEY_LEFT             = 263;
	constexpr int KEY_DOWN             = 264;
	constexpr int KEY_UP               = 265;
	constexpr int KEY_PAGE_UP          = 266;
	constexpr int KEY_PAGE_DOWN        = 267;
	constexpr int KEY_HOME             = 268;
	constexpr int KEY_END              = 269;
	constexpr int KEY_CAPS_LOCK        = 280;
	constexpr int KEY_SCROLL_LOCK      = 281;
	constexpr int KEY_NUM_LOCK         = 282;
	constexpr int KEY_PRINT_SCREEN     = 283;
	constexpr int KEY_PAUSE            = 284;
	constexpr int KEY_F1               = 290;
	constexpr int KEY_F2               = 291;
	constexpr int KEY_F3               = 292;
	constexpr int KEY_F4               = 293;
	constexpr int KEY_F5               = 294;
	constexpr int KEY_F6               = 295;
	constexpr int KEY_F7               = 296;
	constexpr int KEY_F8               = 297;
	constexpr int KEY_F9               = 298;
	constexpr int KEY_F10              = 299;
	constexpr int KEY_F11              = 300;
	constexpr int KEY_F12              = 301;
	constexpr int KEY_F13              = 302;
	constexpr int KEY_F14              = 303;
	constexpr int KEY_F15              = 304;
	constexpr int KEY_F16              = 305;
	constexpr int KEY_F17              = 306;
	constexpr int KEY_F18              = 307;
	constexpr int KEY_F19              = 308;
	constexpr int KEY_F20              = 309;
	constexpr int KEY_F21              = 310;
	constexpr int KEY_F22              = 311;
	constexpr int KEY_F23              = 312;
	constexpr int KEY_F24              = 313;
	constexpr int KEY_F25              = 314;
	constexpr int KEY_KP_0             = 320;
	constexpr int KEY_KP_1             = 321;
	constexpr int KEY_KP_2             = 322;
	constexpr int KEY_KP_3             = 323;
	constexpr int KEY_KP_4             = 324;
	constexpr int KEY_KP_5             = 325;
	constexpr int KEY_KP_6             = 326;
	constexpr int KEY_KP_7             = 327;
	constexpr int KEY_KP_8             = 328;
	constexpr int KEY_KP_9             = 329;
	constexpr int KEY_KP_DECIMAL       = 330;
	constexpr int KEY_KP_DIVIDE        = 331;
	constexpr int KEY_KP_MULTIPLY      = 332;
	constexpr int KEY_KP_SUBTRACT      = 333;
	constexpr int KEY_KP_ADD           = 334;
	constexpr int KEY_KP_ENTER         = 335;
	constexpr int KEY_KP_EQUAL         = 336;
	constexpr int KEY_LEFT_SHIFT       = 340;
	constexpr int KEY_LEFT_CONTROL     = 341;
	constexpr int KEY_LEFT_ALT         = 342;
	constexpr int KEY_LEFT_SUPER       = 343;
	constexpr int KEY_RIGHT_SHIFT      = 344;
	constexpr int KEY_RIGHT_CONTROL    = 345;
	constexpr int KEY_RIGHT_ALT        = 346;
	constexpr int KEY_RIGHT_SUPER      = 347;
	constexpr int KEY_MENU             = 348;
}
