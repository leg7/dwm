/* See LICENSE file for copyright and license details. */

#define TERMINAL "st"

static const int focusonwheel       = 0;

/*============*/
/* APPEARANCE */
/*============*/
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* gaps */
static const int startwithgaps[]    = { 1 };	/* 1 means gaps are used by default, this can be customized for each tag */
static const unsigned int gappx[]   = { 4 };    /* default gap between windows in pixels, this can be customized for each tag */

/* fonts */
static const char *fonts[]          = { "monospace:size=10", "NotoColorEmoji:pixelsize=12:antialias=true:autohint=true" };
static const char dmenufont[]       =  "monospace:size=10";

/*==================*/
/* NORD COLORSCHEME */
/*==================*/
static const char col_gray1[]       = "#2e3440";	/* black */
static const char col_gray2[]       = "#4c566a";	/* gray */
static const char col_gray3[]       = "#d8dee9";	/* white */
static const char col_gray4[]       = "#eceff4"; 	/* bright white */
static const char col_cyan[]        = "#5e81ac"; 	/* blue */

/* No color */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_gray1, col_gray1 },
	[SchemeSel]  = { col_gray4, col_gray2, col_gray2 },
};

/* /1* bugswriter style colors *1/ */
/* static const char *colors[][3]      = { */
/* 	[SchemeNorm] = { col_cyan, col_gray1, col_gray1 }, */
/* 	[SchemeSel]  = { col_gray1, col_cyan, col_cyan }, */
/* }; */

/* /1* default *1/ */
/* static const char *colors[][3]      = { */
/* 	/1*               fg         bg         border   *1/ */
/* 	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 }, */
/* 	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  }, */
/* }; */

/*=========*/
/* TAGGING */
/*=========*/
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class             instance    title               tags mask     isfloating   monitor */
	{  "Gimp",           NULL,       NULL,               0,            1,           -1 },
	{  "firefox",        NULL,       NULL,               1<<8,         0,           -1 },
	{  "st-256color",    NULL,       "alsamixer",        0,            1,           -1 },
	{  "Qalculate-gtk",  NULL,       NULL,	             0,	           1,	        -1 },
	{  "Tor Browser",    NULL,       NULL,               0,            1,           -1 }
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

/* default dmenu colors */
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL }; */

/* nocolor */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray4, "-sb", col_gray2, "-sf", col_gray4, NULL };

static const char *termcmd[]  = { "st", NULL };

