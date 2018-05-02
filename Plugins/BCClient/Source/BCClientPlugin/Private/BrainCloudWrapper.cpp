// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudWrapper.h"

#include "BrainCloudClient.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "OperationParam.h"

#include "BrainCloudSave.h"
#include "Kismet/GameplayStatics.h"

BrainCloudWrapper * BrainCloudWrapper::_instance = nullptr;

BrainCloudWrapper::BrainCloudWrapper()
{
  _client = new BrainCloudClient();
}

BrainCloudWrapper::BrainCloudWrapper(FString wrapperName)
{
	_client = new BrainCloudClient();
	_wrapperName = wrapperName;
}

BrainCloudWrapper::BrainCloudWrapper(BrainCloudClient *client)
{
	_client = client;
}

BrainCloudWrapper * BrainCloudWrapper::getInstance()
{
	if (BrainCloudClient::EnableSingletonMode == false)
	{
		if (BrainCloudClient::EnableSoftErrorMode)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), BrainCloudClient::SINGLETON_USE_ERROR_MESSAGE);
		}
		else
		{
			UE_LOG(LogTemp, Fatal, TEXT("%s"), BrainCloudClient::SINGLETON_USE_ERROR_MESSAGE);
		}
	}

  if (_instance == nullptr)
  {
    _instance = new BrainCloudWrapper();
  }
  return _instance;
}

void BrainCloudWrapper::initialize(FString url, FString secretKey, FString appId, FString appVersion)
{
  // save the game app in case we need to reauthenticate
  _lastUrl = url;
  _lastSecretKey = secretKey;
  _lastAppId = appId;
  _lastAppVersion = appVersion;

  // initialize the client with our app info
  _client->initialize(url, secretKey, appId, appVersion);

  loadData();
}

void BrainCloudWrapper::initializeIdentity(bool isAnonymousAuth)
{
  // create an anonymous ID if necessary
  if ((!_anonymousId.IsEmpty() && _profileId.IsEmpty()) || _anonymousId.IsEmpty())
  {
    setStoredAnonymousId(_client->getAuthenticationService()->generateAnonymousId());
    setStoredProfileId(TEXT(""));
  }

  FString profileIdToAuthenticateWith = _profileId;
  if (!isAnonymousAuth && _alwaysAllowProfileSwitch)
  {
    profileIdToAuthenticateWith = TEXT("");
  }
  setStoredAuthenticationType(isAnonymousAuth ? OperationParam::AuthenticateServiceAuthenticateAuthAnonymous.getValue() : TEXT(""));

  // send our IDs to brainCloud
  _client->initializeIdentity(profileIdToAuthenticateWith, _anonymousId);
}

void BrainCloudWrapper::reauthenticate()
{
  // send our saved game info to brainCloud
  // company and game name can be nullptr since they are already set
  initialize(_lastUrl, _lastSecretKey, _lastAppId, _lastAppVersion);

  if (_authenticationType == OperationParam::AuthenticateServiceAuthenticateAuthAnonymous.getValue())
  {
    authenticateAnonymous();
  }
}

// authenticate the player with an anonymous id
void BrainCloudWrapper::authenticateAnonymous(IServerCallback * callback)
{
  _authenticateCallback = callback;
  initializeIdentity(true);
  _client->getAuthenticationService()->authenticateAnonymous(true, this);
}

void BrainCloudWrapper::authenticateEmailPassword(FString email, FString password, bool forceCreate, IServerCallback * callback)
{
  _authenticateCallback = callback;
  initializeIdentity();
  _client->getAuthenticationService()->authenticateEmailPassword(email, password, forceCreate, this);
}

void BrainCloudWrapper::authenticateExternal(FString userid, FString token, FString externalAuthName, bool forceCreate, IServerCallback * callback)
{
  _authenticateCallback = callback;
  initializeIdentity();
  _client->getAuthenticationService()->authenticateExternal(userid, token, externalAuthName, forceCreate, this);
}

