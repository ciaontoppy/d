#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/custom.hpp"
#include "imgui/images.hpp"
#include "imgui/hotkey.hpp"
#include "imgui/fonts.hpp"
#include <dwmapi.h>
#include <d3d9.h>
#include <tchar.h>
#include "../settings.hpp"
#include "../protection/skstring.h"
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "d3d9.lib")

IDirect3D9Ex* p_object = NULL;
IDirect3DDevice9Ex* p_device = NULL;
D3DPRESENT_PARAMETERS p_params = { NULL };
MSG messager = { NULL };
HWND my_wnd = NULL;
HWND game_wnd = NULL;
ImFont* icon_fnt = nullptr;

HRESULT init_directx()
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_object))) exit(3);
	ZeroMemory(&p_params, sizeof(p_params));
	p_params.Windowed = TRUE;
	p_params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_params.hDeviceWindow = my_wnd;
	p_params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_params.BackBufferWidth = settings::width;
	p_params.BackBufferHeight = settings::height;
	p_params.EnableAutoDepthStencil = TRUE;
	p_params.AutoDepthStencilFormat = D3DFMT_D16;
	p_params.PresentationInterval = 0;

	if (FAILED(p_object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, my_wnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_params, 0, &p_device)))
	{
		p_object->Release();
		exit(4);
	}
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(my_wnd);
	ImGui_ImplDX9_Init(p_device);

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.IniFilename = nullptr;

	ImFontConfig font_config;
	font_config.PixelSnapH = false;
	font_config.FontDataOwnedByAtlas = false;
	font_config.OversampleH = 5;
	font_config.OversampleV = 5;
	font_config.RasterizerMultiply = 1.2f;
	static const ImWchar ranges[] = {

		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0x2DE0, 0x2DFF, // Cyrillic Extended-A
		0xA640, 0xA69F, // Cyrillic Extended-B
		0xE000, 0xE226, // icons
		0,
	};
	font_config.GlyphRanges = ranges;
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 15.0f, &font_config, ranges);
	icon_fnt = io.Fonts->AddFontFromMemoryTTF(&icon_font, sizeof(icon_font), 15.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());

	if (pic::bronze_r == nullptr) D3DXCreateTextureFromFileInMemoryEx(p_device, &bronze_img, sizeof(bronze_img), 20, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &pic::bronze_r);
	if (pic::silver_r == nullptr) D3DXCreateTextureFromFileInMemoryEx(p_device, &silver_img, sizeof(silver_img), 20, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &pic::silver_r);
	if (pic::gold_r == nullptr) D3DXCreateTextureFromFileInMemoryEx(p_device, &gold_img, sizeof(gold_img), 20, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &pic::gold_r);
	if (pic::plat_r == nullptr) D3DXCreateTextureFromFileInMemoryEx(p_device, &plat_img, sizeof(plat_img), 20, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &pic::plat_r);
	if (pic::diamond_r == nullptr) D3DXCreateTextureFromFileInMemoryEx(p_device, &diamon_img, sizeof(diamon_img), 20, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &pic::diamond_r);
	if (pic::elite_r == nullptr) D3DXCreateTextureFromFileInMemoryEx(p_device, &elite_img, sizeof(elite_img), 20, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &pic::elite_r);
	if (pic::champion_r == nullptr) D3DXCreateTextureFromFileInMemoryEx(p_device, &champ_img, sizeof(champ_img), 20, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &pic::champion_r);
	if (pic::unreal_r == nullptr) D3DXCreateTextureFromFileInMemoryEx(p_device, &unreal_img, sizeof(unreal_img), 20, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &pic::unreal_r);
	if (pic::unranked_r == nullptr) D3DXCreateTextureFromFileInMemoryEx(p_device, &unranked_img, sizeof(unranked_img), 20, 20, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &pic::unranked_r);

	ImGui::StyleColorsDark();
	ImGuiStyle* style = &ImGui::GetStyle();
	style->Colors[ImGuiCol_WindowBg] = ImColor(10, 10, 10, 255);
	style->Colors[ImGuiCol_Border] = ImColor(45, 45, 45, 255);
	style->Colors[ImGuiCol_Separator] = ImColor(178, 102, 255);
	style->Colors[ImGuiCol_SeparatorHovered] = ImColor(178, 102, 255);
	style->Colors[ImGuiCol_SeparatorActive] = ImColor(178, 102, 255);
	style->Colors[ImGuiCol_ChildBg] = ImColor(15, 15, 15, 255);
	style->Colors[ImGuiCol_FrameBg] = ImColor(25, 25, 25, 255);
	style->Colors[ImGuiCol_PopupBg] = ImColor(25, 25, 25, 255);
	style->Colors[ImGuiCol_Header] = ImColor(0, 0, 0, 0);
	style->Colors[ImGuiCol_HeaderHovered] = ImColor(0, 0, 0, 0);
	style->Colors[ImGuiCol_HeaderActive] = ImColor(0, 0, 0, 0);
	style->Colors[ImGuiCol_Button] = ImColor(25, 25, 25, 255);
	style->Colors[ImGuiCol_ButtonActive] = ImColor(25, 25, 25, 255);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(25, 25, 25, 255);
	style->Colors[ImGuiCol_CheckMark] = ImColor(178, 102, 255);
	style->Colors[ImGuiCol_SliderGrab] = ImColor(178, 102, 255);
	style->WindowTitleAlign = { 0.5f, 0.5f };
	style->WindowRounding = 0.0f;
	style->ChildRounding = 0.0f;
	style->FrameRounding = 0.0f;
	style->WindowBorderSize = 1.0f;
	style->FrameBorderSize = 1.0f;
	style->ChildBorderSize = 1.0f;
	style->AntiAliasedFill = false;
	style->AntiAliasedLines = false;
	style->Alpha = 1.0f;

	p_object->Release();

	return S_OK;
}

