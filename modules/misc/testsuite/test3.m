/*****************************************************************************
 * test3.m : Empty Objective C module for vlc
 *****************************************************************************
 * Copyright (C) 2000-2001 VideoLAN
 * $Id: test3.m,v 1.2 2003/12/04 16:49:43 sam Exp $
 *
 * Authors: Samuel Hocevar <sam@zoy.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111, USA.
 *****************************************************************************/

/*****************************************************************************
 * Preamble
 *****************************************************************************/
#include <vlc/vlc.h>

#include <objc/Object.h>

/*****************************************************************************
 * The description class
 *****************************************************************************/
@class Desc;

@interface Desc : Object
+ (const char*) ription;
@end

@implementation Desc
+ (const char*) ription
{
    return "Objective C module that does nothing";
}
@end

/*****************************************************************************
 * Module descriptor.
 *****************************************************************************/
vlc_module_begin();
    set_description( _([Desc ription]) );
vlc_module_end();


