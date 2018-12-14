#ifndef CONSTANTS_H
#define CONSTANTS_H

#define VERSION std::string("1.0")
#define PORT 51130

#define DISCORD_DETAILS "Making Client commands..."

#define FONT "assets/fonts/Lucida Sans.ttf"
#define JA_FONT "assets/fonts/KozGoPro-Regular.otf"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define MARGIN 30.f //
#define PADDING 10.f //
#define TAB_HEIGHT 20.f
#define MEMBERLIST_WIDTH 100.f
#define TYPEBOX_HEIGHT 50.f

#define CHATBOX_WIDTH WINDOW_WIDTH - 2.f * MARGIN - MEMBERLIST_WIDTH - PADDING
#define CHATBOX_HEIGHT WINDOW_HEIGHT - 2.f * MARGIN - TYPEBOX_HEIGHT - PADDING - TAB_HEIGHT
#define TYPEBOX_WIDTH CHATBOX_WIDTH + MEMBERLIST_WIDTH - TYPEBOX_HEIGHT

#define TEXT_SIZE 13

#define J_STR(x) x + " has joined!"
#define C_STR(x, y) x + " has changed their username to " + y
#define D_STR(x) x + " has disconnected!"

#define GENERAL_CHANNEL Channel("general", "General")
#define GENERAL_2_CHANNEL Channel("general2", "General 2")

#endif
