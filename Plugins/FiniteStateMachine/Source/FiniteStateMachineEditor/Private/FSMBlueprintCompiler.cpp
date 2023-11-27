// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMBluePrintCompiler.h"
#include "FSMBlueprint.h"
#include "FiniteStateMachine.h"
#include "FSMBlueprintGeneratedClass.h"
#include "Kismet2/KismetReinstanceUtilities.h"
#include "Graph/FSMGraphSchema.h"
#include "EdGraphUtilities.h"

#include "StateNode/FSMStateNode_Base.h"
#include "StateNode/FSMProcessNode.h"
#include "StateNode/FSMStateNode.h"
#include "StateNode/FSMTransitionNode.h"




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

//UEdGraphSchema_K2* FFSMKismetCompilerContext::CreateSchema()
//{
//	return NewObject<UFSMGraphSchema_K2>();
//}


bool FFSMKismetCompilerContext::IsNodePure(const UEdGraphNode* Node) const
{
	if(Node->IsA<UFSMStateNode_Base>())
	{
		return true;
	}
	return Super::IsNodePure(Node);
}

bool FFSMKismetCompilerContext::ShouldForceKeepNode(const UEdGraphNode* Node) const
{
	return Super::ShouldForceKeepNode(Node);
	return Node->IsA<UFSMStateNode_Base>();
}

void FFSMKismetCompilerContext::MergeUbergraphPagesIn(UEdGraph* Ubergraph)
{
	Super::MergeUbergraphPagesIn(Ubergraph);

	UEdGraph* rootFSMGraph = GetBlueprint<UFSMBlueprint>()->GetRootFSMGraph();
	if ((rootFSMGraph))
	{
		TArray<UFSMStateNode*> nodes;
		rootFSMGraph->GetNodesOfClass<UFSMStateNode>(nodes);
		for (auto& item : nodes)
		{
			if (UEdGraph* boundgraph = item->GetBoundGraph())
			{
				FEdGraphUtilities::CloneAndMergeGraphIn(Ubergraph, boundgraph, MessageLog, /*bRequireSchemaMatch=*/ true, /*bIsCompiling*/ true);
			}
		}
	}
}

void FFSMKismetCompilerContext::CreateFunctionList()
{
	Super::CreateFunctionList();
	UEdGraph* rootFSMGraph = GetBlueprint<UFSMBlueprint>()->GetRootFSMGraph();
	if ((rootFSMGraph))
	{
		TArray<UFSMTransitionNode*> nodes;
		rootFSMGraph->GetNodesOfClass<UFSMTransitionNode>(nodes);
		for (auto& item : nodes)
		{
			if (UEdGraph* boundgraph = item->GetBoundGraph())
			{
				ProcessOneFunctionGraph(boundgraph);
			}
		}
	}


}

void FFSMKismetCompilerContext::CompileFunction(FKismetFunctionContext& Context)
{
	UFSMProcessNode* processNode = nullptr;
	int index = 0;
	
	Context.LinearExecutionList.FindItemByClass<UFSMProcessNode>(&processNode, &index);
	Context.LinearExecutionList.Swap(0, index);
	for (int i = 1; i < index; i++)
	{
		Context.LinearExecutionList.Swap(i, index);
	}

	Super::CompileFunction(Context);
}

