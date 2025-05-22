#pragma once
#include <d3d9.h>
#include <vector>
#include <algorithm>
#include "../ui/imgui/imgui.h"
#define M_PI 3.14159265358979323846264338327950288419716939937510

class FVector
{
public:
	FVector() : x(0.f), y(0.f), z(0.f) {}
	FVector(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
	~FVector() {}
	double x, y, z;
	inline double dot(FVector v) { return x * v.x + y * v.y + z * v.z; }
	inline double distance(FVector v) { return double(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0))); }
	inline double length() { return sqrt(x * x + y * y + z * z); }

	FVector operator+(FVector v)
	{
		return FVector(x + v.x, y + v.y, z + v.z);
	}

	FVector operator-(FVector v)
	{
		return FVector(x - v.x, y - v.y, z - v.z);
	}

	FVector operator*(double number) const
	{
		return FVector(x * number, y * number, z * number);
	}
};

class FVector2D
{
public:
	FVector2D() : x(0.f), y(0.f) {}
	FVector2D(double _x, double _y) : x(_x), y(_y) {}
	~FVector2D() {}
	double x, y;
};

template< typename t >
class TArray
{
public:
	TArray() : tData(), iCount(), iMaxCount() {}
	TArray(t* data, int count, int max_count) :
		tData(tData), iCount(iCount), iMaxCount(iMaxCount) {}

public:
	t get(int idx)
	{
		return io->read< t >(reinterpret_cast<__int64>(this->tData) + (idx * sizeof(t)));
	}

	uint32_t size()
	{
		return this->iCount;
	}

	bool is_valid()
	{
		return this->iCount != 0;
	}

	t* tData;
	int iCount;
	int iMaxCount;
};

struct FQuat
{
	double x, y, z, w;
};

struct FTransform
{
	FQuat rotation;
	FVector translation;
	uint8_t pad1c[0x8];
	FVector scale3d;
	uint8_t pad2c[0x8];

