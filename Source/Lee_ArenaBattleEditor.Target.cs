// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Lee_ArenaBattleEditorTarget : TargetRules
{
	public Lee_ArenaBattleEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Lee_ArenaBattle" } );
	}
}
