// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph/FSMTransitionGraphSchema.h"
#include "FSMTransition.h"

#include "Graph/FSMTransitionGraph.h"

#include "K2Node_FunctionEntry.h"
#include "K2Node_FunctionResult.h"

#include "StateNode/FSM_Event.h"
#include "StateNode/FSMTransitionNode.h"
#include "StateNode/FSMTransitionResultNode.h"

void UFSMTransitionGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	UFSMTransitionGraph* TransitionGraph = Cast<UFSMTransitionGraph>(&Graph);
	if(0){
		FGraphNodeCreator<UK2Node_CallFunction> NodeCreator(Graph);
		UK2Node_CallFunction* resultNode = NodeCreator.CreateNode();
		NodeCreator.Finalize();
		SetNodeMetaData(resultNode, FNodeMetadata::DefaultGraphNode);
		//resultNode->set()
		//resultNode->SetFromFunction(FFSMTransitionUtil::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(FFSMTransitionUtil, CheckTransitionCondition)));
	}
	{
		FGraphNodeCreator<UK2Node_FunctionEntry> NodeCreator(Graph);
		UK2Node_FunctionEntry* resultNode = NodeCreator.CreateNode();
		NodeCreator.Finalize();
		SetNodeMetaData(resultNode, FNodeMetadata::DefaultGraphNode);
		resultNode->CustomGeneratedFunctionName = FName(TransitionGraph->owningNode->GetNodeName());
		//resultNode->set()
		//resultNode->SetFromFunction(FFSMTransitionUtil::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(FFSMTransitionUtil, CheckTransitionCondition)));
	} 
	{
		FGraphNodeCreator<UK2Node_FunctionResult> NodeCreator(Graph);
		UK2Node_FunctionResult* resultNode = NodeCreator.CreateNode();
		NodeCreator.Finalize();
		SetNodeMetaData(resultNode, FNodeMetadata::DefaultGraphNode);
		resultNode->CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Boolean, TEXT("Transition Condition"));
		//resultNode->set()
		//resultNode->SetFromFunction(FFSMTransitionUtil::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(FFSMTransitionUtil, CheckTransitionCondition)));
	}
}

void UFSMTransitionGraphSchema::GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& DisplayInfo) const
{
	DisplayInfo.PlainName = FText::FromString(Graph.GetName());

	const UEdGraphNode* TransNode = Cast<const UEdGraphNode>(Graph.GetOuter());

	if (TransNode)
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("NodeTitle"), TransNode->GetNodeTitle(ENodeTitleType::FullTitle));
		DisplayInfo.PlainName = FText::Format(NSLOCTEXT("UFSMTransitionGraphSchema", "TransitionGraphTitle", "{NodeTitle}"), Args);
	}

	DisplayInfo.DisplayName = DisplayInfo.PlainName;
}

EGraphType UFSMTransitionGraphSchema::GetGraphType(const UEdGraph* TestEdGraph) const
{
	return GT_Ubergraph;
}