	D3DMATRIX to_matrix_with_scale()
	{
		D3DMATRIX m{};

		const FVector Scale
		(
			(scale3d.x == 0.0) ? 1.0 : scale3d.x,
			(scale3d.y == 0.0) ? 1.0 : scale3d.y,
			(scale3d.z == 0.0) ? 1.0 : scale3d.z
		);
		
		const double x2 = rotation.x + rotation.x;
		const double y2 = rotation.y + rotation.y;
		const double z2 = rotation.z + rotation.z;
		const double xx2 = rotation.x * x2;
		const double yy2 = rotation.y * y2;
		const double zz2 = rotation.z * z2;
		const double yz2 = rotation.y * z2;
		const double wx2 = rotation.w * x2;
		const double xy2 = rotation.x * y2;
		const double wz2 = rotation.w * z2;
		const double xz2 = rotation.x * z2;
		const double wy2 = rotation.w * y2;

		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;
		m._11 = (1.0f - (yy2 + zz2)) * Scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * Scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * Scale.z;
		m._32 = (yz2 - wx2) * Scale.z;
		m._23 = (yz2 + wx2) * Scale.y;
		m._21 = (xy2 - wz2) * Scale.y;
		m._12 = (xy2 + wz2) * Scale.x;
		m._31 = (xz2 + wy2) * Scale.z;
		m._13 = (xz2 - wy2) * Scale.x;
		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};

D3DMATRIX matrix_multiplication(D3DMATRIX pm1, D3DMATRIX pm2)
{
	D3DMATRIX pout{};
	pout._11 = pm1._11 * pm2._11 + pm1._12 * pm2._21 + pm1._13 * pm2._31 + pm1._14 * pm2._41;
	pout._12 = pm1._11 * pm2._12 + pm1._12 * pm2._22 + pm1._13 * pm2._32 + pm1._14 * pm2._42;
	pout._13 = pm1._11 * pm2._13 + pm1._12 * pm2._23 + pm1._13 * pm2._33 + pm1._14 * pm2._43;
	pout._14 = pm1._11 * pm2._14 + pm1._12 * pm2._24 + pm1._13 * pm2._34 + pm1._14 * pm2._44;
	pout._21 = pm1._21 * pm2._11 + pm1._22 * pm2._21 + pm1._23 * pm2._31 + pm1._24 * pm2._41;
	pout._22 = pm1._21 * pm2._12 + pm1._22 * pm2._22 + pm1._23 * pm2._32 + pm1._24 * pm2._42;
	pout._23 = pm1._21 * pm2._13 + pm1._22 * pm2._23 + pm1._23 * pm2._33 + pm1._24 * pm2._43;
	pout._24 = pm1._21 * pm2._14 + pm1._22 * pm2._24 + pm1._23 * pm2._34 + pm1._24 * pm2._44;
	pout._31 = pm1._31 * pm2._11 + pm1._32 * pm2._21 + pm1._33 * pm2._31 + pm1._34 * pm2._41;
	pout._32 = pm1._31 * pm2._12 + pm1._32 * pm2._22 + pm1._33 * pm2._32 + pm1._34 * pm2._42;
	pout._33 = pm1._31 * pm2._13 + pm1._32 * pm2._23 + pm1._33 * pm2._33 + pm1._34 * pm2._43;
	pout._34 = pm1._31 * pm2._14 + pm1._32 * pm2._24 + pm1._33 * pm2._34 + pm1._34 * pm2._44;
	pout._41 = pm1._41 * pm2._11 + pm1._42 * pm2._21 + pm1._43 * pm2._31 + pm1._44 * pm2._41;
	pout._42 = pm1._41 * pm2._12 + pm1._42 * pm2._22 + pm1._43 * pm2._32 + pm1._44 * pm2._42;
	pout._43 = pm1._41 * pm2._13 + pm1._42 * pm2._23 + pm1._43 * pm2._33 + pm1._44 * pm2._43;
	pout._44 = pm1._41 * pm2._14 + pm1._42 * pm2._24 + pm1._43 * pm2._34 + pm1._44 * pm2._44;
	return pout;
}

D3DMATRIX to_matrix(FVector rot, FVector origin = FVector(0, 0, 0))
{
	float radpitch = (rot.x * M_PI / 180);
	float radyaw = (rot.y * M_PI / 180);
	float radroll = (rot.z * M_PI / 180);
	float sp = sinf(radpitch);
	float cp = cosf(radpitch);
	float sy = sinf(radyaw);
	float cy = cosf(radyaw);
	float sr = sinf(radroll);
	float cr = cosf(radroll);

	D3DMATRIX matrix{};
	matrix.m[0][0] = cp * cy;
	matrix.m[0][1] = cp * sy;
	matrix.m[0][2] = sp;
	matrix.m[0][3] = 0.f;
	matrix.m[1][0] = sr * sp * cy - cr * sy;
	matrix.m[1][1] = sr * sp * sy + cr * cy;
	matrix.m[1][2] = -sr * cp;
	matrix.m[1][3] = 0.f;
	matrix.m[2][0] = -(cr * sp * cy + sr * sy);
	matrix.m[2][1] = cy * sr - cr * sp * sy;
	matrix.m[2][2] = cr * cp;
	matrix.m[2][3] = 0.f;
	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}

struct Camera
{
	FVector location;
	FVector rotation;
	float fov;
};

struct FBoxSphereBounds
{
	FVector origin;
	FVector box_extent;
	double sphere_radius;
};

namespace cache
{
	inline uintptr_t gworld;
	inline uintptr_t game_instance;
	inline uintptr_t local_players;
	inline uintptr_t player_controller;
	inline uintptr_t local_pawn;
	inline uintptr_t player_state;
	inline char team_index;
	inline uintptr_t current_weapon;
	inline float closest_distance;
	inline uintptr_t closest_mesh;
	inline uintptr_t closest_entity;
	inline Camera camera;
}

typedef struct actors
{
	uintptr_t player_state;
	uintptr_t pawn_private;
	uintptr_t mesh;
	std::string platform;
	std::string username;
	std::string weapon;
	FVector relative_location;
} actors;
std::vector<actors> inline actor_list;
std::vector<actors> actor_temp_list;

double get_cross_distance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

Camera get_view_point()
{
	Camera cam{};

	auto location_pointer = io->read<uintptr_t>(cache::gworld + 0x160);
	auto rotation_pointer = io->read<uintptr_t>(cache::gworld + 0x170);

	double pitch = io->read<double>(rotation_pointer);
	double yaw = io->read<double>(rotation_pointer + 0x20);
	double roll = io->read<double>(rotation_pointer + 0x1d0);

	cam.rotation.x = asin(roll) * (180.0 / M_PI);
	cam.rotation.y = ((atan2(pitch * -1, yaw) * (180.0 / M_PI)) * -1) * -1;
	cam.location = io->read<FVector>(location_pointer);
	cam.fov = io->read<float>(cache::local_players + 0x4ac);

	return cam;
}

class USkeletalMeshComponent
{
public:
	FVector get_entity_bone(uintptr_t mesh, int index)
	{
		uintptr_t bone_array = io->read<uintptr_t>(mesh + offsets::bone_array);
		if (bone_array == NULL)
		{
			bone_array = io->read<uintptr_t>(mesh + offsets::bone_array + 0x10);
		}

		FTransform bone = io->read<FTransform>(bone_array + (index * 0x60));
		FTransform component_to_world = io->read<FTransform>(mesh + offsets::component_to_world);
		D3DMATRIX matrix = matrix_multiplication(bone.to_matrix_with_scale(), component_to_world.to_matrix_with_scale());

		return FVector(matrix._41, matrix._42, matrix._43);
	}

	bool recently_rendered(uintptr_t mesh)
	{
		double seconds = io->read<double>(cache::gworld + 0x148);
		float last_render_time = io->read<float>(mesh + offsets::last_submit_time_on_screen);

		return seconds - last_render_time <= 0.06f;
	}

