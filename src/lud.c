/* 
 * Copyright (c) 2015 Milovann Yanatchkov 
 *
 * This file is part of Lud, a free software
 * licensed under the GNU General Public License v2
 * see /LICENSE for more information
 *
 */

#include "ctx.h"
#include "app.h"
#include "lustre.h"
#include "lud.h"

int main( int argc, char **argv)
{
	t_context *C = ctx_init( argc, argv);
	lud_init( C);
	app_launch( C->app);

	return 0;
}
