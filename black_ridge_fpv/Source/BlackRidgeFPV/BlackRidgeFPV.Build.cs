using UnrealBuildTool;

public class BlackRidgeFPV : ModuleRules
{
    public BlackRidgeFPV(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
    }
}
