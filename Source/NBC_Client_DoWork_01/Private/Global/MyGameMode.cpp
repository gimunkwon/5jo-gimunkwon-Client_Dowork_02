#include "NBC_Client_DoWork_01/Public/Global/MyGameMode.h"

#include "NBC_Client_DoWork_01/Public/Player/MyPlayer.h"
#include "NBC_Client_DoWork_01/Public/Player/Controller/MyPlayerControlloer.h"

AMyGameMode::AMyGameMode()
{
	DefaultPawnClass = AMyPlayer::StaticClass();
	PlayerControllerClass = AMyPlayerControlloer::StaticClass();
}
