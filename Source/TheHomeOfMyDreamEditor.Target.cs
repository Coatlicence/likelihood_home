// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TheHomeOfMyDreamEditorTarget : TargetRules
{
	public TheHomeOfMyDreamEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("TheHomeOfMyDream");
	}
}
