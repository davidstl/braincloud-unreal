// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BCMatchmakingProxy.generated.h"

class ABrainCloud;

UCLASS(MinimalAPI)
class UBCMatchmakingProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
    GENERATED_BODY()

public:
    UBCMatchmakingProxy(const FObjectInitializer& ObjectInitializer);

    /**
    * Read match making record
    *
    * Service Name - MatchMaking
    * Service Operation - Read
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Matchmaking")
        static UBCMatchmakingProxy* Read(ABrainCloud *brainCloud);

    /**
    * Sets player rating
    *
    * Service Name - MatchMaking
    * Service Operation - SetPlayerRating
    *
    * Param - playerRating The new player rating.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Matchmaking")
        static UBCMatchmakingProxy* SetPlayerRating(ABrainCloud *brainCloud, int32 playerRating);

    /**
    * Resets player rating
    *
    * Service Name - MatchMaking
    * Service Operation - ResetPlayerRating
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Matchmaking")
        static UBCMatchmakingProxy* ResetPlayerRating(ABrainCloud *brainCloud);

    /**
    * Increments player rating
    *
    * Service Name - MatchMaking
    * Service Operation - IncrementPlayerRating
    *
    * Param - increment The increment amount
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Matchmaking")
        static UBCMatchmakingProxy* IncrementPlayerRating(ABrainCloud *brainCloud, int32 increment);

    /**
    * Decrements player rating
    *
    * Service Name - MatchMaking
    * Service Operation - DecrementPlayerRating
    *
    * Param - decrement The decrement amount
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Matchmaking")
        static UBCMatchmakingProxy* DecrementPlayerRating(ABrainCloud *brainCloud, int32 decrement);

    /**
    * Turns shield on
    *
    * Service Name - MatchMaking
    * Service Operation - ShieldOn
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Matchmaking")
        static UBCMatchmakingProxy* TurnShieldOn(ABrainCloud *brainCloud);

    /**
    * Turns shield on for the specified number of minutes
    *
    * Service Name - MatchMaking
    * Service Operation - ShieldOnFor
    *
    * Param - minutes Number of minutes to turn the shield on for
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Matchmaking")
        static UBCMatchmakingProxy* TurnShieldOnFor(ABrainCloud *brainCloud, int32 minutes);

    /**
    * Turns shield off
    *
    * Service Name - MatchMaking
    * Service Operation - ShieldOff
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Matchmaking")
        static UBCMatchmakingProxy* TurnShieldOff(ABrainCloud *brainCloud);

	/**
	* Increases the shield on time by specified number of minutes 
	*
	* Service Name - MatchMaking
	* Service Operation - IncrementShieldOnFor
	*
	* Param - minutes Number of minutes to increase the shield time for
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Matchmaking")
		static UBCMatchmakingProxy* IncrementShieldOnFor(ABrainCloud *brainCloud, int32 minutes);

    /**
    * Finds matchmaking enabled players
    *
    * Service Name - MatchMaking
    * Service Operation - FindPlayers
    *
    * Param - rangeDelta The range delta
    * Param - numMatches The maximum number of matches to return
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Matchmaking")
        static UBCMatchmakingProxy* FindPlayers(ABrainCloud *brainCloud, int32 rangeDelta, int32 numMatches);

    /**
    * Finds matchmaking enabled players with additional attributes
    *
    * Service Name - MatchMaking
    * Service Operation - FIND_PLAYERS
    *
    * Param - rangeDelta The range delta
    * Param - numMatches The maximum number of matches to return
    * Param - jsonAttributes Attributes match criteria
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Matchmaking")
        static UBCMatchmakingProxy* FindPlayersWithAttributes(ABrainCloud *brainCloud, int32 rangeDelta, int32 numMatches, const FString& jsonAttributes);

    /**
    * Finds matchmaking enabled players
    *
    * Service Name - MatchMaking
    * Service Operation - FindPlayersUsingFilter
    *
    * Param - rangeDelta The range delta
    * Param - numMatches The maximum number of matches to return
    * Param - jsonExtraParms Other parameters
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Matchmaking")
        static UBCMatchmakingProxy* FindPlayersUsingFilter(ABrainCloud *brainCloud, int32 rangeDelta, int32 numMatches, const FString& jsonExtraParms);

    /**
    * Finds matchmaking enabled players using a cloud code filter
    * and additional attributes
    *
    * Service Name - MatchMaking
    * Service Operation - FIND_PLAYERS_USING_FILTER
    *
    * Param - rangeDelta The range delta
    * Param - numMatches The maximum number of matches to return
    * Param - jsonAttributes Attributes match criteria
    * Param - jsonExtraParms Parameters to pass to the CloudCode filter script
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Matchmaking")
        static UBCMatchmakingProxy* FindPlayersWithAttributesUsingFilter(ABrainCloud *brainCloud, int32 rangeDelta, int32 numMatches, const FString& jsonAttributes, const FString& jsonExtraParms);

    /**
    * Enables Match Making for the Player
    *
    * Service Name - MatchMaking
    * Service Operation - EnableMatchMaking
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Matchmaking")
        static UBCMatchmakingProxy* EnableMatchMaking(ABrainCloud *brainCloud);

    /**
    * Disables Match Making for the Player
    *
    * Service Name - MatchMaking
    * Service Operation - EnableMatchMaking
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Matchmaking")
        static UBCMatchmakingProxy* DisableMatchMaking(ABrainCloud *brainCloud);

    //Response delegates
    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnFailure;

protected:
    // IServerCallback interface
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
    // End of IServerCallback interface
};