void create_overlay()
{
	WNDCLASSEXA wcex = {
		sizeof(WNDCLASSEXA), 0, DefWindowProcA, 0, 0, nullptr,
		LoadIcon(nullptr, IDI_APPLICATION), LoadCursor(nullptr, IDC_ARROW),
		nullptr, nullptr, ("xas"), LoadIcon(nullptr, IDI_APPLICATION)
	};

	RECT Rect;
	GetWindowRect(GetDesktopWindow(), &Rect);

	RegisterClassExA(&wcex);

	my_wnd = CreateWindowExA(NULL, ("xas"), ("meow"), WS_POPUP, Rect.left, Rect.top, Rect.right, Rect.bottom, NULL, NULL, wcex.hInstance, NULL);

	SetWindowLong(my_wnd, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_LAYERED);
	MARGINS margin = { -1 };
	DwmExtendFrameIntoClientArea(my_wnd, &margin);
	ShowWindow(my_wnd, SW_SHOW);
	SetWindowPos(my_wnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetLayeredWindowAttributes(my_wnd, RGB(0, 0, 0), 255, LWA_ALPHA);
	UpdateWindow(my_wnd);
}

void render_menu()
{
	if (GetAsyncKeyState(VK_INSERT) & 1) settings::show_menu = !settings::show_menu;
	if (settings::show_menu)
	{
		ImGui::SetNextWindowSize({ 620, 420 });
		ImGui::Begin("##", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);
		{
			ImGui::Text(skCrypt("lukky.rip"));
			ImGui::Separator();

			if (ImGui::Button(skCrypt("Aim"), ImVec2(151, 25))) settings::current_tab = 0;
			ImGui::SameLine(0, 0);
			if (ImGui::Button(skCrypt("Visuals"), ImVec2(151, 25))) settings::current_tab = 1;
			ImGui::SameLine(0, 0);
			if (ImGui::Button(skCrypt("Misc"), ImVec2(151, 25))) settings::current_tab = 2;
			ImGui::SameLine(0, 0);
			if (ImGui::Button(skCrypt("Settings"), ImVec2(151, 25))) settings::current_tab = 3;

			float window_width = ImGui::GetContentRegionAvailWidth() - ImGui::GetStyle().WindowPadding.x;
			float window_height = ImGui::GetContentRegionAvail().y - ImGui::GetStyle().WindowPadding.y;

			switch (settings::current_tab)
			{
			case 0:
			{
				imgui_custom->begin_child(skCrypt("Aim Configuration"), ImVec2(window_width / 2, window_height / 2));
				{
					ImGui::Checkbox(skCrypt("Enable"), &settings::aim::mouse_aim);
					ImGui::Checkbox(skCrypt("Prediction"), &settings::aim::prediction);
					ImGui::Checkbox(skCrypt("Visible Only"), &settings::aim::visible_only);
					ImGui::Checkbox(skCrypt("FOV Circle"), &settings::aim::show_fov);
					ImGui::Checkbox(skCrypt("Crosshair"), &settings::aim::show_crosshair);
				}
				imgui_custom->end_child();

				ImGui::SameLine();

				imgui_custom->begin_child(skCrypt("Extra Aim Configuration"), ImVec2(window_width / 2, window_height / 2));
				{
					ImGui::SliderFloat(skCrypt("FOV"), &settings::aim::fov, 0, 500, "%.f");
					ImGui::SliderFloat(skCrypt("Smoothness"), &settings::aim::smoothness, 2, 50, "%.f");
					ImGui::BeginGroup();
					{
						ImGui::Text(skCrypt("Keybind"));
						hotkey_button(settings::aim::aim_key, ChangeKeyAim, keystatus);
					}
					ImGui::EndGroup();
				}
				imgui_custom->end_child();

				ImGui::Dummy(ImVec2(0, 1.0f));

				imgui_custom->begin_child(skCrypt("Triggerbot Configuration"), ImVec2(window_width / 2, window_height / 2));
				{
					ImGui::Checkbox(skCrypt("Enable"), &settings::aim::triggerbot);
					ImGui::Checkbox(skCrypt("Shotgun Only"), &settings::aim::shotgun_only);
				}
				imgui_custom->end_child();

				ImGui::SameLine();

				imgui_custom->begin_child(skCrypt("Extra Triggerbot Configuration"), ImVec2(window_width / 2, window_height / 2));
				{
					ImGui::SliderFloat(skCrypt("Speed"), &settings::aim::triggerbot_speed, 1, 50, "%.f");
					ImGui::BeginGroup();
					{
						ImGui::Text(skCrypt("Keybind"));
						hotkey_button(settings::aim::trig_key, ChangeKeyTrig, keystatus2);
					}
					ImGui::EndGroup();
				}
				imgui_custom->end_child();

				break;
			}
			case 1:
			{
				imgui_custom->begin_child(skCrypt("Visuals Configuration"), ImVec2(window_width / 2, 0));
				{
					ImGui::Checkbox(skCrypt("2D Box"), &settings::visuals::box);
					ImGui::Checkbox(skCrypt("Skeleton"), &settings::visuals::skeleton);
					ImGui::Checkbox(skCrypt("Rank"), &settings::visuals::rank);
					ImGui::Checkbox(skCrypt("Platform"), &settings::visuals::platform);
					ImGui::Checkbox(skCrypt("Username"), &settings::visuals::username);
					ImGui::Checkbox(skCrypt("Weapon"), &settings::visuals::weapon);
					ImGui::Checkbox(skCrypt("Distance"), &settings::visuals::distance);
					ImGui::Checkbox(skCrypt("Kill Count"), &settings::visuals::kills);
					ImGui::Checkbox(skCrypt("Thanked Bus Driver"), &settings::visuals::thanked_bus_driver);
					ImGui::Checkbox(skCrypt("Indication Arrows"), &settings::visuals::indication_arrows);
				}
				imgui_custom->end_child();

				ImGui::SameLine();

				imgui_custom->begin_child(skCrypt("Extra Visuals Configuration"), ImVec2(window_width / 2, 0));
				{
					ImGui::Checkbox(skCrypt("Filled"), &settings::visuals::filled);
					imgui_custom->selector(skCrypt("Box Type"), settings::visuals::box_type, 1, settings::box_types, sizeof(settings::box_types) / sizeof(settings::box_types[0]));
				}
				imgui_custom->end_child();

				break;
			}
			case 2:
			{
				imgui_custom->begin_child(skCrypt("Misc Configuration"), ImVec2(0, 0));
				{
					ImGui::Checkbox(skCrypt("Ignore Teamates"), &settings::misc::ignore_team);
				}
				imgui_custom->end_child();

				break;
			}
			case 3:
			{
				imgui_custom->begin_child(skCrypt("Settings Configuration"), ImVec2(0, 0));
				{
					if (ImGui::Button(skCrypt("Unload"), ImVec2(100, 25))) exit(0);
				}
				imgui_custom->end_child();

				break;
			}
			}
		}
		ImGui::End();
	}
}

void features()
{
	if (settings::aim::mouse_aim && GetAsyncKeyState(settings::aim::aim_key))
	{
		aim(cache::closest_mesh, cache::closest_entity);
	}
	if (settings::aim::triggerbot && GetAsyncKeyState(settings::aim::trig_key))
	{
		std::string weapon_name = afortweapon->get_weapon_name(cache::local_pawn);
		std::transform(weapon_name.begin(), weapon_name.end(), weapon_name.begin(), ::tolower);

		if (settings::aim::shotgun_only)
		{
			if (weapon_name.find("shotgun") != std::string::npos)
			{
				if (has_clicked)
				{
					tb_begin = std::chrono::steady_clock::now();
					has_clicked = 0;
				}

				tb_end = std::chrono::steady_clock::now();
				tb_time_since = std::chrono::duration_cast<std::chrono::milliseconds>(tb_end - tb_begin).count();

				if (tb_time_since >= settings::aim::triggerbot_speed * 10)
				{
					INPUT Input = { 0 };

					Input.type = INPUT_MOUSE;
					Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
					SendInput(1, &Input, sizeof(INPUT));

					ZeroMemory(&Input, sizeof(INPUT));

					Input.type = INPUT_MOUSE;
					Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
					SendInput(1, &Input, sizeof(INPUT));

					has_clicked = 1;
				}
			}
		}
		else
		{
			if (has_clicked)
			{
				tb_begin = std::chrono::steady_clock::now();
				has_clicked = 0;
			}

			tb_end = std::chrono::steady_clock::now();
			tb_time_since = std::chrono::duration_cast<std::chrono::milliseconds>(tb_end - tb_begin).count();

			if (tb_time_since >= settings::aim::triggerbot_speed * 10)
			{
				INPUT Input = { 0 };

				Input.type = INPUT_MOUSE;
				Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
				SendInput(1, &Input, sizeof(INPUT));

				ZeroMemory(&Input, sizeof(INPUT));

				Input.type = INPUT_MOUSE;
				Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
				SendInput(1, &Input, sizeof(INPUT));

				has_clicked = 1;
			}
		}
	}
	if (settings::aim::show_fov)
	{
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(settings::screen_center_x, settings::screen_center_y), settings::aim::fov, ImColor(255, 255, 255), 100, 1.5f);
	}
	if (settings::aim::show_crosshair)
	{
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(settings::screen_center_x - 6, settings::screen_center_y), ImVec2(settings::screen_center_x + 6, settings::screen_center_y), ImColor(255, 255, 255), 1.5f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(settings::screen_center_x, settings::screen_center_y - 6), ImVec2(settings::screen_center_x, settings::screen_center_y + 6), ImColor(255, 255, 255), 1.5f);
	}

	actor_drawing();
}

