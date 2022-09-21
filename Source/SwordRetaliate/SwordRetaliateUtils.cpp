#include "SwordRetaliateUtils.h"

#include "Kismet/GameplayStatics.h"

ASwordRetaliateCharacter* USwordRetaliateUtils::GetSwordRetaliateCharacter(const UObject* WorldContextObject)
{
	return Cast<ASwordRetaliateCharacter>(UGameplayStatics::GetPlayerPawn(WorldContextObject, 0));
}
