/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 2;        /* border pixel of windows */
static int smartborders 	  = 1; /* 1 = quitar bordes con 1 sola ventana, 0 = siempre bordes */
static unsigned int snap      = 32;       /* snap pixel */
static unsigned int gappih    = 2;       /* horiz inner gap between windows */
static unsigned int gappiv    = 2;       /* vert inner gap between windows */
static unsigned int gappoh    = 2;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 2;       /* vert outer gap between windows and screen edge */
static       int smartgaps    = 0;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static int user_bh            = 16;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static unsigned int systraypinning 	= 0;  		/* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static unsigned int systrayonleft 	= 0;    	/* 0: systray in the right corner, >0: systray on left of status text */
static unsigned int systrayspacing 	= 2;   		/* systray spacing */
static int systraypinningfailfirst 	= 1;   		/* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static int showsystray        		= 1;        /* 0 means no systray */
static char font[]                  = "Ubuntu Mono:bold:size=10";
static const char *fonts[]          = { font, "Material Design Icons:size=10" };
static char normbgcolor[]      		= "#222222";
static char normbordercolor[]   	= "#444444";
static char normfgcolor[]       	= "#bbbbbb";
static char selfgcolor[]        	= "#eeeeee";
static char selbordercolor[]    	= "#005577";
static char selbgcolor[]        	= "#005577";
static char *colors[][3] = {
    [SchemeNorm]     = { normfgcolor,    normbgcolor,  normbordercolor },
    [SchemeSel]      = { selfgcolor,     selbgcolor,   selbordercolor }, // Usando solo los colores especificados
    [SchemeTagsSel]  = { selfgcolor,     selbgcolor,   "#000000" }, /* Tagbar left selected {text,background,not used but cannot be empty} */
    [SchemeTagsNorm] = { normfgcolor,    normbgcolor,  "#000000" }, /* Tagbar left unselected {text,background,not used but cannot be empty} */
    [SchemeInfoSel]  = { selfgcolor,     selbgcolor,   "#000000" }, /* infobar middle selected {text,background,not used but cannot be empty} */
    [SchemeInfoNorm] = { normfgcolor,    normbgcolor,  "#000000" }, /* infobar middle unselected {text,background,not used but cannot be empty} */
	[SchemeStatus]   = { normfgcolor, 	 normbgcolor,  "#000000" }, /* statusbar right {text,background,not used} */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* comando para saber class:
	 xprop | grep WM_CLASS -> WM_CLASS(STRING) = "Instancia", "Clase"
	 */
	/* class        instance    title       tags mask     isfloating   monitor */
	{ "librewolf",  NULL, 		NULL, 		1 << 2, 	  0, 		   -1 },
};

/* layout(s) */
static float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define MODKEYALT Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "borderpx",          	INTEGER, &borderpx },
//		{ "smartborders",       INTEGER, &smartborders },
		{ "snap",          		INTEGER, &snap },
		{ "gappih",        		INTEGER, &gappih },
		{ "gappiv",       		INTEGER, &gappiv },
		{ "gappoh",        		INTEGER, &gappoh },
		{ "gappov",        		INTEGER, &gappov },
		{ "smartgaps",     		INTEGER, &smartgaps },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "user_bh",          	INTEGER, &user_bh },
		{ "font",               STRING,  &font },
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
	{ "systraypinning",          INTEGER, &systraypinning },
    { "systrayonleft",           INTEGER, &systrayonleft },
    { "systrayspacing",          INTEGER, &systrayspacing },
    { "systraypinningfailfirst", INTEGER, &systraypinningfailfirst },
    { "showsystray",             INTEGER, &showsystray },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};

#include "movestack.c"
#include <X11/XF86keysym.h>

static const Key keys[] = {

	/* modifier                     key        function        argument */
//	Programas
	{ MODKEY,			 			XK_Return, spawn,		   SHCMD("st") },
	{ MODKEY, 						XK_F1, 	   spawn,		   SHCMD("dmenu_run -i -p 'Ejecutar'") },
	{ MODKEY, 						XK_w, 	   spawn,		   SHCMD("librewolf") },
	{ MODKEY, 						XK_e, 	   spawn,		   SHCMD("st -e lf") },
	{ MODKEY, 						XK_m, 	   spawn,		   SHCMD("st -e cmus") },

//	Scripts
	{ MODKEY, 						XK_F2, 	   spawn,		   SHCMD("Screenshot") },
	{ MODKEY, 						XK_F3, 	   spawn,		   SHCMD("AppImage") },
	{ MODKEY, 						XK_F10,	   spawn,		   SHCMD("Wallpaper") },
	{ MODKEY,	 					XK_F11,	   spawn,		   SHCMD("Suckless-Themes") },
	{ MODKEY, 						XK_F12,	   spawn,		   SHCMD("PowerMenu") },

//	Volumen
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		   SHCMD("pamixer -i 5 && kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume, 	spawn,		   SHCMD("pamixer -d 5 && kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioMute,			spawn,		   SHCMD("pamixer -t && kill -44 $(pidof dwmblocks)") },

//  Brillo
	{ 0, XF86XK_MonBrightnessUp,   	spawn,		   SHCMD("brightnessctl set +5% && kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_MonBrightnessDown,  spawn,		   SHCMD("brightnessctl set 5%- && kill -44 $(pidof dwmblocks)") },

//	Cambiar de ventana
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },

//	Mover ventanas
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },

//	Redimencionar ventanas
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },

// 	Cerrar ventanas
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },

//	Cambiar layout
	{ MODKEY,						XK_Tab,    cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,				XK_Tab,    cyclelayout,    {.i = -1 } },

//	Cambiar ventanas a tiling / floating
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

//	Cambiar de escritorio
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

//	Vista de escritorios
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

// Cambiar de monitor
	{ MODKEY,                       XK_minus,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_plus,   focusmon,       {.i = +1 } },

// Mover ventanas a otro monitor
	{ MODKEY|ShiftMask,             XK_plus,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_minus, tagmon,         {.i = +1 } },

//	Reiniciar dwm
	{ MODKEY|ShiftMask, 			XK_r,      quit,           {1} }, 

//	Salir de dwm
	{ MODKEY|ShiftMask,             XK_F11,    quit,           {0} },

/*
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ControlMask,		XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
*/
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,			0,				Button1,	    cyclelayout,    {.i = +1 } },
	{ ClkLtSymbol,			0,				Button3,	    cyclelayout,    {.i = -1 } },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

