// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MovementState.h"

/**
 * 
 */
class PB_API Dashing : public MovementState
{
public:
	Dashing(APBCharacter* _character);
	~Dashing();
    virtual void EnterState(MovementState* NewState);
    virtual void ExitState(MovementState* NextState);
    virtual void Tick(float delta);
};
