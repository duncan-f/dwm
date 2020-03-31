/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const char *fonts[] = {
	"monospace:size=10:antialias=true:autohint=true",
	"NotoColorEmoji:pixelsize=10:antialias=true:autohint=true"
};
static const char dmenufont[]       = "monospace:size=10";
static char normbordercolor[]       = "#32302f";
static char normbgcolor[]           = "#282828";
static char normfgcolor[]           = "#a89984";
static char selbordercolor[]        = "#689d6a";
static char selbgcolor[]            = "#458588";
static char selfgcolor[]            = "#ebdbb2";
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 4;        /* gap pixel between windows */
static const unsigned int snap      = 12;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor  },
	[SchemeSel]  = { selfgcolor, selbgcolor, selbordercolor },
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Brave-browser",  NULL,       NULL,       1 << 1,       0,           -1 },
	{ "firefox",  		NULL,       NULL,       1 << 1,       0,           -1 },
	{ "tabbed","tabbed-surf",       NULL,       1 << 1,       0,           -1 },
	{ "Code",     		NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Gimp",     		NULL,       NULL,       1 << 3,       0,           -1 },
	{ "krita",    		NULL,       NULL,       1 << 3,       0,           -1 },
	{ "grafx2",   		NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Inkscape", 		NULL,       NULL,       1 << 3,       0,           -1 },
	{ "St", 			"st",       "newsboat", 1 << 4,       0,           -1 },
	{ "St", 			"st",       "calcurse", 1 << 5,       0,           -1 },
	{ "St", 			"st",       "weechat",  1 << 7,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",   tile },    	/* first entry is default */
	{ "[F]",   NULL },   	/* no layout function means floating behavior */
	{ "[M]",   monocle },   /* monocle is good for maximizing the preservation and focusing of the window */
};

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
static const char *dmenucmd[] = { "dmenu_run", "-p", "Run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key                 function        argument */
	{ MODKEY,                       XK_b,               spawn,          SHCMD("$BROWSER") },
	{ MODKEY|ShiftMask,             XK_b,               spawn,          SHCMD("surf-open https://duckduckgo.com") },
	{ MODKEY|Mod1Mask,              XK_b,               togglebar,      {0} },
	{ MODKEY,                       XK_c,               spawn,          SHCMD("$TERMINAL -e weechat") },
	{ MODKEY|ShiftMask,             XK_c,               spawn,          SHCMD("$TERMINAL -e calcurse -D ~/.config/calcurse") },
	{ MODKEY,                       XK_d,               spawn,          {.v = dmenucmd } },
	{ Mod1Mask,			            XK_d,               incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,               setmfact,       {.f = -0.05} },
	{ Mod1Mask,			            XK_i,               incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_j,               focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,               focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_l,               setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_m,               spawn,          SHCMD("$TERMINAL -e neomutt") },
	{ MODKEY|ShiftMask,             XK_m,               spawn,          SHCMD("$TERMINAL -e ncmpcpp") },
	{ MODKEY,                       XK_n,               spawn,          SHCMD("$TERMINAL -e newsboat") },
	{ MODKEY,                       XK_p,               spawn,          SHCMD("displayselect") },
	{ MODKEY|ShiftMask,             XK_p,               spawn,          SHCMD("mpd-toggle") },
	{ MODKEY|Mod1Mask,              XK_p,               spawn,          SHCMD("volman toggle") },
	{ MODKEY,                       XK_q,               spawn,          SHCMD("prompt 'Shutdown?' 'systemctl poweroff'") },
	{ MODKEY|ShiftMask,             XK_q,               killclient,     {0} },
	{ MODKEY,                       XK_r,               spawn,          SHCMD("$TERMINAL -e ranger") },
	{ MODKEY|ShiftMask,             XK_s,               spawn,          SHCMD("volman restart") },
	{ MODKEY,                       XK_t,               spawn,          SHCMD("$TERMINAL -e transmission-remote-cli") },
	{ MODKEY|ShiftMask,             XK_t,               spawn,          SHCMD("td-toggle") },
	{ MODKEY,                       XK_v,               spawn,          SHCMD("$TERMINAL -e vifmrun") },
	{ MODKEY,                       XK_w,               spawn,          SHCMD("$TERMINAL -e nmtui") },
	{ MODKEY,                       XK_x,               spawn,          SHCMD("lockscreen -l dimblur") },
	{ MODKEY,                       XK_BackSpace,       spawn,          SHCMD("prompt 'Reboot?' 'systemctl reboot'") },
	{ MODKEY,                       XK_Escape,          spawn,          SHCMD("prompt 'Logout?' 'killall Xorg'") },
	{ MODKEY|ShiftMask,             XK_Escape,          spawn,          SHCMD("prompt 'Hibernate?' 'systemctl hibernate'") },
	{ MODKEY,                       XK_Return,          spawn,          SHCMD("$TERMINAL") },
	{ Mod1Mask,                     XK_Return,          spawn,          {.v = termcmd} },
	{ MODKEY|ShiftMask,             XK_Return,          zoom,           {0} },
	{ MODKEY,                       XK_Tab,             view,           {0} },
	{ MODKEY,                       XK_space,           setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,           togglefloating, {0} },
	{ MODKEY,                       XK_agrave,      	view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_agrave,      	tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,           focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,          focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,           tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,          tagmon,         {.i = +1 } },
	{ Mod1Mask,                     XK_F4,              killclient,     {0} },
	{ MODKEY,                       XK_F5,              xrdb,           { .v = NULL } },
	{ MODKEY,                       XK_F8,              spawn,          SHCMD("volman toggle") },
	{ MODKEY,                       XK_F9,              spawn,          SHCMD("dmenumount") },
	{ MODKEY,                       XK_F10,             spawn,          SHCMD("dmenuumount") },
	{ MODKEY,                       XK_F12,             spawn,          SHCMD("dmenuicons") },
	TAGKEYS(                        XK_ampersand,                       0)
	TAGKEYS(                        XK_eacute,                          1)
	TAGKEYS(                        XK_quotedbl,                        2)
	TAGKEYS(                        XK_apostrophe,                      3)
	TAGKEYS(                        XK_parenleft,                       4)
	TAGKEYS(                        XK_minus,                           5)
	TAGKEYS(                        XK_egrave,                          6)
	TAGKEYS(                        XK_underscore,                      7)
	TAGKEYS(                        XK_ccedilla,                        8)
	{ Mod1Mask,              		XK_t,				setlayout,      {.v = &layouts[0]} },
	{ Mod1Mask,              		XK_f,				setlayout,      {.v = &layouts[1]} },
	{ Mod1Mask,              		XK_m,				setlayout,      {.v = &layouts[2]} },
	{ Mod1Mask,                     XK_x,				killclient,     {0} },
	{ Mod1Mask,                     XK_q,				quit,           {1} },
	{ 0,                            XK_Insert,			spawn,          SHCMD("dmenurecord") },
	{ 0,                            XK_Pause,			spawn,          SHCMD("dmenurecord kill") },
	{ 0,                            XK_Print,			spawn,          SHCMD("screenshot") },
	{ 0,                            XF86XK_HomePage,	spawn,          SHCMD("surf-open https://duckduckgo.com") },
	{ 0,							XF86XK_PowerOff,	spawn,			SHCMD("prompt 'Shutdown?' 'systemctl poweroff'") },
	{ 0,							XF86XK_Sleep,		spawn,			SHCMD("prompt 'Hibernate?' 'systemctl hibernate'") },
	{ 0,							XF86XK_Calculator,	spawn,			SHCMD("st -e bc -l") },
	{ 0,                            XF86XK_WWW,                 spawn,          SHCMD("$BROWSER") },
    { 0,                            XF86XK_MonBrightnessDown,   spawn,          SHCMD("blman dec 5 && refbar") },
    { 0,                            XF86XK_MonBrightnessUp,     spawn,          SHCMD("blman inc 5 && refbar") },
    { MODKEY,                       XF86XK_MonBrightnessDown,   spawn,          SHCMD("blman set 15 && refbar") },
    { MODKEY,                       XF86XK_MonBrightnessUp,     spawn,          SHCMD("blman set 100 && refbar") },
    { 0,                            XF86XK_AudioPrev,			spawn,          SHCMD("volman prev") },
    { 0,                            XF86XK_AudioNext,			spawn,          SHCMD("volman next") },
    { 0,                            XF86XK_AudioPlay,           spawn,          SHCMD("volman toggle") },
    { 0,                            XF86XK_AudioRaiseVolume,    spawn,          SHCMD("volman inc && refbar") },
    { 0,                            XF86XK_AudioLowerVolume,    spawn,          SHCMD("volman dec && refbar") },
    { 0,                            XF86XK_AudioMute,           spawn,          SHCMD("volman mute && refbar") },
    { MODKEY,                       XF86XK_AudioRaiseVolume,    spawn,          SHCMD("volman next") },
    { MODKEY,                       XF86XK_AudioLowerVolume,    spawn,          SHCMD("volman prev") },
    { MODKEY,                       XF86XK_AudioMute,           spawn,          SHCMD("volman stop") },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button2,        setlayout,      {.v = &layouts[1]} },
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

