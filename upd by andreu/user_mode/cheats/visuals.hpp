#pragma once
#include "../ui/imgui/imgui.h"
#include "../vmp.best/header/api.h"

void draw_text(ImFont* font, float fontSize, ImVec2 position, ImColor color, const char* text)
{
	ImGui::GetOverlayDrawList()->AddText(font, fontSize, ImVec2(position.x - 1, position.y - 1), ImColor(0, 0, 0), text);
	ImGui::GetOverlayDrawList()->AddText(font, fontSize, ImVec2(position.x + 1, position.y - 1), ImColor(0, 0, 0), text);
	ImGui::GetOverlayDrawList()->AddText(font, fontSize, ImVec2(position.x - 1, position.y + 1), ImColor(0, 0, 0), text);
	ImGui::GetOverlayDrawList()->AddText(font, fontSize, ImVec2(position.x + 1, position.y + 1), ImColor(0, 0, 0), text);
	ImGui::GetOverlayDrawList()->AddText(font, fontSize, position, color, text);
}
void draw_skeleton(uintptr_t mesh, ImColor color, int thickness)
{
	FVector2D ChestAtLeft = aplayercontroller->project_world_to_screen(uskeletalmeshcomponent->get_entity_bone(mesh, 37));
	FVector2D ChestAtRight = aplayercontroller->project_world_to_screen(uskeletalmeshcomponent->get_entity_bone(mesh, 8));
	FVector2D Chest = { ChestAtLeft.x + (ChestAtRight.x - ChestAtLeft.x) / 2, ChestAtLeft.y };
	FVector2D Neck = aplayercontroller->project_world_to_screen(uskeletalmeshcomponent->get_entity_bone(mesh, 66));
	FVector2D Pelvis = aplayercontroller->project_world_to_screen(uskeletalmeshcomponent->get_entity_bone(mesh, 2));
	FVector2D LeftThigh = aplayercontroller->project_world_to_screen(uskeletalmeshcomponent->get_entity_bone(mesh, 79));
	FVector2D RightThigh = aplayercontroller->project_world_to_screen(uskeletalmeshcomponent->get_entity_bone(mesh, 72));
	FVector2D LeftLeg = aplayercontroller->project_world_to_screen(uskeletalmeshcomponent->get_entity_bone(mesh, 78));
	FVector2D RightLeg = aplayercontroller->project_world_to_screen(uskeletalmeshcomponent->get_entity_bone(mesh, 71));
	FVector2D LeftFoot = aplayercontroller->project_world_to_screen(uskeletalmeshcomponent->get_entity_bone(mesh, 80));
	FVector2D RightFoot = aplayercontroller->project_world_to_screen(uskeletalmeshcomponent->get_entity_bone(mesh, 73));
	FVector2D LeftFeet = aplayercontroller->project_world_to_screen(uskeletalmeshcomponent->get_entity_bone(mesh, 82));
	FVector2D RightFeet = aplayercontroller->project_world_to_screen(uskeletalmeshcomponent->get_entity_bone(mesh, 75));
	FVector2D LeftShoulder = aplayercontroller->project_world_to_screen(uskeletalmeshcomponent->get_entity_bone(mesh, 38));
	FVector2D RightShoulder = aplayercontroller->project_world_to_screen(uskeletalmeshcomponent->get_entity_bone(mesh, 9));
	FVector2D LeftElbow = aplayercontroller->project_world_to_screen(uskeletalmeshcomponent->get_entity_bone(mesh, 39));
	FVector2D RightElbow = aplayercontroller->project_world_to_screen(uskeletalmeshcomponent->get_entity_bone(mesh, 10));
	FVector2D LeftHand = aplayercontroller->project_world_to_screen(uskeletalmeshcomponent->get_entity_bone(mesh, 91));
	FVector2D RightHand = aplayercontroller->project_world_to_screen(uskeletalmeshcomponent->get_entity_bone(mesh, 33));

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(Neck.x, Neck.y), ImVec2(Chest.x, Chest.y), ImColor(0, 0, 0), thickness + 2.0f);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(Chest.x, Chest.y), ImVec2(RightShoulder.x, RightShoulder.y), ImColor(0, 0, 0), thickness + 2.0f);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(Chest.x, Chest.y), ImVec2(LeftShoulder.x, LeftShoulder.y), ImColor(0, 0, 0), thickness + 2.0f);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(LeftShoulder.x, LeftShoulder.y), ImVec2(LeftElbow.x, LeftElbow.y), ImColor(0, 0, 0), thickness + 2.0f);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(RightShoulder.x, RightShoulder.y), ImVec2(RightElbow.x, RightElbow.y), ImColor(0, 0, 0), thickness + 2.0f);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(RightElbow.x, RightElbow.y), ImVec2(RightHand.x, RightHand.y), ImColor(0, 0, 0), thickness + 2.0f);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(LeftElbow.x, LeftElbow.y), ImVec2(LeftHand.x, LeftHand.y), ImColor(0, 0, 0), thickness + 2.0f);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(Chest.x, Chest.y), ImVec2(Pelvis.x, Pelvis.y), ImColor(0, 0, 0), thickness + 2.0f);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(Pelvis.x, Pelvis.y), ImVec2(LeftLeg.x, LeftLeg.y), ImColor(0, 0, 0), thickness + 2.0f);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(Pelvis.x, Pelvis.y), ImVec2(RightLeg.x, RightLeg.y), ImColor(0, 0, 0), thickness + 2.0f);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(RightLeg.x, RightLeg.y), ImVec2(RightThigh.x, RightThigh.y), ImColor(0, 0, 0), thickness + 2.0f);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(LeftLeg.x, LeftLeg.y), ImVec2(LeftThigh.x, LeftThigh.y), ImColor(0, 0, 0), thickness + 2.0f);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(LeftThigh.x, LeftThigh.y), ImVec2(LeftFoot.x, LeftFoot.y), ImColor(0, 0, 0), thickness + 2.0f);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(RightThigh.x, RightThigh.y), ImVec2(RightFoot.x, RightFoot.y), ImColor(0, 0, 0), thickness + 2.0f);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(RightFoot.x, RightFoot.y), ImVec2(RightFeet.x, RightFeet.y), ImColor(0, 0, 0), thickness + 2.0f);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(LeftFoot.x, LeftFoot.y), ImVec2(LeftFeet.x, LeftFeet.y), ImColor(0, 0, 0), thickness + 2.0f);

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(Neck.x, Neck.y), ImVec2(Chest.x, Chest.y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(Chest.x, Chest.y), ImVec2(RightShoulder.x, RightShoulder.y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(Chest.x, Chest.y), ImVec2(LeftShoulder.x, LeftShoulder.y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(LeftShoulder.x, LeftShoulder.y), ImVec2(LeftElbow.x, LeftElbow.y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(RightShoulder.x, RightShoulder.y), ImVec2(RightElbow.x, RightElbow.y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(RightElbow.x, RightElbow.y), ImVec2(RightHand.x, RightHand.y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(LeftElbow.x, LeftElbow.y), ImVec2(LeftHand.x, LeftHand.y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(Chest.x, Chest.y), ImVec2(Pelvis.x, Pelvis.y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(Pelvis.x, Pelvis.y), ImVec2(LeftLeg.x, LeftLeg.y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(Pelvis.x, Pelvis.y), ImVec2(RightLeg.x, RightLeg.y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(RightLeg.x, RightLeg.y), ImVec2(RightThigh.x, RightThigh.y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(LeftLeg.x, LeftLeg.y), ImVec2(LeftThigh.x, LeftThigh.y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(LeftThigh.x, LeftThigh.y), ImVec2(LeftFoot.x, LeftFoot.y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(RightThigh.x, RightThigh.y), ImVec2(RightFoot.x, RightFoot.y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(RightFoot.x, RightFoot.y), ImVec2(RightFeet.x, RightFeet.y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(LeftFoot.x, LeftFoot.y), ImVec2(LeftFeet.x, LeftFeet.y), color, thickness);
}
void draw_arrow(float x, float y, float angle, float size, ImColor color)
{
	float arrow_half_size = size / 2.0f;

	ImVec2 points[3];
	points[0] = ImVec2(x + cosf(angle) * size, y + sinf(angle) * size);
	points[1] = ImVec2(x + cosf(angle + 1.5f) * arrow_half_size, y + sinf(angle + 1.5f) * arrow_half_size);
	points[2] = ImVec2(x + cosf(angle - 1.5f) * arrow_half_size, y + sinf(angle - 1.5f) * arrow_half_size);

	ImGui::GetOverlayDrawList()->AddLine(points[0], points[1], ImColor(0, 0, 0), 2.0f);
	ImGui::GetOverlayDrawList()->AddLine(points[1], points[2], ImColor(0, 0, 0), 2.0f);
	ImGui::GetOverlayDrawList()->AddLine(points[2], points[0], ImColor(0, 0, 0), 2.0f);
	ImGui::GetOverlayDrawList()->AddConvexPolyFilled(points, 3, color);
}

void init() {
	offsetlib::initialize();

	offsets::game_instance = offsetlib::get_offset("World", "OwningGameInstance");
	offsets::local_players = offsetlib::get_offset("GameInstance", "LocalPlayers");
	offsets::player_controller = offsetlib::get_offset("Player", "PlayerController");
	offsets::player_state = offsetlib::get_offset("Controller", "PlayerState");
	offsets::local_pawn = offsetlib::get_offset("PlayerController", "AcknowledgedPawn");
	offsets::game_state = offsetlib::get_offset("World", "GameState");
	offsets::player_array = offsetlib::get_offset("GameStateBase", "PlayerArray");
	offsets::current_weapon = offsetlib::get_offset("FortPawn", "CurrentWeapon");
	offsets::pawn_private = offsetlib::get_offset("PlayerState", "PawnPrivate");
	offsets::team_index = offsetlib::get_offset("FortPlayerStateAthena", "TeamIndex");
	offsets::mesh = offsetlib::get_offset("Character", "Mesh");
	offsets::kill_score = offsetlib::get_offset("FortPlayerStateAthena", "KillScore");
	offsets::root_component = offsetlib::get_offset("Info", "RootComponent");

	/*std::cout << "owning_game_instance: 0x" << std::hex << offsets::game_instance << std::endl;
	std::cout << "local_players: 0x" << std::hex << offsets::local_players << std::endl;
	std::cout << "player_controller: 0x" << std::hex << offsets::player_controller << std::endl;
	std::cout << "player_state: 0x" << std::hex << offsets::player_state << std::endl;
	std::cout << "acknowledged_pawn: 0x" << std::hex << offsets::local_pawn << std::endl;
	std::cout << "game_state: 0x" << std::hex << offsets::game_state << std::endl;
	std::cout << "player_array: 0x" << std::hex << offsets::player_array << std::endl;
	std::cout << "current_weapon: 0x" << std::hex << offsets::current_weapon << std::endl;
	std::cout << "team_id: 0x" << std::hex << offsets::team_index << std::endl;
	std::cout << "mesh: 0x" << std::hex << offsets::mesh << std::endl;
	std::cout << "kill_score: 0x" << std::hex << offsets::kill_score << std::endl;
	std::cout << "root_component: 0x" << std::hex << offsets::root_component << std::endl;*/
	// add more as needed ( duh )
	// do this once also
	offsetlib::cleanup();
}

void actor_caching()
{
	actor_temp_list.clear();

	cache::gworld = io->read<uintptr_t>(virtaddrxd + offsets::gworld);
	cache::game_instance = io->read<uintptr_t>(cache::gworld + offsets::game_instance);
	cache::local_players = io->read<uintptr_t>(io->read<uintptr_t>(cache::game_instance + offsets::local_players));
	cache::player_controller = io->read<uintptr_t>(cache::local_players + offsets::player_controller);
	cache::local_pawn = io->read<uintptr_t>(cache::player_controller + offsets::local_pawn);
	cache::player_state = io->read<uintptr_t>(cache::local_pawn + offsets::player_state);
	cache::team_index = afortplayerstate->get_team_index(cache::player_state);
	cache::current_weapon = io->read<uintptr_t>(cache::local_pawn + offsets::current_weapon);
	cache::closest_distance = FLT_MAX;
	cache::closest_mesh = NULL;
	cache::closest_entity = NULL;

	uintptr_t game_state = io->read<uintptr_t>(cache::gworld + offsets::game_state);
	uintptr_t player_array = io->read<uintptr_t>(game_state + offsets::player_array);
	int player_count = io->read<int>(game_state + (offsets::player_array + sizeof(uintptr_t)));

	for (int i = 0; i < player_count; i++)
	{
		uintptr_t player_state = io->read<uintptr_t>(player_array + (i * sizeof(uintptr_t)));
		uintptr_t pawn_private = io->read<uintptr_t>(player_state + offsets::pawn_private);
		if (pawn_private == cache::local_pawn) continue;

		uintptr_t mesh = io->read<uintptr_t>(pawn_private + offsets::mesh);
		if (!mesh) continue;

		if (afortpawn->is_dead(pawn_private)) continue;

		auto team_index = afortplayerstate->get_team_index(player_state);
		if (settings::misc::ignore_team && cache::local_pawn)
		{
			if (team_index == cache::team_index) continue;
		}

		uintptr_t actor_root_component = io->read<uintptr_t>(pawn_private + offsets::root_component);
		FVector actor_relative_location = io->read<FVector>(actor_root_component + offsets::relative_location);

		actors cached_actor{};
		cached_actor.player_state = player_state;
		cached_actor.pawn_private = pawn_private;
		cached_actor.mesh = mesh;
		cached_actor.username = afortplayerstate->get_username(player_state);
		cached_actor.platform = afortplayerstate->get_platform(player_state);
		cached_actor.weapon = afortweapon->get_weapon_name(pawn_private);
		cached_actor.relative_location = actor_relative_location;

		actor_temp_list.push_back(cached_actor);
	}

	actor_list.clear();
	actor_list = actor_temp_list;

	std::this_thread::sleep_for(std::chrono::milliseconds(250));
}

void actor_drawing()
{
	for (actors actor : actor_list)
	{
		FVector head3d = uskeletalmeshcomponent->get_entity_bone(actor.mesh, 110);
		FVector2D head2d = aplayercontroller->project_world_to_screen(head3d);
		FVector bottom3d = uskeletalmeshcomponent->get_entity_bone(actor.mesh, 0);
		FVector2D bottom2d = aplayercontroller->project_world_to_screen(bottom3d);

		FBoxSphereBounds bounds = io->read<FBoxSphereBounds>(actor.mesh + offsets::box_sphere_bounds);
		double most_left = DBL_MAX;
		double most_right = DBL_MIN;
		double most_top = DBL_MAX;
		double most_bottom = DBL_MIN;
		for (int i = 0; i < 8; i++)
		{
			FVector corner;

			if (i & 1)
			{
				corner.x = 1.0 * bounds.box_extent.x;
			}
			else
			{
				corner.x = -1.0 * bounds.box_extent.x;
			}

			if (i & 2)
			{
				corner.y = 1.0 * bounds.box_extent.y;
			}
			else
			{
				corner.y = -1.0 * bounds.box_extent.y;
			}

			if (i & 2)
			{
				corner.z = 1.0 * bounds.box_extent.z;
			}
			else
			{
				corner.z = -1.0 * bounds.box_extent.z;
			}

			FVector2D origin2d = aplayercontroller->project_world_to_screen(bounds.origin + corner);

			if (origin2d.x < most_left)
			{
				most_left = origin2d.x;
			}

			if (origin2d.x > most_right)
			{
				most_right = origin2d.x;
			}

			if (origin2d.y < most_top)
			{
				most_top = origin2d.y;
			}

			if (origin2d.y > most_bottom)
			{
				most_bottom = origin2d.y;
			}
		}
		double actor_height = most_bottom - most_top;
		double actor_width = most_right - most_left;
		double corner_width = actor_width / 5.0;
		double corner_height = actor_height / 5.0;
		FVector2D bottom_middle = FVector2D(most_left + (actor_width / 2.0), most_bottom);

		float distance = cache::camera.location.distance(head3d) * 0.01f;

		ImColor esp_color;
		ImColor esp_fill_color;
		if (uskeletalmeshcomponent->recently_rendered(actor.mesh))
		{
			esp_color = ImColor(255, 0, 0, 200);
			esp_fill_color = ImColor(255, 0, 0, 100);
		}
		else
		{
			esp_color = ImColor(255, 255, 255, 200);
			esp_fill_color = ImColor(255, 255, 255, 100);
		}

		if (settings::visuals::indication_arrows)
		{
			FVector vAngle = cache::camera.rotation;
			float fYaw = vAngle.y * M_PI / 180.0f;
			float dx = actor.relative_location.x - cache::camera.location.x;
			float dy = actor.relative_location.y - cache::camera.location.y;
			float fsin_yaw = sinf(fYaw);
			float fminus_cos_yaw = -cosf(fYaw);
			float x = dy * fminus_cos_yaw + dx * fsin_yaw;
			x = -x;
			float y = dx * fminus_cos_yaw - dy * fsin_yaw;
			float length = sqrtf(x * x + y * y);
			x /= length;
			y /= length;
			float angle = atan2f(y, x);
			float fov_radius = settings::aim::fov + 5.0f;
			float screen_center_x = settings::width / 2.0f;
			float screen_center_y = settings::height / 2.0f;
			FVector2D arrow_pos = { screen_center_x + x * fov_radius, screen_center_y + y * fov_radius };

			draw_arrow(arrow_pos.x, arrow_pos.y, angle, 15.0f, esp_color);
		}

		if (!uskeletalmeshcomponent->is_in_screen(head2d)) continue;

		if (settings::visuals::box)
		{
			if (settings::visuals::filled)
			{
				ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(most_left, most_top), ImVec2(most_left + actor_width, most_top + actor_height), esp_fill_color, 0, 0);
			}

			if (settings::visuals::box_type == 0)
			{
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left, most_top), ImVec2(most_right, most_top), ImColor(0, 0, 0, 255), 3.5f);
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left, most_bottom), ImVec2(most_right, most_bottom), ImColor(0, 0, 0, 255), 3.5f);
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left, most_bottom), ImVec2(most_left, most_top), ImColor(0, 0, 0, 255), 3.5f);
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_right, most_top), ImVec2(most_right, most_bottom), ImColor(0, 0, 0, 255), 3.5f);

				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left, most_top), ImVec2(most_right, most_top), esp_color, 1.5f);
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left, most_bottom), ImVec2(most_right, most_bottom), esp_color, 1.5f);
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left, most_bottom), ImVec2(most_left, most_top), esp_color, 1.5f);
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_right, most_top), ImVec2(most_right, most_bottom), esp_color, 1.5f);
			}

			if (settings::visuals::box_type == 1)
			{
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left, most_top), ImVec2(most_left, most_top + corner_height), ImColor(0, 0, 0, 255), 3.5f);
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left, most_top), ImVec2(most_left + corner_width, most_top), ImColor(0, 0, 0, 255), 3.5f);

				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left + actor_width - corner_width, most_top), ImVec2(most_left + actor_width, most_top), ImColor(0, 0, 0, 255), 3.5f);
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left + actor_width, most_top), ImVec2(most_left + actor_width, most_top + corner_height), ImColor(0, 0, 0, 255), 3.5f);

				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left, most_top + actor_height - corner_height), ImVec2(most_left, most_top + actor_height), ImColor(0, 0, 0, 255), 3.5f);
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left, most_top + actor_height), ImVec2(most_left + corner_width, most_top + actor_height), ImColor(0, 0, 0, 255), 3.5f);

				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left + actor_width - corner_width, most_top + actor_height), ImVec2(most_left + actor_width, most_top + actor_height), ImColor(0, 0, 0, 255), 3.5f);
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left + actor_width, most_top + actor_height - corner_height), ImVec2(most_left + actor_width, most_top + actor_height), ImColor(0, 0, 0, 255), 3.5f);

				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left, most_top), ImVec2(most_left, most_top + corner_height), esp_color, 1.5f);
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left, most_top), ImVec2(most_left + corner_width, most_top), esp_color, 1.5f);

				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left + actor_width - corner_width, most_top), ImVec2(most_left + actor_width, most_top), esp_color, 1.5f);
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left + actor_width, most_top), ImVec2(most_left + actor_width, most_top + corner_height), esp_color, 1.5f);

				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left, most_top + actor_height - corner_height), ImVec2(most_left, most_top + actor_height), esp_color, 1.5f);
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left, most_top + actor_height), ImVec2(most_left + corner_width, most_top + actor_height), esp_color, 1.5f);

				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left + actor_width - corner_width, most_top + actor_height), ImVec2(most_left + actor_width, most_top + actor_height), esp_color, 1.5f);
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(most_left + actor_width, most_top + actor_height - corner_height), ImVec2(most_left + actor_width, most_top + actor_height), esp_color, 1.5f);
			}
		}

		if (settings::visuals::skeleton)
		{
			draw_skeleton(actor.mesh, esp_color, 1.5f);
		}

		float yOffsetTop = 10.0f;
		if (settings::visuals::username)
		{
			ImVec2 text_size = ImGui::CalcTextSize(actor.username.c_str());

			draw_text(ImGui::GetFont(), 15.0f, ImVec2(bottom_middle.x - text_size.x / 2, most_top - yOffsetTop - text_size.y / 2), ImColor(255, 255, 255, 255), actor.username.c_str());

			yOffsetTop += 15.0f;
		}

		if (settings::visuals::platform)
		{
			ImVec2 text_size = ImGui::CalcTextSize(actor.platform.c_str());

			draw_text(ImGui::GetFont(), 15.0f, ImVec2(bottom_middle.x - text_size.x / 2, most_top - yOffsetTop - text_size.y / 2), ImColor(255, 255, 255, 255), actor.platform.c_str());

			yOffsetTop += 15.0f;
		}

		if (settings::visuals::rank)
		{
			uintptr_t habenaro = io->read<uintptr_t>(actor.player_state + offsets::habenaro_component);
			int32_t ranked_progress = io->read<int32_t>(habenaro + offsets::ranked_progress + 0x10);
			float imageWidth = 20.0f;
			float imageX = bottom_middle.x - (imageWidth / 2);
			float imageY = most_top - (yOffsetTop + 5) - (imageWidth / 2);

			if (ranked_progress == 0 || ranked_progress == 1 || ranked_progress == 2)
			{
				ImGui::GetOverlayDrawList()->AddImage(pic::bronze_r, ImVec2(imageX, imageY), ImVec2(imageX + imageWidth, imageY + imageWidth));
			}
			else if (ranked_progress == 3 || ranked_progress == 4 || ranked_progress == 5)
			{
				ImGui::GetOverlayDrawList()->AddImage(pic::silver_r, ImVec2(imageX, imageY), ImVec2(imageX + imageWidth, imageY + imageWidth));
			}
			else if (ranked_progress == 6 || ranked_progress == 7 || ranked_progress == 8)
			{
				ImGui::GetOverlayDrawList()->AddImage(pic::gold_r, ImVec2(imageX, imageY), ImVec2(imageX + imageWidth, imageY + imageWidth));
			}
			else if (ranked_progress == 9 || ranked_progress == 10 || ranked_progress == 11)
			{
				ImGui::GetOverlayDrawList()->AddImage(pic::plat_r, ImVec2(imageX, imageY), ImVec2(imageX + imageWidth, imageY + imageWidth));
			}
			else if (ranked_progress == 12 || ranked_progress == 13 || ranked_progress == 14)
			{
				ImGui::GetOverlayDrawList()->AddImage(pic::diamond_r, ImVec2(imageX, imageY), ImVec2(imageX + imageWidth, imageY + imageWidth));
			}
			else if (ranked_progress == 15)
			{
				ImGui::GetOverlayDrawList()->AddImage(pic::elite_r, ImVec2(imageX, imageY), ImVec2(imageX + imageWidth, imageY + imageWidth));
			}
			else if (ranked_progress == 16)
			{
				ImGui::GetOverlayDrawList()->AddImage(pic::champion_r, ImVec2(imageX, imageY), ImVec2(imageX + imageWidth, imageY + imageWidth));
			}
			else if (ranked_progress == 17)
			{
				ImGui::GetOverlayDrawList()->AddImage(pic::unreal_r, ImVec2(imageX, imageY), ImVec2(imageX + imageWidth, imageY + imageWidth));
			}
			else
			{
				ImGui::GetOverlayDrawList()->AddImage(pic::unranked_r, ImVec2(imageX, imageY), ImVec2(imageX + imageWidth, imageY + imageWidth));
			}
		}

		float yOffsetBottom = 10.0f;
		if (settings::visuals::weapon)
		{
			std::string weapon;
			if (actor.weapon.empty())
			{
				weapon = "Building Plan";
			}
			else
			{
				weapon = actor.weapon;
			}

			ImVec2 text_size = ImGui::CalcTextSize(weapon.c_str());

			draw_text(ImGui::GetFont(), 15.0f, ImVec2(bottom_middle.x - text_size.x / 2, most_bottom + yOffsetBottom - text_size.y / 2), ImColor(255, 255, 255, 255), weapon.c_str());

			yOffsetBottom += 15.0f;
		}

		if (settings::visuals::distance)
		{
			char dist[64];
			sprintf_s(dist, "(%.fm)", distance);

			ImVec2 text_size = ImGui::CalcTextSize(dist);

			draw_text(ImGui::GetFont(), 15.0f, ImVec2(bottom_middle.x - text_size.x / 2, most_bottom + yOffsetBottom - text_size.y / 2), ImColor(255, 255, 255, 255), dist);

			yOffsetBottom += 15.0f;
		}

		if (settings::visuals::kills)
		{
			std::string kill_score = std::to_string(afortplayerstate->get_kill_score(actor.player_state)) + " Kills";

			ImVec2 text_size = ImGui::CalcTextSize(kill_score.c_str());

			draw_text(ImGui::GetFont(), 15.0f, ImVec2(bottom_middle.x - text_size.x / 2, most_bottom + yOffsetBottom - text_size.y / 2), ImColor(255, 255, 255, 255), kill_score.c_str());

			yOffsetBottom += 15.0f;
		}

		if (settings::visuals::thanked_bus_driver)
		{
			std::string thanked;

			if (afortplayerstate->thanked_bus_driver(actor.player_state))
			{
				thanked = "Thanked Bus Driver";
			}
			else
			{
				thanked = "Didnt Thank Bus Driver";
			}

			ImVec2 text_size = ImGui::CalcTextSize(thanked.c_str());

			draw_text(ImGui::GetFont(), 15.0f, ImVec2(bottom_middle.x - text_size.x / 2, most_bottom + yOffsetBottom - text_size.y / 2), ImColor(255, 255, 255, 255), thanked.c_str());
		}

		auto cross_dist = get_cross_distance(head2d.x, head2d.y, settings::screen_center_x, settings::screen_center_y);
		if (cross_dist <= settings::aim::fov && cross_dist <= cache::closest_distance)
		{
			cache::closest_distance = cross_dist;
			cache::closest_mesh = actor.mesh;
			cache::closest_entity = actor.pawn_private;
		}
	}
}