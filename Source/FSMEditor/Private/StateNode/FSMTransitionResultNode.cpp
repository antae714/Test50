// Fill out your copyright notice in the Description page of Project Settings.


#include "StateNode/FSMTransitionResultNode.h"
#include "VariableSetHandler.h"
#include "KismetCompiledFunctionContext.h"
#include "EdGraphUtilities.h"
#include "FiniteStateMachine.h"
#include "Graph/FSMStateGraph.h"
#include "Graph/FSMTransitionGraph.h"
#include "StateNode/FSMTransitionNode.h"
#include "FSMBlueprintGeneratedClass.h"
#include "KismetCompiler.h"


class FKCHandler_FSMTransitionResult : public FNodeHandlingFunctor
{
public:
	FKCHandler_FSMTransitionResult(FKismetCompilerContext& InCompilerContext)
		: FNodeHandlingFunctor(InCompilerContext)
	{
	}
	void SettingTransition(FKismetFunctionContext& Context, UEdGraphNode* Node)
	{
		UFSMTransitionResultNode* FSMTransitionResult = CastChecked<UFSMTransitionResultNode>(Node);
		UFSMBlueprintGeneratedClass* BPClass = Cast<UFSMBlueprintGeneratedClass>(Context.NewClass);

		UFunction* findfuction = Context.NewClass->FindFunctionByName(FSMTransitionResult->transitionName);
		if (findfuction)
		{
			FFSMTransitionClass* transtion = BPClass->Transitions.FindByKey(FSMTransitionResult->transitionGuid);
			transtion->SettingFunction(findfuction);

			Context.NewClass->RemoveFunctionFromFunctionMap(findfuction);
		}
	}
	virtual FBPTerminal* RegisterLiteral(FKismetFunctionContext& Context, UEdGraphPin* Net) 
	{
		if (Net->LinkedTo.Num() == 0)
		{
			// Make sure the default value is valid
			FString DefaultAllowedResult = CompilerContext.GetSchema()->IsCurrentPinDefaultValid(Net);

			FBPTerminal* LiteralTerm = Context.RegisterLiteral(Net);
			Context.LiteralHackMap.Add(Net, LiteralTerm);
		}
		RegisterNet(Context, Net);
		return Context.NetMap[Net];

		FBPTerminal* temp = FNodeHandlingFunctor::RegisterLiteral(Context, Net);
		Context.Results.Add(temp);
		return temp;

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
		SettingTransition(Context, Node);

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

			FBPTerminal** ValueTerm = Context.LiteralHackMap.Find(VariablePin);
			if (!ValueTerm) 
			{
				ValueTerm = Context.NetMap.Find(FEdGraphUtilities::GetNetFromPin(VariablePin));
			}

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

bool UFSMTransitionResultNode::CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const
{
	return DesiredSchema->GetClass()->IsChildOf(UFSMTransitionGraph::StaticClass());
}
