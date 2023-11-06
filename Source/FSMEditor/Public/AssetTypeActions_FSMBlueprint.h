// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions/AssetTypeActions_Blueprint.h"
#include "FSMBlueprint.h"

/**
 * 
 */
class FSMEDITOR_API FAssetTypeActions_FSMBlueprint : public FAssetTypeActions_Blueprint
{
public:
	FAssetTypeActions_FSMBlueprint(EAssetTypeCategories::Type AssetCategory) { m_AssetCategory = AssetCategory; }

public:
#pragma region FAssetTypeActions_Blueprint Interface
	virtual FText GetName() const override { return NSLOCTEXT("FAssetTypeActions_FSM", "Finite State Machine", "Finite State Machine"); }
	virtual FColor GetTypeColor() const override { return FColor::Purple; }
	virtual UClass* GetSupportedClass() const override { return UFSMBlueprint::StaticClass(); }
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories() override { return m_AssetCategory; }
#pragma endregion


private:
	EAssetTypeCategories::Type m_AssetCategory;
};
