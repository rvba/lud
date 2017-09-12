/* 
 * Copyright (c) 2015 Milovann Yanatchkov 
 *
 * This file is part of Lud, a free software
 * licensed under the GNU General Public License v2
 * see /LICENSE for more information
 *
 */

#include "base.h"
#include "ctx.h"
#include "app.h"
#include "event.h"
#include "node.h"
#include "scene.h"
#include "ui.h"
#include "screen.h"
#include "block.h"
#include "mode.h"
#include "brick.h"
#include "op.h"
#include "draw.h"
#include "sketch.h"
#include "viewport.h"
#include "lustre.h"

void lud_tweak_menu_sketch( t_context *C)
{
	t_node *node = scene_get_node_by_type_name( C->scene, dt_block, "menu_sketch");
	t_block *block = node->data;

	add_brick_switch(C,block,"line smooth", &C->skt->line_smooth, NULL);
}

void lud_tweak_menu_draw( t_context *C)
{
	t_node *node = scene_get_node_by_type_name( C->scene, dt_block, "menu_draw");
	t_block *block = node->data;

	add_brick_switch(C,block,"restrict",&C->draw->with_restrict_matrix, NULL);
	add_brick_switch(C,block,"direct",&C->draw->mode_direct, NULL);
	add_brick_switch(C,block,"selection pass",&C->draw->with_selection_pass, NULL);
	add_brick_switch(C,block,"selection object",&C->draw->with_object_selection, NULL);
	add_brick_switch(C,block,"shaders", &C->draw->with_shaders, NULL);
}

void lud_tweak_menu_time( t_context *C)
{
	t_node *node = scene_get_node_by_type_name( C->scene, dt_block, "menu_time");
	t_block *block = node->data;
	add_brick_trigger(C,block,"timer",op_brick_add);
	add_brick_trigger(C,block,"timer low",op_brick_add);
}

t_block *lud_makemenu_lst( t_context *C)
{
	t_block *block = add_menu_block( C, "menu_lst");

	add_brick_trigger(C,block,"last?",op_brick_add);
	add_brick_trigger(C,block,"rewind",op_brick_add);

	return block;
}

// menu process

t_block *lud_makemenu_process( t_context *C)
{
	t_block *block = add_menu_block( C, "menu_process");

	add_brick_switch( C, block, "debug process", &C->event->debug_process, NULL);
	add_brick_slider_float( C, block, "limit", &C->engine->global_limit, NULL);
	add_brick_slider_float( C, block, "freq", &C->engine->global_freq, NULL);
	add_brick_switch( C, block, "limit process", &C->engine->with_global_limit, NULL);

	return block;
}

// menu debug

t_block *lud_makemenu_debug( t_context *C)
{
	t_block *block = add_menu_block( C, "menu_debug");

	add_brick_switch(C,block,"show terminal",&C->ui->show_term, NULL);
	add_brick_switch(C,block,"debug keyboard",&C->app->debug_keyboard, NULL);
	add_brick_switch(C,block,"debug select",&C->event->debug_select, NULL);
	add_brick_switch(C,block,"debug console",&C->event->debug_console, NULL);
	add_brick_switch(C,block,"debug terminal",&C->event->debug_terminal, NULL);
	add_brick_switch(C,block,"debug loop",&C->event->debug_loop, NULL);
	add_brick_switch(C,block,"debug key",&C->event->debug_key, NULL);
	add_brick_switch(C,block,"debug plug",&C->event->debug_plug, NULL);
	add_brick_int(C,block,"mem",(int *) &MEM_SIZE);

	return block;
}

// menu view

t_block *lud_makemenu_view( t_context *C)
{
	t_block *block = add_menu_block( C, "menu_view");

	add_brick_slider_int(C,block,"win width",&C->app->window->width_def,op_window);
	add_brick_slider_int(C,block,"win height",&C->app->window->height_def,op_window);
	add_brick_slider_int(C,block,"vp width",&C->app->window->viewport_width,NULL);
	add_brick_switch(C,block,"viewport controls",&opt_viewport_show_controls, NULL);

	return block;
}

// menu app

t_block *lud_makemenu_app( t_context *C)
{
	t_block *block = add_menu_block( C, "menu_app");

	add_brick_switch(C,block,"loop",&C->app->loop, NULL);
	add_brick_switch(C,block,"rec save",&C->event->rec_save, NULL);
	add_brick_switch(C,block,"use threading",&C->event->use_threading, NULL);

	return block;
}

// menu ui

