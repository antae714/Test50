// Fill out your copyright notice in the Description page of Project Settings.


#include "StateNode/FSM_Event.h"
#include "EventEntryHandler.h"
#include "Graph/FSMStateGraph.h"
#include "Graph/FSMTransitionGraph.h"
#include "StateNode/FSMStateNode.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "KismetCompiledFunctionContext.h"
#include "FiniteStateMachine.h"

class FKCHandler_FSMEventEntry : public FNodeHandlingFunctor
{
public:
	FKCHandler_FSMEventEntry(FKismetCompilerContext& InCompilerContext)
		: FNodeHandlingFunctor(InCompilerContext)
	{
	}

	virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override 
	{
		
		UFSM_Event* EventNode = CastChecked<UFSM_Event>(Node);
		
		UFunction* findfuction = Context.NewClass->FindFunctionByName(EventNode->CustomFunctionName);
		if (findfuction) 
		{
			UFiniteStateMachine* CDO = Context.NewClass->GetDefaultObject<UFiniteStateMachine>();
			FFSMState* state = CDO->m_State.FindByKey(EventNode->StateGuid);
			state->SettingFunction(EventNode->DelegateName, findfuction);

			Context.NewClass->RemoveFunctionFromFunctionMap(findfuction);
		}

		//FKCHandler_EventEntry::Compile(Context, Node);
		FBlueprintCompiledStatement& Statement = GenerateSimpleThenGoto(Context, *Node);
	}
};


void UFSM_Event::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
	//CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, TEXT(""));
}

FText UFSM_Event::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    return FText::FromName(DelegateName);
}

bool UFSM_Event::CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const
{
	bool bIsInStateGraph = DesiredSchema->GetClass()->IsChildOf(UFSMStateGraph::StaticClass());
	bool bIsInTransitionGraph = DesiredSchema->GetClass()->IsChildOf(UFSMTransitionGraph::StaticClass());
	return bIsInStateGraph || bIsInTransitionGraph;
}

FNodeHandlingFunctor* UFSM_Event::CreateNodeHandler(FKismetCompilerContext& CompilerContext) const
{
	return new FKCHandler_FSMEventEntry(CompilerContext);
}

FSlateIcon UFSM_Event::GetIconAndTint(FLinearColor& OutColor) const
{
	static FSlateIcon Icon("EditorStyle", "GraphEditor.Event_16x");
	return Icon;
}

FLinearColor UFSM_Event::GetNodeTitleColor() const
{
	return FLinearColor(1.f, 0.0f, 0.0f, 1.0f);
}

void UFSM_Event::SetDelegateName(FName _DelegateName)
{
	DelegateName = _DelegateName;
	UFSMStateGraph* ownerdgarph = Cast<UFSMStateGraph>(GetGraph());
	
	StateGuid = ownerdgarph->owningNode->NodeGuid;
	CustomFunctionName = FName(FString::Printf(TEXT("%s_%s"), *StateGuid.ToString(), *DelegateName.ToString()));
}
