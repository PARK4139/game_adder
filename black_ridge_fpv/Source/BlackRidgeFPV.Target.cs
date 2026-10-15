using UnrealBuildTool;
using System.Collections.Generic;

public class BlackRidgeFPVTarget : TargetRules
{
    public BlackRidgeFPVTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.Add("BlackRidgeFPV");
    }
}
