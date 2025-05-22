#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

namespace pic
{
	IDirect3DTexture9* bronze_r = nullptr;
	IDirect3DTexture9* silver_r = nullptr;
	IDirect3DTexture9* gold_r = nullptr;
	IDirect3DTexture9* plat_r = nullptr;
	IDirect3DTexture9* diamond_r = nullptr;
	IDirect3DTexture9* elite_r = nullptr;
	IDirect3DTexture9* champion_r = nullptr;
	IDirect3DTexture9* unreal_r = nullptr;
	IDirect3DTexture9* unranked_r = nullptr;
}

#include "communication/driver.hpp"
#include "settings.hpp"
#include "ue5/offsets.hpp"
#include "ue5/sdk.hpp"
#include "cheats/aim.hpp"
#include "cheats/visuals.hpp"
#include "ui/overlay.hpp"