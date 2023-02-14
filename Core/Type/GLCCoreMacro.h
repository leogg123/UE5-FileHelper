#pragma once


#define REGISTER_SINGLE_SAVE_INFO(str) \
	FString Get##str() \
	{ \
		if (UGLCSaveObject* InObject___ = GetMutableDefault<UGLCSaveObject>()) \
		{ \
			InObject___->LoadConfig(); \
			return InObject___->str; \
		} \
		return FString();\
	}\
	void Set##str(const FString& InStr) \
	{ \
		if (UGLCSaveObject* InObject___ = GetMutableDefault<UGLCSaveObject>()) \
		{ \
			InObject___->LoadConfig();\
			InObject___->str = InStr; \
			InObject___->SaveConfig(); \
		} \
	}

#define REGISTER_SAVE_INFOS(str)\
	FString Get##str##Path() \
	{ \
		if (UGLCSaveObject* InObject___ = GetMutableDefault<UGLCSaveObject>()) \
		{ \
			InObject___->LoadConfig(); \
			return InObject___->str.Path; \
		} \
			return FString();\
	}\
	FString Get##str##Param() \
	{ \
		if (UGLCSaveObject* InObject___ = GetMutableDefault<UGLCSaveObject>()) \
		{ \
			InObject___->LoadConfig(); \
			return InObject___->str.Param; \
		} \
			return FString();\
	}\
	void Set##str##Path(const FString& InPath) \
	{\
		if (UGLCSaveObject* InObject___ = GetMutableDefault<UGLCSaveObject>()) \
		{ \
			InObject___->LoadConfig(); \
			InObject___->str.Path = InPath; \
			InObject___->SaveConfig(); \
		} \
	}\
	void Set##str##Param(const FString& InParam) \
	{\
		if (UGLCSaveObject* InObject___ = GetMutableDefault<UGLCSaveObject>()) \
		{ \
			InObject___->LoadConfig(); \
			InObject___->str.Param = InParam; \
			InObject___->SaveConfig(); \
		} \
	}
