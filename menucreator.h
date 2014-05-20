
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
