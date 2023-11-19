// Fill out your copyright notice in the Description page of Project Settings.


#include "StateNode/FSMProcessNode.h"
#include "KismetCompiler.h"
#include "Graph/FSMGraph.h"
#include "StateNode/FSMStateNode_Base.h"

#include "FSMBlueprint.h"
#include "FiniteStateMachine.h"
#include "FSMBlueprintGeneratedClass.h"

DECLARE_LOG_CATEGORY_EXTERN(Log_ProcessNode, Log, All);
DEFINE_LOG_CATEGORY(Log_ProcessNode);

class FKCHandler_FSMProcess : public FNodeHandlingFunctor
{
public:
	FKCHandler_FSMProcess(FKismetCompilerContext& InCompilerContext)
		: FNodeHandlingFunctor(InCompilerContext)
	{
	}
	virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override
	{
		UFSMProcessNode* ProcessNode = CastChecked<UFSMProcessNode>(Node);
		UFSMBlueprint* FSMBlueprint = CastChecked<UFSMBlueprint>(ProcessNode->GetBlueprint());
		TArray<UFSMProcessNode*> ProcessNodes;
		TArray<UFSMStateNode_Base*> GrapNodes;
		TArray<UEdGraph*> BP_Graps;

		Context.GetBlueprint()->GetAllGraphs(BP_Graps); 
		
		for (UEdGraph*& Grap : BP_Graps)
		{
			if(!Grap->IsA<UFSMGraph>()) continue;
			Grap->GetNodesOfClass<UFSMProcessNode>(ProcessNodes);
		}
		for (UFSMProcessNode*& item : ProcessNodes)
		{
			if (item->NodeGuid == Node->NodeGuid)
			{
				item->GetGraph()->GetNodesOfClass<UFSMStateNode_Base>(GrapNodes);
				break;
			}
		}
		for (auto& StateNode : GrapNodes)
		{
			StateNode->Compile(Context);
		}

		
		UObject* tempobj = Context.NewClass->GetDefaultObject();



		UE_LOG(Log_ProcessNode, Log, TEXT("compile!"));
		Context.MessageLog.Note(
			*FString::Printf(TEXT("[%s] compile!"), *Node->GetName())
		);
	}

};



void UFSMProcessNode::AllocateDefaultPins()
{
	Pins.Empty();
}

void UFSMProcessNode::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	//SourceGraph->RemoveNode(this);
	UBlueprint* sssss = CompilerContext.Blueprint;
	UClass* tempstatema = sssss->ParentClass.Get();
	UFSMBlueprintGeneratedClass* BPClass = Cast<UFSMBlueprintGeneratedClass>(CompilerContext.Blueprint->GeneratedClass);

	BPClass->States.Empty();
	BPClass->Transitions.Empty();

	//FSM->ssss += 1;

}

FNodeHandlingFunctor* UFSMProcessNode::CreateNodeHandler(FKismetCompilerContext& CompilerContext) const
{
	return new FKCHandler_FSMProcess(CompilerContext);
}

bool UFSMProcessNode::CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const
{
	return  DesiredSchema->GetClass()->IsChildOf(UFSMGraph::StaticClass());
}