WPARAM render_loop()
{
	static RECT old_rc;
	ZeroMemory(&messager, sizeof(MSG));
	while (messager.message != WM_QUIT)
	{
		if (PeekMessage(&messager, my_wnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&messager);
			DispatchMessage(&messager);
		}

		HWND hwnd_active = GetForegroundWindow();
		if (hwnd_active == game_wnd)
		{
			HWND hwndxd = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(my_wnd, hwndxd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		RECT rc;
		POINT xy;
		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(game_wnd, &rc);
		ClientToScreen(game_wnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;
		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = game_wnd;
		io.DeltaTime = 1.0f / 60.0f;
		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;
		if (GetAsyncKeyState(0x1))
		{
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
		{
			io.MouseDown[0] = false;
		}
		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{
			old_rc = rc;
			settings::width = rc.right;
			settings::height = rc.bottom;
			p_params.BackBufferWidth = settings::width;
			p_params.BackBufferHeight = settings::height;
			SetWindowPos(my_wnd, (HWND)0, xy.x, xy.y, settings::width, settings::height, SWP_NOREDRAW);
			p_device->Reset(&p_params);
		}
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		{
			render_menu();
			features();
		}
		ImGui::EndFrame();
		p_device->SetRenderState(D3DRS_ZENABLE, false);
		p_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		p_device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
		p_device->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
		if (p_device->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			p_device->EndScene();
		}
		HRESULT result = p_device->Present(0, 0, 0, 0);
		if (result == D3DERR_DEVICELOST && p_device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			p_device->Reset(&p_params);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	if (p_device != 0)
	{
		p_device->EndScene();
		p_device->Release();
	}

	if (p_object != 0)
	{
		p_object->Release();
	}

	DestroyWindow(my_wnd);

	return messager.wParam;
}