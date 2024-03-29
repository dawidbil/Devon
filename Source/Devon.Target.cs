using UnrealBuildTool;
using System.Collections.Generic;

public class DevonTarget : TargetRules
{
	public DevonTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.AddRange(new string[] { "DevonCore", "Weapons"} );
	}
}
