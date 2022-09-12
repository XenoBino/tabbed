/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]        = "mononoki Nerd Font:size=12";
static const char* normbgcolor  = "#222222";
static const char* normfgcolor  = "#cccccc";
static const char* selbgcolor   = "#555555";
static const char* selfgcolor   = "#ffffff";
static const char* urgbgcolor   = "#111111";
static const char* urgfgcolor   = "#cc0000";
static const char before[]      = "<";
static const char after[]       = ">";
static const char titletrim[]   = "...";
static const int  tabwidth      = 200;
static const Bool foreground    = True;
static       Bool urgentswitch  = False;
static const int barHeight      = 24;

/*
 * Where to place a new tab when it is opened. When npisrelative is True,
 * then the current position is changed + newposition. If npisrelative
 * is False, then newposition is an absolute position.
 */
static int  newposition   = 0;
static Bool npisrelative  = False;

#define SETPROP(p) { \
        .v = (char *[]){ "/bin/sh", "-c", \
                "prop=\"`xwininfo -children -id $1 | grep '^     0x' |" \
                "sed -e's@^ *\\(0x[0-9a-f]*\\) \"\\([^\"]*\\)\".*@\\1 \\2@' |" \
                "xargs -0 printf %b | dmenu -l 10 -w $1`\" &&" \
                "xprop -id $1 -f $0 8s -set $0 \"$prop\"", \
                p, winid, NULL \
        } \
}

#define MODKEY ControlMask
static Key keys[] = {
	/* modifier             key        function     argument */
	{ MODKEY|ShiftMask,     36,        focusonce,   { 0 } },
	{ MODKEY|ShiftMask,     36,        spawn,       { 0 } },

	{ MODKEY|ShiftMask,     46,        rotate,      { .i = +1 } },
	{ MODKEY|ShiftMask,     43,        rotate,      { .i = -1 } },
	{ MODKEY|ShiftMask,     44,        movetab,     { .i = -1 } },
	{ MODKEY|ShiftMask,     45,        movetab,     { .i = +1 } },
	{ MODKEY,               23,        rotate,      { .i = 0 } },

	{ MODKEY,               49,        spawn,       SETPROP("_TABBED_SELECT_TAB") },
	{ MODKEY,               10,        move,        { .i = 0 } },
	{ MODKEY,               11,        move,        { .i = 1 } },
	{ MODKEY,               12,        move,        { .i = 2 } },
	{ MODKEY,               13,        move,        { .i = 3 } },
	{ MODKEY,               14,        move,        { .i = 4 } },
	{ MODKEY,               15,        move,        { .i = 5 } },
	{ MODKEY,               16,        move,        { .i = 6 } },
	{ MODKEY,               17,        move,        { .i = 7 } },
	{ MODKEY,               18,        move,        { .i = 8 } },
	{ MODKEY,               19,        move,        { .i = 9 } },

	{ MODKEY,               24,        killclient,  { 0 } },

	{ MODKEY,               30,        focusurgent, { .v = NULL } },
	{ MODKEY|ShiftMask,     30,        toggle,      { .v = (void*) &urgentswitch } },

	{ 0,                    95,        fullscreen,  { 0 } },
};
