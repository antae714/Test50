// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMBluePrintCompiler.h"
#include "FSMBlueprint.h"
#include "FiniteStateMachine.h"
#include "FSMBlueprintGeneratedClass.h"
#include "StateNode/FSMStateNode_Base.h"
#include "Kismet2/KismetReinstanceUtilities.h"

bool FFSMBlueprintCompiler::CanCompile(const UBlueprint* Blueprint)
{
	return Cast<UFSMBlueprint>(Blueprint) != nullptr;
}

void FFSMBlueprintCompiler::Compile(UBlueprint* Blueprint, const FKismetCompilerOptions& CompileOptions, FCompilerResultsLog& Results)
{
	if (UFSMBlueprint* fsmBlueprint = CastChecked<UFSMBlueprint>(Blueprint))
	{
		FKismetCompilerContext Compiler(Blueprint, Results, CompileOptions);
		Compiler.Compile();
		check(Compiler.NewClass);
		//FWidgetBlueprintCompilerContext Compiler(UFSMBlueprint, Results, CompileOptions);
		//Compiler.Compile();
		//check(Compiler.NewClass);
	}
}

bool FFSMBlueprintCompiler::GetBlueprintTypesForClass(UClass* ParentClass, UClass*& OutBlueprintClass, UClass*& OutBlueprintGeneratedClass) const
{
	if (ParentClass == UFiniteStateMachine::StaticClass() || ParentClass->IsChildOf(UFiniteStateMachine::StaticClass()))
	{
		OutBlueprintClass = UFSMBlueprint::StaticClass();
		OutBlueprintGeneratedClass = UFSMBlueprintGeneratedClass::StaticClass();
		return true;
	}

	return false;
}

FFSMKismetCompilerContext::FFSMKismetCompilerContext(UFSMBlueprint* SourceSketch, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompileOptions)
	: FKismetCompilerContext(SourceSketch, InMessageLog, InCompileOptions)
{
}

void FFSMKismetCompilerContext::SpawnNewClass(const FString& NewClassName)
{
	NewClass = FindObject<UFSMBlueprintGeneratedClass>(Blueprint->GetOutermost(), *NewClassName);

	if (NewClass == NULL)
	{
		NewClass = NewObject<UFSMBlueprintGeneratedClass>(Blueprint->GetOutermost(), *NewClassName, RF_Public | RF_Transactional);
	}
	else
	{
		// Already existed, but wasn't linked in the Blueprint yet due to load ordering issues
		FBlueprintCompileReinstancer::Create(NewClass);
	}
}

//bool FFSMKismetCompilerContext::IsNodePure(const UEdGraphNode* Node) const
//{
//	if(Node->IsA<UFSMStateNode_Base>())
//	{
//		return true;
//	}
//	return FKismetCompilerContext::IsNodePure(Node);
//}
//
//bool FFSMKismetCompilerContext::ShouldForceKeepNode(const UEdGraphNode* Node) const
//{
//	return Node->IsA<UFSMStateNode_Base>();
//}

