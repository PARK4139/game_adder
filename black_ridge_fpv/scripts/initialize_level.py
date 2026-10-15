"""Create the initial empty map inside Unreal Editor; never overwrite an existing map."""
import unreal

MAP = "/Game/Maps/FlightTest"
if unreal.EditorAssetLibrary.does_asset_exist(MAP):
    unreal.log("367c7496: FlightTest already exists; leaving it unchanged.")
else:
    world = unreal.EditorLoadingAndSavingUtils.new_blank_map(False)
    if not world:
        raise RuntimeError("367c7496: failed to create an empty world")
    unreal.EditorAssetLibrary.make_directory("/Game/Maps")
    if not unreal.EditorLoadingAndSavingUtils.save_map(world, MAP):
        raise RuntimeError("367c7496: failed to save FlightTest")
    unreal.log("367c7496: empty FlightTest map saved successfully")
