#pragma once

bool has_clicked;
std::chrono::steady_clock::time_point tb_begin;
std::chrono::steady_clock::time_point tb_end;
int tb_time_since;

void move_mouse(float targetX, float targetY)
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dx = targetX;
	input.mi.dy = targetY;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	input.mi.dwExtraInfo = 0;

	SendInput(1, &input, sizeof(INPUT));
}

ImVec2 calculate_aim(const FVector2D& target2D)
{
	float targetX = 0.0f;
	float targetY = 0.0f;

	if (target2D.x != 0)
	{
		if (target2D.x > settings::screen_center_x)
		{
			targetX = -(settings::screen_center_x - target2D.x);
			targetX /= settings::aim::smoothness;
			if (targetX + settings::screen_center_x > settings::screen_center_x * 2) targetX = 0;
		}
		if (target2D.x < settings::screen_center_x)
		{
			targetX = target2D.x - settings::screen_center_x;
			targetX /= settings::aim::smoothness;
			if (targetX + settings::screen_center_x < 0) targetX = 0;
		}
	}

	if (target2D.y != 0)
	{
		if (target2D.y > settings::screen_center_y)
		{
			targetY = -(settings::screen_center_y - target2D.y);
			targetY /= settings::aim::smoothness;
			if (targetY + settings::screen_center_y > settings::screen_center_y * 2) targetY = 0;
		}
		if (target2D.y < settings::screen_center_y)
		{
			targetY = target2D.y - settings::screen_center_y;
			targetY /= settings::aim::smoothness;
			if (targetY + settings::screen_center_y < 0) targetY = 0;
		}
	}

	return ImVec2(targetX, targetY);
}

FVector prediction(FVector TargetPosition, FVector ComponentVelocity, float player_distance, float projectile_speed = 239, float projectile_gravity = 3.5)
{
	float TimeToTarget = player_distance / projectile_speed;
	float bulletDrop = abs(projectile_gravity) * (TimeToTarget * TimeToTarget) * 0.5;

	return FVector
	{
		TargetPosition.x + TimeToTarget * ComponentVelocity.x,
		TargetPosition.y + TimeToTarget * ComponentVelocity.y,
		TargetPosition.z + TimeToTarget * ComponentVelocity.z + bulletDrop
	};
}

void aim(uintptr_t target_mesh, uintptr_t target_entity)
{
	if (!target_mesh || !target_entity) return;
	if (settings::aim::visible_only && !uskeletalmeshcomponent->recently_rendered(target_mesh)) return;

	FVector bone3d = uskeletalmeshcomponent->get_entity_bone(target_mesh, 110);
	FVector2D bone2d = aplayercontroller->project_world_to_screen(bone3d);
	ImVec2 target;

	auto cross_dist = get_cross_distance(bone2d.x, bone2d.y, settings::screen_center_x, settings::screen_center_y);
	if (cross_dist > settings::aim::fov || bone2d.x == 0 || bone2d.y == 0)
	{
		cache::closest_distance = FLT_MAX;
		cache::closest_mesh = NULL;
		cache::closest_entity = NULL;

		return;
	}

	if (settings::aim::prediction)
	{
		float projectile_speed = afortweapon->projectile_speed(cache::current_weapon);
		float projectile_gravity = afortweapon->projectile_gravity(cache::current_weapon);
		float distance = cache::camera.location.distance(bone3d);
		uintptr_t actor_root_component = io->read<uintptr_t>(target_entity + offsets::root_component);
		FVector velocity = io->read<FVector>(actor_root_component + offsets::velocity);
		FVector precit3d = prediction(bone3d, velocity, distance, projectile_speed, projectile_gravity);
		FVector2D predict2d = aplayercontroller->project_world_to_screen(precit3d);

		if (projectile_speed > 1.0f)
		{
			target = calculate_aim(predict2d);
		}
		else
		{
			target = calculate_aim(bone2d);
		}
	}
	else
	{
		target = calculate_aim(bone2d);
	}

	move_mouse(target.x, target.y);

	cache::closest_distance = FLT_MAX;
	cache::closest_mesh = NULL;
}