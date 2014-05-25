/*
 * EZGraphics: OpenGL object wrappers, GLUT tools and mesh data structures 
 * designed to simplify basic OpenGL programming
 * Copyright (c) 2014  Andrzej Szymczak
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * ANDRZEJ SZYMCZAK BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF 
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
 * SOFTWARE.
 *
*/

#include <string>
#include <map>
#include <vector>
#include <utility>

#pragma once

namespace EZGraphics {

  /* -------------------------------------- */

  /** Class containing methods to simplify the popup menu creation.
      Menu entries are declared using the addMenuEntry method inside a beginMenu()...endMenu() block.
      Submenus are defined using the beginSubMenu...endSubMenu blocks.
      The menu is automatically attached to the right mouse button.
  */
  class MenuCreator {

  public:

    /** convenient type of a menu handler */
    typedef void (*MENUHANDLER)();
  
  private:

    typedef std::pair < std::pair<std::string, int>, std::pair<int, MENUHANDLER> > MENUENTRY;

    enum CODE { ENTRY=0, BEGIN=-1, BEGINSUB=-3, ENDSUB=-4, COLLAPSEDSUB=-5 };

    static std::vector<MENUENTRY> s;
    static int currentval;
    static std::map<int,MENUHANDLER> HandlerFunc;

    static MENUENTRY mkMENUENTRY ( std::string s, int a, int b, MENUHANDLER f );
    static void menuHandlerBase ( int );

  public:
    /** start menu specification */
    static void beginMenu();

    /** add a menu entry
	\param name is the text shown as the menu entry 
	\param handler is the function that is called when the menu entry is selected */
    static void addMenuEntry ( const char *name, MENUHANDLER handler );

    /** start specifying submenu entries
	\param name is the name of the submenu (shown on the popup menu)
    */
    static void beginSubMenu ( const char *name );

    /** end submenu specification */
    static int endSubMenu ( );

    /** end menu specification */
    static int endMenu();

  };

  /* -------------------------------------- */

};
