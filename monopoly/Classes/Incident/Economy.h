#ifndef _ECONOMY_H_
#define _ECONOMY_H_

#include "cocos2d.h"
USING_NS_CC;
class Character;
//最好将所有人的税同时都收了
//函数的返回值为征收的数目

//政府征收所得税
int LevyIncomeTax(Character* character);
//政府征收地产税
int LevyEstateTax(Character* character);
//政府征收股票税
int LevyStockTax(Character* character);

//得知地产最多者是谁
Character* GetMostEstate(); 
//得知地产最少者是谁
Character* GetLeastEstate();
//得知股票最多者是谁
Character* GetMostStock();

//奖励地产最多者
void RewardMostEstate(Character*character);
//补助地产最少者
void HelpLeastEstate(Character* character);
//奖励股票拥有最多者
void RewardMostStock(Character* character);

//因交通原因罚款
void TraficFine(Character* character);
#endif