void BrainCloudWrapper::authenticateFacebook(FString fbUserId, FString fbAuthToken, bool forceCreate, IServerCallback * callback)
{
  _authenticateCallback = callback;
  initializeIdentity();
  _client->getAuthenticationService()->authenticateFacebook(fbUserId, fbAuthToken, forceCreate, this);
}

void BrainCloudWrapper::authenticateGameCenter(FString gameCenterId, bool forceCreate, IServerCallback * callback)
{
  _authenticateCallback = callback;
  initializeIdentity();
  _client->getAuthenticationService()->authenticateGameCenter(gameCenterId, forceCreate, this);
}

void BrainCloudWrapper::authenticateGoogle(FString userid, FString token, bool forceCreate, IServerCallback * callback)
{
  _authenticateCallback = callback;
  initializeIdentity();
  _client->getAuthenticationService()->authenticateGoogle(userid, token, forceCreate, this);
}

void BrainCloudWrapper::authenticateSteam(FString userid, FString sessionticket, bool forceCreate, IServerCallback * callback)
{
  _authenticateCallback = callback;
  initializeIdentity();
  _client->getAuthenticationService()->authenticateSteam(userid, sessionticket, forceCreate, this);
}

void BrainCloudWrapper::authenticateTwitter(FString userid, FString token, FString secret, bool forceCreate, IServerCallback * callback)
{
  _authenticateCallback = callback;
  initializeIdentity();
  _client->getAuthenticationService()->authenticateTwitter(userid, token, secret, forceCreate, this);
}

void BrainCloudWrapper::authenticateUniversal(FString userid, FString password, bool forceCreate, IServerCallback * callback)
{
  _authenticateCallback = callback;
  initializeIdentity();
  //_client->getAuthenticationService()->authenticateUniversal(userid, password, forceCreate, this);


	smartSwitchAuthenticateUniversal(userid, password, forceCreate, callback);
}







