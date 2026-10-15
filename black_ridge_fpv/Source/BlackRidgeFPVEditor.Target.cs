using UnrealBuildTool;

public class BlackRidgeFPVEditorTarget : TargetRules
{
    public BlackRidgeFPVEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.Add("BlackRidgeFPV");
    }
}
