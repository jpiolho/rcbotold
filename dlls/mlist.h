// vi: set ts=4 sw=4 :
// vim: set tw=75 :

// mlist.h - class and constants to describe a list of plugins

/*
 * Copyright (c) 2001-2003 Will Day <willday@hpgx.net>
 *
 *    This file is part of Metamod.
 *
 *    Metamod is free software; you can redistribute it and/or modify it
 *    under the terms of the GNU General Public License as published by the
 *    Free Software Foundation; either version 2 of the License, or (at
 *    your option) any later version.
 *
 *    Metamod is distributed in the hope that it will be useful, but
 *    WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Metamod; if not, write to the Free Software Foundation,
 *    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *    In addition, as a special exception, the author gives permission to
 *    link the code of this program with the Half-Life Game Engine ("HL
 *    Engine") and Modified Game Libraries ("MODs") developed by Valve,
 *    L.L.C ("Valve").  You must obey the GNU General Public License in all
 *    respects for all of the code used other than the HL Engine and MODs
 *    from Valve.  If you modify this file, you may extend this exception
 *    to your version of the file, but you are not obligated to do so.  If
 *    you do not wish to do so, delete this exception statement from your
 *    version.
 *
 */

#ifndef MLIST_H
#define MLIST_H

#include "types_meta.h"		// mBOOL
#include "mplugin.h"		// class MPlugin
#include "plinfo.h"			// plid_t, etc

// Max number of plugins we can manage.  This is an arbitrary, fixed number,
// for convenience.  It would probably be better to dynamically grow the
// list as needed, but we do this for now.
#define MAX_PLUGINS 50
// Width required to printf above MAX, for show() functions.
#define WIDTH_MAX_PLUGINS	2


// A list of plugins.
class MPluginList {
	public:
	// data:
		char inifile[PATH_MAX];				// full pathname
		MPlugin plist[MAX_PLUGINS];			// array of plugins
		int size;							// size of list, ie MAX_PLUGINS
		int endlist;						// index of last used entry

	// constructor:
		MPluginList(const char *ifile);

	// functions:
		MPlugin *find(int pindex);			// find by index
		MPlugin *find(const char *findpath); // find by pathname
		MPlugin *find(plid_t id);			// find by plid_t
		MPlugin *find_memloc(void *memptr);	// find by memory location
		MPlugin *find_match(const char *prefix);	// find by partial prefix match
		MPlugin *add(MPlugin *padd);

		mBOOL ini_startup();			// read inifile at startup
		mBOOL ini_refresh();			// re-read inifile
		mBOOL cmd_addload(const char *args);	// load from console command

		mBOOL load();					// load the list, at startup
		mBOOL refresh(PLUG_LOADTIME now);	// update from re-read inifile
		void unpause_all();				// unpause any paused plugins
		void retry_all(PLUG_LOADTIME now);	// retry any pending plugin actions
		void show();					// list plugins to console
		void show_client(edict_t *pEntity);	// list plugins to player client
};

#endif /* MLIST_H */