	bool is_in_screen(FVector2D screen_location)
	{
		if (screen_location.x > 0 && screen_location.x < settings::width && screen_location.y > 0 && screen_location.y < settings::height)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
inline USkeletalMeshComponent* uskeletalmeshcomponent;

class AFortPlayerState
{
public:
	char get_team_index(uintptr_t player_state)
	{
		return io->read<char>(player_state + offsets::team_index);
	}

	std::string get_platform(uintptr_t player_state)
	{
		uintptr_t platform_ptr = io->read<uintptr_t>(player_state + offsets::platform);
		wchar_t platform_char[64] = { 0 };

		io->read_physical(reinterpret_cast<PVOID>(platform_ptr), reinterpret_cast<uint8_t*>(platform_char), sizeof(platform_char));

		std::wstring platform_wide_str(platform_char);
		std::string platform_str(platform_wide_str.begin(), platform_wide_str.end());

		return platform_str;
	}

	std::string get_username(uintptr_t player_state)
	{
		__int64 FString = io->read<__int64>(player_state + offsets::p_name_structure);
		int Length = io->read<int>(FString + 16);
		uintptr_t FText = io->read<__int64>(FString + 8);

		__int64 v6 = Length;
		if (!v6) return std::string("BOT");

		wchar_t* NameBuffer = new wchar_t[Length];
		io->read_physical((PVOID)FText, NameBuffer, Length * sizeof(wchar_t));

		char v21;
		int v22;
		int i;
		int v25;
		WORD* v23;

		v21 = v6 - 1;
		if (!(DWORD)v6)
			v21 = 0;
		v22 = 0;
		v23 = (WORD*)NameBuffer;
		for (i = (v21) & 3; ; *v23++ += i & 7)
		{
			v25 = v6 - 1;
			if (!(DWORD)v6)
				v25 = 0;
			if (v22 >= v25)
				break;
			i += 3;
			++v22;
		}

		std::wstring wbuffer{ NameBuffer };

		return std::string(wbuffer.begin(), wbuffer.end());
	}

	int get_kill_score(uintptr_t player_state)
	{
		return io->read<int>(player_state + offsets::kill_score);
	}

	bool thanked_bus_driver(uintptr_t player_state)
	{
		return io->read<char>(player_state + offsets::b_thanked_bus_driver);
	}
};
inline AFortPlayerState* afortplayerstate;

class AFortPawn
{
public:
	bool is_dead(uintptr_t pawn_private)
	{
		return (io->read<char>(pawn_private + offsets::b_is_dying) >> 5);
	}
};
inline AFortPawn* afortpawn;

class APlayerController
{
public:
	FVector2D project_world_to_screen(FVector world_location)
	{
		cache::camera = get_view_point();
		D3DMATRIX temp_matrix = to_matrix(cache::camera.rotation);
		FVector vaxisx = FVector(temp_matrix.m[0][0], temp_matrix.m[0][1], temp_matrix.m[0][2]);
		FVector vaxisy = FVector(temp_matrix.m[1][0], temp_matrix.m[1][1], temp_matrix.m[1][2]);
		FVector vaxisz = FVector(temp_matrix.m[2][0], temp_matrix.m[2][1], temp_matrix.m[2][2]);
		FVector vdelta = world_location - cache::camera.location;
		FVector vtransformed = FVector(vdelta.dot(vaxisy), vdelta.dot(vaxisz), vdelta.dot(vaxisx));

		if (vtransformed.z < 1) vtransformed.z = 1;

		return FVector2D(settings::screen_center_x + vtransformed.x * ((settings::screen_center_x / tanf(cache::camera.fov * (float)M_PI / 360.0f))) / vtransformed.z, settings::screen_center_y - vtransformed.y * ((settings::screen_center_x / tanf(cache::camera.fov * (float)M_PI / 360.0f))) / vtransformed.z);
	}
};
inline APlayerController* aplayercontroller;

class AFortWeapon
{
public:
	std::string get_weapon_name(uintptr_t pawn_private)
	{
		std::string weapon_name;
		uint64_t current_weapon = io->read<uint64_t>(pawn_private + offsets::current_weapon);
		uint64_t weapon_data = io->read<uint64_t>(current_weapon + offsets::weapon_data);
		uint64_t item_name = io->read<uint64_t>(weapon_data + 0x40);
		if (!item_name) return "No Weapon";

		uint64_t FData = io->read<uint64_t>(item_name + 0x18);
		int FLength = io->read<int>(item_name + 0x20);

		if (FLength > 0 && FLength < 50)
		{
			wchar_t* WeaponBuffer = new wchar_t[FLength];
			io->read_physical((void*)FData, (PVOID)WeaponBuffer, FLength * sizeof(wchar_t));
			std::wstring wstr_buf(WeaponBuffer);
			weapon_name.append(std::string(wstr_buf.begin(), wstr_buf.end()));

			delete[] WeaponBuffer;
		}

		return weapon_name;
	}

	float projectile_speed(uintptr_t current_weapon)
	{
		return io->read<float>(current_weapon + offsets::projectile_speed);
	}

	float projectile_gravity(uintptr_t current_weapon)
	{
		return io->read<float>(current_weapon + offsets::projectile_gravity);
	}
};
inline AFortWeapon* afortweapon;