/**
	*	Callbacks used for the smart switches
	*/
	class IdentityCallback : public IServerCallback
	{
	public: 
		 FString JSON_DATA = "data";
		 FString JSON_IDENTITIES = "identities";

		BrainCloudWrapper * wrapper;
		IServerCallback * authenticateCallback;

		IdentityCallback(BrainCloudWrapper * in_wrapper, IServerCallback * in_authenticateCallback) {
			wrapper = in_wrapper;
			authenticateCallback = in_authenticateCallback;
		}

		void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
		{
            TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(*jsonData);
            TSharedPtr<FJsonObject> jsonReadObject;
            bool result = FJsonSerializer::Deserialize(reader, jsonReadObject);

            if (result == true) //if deserializing was successful
            {
                 TSharedPtr<FJsonObject> data = jsonReadObject->GetObjectField(TEXT("data"));
								 

								 TSharedPtr<FJsonObject>;
								 TArray<FString> ArrayJson;


                TSharedPtr<FJsonObject> identities = data->TryGetStringArrayField(TEXT("identities", ArrayJson));

								TSharedPtr<FJsonObject> identities2 = data->TryGetObjectField(TEXT("identities", ArrayJson));


/*
                if(identities.count > 0)
                {
                    wrapper->getClient()->getPlayerStateService()->logout();
                } 
                else 
                {
                    wrapper->getClient()->getPlayerStateService()->deletePlayer();
                }

                wrapper->getClient()->insertEndOfMessageBundleMarker();
			    
					authenticateCallback->serverCallback(serviceName, serviceOperation, jsonData);
					*/
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to deserialize JSON!"));
            }
            

        /*
			if (listOfIdentities.size()) {
				wrapper->getClient()->getPlayerStateService()->logout();
			}
			else {
				wrapper->getClient()->getPlayerStateService()->deletePlayer();
			}
			
			wrapper->getClient()->insertEndOfMessageBundleMarker();
			authenticateCallback->serverCallback(serviceName, serviceOperation, jsonData);
            */
			delete this;
		}

		void serverError(ServiceName serviceName, ServiceOperation serviceOperation,int32 statusCode, int32 reasonCode, const FString& jsonError)
		{
		//	authenticateCallback->serverError(serviceName, serviceOperation, statusCode, reasonCode, jsonError);
			delete this;
		}

	};

	class SmartSwitchCallback : public IServerCallback
	{
	public:
		SmartSwitchCallback(BrainCloudWrapper *in_wrapper, IServerCallback * in_callback) {
			wrapper = in_wrapper;
			callback = in_callback;
		}

		BrainCloudWrapper * wrapper;
		IServerCallback * callback;

		void clearIds() {
			wrapper->resetStoredAnonymousId();
			wrapper->resetStoredProfileId();
			wrapper->getClient()->getAuthenticationService()->clearSavedProfileId();
		}

		void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
		{
			callback->serverError(serviceName, serviceOperation, statusCode, reasonCode, jsonError);
			delete this;
		}
	};

	void BrainCloudWrapper::smartSwitchAuthenticateEmailPassword(FString email, FString password, bool forceCreate, IServerCallback * callback)
	{
		class SmartSwitchAuthenticateCallback : public SmartSwitchCallback
		{
		public:
			SmartSwitchAuthenticateCallback(BrainCloudWrapper * in_wrapper, FString in_email, FString in_password, bool in_forceCreate, IServerCallback * in_callback) : SmartSwitchCallback(in_wrapper, in_callback) {
				email = in_email;
				password = in_password;
				forceCreate = in_forceCreate;
			}

			 FString email; FString password; bool forceCreate;

			void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
			{
				clearIds();
				wrapper->getClient()->getAuthenticationService()->authenticateEmailPassword(email, password, forceCreate, callback);
				delete this;
			}
		};

		SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, email, password, forceCreate, callback);
		getIdentitiesCallback(smartCallback);
	}

	void BrainCloudWrapper::smartSwitchAuthenticateExternal(FString userid, FString token, FString externalAuthName, bool forceCreate, IServerCallback * callback)
	{
		class SmartSwitchAuthenticateCallback : public SmartSwitchCallback
		{
		public:
			SmartSwitchAuthenticateCallback(BrainCloudWrapper * in_wrapper, FString in_userid, FString in_token, FString in_externalAuthName, bool in_forceCreate, IServerCallback * in_callback) : SmartSwitchCallback(in_wrapper, in_callback) {
				userid = in_userid;
				token = in_token;
				externalAuthName = in_externalAuthName;
				forceCreate = in_forceCreate;
			}

			 FString userid; FString token; FString externalAuthName; FString fbAuthToken; bool forceCreate;

			void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
			{
				clearIds();
				wrapper->getClient()->getAuthenticationService()->authenticateExternal(userid, token, externalAuthName, forceCreate, callback);
				delete this;
			}
		};

		SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, userid, token, externalAuthName, forceCreate, callback);
		getIdentitiesCallback(smartCallback);
	}

	void BrainCloudWrapper::smartSwitchAuthenticateFacebook(FString fbUserId, FString fbAuthToken, bool forceCreate, IServerCallback * callback)
	{
		class SmartSwitchAuthenticateCallback : public SmartSwitchCallback
		{
		public:
			SmartSwitchAuthenticateCallback(BrainCloudWrapper *in_wrapper, FString in_fbUserId, FString in_fbAuthToken, bool in_forceCreate, IServerCallback * in_callback) : SmartSwitchCallback(in_wrapper, in_callback) {
				fbUserId = in_fbUserId;
				fbAuthToken = in_fbAuthToken;
				forceCreate = in_forceCreate;
			}

			 FString fbUserId; FString fbAuthToken; bool forceCreate;

			void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
			{
				clearIds();
				wrapper->getClient()->getAuthenticationService()->authenticateFacebook(fbUserId, fbAuthToken, forceCreate, callback);
				delete this;
			}
		};

		SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, fbUserId, fbAuthToken, forceCreate, callback);
		getIdentitiesCallback(smartCallback);
	}

	void BrainCloudWrapper::smartSwitchAuthenticateGameCenter(FString gameCenterId, bool forceCreate, IServerCallback * callback)
	{
		class SmartSwitchAuthenticateCallback : public SmartSwitchCallback
		{
		public:
			SmartSwitchAuthenticateCallback(BrainCloudWrapper * in_wrapper, FString in_gameCenterId, bool in_forceCreate, IServerCallback * in_callback) : SmartSwitchCallback(in_wrapper, in_callback) {
				gameCenterId = in_gameCenterId;
				forceCreate = in_forceCreate;
			}

			 FString gameCenterId; bool forceCreate;

			void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
			{
				clearIds();
				wrapper->getClient()->getAuthenticationService()->authenticateGameCenter(gameCenterId, forceCreate, callback);
				delete this;
			}
		};

		SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, gameCenterId, forceCreate, callback);
		getIdentitiesCallback(smartCallback);
	}

	void BrainCloudWrapper::smartSwitchAuthenticateGoogle(FString userid, FString token, bool forceCreate, IServerCallback * callback)
	{
		class SmartSwitchAuthenticateCallback : public SmartSwitchCallback
		{
		public:
			SmartSwitchAuthenticateCallback(BrainCloudWrapper *in_wrapper, FString in_userid, FString in_token, bool in_forceCreate, IServerCallback * in_callback) : SmartSwitchCallback(in_wrapper, in_callback) {
				userid = in_userid;
				token = in_token;
				forceCreate = in_forceCreate;
			}

			 FString userid; FString token; bool forceCreate;

			void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
			{
				clearIds();
				wrapper->getClient()->getAuthenticationService()->authenticateGoogle(userid, token, forceCreate, callback);
				delete this;
			}
		};

		SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, userid, token, forceCreate, callback);
		getIdentitiesCallback(smartCallback);
	}

	void BrainCloudWrapper::smartSwitchAuthenticateSteam(FString userid, FString sessionticket, bool forceCreate, IServerCallback * callback)
	{
		class SmartSwitchAuthenticateCallback : public SmartSwitchCallback
		{
		public:
			SmartSwitchAuthenticateCallback(BrainCloudWrapper *in_wrapper, FString in_userid, FString in_sessionticket, bool in_forceCreate, IServerCallback * in_callback) : SmartSwitchCallback(in_wrapper, in_callback) {
				userid = in_userid;
				sessionticket = in_sessionticket;
				forceCreate = in_forceCreate;
			}

			 FString userid; FString sessionticket; bool forceCreate;

			void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
			{
				clearIds();
				wrapper->getClient()->getAuthenticationService()->authenticateSteam(userid, sessionticket, forceCreate, callback);
				delete this;
			}
		};

		SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, userid, sessionticket, forceCreate, callback);
		getIdentitiesCallback(smartCallback);
	}

	void BrainCloudWrapper::smartSwitchAuthenticateTwitter(FString userid, FString token, FString secret, bool forceCreate, IServerCallback * callback)
	{
		class SmartSwitchAuthenticateCallback : public SmartSwitchCallback
		{
		public:
			SmartSwitchAuthenticateCallback(BrainCloudWrapper *in_wrapper, FString in_userid, FString in_token, FString in_secret, bool in_forceCreate, IServerCallback * in_callback) : SmartSwitchCallback(in_wrapper, in_callback) {
				userid = in_userid;
				token = in_token;
				secret = in_secret;
				forceCreate = in_forceCreate;
			}

			 FString userid; FString token; FString secret; bool forceCreate;

			void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
			{
				clearIds();
				wrapper->getClient()->getAuthenticationService()->authenticateTwitter(userid, token, secret, forceCreate, callback);
				delete this;
			}
		};

		SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, userid, token, secret, forceCreate, callback);
		getIdentitiesCallback(smartCallback);
	}

  void BrainCloudWrapper::smartSwitchAuthenticateUniversal(FString userid, FString password, bool forceCreate, IServerCallback * callback)
  {
		class SmartSwitchAuthenticateCallback : public SmartSwitchCallback
		{
		public:
			SmartSwitchAuthenticateCallback(BrainCloudWrapper * in_wrapper, FString in_userid, FString in_password, bool in_forceCreate, IServerCallback * in_callback) : SmartSwitchCallback(in_wrapper, in_callback) {
				userid = in_userid;
				password = in_password;
				forceCreate = in_forceCreate;
			}

			FString userid; FString password; bool forceCreate;
			
			void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
			{
				clearIds();
				wrapper->getClient()->getAuthenticationService()->authenticateUniversal(userid, password, forceCreate, callback);
				delete this;
			}
		};

		SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, userid, password, forceCreate, callback);
		getIdentitiesCallback(smartCallback);
  }







