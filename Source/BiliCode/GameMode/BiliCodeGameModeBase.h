// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BiliCodeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BILICODE_API ABiliCodeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		ABiliCodeGameModeBase();//���GameMode���캯��

public:
	virtual void BeginPlay() override;//���overr��ȫһЩ

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayPawn")
		class ASphereBase * PlayerPawn;//����С�����ָ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector StartPosition;
	//FVector CameraStartPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeathSum")
		int32 DeathSum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsEnd;//�����Ϸ�Ƿ��ѽ���
public:
	UFUNCTION(BlueprintCallable)
		void SetPlayerLocation();//���������¼�

	UFUNCTION(BlueprintCallable)
		void SetStartPosition(FVector Location);//�������º���

	UFUNCTION(BlueprintCallable)
		void SetPlayerInput(bool isInput);

};
