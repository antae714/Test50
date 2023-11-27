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
#include "Styling/SlateStyle.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

#define LOCTEXT_NAMESPACE "FSMEditorModule"
DECLARE_LOG_CATEGORY_EXTERN(LOG_FSMEditor, Log, All);
DEFINE_LOG_CATEGORY(LOG_FSMEditor);



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

	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	//TSharedPtr<FSlateStyleSet> StyleSet = MakeShareable(new FSlateStyleSet("FSMStyle"));

	////Content path of this plugin
	////FString ContentDir = IPluginManager::Get().FindPlugin("FSMEditor")->GetBaseDir();
	//FString ContentDir = "D:/UnrealEngine/Project/Test50";
	////The image we wish to load is located inside the Resources folder inside the Base Directory
	////so let's set the content dir to the base dir and manually switch to the Resources folder:
	//StyleSet->SetContentRoot(ContentDir);

	////Create a brush from the icon
	//FSlateImageBrush* ThumbnailBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("Resources/FSM"), TEXT(".png")), FVector2D(128.f, 128.f));

	//if (ThumbnailBrush)
	//{
	//	//In order to bind the thumbnail to our class we need to type ClassThumbnail.X where X is the name of the C++ class of the asset
	//	StyleSet->Set("FSM.FiniteStateMachine", ThumbnailBrush);

	//	//Reguster the created style
	//	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
	//}
}

#undef LOCTEXT_NAMESPACE