void BrainCloudWrapper::getIdentitiesCallback(IServerCallback *success)
{
	 FString JSON_DATA = "data";
	 FString JSON_IDENTITIES = "identities";

	IdentityCallback *identityCallback = new IdentityCallback(this, success);
	identityCallback->authenticateCallback = success;


	if (getClient()->isAuthenticated()) {
		getClient()->getIdentityService()->getIdentities(identityCallback);
	}
	else {
		success->serverCallback(ServiceName::AuthenticateV2, ServiceOperation::Authenticate, "");
	}
}

void BrainCloudWrapper::reconnect(IServerCallback * callback)
{
	authenticateAnonymous(callback);
}

void BrainCloudWrapper::runCallbacks()
{
  _client->runCallbacks();
}

void BrainCloudWrapper::setAlwaysAllowProfileSwitch(bool alwaysAllow)
{
  _alwaysAllowProfileSwitch = alwaysAllow;
}

bool BrainCloudWrapper::getAlwaysAllowProfileSwitch()
{
  return _alwaysAllowProfileSwitch;
}

void BrainCloudWrapper::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, FString const & jsonData)
{
  if (serviceName == ServiceName::AuthenticateV2 && serviceOperation == ServiceOperation::Authenticate)
  {
    FString profileId = TEXT("");
    TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(jsonData);
    TSharedPtr<FJsonObject> jsonPacket = MakeShareable(new FJsonObject());
    bool res = FJsonSerializer::Deserialize(reader, jsonPacket);

    if (res)
    {
      TSharedPtr<FJsonObject> data = jsonPacket->GetObjectField(TEXT("data"));
      profileId = data->GetStringField(TEXT("profileId"));
    }

    if (profileId != TEXT(""))
    {
      setStoredProfileId(profileId);
    }
  }

  if (_authenticateCallback != nullptr)
  {
    _authenticateCallback->serverCallback(serviceName, serviceOperation, jsonData);
  }
}