t_block *lud_makemenu_ui( t_context *C)
{
	t_block *block = add_menu_block( C, "menu_ui");

	add_brick_switch(C,block,"realtime",&C->ui->realtime, NULL);
	add_brick_switch(C,block,"update links",&C->ui->update_links, NULL);
	add_brick_switch(C,block,"fixed menu",&C->ui->fixed_menu, NULL);
	add_brick_switch(C,block,"selection",&C->ui->object_selection, NULL);
	add_brick_switch(C,block,"bitmap font",&C->ui->use_bitmap_font, NULL);
	add_brick_switch(C,block,"show states",&C->ui->show_states, NULL);
	add_brick_switch(C,block,"show step",&C->ui->show_step, NULL);
	add_brick_switch(C,block,"show brick step",&C->ui->show_brick_step, NULL);
	add_brick_switch(C,block,"video build",&C->app->video_build, NULL);
	add_brick_slider_int(C,block,"video offset",&C->app->video_offset,NULL);
	add_brick_slider_int(C,block,"mouse size",&C->ui->mouse_size,NULL);
	add_brick_switch(C,block,"show mouse",&C->ui->show_mouse_rec, NULL);
	add_brick_switch(C,block,"draw plug state",&C->ui->show_plug_state, NULL);

	return block;
}


t_block *lud_makemenu_set( t_context *C)
{
	t_block * block = add_menu_block( C, "menu_set");

	add_brick_submenu( C, block, lud_makemenu_view( C), "view");
	add_brick_submenu( C, block, lud_makemenu_debug( C), "debug");
	add_brick_submenu( C, block, lud_makemenu_app( C), "app");
	add_brick_submenu( C, block, lud_makemenu_ui( C), "ui");
	add_brick_submenu( C, block, lud_makemenu_process( C), "process");

	return block;
}

void lud_init_menu_brick( t_context *C)
{
	t_node *node_menu_brick = scene_get_node_by_type_name( C->scene, dt_block, "menu_brick_add");
	t_block *menu_brick = node_menu_brick->data;
	add_brick_submenu( C, menu_brick, lud_makemenu_lst( C), "list");
}

void lud_init_menu_main( t_context *C)
{
	t_node *node = scene_get_node_by_type_name(C->scene, dt_block, "menu_mouse");
	t_block *block = node->data;

	add_brick_submenu(C, block, lud_makemenu_set( C), "set");

}

void lud_add_menus(t_context *C)
{
	set_draw_plug=0;

	lud_init_menu_main( C);
	lud_init_menu_brick( C);

	lud_tweak_menu_draw( C);
	lud_tweak_menu_sketch( C);
	lud_tweak_menu_time( C);

	set_draw_plug=1;
}

void lud_keymap( int key)
{
	t_context *C = ctx_get();
	
	// Main Keymap
	keymap_main( key);

	switch( key)
	{

		case TABKEY:
			if(C->app->keyboard->ctrl) lu_editor_open( C);
			break;
	}
}

void lud_set_keyboard( t_context *C)
{
	t_node *screen_node = scene_get_node_by_type_name( C->scene, dt_screen, "screen_main");
	t_screen *screen_main = screen_node->data;
	screen_main->keymap = lud_keymap;
	C->ui->screen_active = screen_main;
}

void lud_set_options( t_context *C)
{
	// Change App Name
	set_name(C->app->app_name,"editor");

	// Set With Points
	C->event->with_edge = 1;
	C->event->with_face = 1;
	C->event->with_point = 1;

	// Change version
	set_name(C->app->version,"0.5.1");

	set_draw_plug=1;
	C->event->debug_terminal = 1;
}

typedef void (* t_module_method)( t_context *C);

typedef struct Module_Startup
{
	int done;
	t_module_method method;

}t_module_startup;

void lud_module_startup( t_module *module)
{
	t_module_startup *mod = ( t_module_startup *) module->data;
	if( !mod->done)
	{
		mod->done = 1;
		t_context *C = ctx_get();
		mod->method( C);
	}
}

void lud_add_module_startup( t_context *C, t_module_method f)
{
	t_module_startup *mod = ( t_module_startup *) malloc( sizeof( t_module_startup));
	mod->done = 0;
	mod->method = f;


	t_node *node = scene_add( C->scene, dt_module, "startup");
	t_module *module = ( t_module *) node->data;
	module->update = lud_module_startup;
	module->data = mod;
	lst_add( C->mode->modules, module, module->id.name);
}

void lud_addmod( t_module_method f)
{
	t_context *C = ctx_get();
	lud_add_module_startup( C, f);
}

void lud_init_lua( t_context *C)
{
	lustre_init();
}

void lud_init( t_context *C)
{
	lud_add_menus(C);
	lud_set_keyboard( C);
	lud_init_lua( C);
	lud_set_options( C);
}
