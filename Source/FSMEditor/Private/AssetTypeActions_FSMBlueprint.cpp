// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetTypeActions_FSMBlueprint.h"
#include "FSMBlueprintEditor.h"

void FAssetTypeActions_FSMBlueprint::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (UObject* Object : InObjects)
	{
		UFSMBlueprint* NewAsset = Cast<UFSMBlueprint>(Object);
		if (NewAsset)
		{
			TSharedRef<FFSMBlueprintEditor> NewEditor(new FFSMBlueprintEditor());

			NewEditor->InitEditor(Mode, EditWithinLevelEditor, NewAsset);
		}
	}

}
