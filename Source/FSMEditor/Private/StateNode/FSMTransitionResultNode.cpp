// Fill out your copyright notice in the Description page of Project Settings.


#include "StateNode/FSMTransitionResultNode.h"
#include "VariableSetHandler.h"
#include "KismetCompiledFunctionContext.h"
#include "EdGraphUtilities.h"
#include "FiniteStateMachine.h"
#include "Graph/FSMTransitionGraph.h"
#include "StateNode/FSMTransitionNode.h"

class FKCHandler_FSMTransitionResult : public FNodeHandlingFunctor
{
public:
	FKCHandler_FSMTransitionResult(FKismetCompilerContext& InCompilerContext)
		: FNodeHandlingFunctor(InCompilerContext)
	{
	}

	virtual FBPTerminal* RegisterLiteral(FKismetFunctionContext& Context, UEdGraphPin* Net) 
	{
		RegisterNet(Context, Net);
		return Context.NetMap[Net];
		Context.Results.Add(FNodeHandlingFunctor::RegisterLiteral(Context, Net));
	}
	virtual void RegisterNet(FKismetFunctionContext& Context, UEdGraphPin* Net) override
	{
		// Do not register as a default any Pin that comes from being Split
		if (Net->ParentPin == nullptr)
		{
			FString NetPinName = Net->PinName.ToString();
			for (FBPTerminal& ResultTerm : Context.Results)
			{
				if ((ResultTerm.Name == NetPinName) && (ResultTerm.Type == Net->PinType))
				{
					Context.NetMap.Add(Net, &ResultTerm);
					return;
				}
			}
			FBPTerminal* Term = new FBPTerminal();
			Context.Results.Add(Term);
			Term->CopyFromPin(Net, MoveTemp(NetPinName));
			Context.NetMap.Add(Net, Term);
		}
	}

	virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override
	{
		UFSMTransitionResultNode* FSMTransitionResult = CastChecked<UFSMTransitionResultNode>(Node);

		//UFunction* findfuction = Context.NewClass->FindFunctionByName(FName(FSMTransitionResult->transitionGuid.ToString()));
		UFunction* findfuction = Context.NewClass->FindFunctionByName(FSMTransitionResult->transitionName);
		if (findfuction)
		{
			UFSMTransitionGraph* ownerdgarph = Cast<UFSMTransitionGraph>(Node->GetGraph());

			UFiniteStateMachine* CDO = Context.NewClass->GetDefaultObject<UFiniteStateMachine>();
			FFSMTransition* transtion = CDO->Transition.FindByKey(FSMTransitionResult->transitionGuid);
			transtion->SettingFunction(findfuction);

			Context.NewClass->RemoveFunctionFromFunctionMap(findfuction);
		}


		static const FBoolConfigValueHelper ExecutionAfterReturn(TEXT("Kismet"), TEXT("bExecutionAfterReturn"), GEngineIni);

		if (ExecutionAfterReturn)
		{
			ensure(0);
			//복붙 해주기...
			// for backward compatibility only
			//FKCHandler_VariableSet::Compile(Context, Node);
		}
		else
		{
			UEdGraphPin* VariablePin = Node->FindPin(TEXT("Transition Condition"), EGPD_Input);
			FBPTerminal** VariableTerm = Context.NetMap.Find(VariablePin);

			FBPTerminal** ValueTerm = Context.NetMap.Find(FEdGraphUtilities::GetNetFromPin(VariablePin));

			if (VariableTerm && ValueTerm)
			{
				FKismetCompilerUtilities::CreateObjectAssignmentStatement(Context,
					Node,
					*ValueTerm,
					*VariableTerm,
					VariablePin);
			}



			if (Context.IsDebuggingOrInstrumentationRequired() && Node)
			{
				FBlueprintCompiledStatement& TraceStatement = Context.AppendStatementForNode(Node);
				TraceStatement.Type = Context.GetWireTraceType();
				TraceStatement.Comment = Node->NodeComment.IsEmpty() ? Node->GetName() : Node->NodeComment;
			}

			// always go to return
			FBlueprintCompiledStatement& GotoStatement = Context.AppendStatementForNode(Node);
			GotoStatement.Type = KCST_GotoReturn;
		}
	}

	virtual bool RequiresRegisterNetsBeforeScheduling() const override
	{
		return true;
	}

};



void UFSMTransitionResultNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Boolean, TEXT("Transition Condition"));
}

FText UFSMTransitionResultNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return NSLOCTEXT("UFSMTransitionResultNode", "TransitionResultNodeName", "TransitionResult");
}

FLinearColor UFSMTransitionResultNode::GetNodeTitleColor() const
{
	return FLinearColor(0.0f, 0.0f, 0.502f, 0.0f);
}

FNodeHandlingFunctor* UFSMTransitionResultNode::CreateNodeHandler(FKismetCompilerContext& CompilerContext) const
{
	return new FKCHandler_FSMTransitionResult(CompilerContext);
}

void UFSMTransitionResultNode::Setting()
{
	UFSMTransitionGraph* ownerdgarph = Cast<UFSMTransitionGraph>(GetGraph());
	transitionGuid = ownerdgarph->owningNode->NodeGuid;
	transitionName = ownerdgarph->owningNode->GetFName();


}
