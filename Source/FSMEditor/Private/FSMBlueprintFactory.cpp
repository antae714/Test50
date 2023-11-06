// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMBlueprintFactory.h"
#include "FSMBlueprint.h"
#include "FiniteStateMachine.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "FSMGraph.h"
#include "FSMGraphSchema.h"

UFSMBlueprintFactory::UFSMBlueprintFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UFSMBlueprint::StaticClass();
	ParentClass = UFiniteStateMachine::StaticClass();
}

UObject* UFSMBlueprintFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	UFSMBlueprint* blueprint = Cast<UFSMBlueprint>(Super::FactoryCreateNew(Class, InParent, Name, Flags, Context, Warn, CallingContext));

	UEdGraph* FSMGraph = FBlueprintEditorUtils::CreateNewGraph(blueprint, "FSMGraph", UFSMGraph::StaticClass(), UFSMGraphSchema::StaticClass());
	FSMGraph->GetSchema()->CreateDefaultNodesForGraph(*FSMGraph);
	FSMGraph->bAllowDeletion = false; 
	FBlueprintEditorUtils::AddUbergraphPage(blueprint, FSMGraph);

	blueprint->LastEditedDocuments.Add(FSMGraph);
	
	return blueprint;
}

