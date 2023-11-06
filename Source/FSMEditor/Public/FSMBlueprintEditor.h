// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlueprintEditor.h"

/**
 * 
 */
class FSMEDITOR_API FFSMBlueprintEditor : public FBlueprintEditor
{
public:
	void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UFSMBlueprint* InObject);
};
