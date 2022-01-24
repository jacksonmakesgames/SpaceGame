#pragma once
//AUTO-GENERATED FILE, EDIT AT YOUR OWN RISK

#include <Resource.h>
struct RawResources {
	//AUTO-BEGIN-RES
	//
static const unsigned char TEST_txt[];;
static const unsigned TEST_txt_size;
;
static const unsigned char fonts_arial_ttf[];;
static const unsigned fonts_arial_ttf_size;
;
static const unsigned char shaders_grid_frag[];;
static const unsigned shaders_grid_frag_size;
;
static const unsigned char shaders_grid_vert[];;
static const unsigned shaders_grid_vert_size;
;
static const unsigned char sounds_slow_motion_ogg[];;
static const unsigned sounds_slow_motion_ogg_size;
;
static const unsigned char sounds_test_ogg[];;
static const unsigned sounds_test_ogg_size;
;
static const unsigned char textures_Background_png[];;
static const unsigned textures_Background_png_size;
;
static const unsigned char textures_Enemy_png[];;
static const unsigned textures_Enemy_png_size;
;
static const unsigned char textures_Enemy_xcf[];;
static const unsigned textures_Enemy_xcf_size;
;
static const unsigned char textures_Player_png[];;
static const unsigned textures_Player_png_size;
;
static const unsigned char textures_Player_xcf[];;
static const unsigned textures_Player_xcf_size;
;
static const unsigned char textures_PlayerLit_png[];;
static const unsigned textures_PlayerLit_png_size;
;
static const unsigned char textures_Ship_png[];;
static const unsigned textures_Ship_png_size;
;
static const unsigned char textures_ShipThrust_png[];;
static const unsigned textures_ShipThrust_png_size;
;
static const unsigned char textures_box_png[];;
static const unsigned textures_box_png_size;
;
static const unsigned char textures_floor_png[];;
static const unsigned textures_floor_png_size;
;
static const unsigned char textures_projectile_png[];;
static const unsigned textures_projectile_png_size;
;
static const unsigned char textures_scheme_PNG[];;
static const unsigned textures_scheme_PNG_size;

	//AUTO-END-RES
static void Init() {
	//AUTO-BEGIN-INIT
	//
Resources::all.push_back(new Resource("TEST.txt", TEST_txt, TEST_txt_size));
;
Resources::all.push_back(new Resource("fonts/arial.ttf", fonts_arial_ttf, fonts_arial_ttf_size));
;
Resources::all.push_back(new Resource("shaders/grid.frag", shaders_grid_frag, shaders_grid_frag_size));
;
Resources::all.push_back(new Resource("shaders/grid.vert", shaders_grid_vert, shaders_grid_vert_size));
;
Resources::all.push_back(new Resource("sounds/slow_motion.ogg", sounds_slow_motion_ogg, sounds_slow_motion_ogg_size));
;
Resources::all.push_back(new Resource("sounds/test.ogg", sounds_test_ogg, sounds_test_ogg_size));
;
Resources::all.push_back(new Resource("textures/Background.png", textures_Background_png, textures_Background_png_size));
;
Resources::all.push_back(new Resource("textures/Enemy.png", textures_Enemy_png, textures_Enemy_png_size));
;
Resources::all.push_back(new Resource("textures/Enemy.xcf", textures_Enemy_xcf, textures_Enemy_xcf_size));
;
Resources::all.push_back(new Resource("textures/Player.png", textures_Player_png, textures_Player_png_size));
;
Resources::all.push_back(new Resource("textures/Player.xcf", textures_Player_xcf, textures_Player_xcf_size));
;
Resources::all.push_back(new Resource("textures/PlayerLit.png", textures_PlayerLit_png, textures_PlayerLit_png_size));
;
Resources::all.push_back(new Resource("textures/Ship.png", textures_Ship_png, textures_Ship_png_size));
;
Resources::all.push_back(new Resource("textures/ShipThrust.png", textures_ShipThrust_png, textures_ShipThrust_png_size));
;
Resources::all.push_back(new Resource("textures/box.png", textures_box_png, textures_box_png_size));
;
Resources::all.push_back(new Resource("textures/floor.png", textures_floor_png, textures_floor_png_size));
;
Resources::all.push_back(new Resource("textures/projectile.png", textures_projectile_png, textures_projectile_png_size));
;
Resources::all.push_back(new Resource("textures/scheme.PNG", textures_scheme_PNG, textures_scheme_PNG_size));

	//AUTO-END-INIT
}
};
