// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetTypeActions_FSMBlueprint.h"
#include "FSMBlueprintEditor.h"


#define LOCTEXT_NAMESPACE "FAssetTypeActions_FSM"

FText FAssetTypeActions_FSMBlueprint::GetName() const
{
	return LOCTEXT("FiniteStateMachine Name", "Finite State Machine");
}

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

#undef LOCTEXT_NAMESPACE