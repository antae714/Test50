// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMEditorModule.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_FSMBlueprint.h"
#include "KismetCompilerModule.h"
#include "FSMBluePrintCompiler.h"
#include "FSMBlueprint.h"
#include "EdGraphUtilities.h"
#include "FSMGraphFactory.h"

#define LOCTEXT_NAMESPACE "FSMEditorModule"
DECLARE_LOG_CATEGORY_EXTERN(LOG_FSMEditor, Log, All);



void FFSMEditorModule::StartupModule()
{
	UE_LOG(LOG_FSMEditor, Log, TEXT("FFSMEditorModule::StartupModule"));

	EAssetTypeCategories::Type AssetCategoryBit = EAssetTypeCategories::None;
	//Register
	IAssetTools& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	//AssetCategory

	AssetCategoryBit = AssetToolsModule.RegisterAdvancedAssetCategory(FName(TEXT("FStateMachine")), LOCTEXT("FSMCategory", "FiniteStateMachine"));
	TSharedPtr<FAssetTypeActions_FSMBlueprint> AssetTypeAction = MakeShareable(new FAssetTypeActions_FSMBlueprint(AssetCategoryBit));
	AssetToolsModule.RegisterAssetTypeActions(AssetTypeAction.ToSharedRef());

	IKismetCompilerInterface& KismetCompilerModule = FModuleManager::LoadModuleChecked<IKismetCompilerInterface>("KismetCompiler");
	KismetCompilerModule.GetCompilers().Add(new FFSMBlueprintCompiler());
	
	FKismetCompilerContext::RegisterCompilerForBP(UFSMBlueprint::StaticClass(), [](UBlueprint* InBlueprint, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompileOptions)
		{
			return MakeShared<FFSMKismetCompilerContext>(CastChecked<UFSMBlueprint>(InBlueprint), InMessageLog, InCompileOptions);
		});

	FEdGraphUtilities::RegisterVisualNodeFactory(MakeShareable(new FFSMGraphNodeFactory()));
	FEdGraphUtilities::RegisterVisualPinFactory(MakeShareable(new FFSMGraphPinFactory()));
	FEdGraphUtilities::RegisterVisualPinConnectionFactory(MakeShareable(new FFSMGraphPinConnectionFactory()));


}
