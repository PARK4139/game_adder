# Unreal Engine baseline

Decision date: 2026-10-15. Target: **Unreal Engine 5.8**. The last Launcher observation showed **5.8.3 installing at 53%**. Installation completion and Engine/Build/Build.version remain unverified. Do not select Preview or UE6 development builds.

UE5 remains the chosen engine for the planned realistic mountain environment. The isolated C++ module keeps runtime gameplay independent from editor-only Python; the Python plugin only creates the initial empty map.

Official references:
- [UE 5.8 release](https://www.unrealengine.com/news/unreal-engine-5-8-is-now-available)
- [Installation](https://dev.epicgames.com/documentation/en-us/unreal-engine/install-unreal-engine)
- [Python editor scripting](https://dev.epicgames.com/documentation/en-us/unreal-engine/scripting-the-unreal-editor-using-python)
- [Licensing information](https://www.unrealengine.com/download)

The download page describes the game royalty licensing route. No paid assets or seat subscription are selected here. Installation/account terms must be reviewed in the user's own Epic account.

## Observed host

Windows 11 Pro 10.0.26200, about 32 GiB RAM, RTX 4070 Laptop GPU 8188 MiB, driver 617.42, MSVC 14.44.35207 Build Tools and Windows SDK 10.0.26100.0. Launcher installation and login have progressed; UE 5.8.3 is installing. At the latest filesystem check the installation list remained empty and the final editor executable and Build.version were absent. Confirm compiler and SDK compatibility after installation; presence of MSVC alone is not a successful build.

## Startup

1. Install the current stable 5.8 release through Epic Games Launcher. Keep the Windows editor and development prerequisites. Set UE_ROOT if not installed in the standard Program Files/Epic Games/UE_5.8 path.
2. Run build_editor.cmd.
3. Run initialize_level.cmd once. It creates Content/Maps/FlightTest.umap and preserves an existing map.
4. Run launch_editor.cmd. Close the editor and launch it again to verify AC-001 twice.
5. Record exact engine patch, both successful launches and build output in the canonical issue evidence directory.

The editor, level-generation script and C++ compilation remain unverified until the actual engine is installed. The empty map is a setup checkpoint, not a playable game. All paths resolve from this project; the car project is not an input.