void BrainCloudWrapper::serverError(ServiceName serviceName, ServiceOperation serviceOperation,
  int32 statusCode, int32 reasonCode, const FString & message)
{
  if (_authenticateCallback != nullptr)
  {
    _authenticateCallback->serverError(serviceName, serviceOperation, statusCode, reasonCode, message);
  }
}

void BrainCloudWrapper::loadData()
{
  UBrainCloudSave* LoadGameInstance = Cast<UBrainCloudSave>(UGameplayStatics::CreateSaveGameObject(UBrainCloudSave::StaticClass()));
  
	FString slotPrefix = _wrapperName;

	LoadGameInstance = Cast<UBrainCloudSave>(UGameplayStatics::LoadGameFromSlot(slotPrefix + LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
  if (LoadGameInstance == nullptr) return;

  _profileId = LoadGameInstance->ProfileId;
  _anonymousId = LoadGameInstance->AnonymousId;
  _authenticationType = LoadGameInstance->AuthenticationType;
}

void BrainCloudWrapper::saveData()
{
  UBrainCloudSave* SaveGameInstance = Cast<UBrainCloudSave>(UGameplayStatics::CreateSaveGameObject(UBrainCloudSave::StaticClass()));
  SaveGameInstance->ProfileId = _profileId;
  SaveGameInstance->AnonymousId = _anonymousId;
  SaveGameInstance->AuthenticationType = _authenticationType;

	FString slotPrefix = _wrapperName;

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, _wrapperName + SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}
