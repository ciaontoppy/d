#pragma once
#include "ui/imgui/imgui.h"

namespace settings
{
	inline int width = GetSystemMetrics(SM_CXSCREEN);
	inline int height = GetSystemMetrics(SM_CYSCREEN);
	inline int screen_center_x = width / 2;
	inline int screen_center_y = height / 2;
	inline bool show_menu = true;
	static int current_tab = 0;
	const char* box_types[] = { "Full", "Corner" };

	namespace aim
	{
		inline bool mouse_aim = false;
		inline bool weakspot_aim = false;
		inline bool prediction = false;
		inline int aim_key = 2;
		inline bool show_fov = false;
		inline bool show_crosshair = false;
		inline bool visible_only = false;
		inline float fov = 150.0f;
		inline float smoothness = 3.0f;
		inline bool triggerbot = false;
		inline bool shotgun_only = false;
		inline int trig_key = 5;
		inline float triggerbot_speed = 1.0f;
	}
	namespace visuals
	{
		inline bool box = true;
		inline bool skeleton = true;
		inline bool rank = true;
		inline bool platform = true;
		inline bool username = true;
		inline bool weapon = true;
		inline bool distance = true;
		inline bool kills = true;
		inline bool thanked_bus_driver = true;
		inline bool indication_arrows = true;
		inline bool filled = true;
		inline int box_type = 0;
	}
	namespace misc
	{
		inline bool ignore_team = false;
	}
}