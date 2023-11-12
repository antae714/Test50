// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMElements.h"


void FFSMElements::Init(FString _Name, FGuid _CompiledNodeGuid)
{
	m_Name = _Name;
	m_CompiledNodeGuid = _CompiledNodeGuid;
}

bool FFSMElements::operator==(FGuid _NodeGuid)
{
	return m_CompiledNodeGuid == _NodeGuid;
}
