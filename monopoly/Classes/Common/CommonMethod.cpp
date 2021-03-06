#include <string>
#include "cocos2d.h"
#include "Common/CommonMethod.h"
#include "Common/CommonConstant.h"
#include "Scene/MapScene.h"
#include "Scene/GameController.h"
#include "Scene/StockScene.h"
#include "Scene/ItemScene.h"
USING_NS_CC;


std::string ZH(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

void SendMsg(int msg)
{
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	char* buf = new char[10];
	sprintf(buf, "%d", msg);

	log("message sending : %s", buf);

	EventCustom event = EventCustom("monopoly_msg");
	event.setUserData(buf);
	dispatcher->dispatchEvent(&event);
	CC_SAFE_DELETE_ARRAY(buf);
}

MapScene* GetMapScene()
{
	return dynamic_cast<MapScene*>(Director::getInstance()->getRunningScene());
}

GameController* GetGameController()
{
	auto map_scene = GetMapScene();
	if (!map_scene) return nullptr;
	return dynamic_cast<GameController*>(map_scene->getChildByName("game_controller"));
}

StockScene* GetStockScene()
{
	auto map_scene = GetMapScene();
	if (!map_scene) return nullptr;
	return dynamic_cast<StockScene*>(map_scene->getChildByName("stock_scene"));
}

ItemScene* GetItemScene()
{
	auto map_scene = GetMapScene();
	if (!map_scene) return nullptr;
	return dynamic_cast<ItemScene*>(map_scene->getChildByName("item_scene"));
}

