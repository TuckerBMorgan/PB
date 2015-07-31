// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MovementState.h"

/**
 * 
 */
class PB_API Walking : public MovementState
{
private:
    float direction;
public:
	Walking(APBCharacter* _character);
	~Walking();
    virtual void Tick(float delta);
    virtual void EnterState(MovementState* previous);
    virtual void ExitState(MovementState* next);
    void SetDirection(float value);
    
};
