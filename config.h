/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = {
    "Siji:size=10",
	"Hack:size=9"
};
static const char dmenufont[]       = "Hack:size=9";
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
	[SchemeUrg]  = { "#ebdbb2", "#cc241d", "#fb4934" },
};


/* tagging */
static const char *tags[] = { "\ue1ef", "\ue26d", "\ue1ec", "\ue1e5", "\ue1a7", "\ue1dd" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "firefox",  NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Code",     NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Gimp",     NULL,       NULL,       1 << 3,       0,           -1 },
	{ "krita",    NULL,       NULL,       1 << 3,       0,           -1 },
	{ "grafx2",   NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Inkscape", NULL,       NULL,       1 << 3,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "\ue002",   tile },    	/* first entry is default */
	{ "\ue006",   NULL },   	/* no layout function means floating behavior */
	{ "\ue000",   monocle },    /* monocle is good for maximizing the preservation and focusing of the window */
};

/* key definitions */
#define XF86MonBrightnessDown		0x1008ff03
#define XF86MonBrightnessUp			0x1008ff02
#define XF86AudioMute				0x1008ff12
#define XF86AudioLowerVolume		0x1008ff11
#define XF86AudioRaiseVolume	    0x1008ff13
#define TERMINAL                    "st"
#define BROWSER                     "brave"
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
static const char *termcmd[]  = { TERMINAL, NULL };
static const char *weechat[]  = { TERMINAL, "-e", "weechat", NULL };
static const char *calcurse[] = { TERMINAL, "-e", "calcurse -D ~/.config/calcurse", NULL };
static const char *neomutt[]  = { TERMINAL, "-e", "neomutt", NULL };
static const char *ncmpcpp[]  = { TERMINAL, "-e", "ncmpcpp", NULL };
static const char *newsboat[] = { TERMINAL, "-e", "newsboat", NULL };
static const char *ranger[]   = { TERMINAL, "-e", "ranger", NULL };
static const char *vifm[]     = { TERMINAL, "-e", "vifm", NULL };
static const char *torrent[]  = { TERMINAL, "-e", "transmission-remote-cli", NULL };
static const char *browser[]  = { BROWSER, NULL };
static const char *surfcmd[]  = { "tabbed", "-dc", "surf", "-e", NULL };

static Key keys[] = {
	/* modifier                     key                 function        argument */
	{ MODKEY,                       XK_b,               spawn,          {.v = browser } },
	//{ MODKEY|ShiftMask,             XK_b,               spawn,          SHCMD("volman prev") },
	{ MODKEY|Mod1Mask,              XK_b,               togglebar,      {0} },
	{ MODKEY,                       XK_c,               spawn,          {.v = weechat } },
	{ MODKEY|ShiftMask,             XK_c,               spawn,          {.v = calcurse } },
	{ MODKEY,                       XK_d,               spawn,          {.v = dmenucmd } },
	{ Mod1Mask,			            XK_d,               incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,               setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_h,               spawn,          {.v = surfcmd } },
	{ Mod1Mask,			            XK_i,               incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_j,               focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,               focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_l,               setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_m,               spawn,          {.v = neomutt} },
	{ MODKEY|ShiftMask,             XK_m,               spawn,          {.v = ncmpcpp} },
	{ MODKEY,                       XK_n,               spawn,          {.v = newsboat} },
	//{ MODKEY|ShiftMask,             XK_n,               spawn,          SHCMD("volman next") },
	{ MODKEY,                       XK_p,               spawn,          SHCMD("displayselect") },
	{ MODKEY|ShiftMask,             XK_p,               spawn,          SHCMD("mpd-toggle") },
	{ MODKEY|Mod1Mask,              XK_p,               spawn,          SHCMD("volman toggle") },
	{ MODKEY,                       XK_q,               spawn,          SHCMD("prompt 'Shutdown?' 'systemctl poweroff'") },
	{ MODKEY|ShiftMask,             XK_q,               killclient,     {0} },
	{ MODKEY,                       XK_r,               spawn,          {.v = ranger} },
	//{ MODKEY,                       XK_s,               spawn,          SHCMD("volman stop") },
	{ MODKEY|ShiftMask,             XK_s,               spawn,          SHCMD("volman restart") },
	{ MODKEY,                       XK_t,               spawn,          {.v = torrent} },
	{ MODKEY|ShiftMask,             XK_t,               spawn,          SHCMD("td-toggle") },
	{ MODKEY,                       XK_v,               spawn,          {.v = vifm} },
	{ MODKEY|ShiftMask,             XK_v,               spawn,          SHCMD("vifmrun") },
	{ MODKEY,                       XK_x,               spawn,          SHCMD("lockscreen -l dimblur") },
	{ MODKEY|Mod1Mask,              XK_x,               quit,           {0} },
	{ MODKEY,                       XK_BackSpace,       spawn,          SHCMD("prompt 'Reboot?' 'systemctl reboot'") },
	{ MODKEY,                       XK_Escape,          spawn,          SHCMD("dwmshutdown") },
	{ MODKEY|ShiftMask,             XK_Escape,          spawn,          SHCMD("prompt 'Hibernate?' 'systemctl hibernate'") },
	{ MODKEY,                       XK_Return,          spawn,          {.v = termcmd } },
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
	TAGKEYS(                        XK_ampersand,                       0)
	TAGKEYS(                        XK_eacute,                          1)
	TAGKEYS(                        XK_quotedbl,                        2)
	TAGKEYS(                        XK_apostrophe,                      3)
	TAGKEYS(                        XK_parenleft,                       4)
	TAGKEYS(                        XK_minus,                           5)
	//TAGKEYS(                        XK_egrave,                          6)
	//TAGKEYS(                        XK_underscore,                      7)
	//TAGKEYS(                        XK_ccedilla,                        8)
	{ Mod1Mask,              		XK_t,                       setlayout,      {.v = &layouts[0]} },
	{ Mod1Mask,              		XK_f,                       setlayout,      {.v = &layouts[1]} },
	{ Mod1Mask,              		XK_m,                       setlayout,      {.v = &layouts[2]} },
	{ Mod1Mask,                     XK_q,			            quit,           {1} },
	{ 0,                            XK_Insert,                  spawn,          SHCMD("dmenurecord") },
	{ 0,                            XK_Pause,                  	spawn,          SHCMD("dmenurecord kill") },
	{ 0,                            XK_Print,                   spawn,          SHCMD("screenshot") },
	{ ControlMask|Mod1Mask,         XK_Tab,                     spawn,          SHCMD("dmenuicons") },
    { 0,                            XF86MonBrightnessDown,      spawn,          SHCMD("blman dec 5 && refbar") },
    { 0,                            XF86MonBrightnessUp,        spawn,          SHCMD("blman inc 5 && refbar") },
    { MODKEY,                       XF86MonBrightnessDown,      spawn,          SHCMD("blman dec 10 && refbar") },
    { MODKEY,                       XF86MonBrightnessUp,        spawn,          SHCMD("blman inc 10 && refbar") },
    { 0,                            XF86AudioRaiseVolume,       spawn,          SHCMD("volman inc && refbar") },
    { 0,                            XF86AudioLowerVolume,       spawn,          SHCMD("volman dec && refbar") },
    { 0,                            XF86AudioMute,              spawn,          SHCMD("volman mute && refbar") },
    { MODKEY,                       XF86AudioRaiseVolume,       spawn,          SHCMD("volman next") },
    { MODKEY,                       XF86AudioLowerVolume,       spawn,          SHCMD("volman prev") },
    { MODKEY,                       XF86AudioMute,              spawn,          SHCMD("volman stop") },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