#include "shift-tools.c"
#include <X11/XF86keysym.h> // This is for XF86 keys to work
static Key keys[] = {
	/* modifier                     key        function        argument */
    /* shifting */
	{ MODKEY,                       XK_n,	        shiftview,           { .i = +1 } },
	{ MODKEY,                       XK_p,	        shiftview,           { .i = -1 } },
    /* These don't work */
	/* { MODKEY|ShiftMask,          XK_n,           shiftviewclients,    { .i = +1 } }, */
	/* { MODKEY|ShiftMask,          XK_p,           shiftviewclients,    { .i = -1 } }, */
	{ MODKEY|ControlMask,	        XK_h,           shiftswaptags,       { .i = -1 } },
	{ MODKEY|ControlMask,	        XK_l,           shiftswaptags,       { .i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,           shiftboth,           { .i = +1 } },
	{ MODKEY|ShiftMask,		        XK_h,           shiftboth,           { .i = -1 } },
    /* layouts */
	{ MODKEY,                       XK_t,           setlayout,           {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,           setlayout,           {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,           setlayout,           {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,           setlayout,           {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,           setlayout,           {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,       setlayout,           {0} },
	{ MODKEY|ShiftMask,             XK_space,       togglefloating,      {0} },
	{ MODKEY,                       XK_b,           togglebar,           {0} },
    /* window controls */
	{ MODKEY,                       XK_j,           focusstack,          {.i = +1 } },
	{ MODKEY,                       XK_k,           focusstack,          {.i = -1 } },
	{ MODKEY,                       XK_i,           incnmaster,          {.i = +1 } },
	{ MODKEY,                       XK_d,           incnmaster,          {.i = -1 } },
    /* window resize */
	{ MODKEY,                       XK_h,           setmfact,            {.f = -0.05} },
	{ MODKEY,                       XK_l,           setmfact,            {.f = +0.05} },
	{ MODKEY,                       XK_Return,      zoom,                {0} },
	{ MODKEY|ShiftMask,             XK_c,           killclient,          {0} },
    /* monitors */
	{ MODKEY,                       XK_comma,       focusmon,            {.i = -1 } },
	{ MODKEY,                       XK_period,      focusmon,            {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,       tagmon,              {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,      tagmon,              {.i = +1 } },
    /* gaps */
	{ MODKEY,                       XK_minus,       setgaps,             {.i = -5 } },
	{ MODKEY|ShiftMask,             XK_minus,       setgaps,             {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_g,           setgaps,             {.i = GAP_RESET } },
	{ MODKEY,                       XK_g,           setgaps,             {.i = GAP_TOGGLE} },
    /* Tags */
	TAGKEYS(XK_ampersand,  0)
	TAGKEYS(XK_bracketleft,1)
	TAGKEYS(XK_braceleft,  2)
	TAGKEYS(XK_braceright, 3)
	TAGKEYS(XK_parenleft,  4)
	TAGKEYS(XK_equal,      5)
	TAGKEYS(XK_asterisk,   6)
	TAGKEYS(XK_parenright, 7)
	TAGKEYS(XK_plus,       8)
	{ MODKEY,                       XK_Tab,              view,           {0} },
	{ MODKEY,                       XK_bracketright,     view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_bracketright,     tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_s,                togglesticky,   {0} },
    /* Open programs */
	{ MODKEY|ShiftMask,             XK_Return,           spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_dollar,           spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,		        XK_n,		         spawn,	  	     SHCMD(TERMINAL " -e newsboat") },
    { MODKEY|ShiftMask,             XK_a,                spawn,          SHCMD(TERMINAL " -e alsamixer") },
    { MODKEY|ShiftMask,             XK_z,                spawn,          SHCMD(TERMINAL " -e ikhal") },
    { MODKEY|ShiftMask,             XK_m,                spawn,          SHCMD(TERMINAL " -e ncmpcpp") },
    { MODKEY|ShiftMask,             XK_t,                spawn,          SHCMD(TERMINAL " -e tremc") },
    { MODKEY,                       XK_e,                spawn,          SHCMD("emoji-picker") },
    { MODKEY|ShiftMask,             XK_e,                spawn,          SHCMD("emoji-picker insert") },
    { MODKEY|ShiftMask,             XK_b,                spawn,          SHCMD("firefox-bin") },
    { MODKEY|ShiftMask,             XK_BackSpace,        spawn,          SHCMD("qalculate-gtk") },
    { MODKEY|ShiftMask,             XK_w,                spawn,          SHCMD("wpa_gui") },
    { 0,                            XK_Print,            spawn,          SHCMD("flameshot gui") },
    /* Control system programs */
    { ShiftMask,                    XK_space,            spawn,          SHCMD("dunstctl close") },
    { MODKEY|ShiftMask,             XK_p,                spawn,          SHCMD("toggle-picom") },
    { MODKEY|ShiftMask,             XK_v,                spawn,          SHCMD("toggle-vpn") },
    { MODKEY|ShiftMask,             XK_s,                spawn,          SHCMD("toggle-screenkey") },
    { MODKEY|ShiftMask,             XK_r,                spawn,          SHCMD("~/.local/bin/dwm-6.3/statusbar/refresh &") },
    { 0,                            XF86XK_AudioPrev,    spawn,          SHCMD("mpc -q prev") },
    { 0,                            XF86XK_AudioNext,    spawn,          SHCMD("mpc -q next") },
    { 0,                            XF86XK_AudioStop,    spawn,          SHCMD("mpc -q pause") },
    { 0,                            XF86XK_AudioPlay,    spawn,          SHCMD("mpc -q play") },
    /* other */
	{ MODKEY|ShiftMask,             XK_Caps_Lock,                quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

