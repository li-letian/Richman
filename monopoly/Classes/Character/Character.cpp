#include "Character/Character.h"
#include "Common/CommonConstant.h"
#include "Common/CommonMethod.h"

USING_NS_CC;

Character::Character()
	:character_anim_down_(nullptr),
	character_anim_left_(nullptr),
	character_anim_right_(nullptr),
	character_anim_up_(nullptr),
	character_frame_cache_(nullptr),
	name_(),
	money_(initial_money),
	cur_pos_(0),
	steps_scope_(walk_steps),
	stop_times_(0),
	condition_(normal),
	estate_value_(0),
	gain_value_(0),
	god_possessed_(no_god),
	turtle_times_(0),
	control_dice_point_(0),
	is_stay_(false),
	toward_direction_(forward_dir),
	is_ai_(false)
{
	this->setTag(0);
}

Character::~Character()
{
	//释放先前retain的动画对象
	character_anim_down_->release();
	character_anim_left_->release();
	character_anim_right_->release();
	character_anim_up_->release();
}


bool Character::init(const std::string& name, int tag, int money, int cur_pos, MapScene* map_scene)
{
	if (!Sprite::init())
	{
		return false;
	}

	//设置一些基本属性
	name_ = name;
	this->setTag(tag);
	money_ = money;
	cur_pos_ = cur_pos;

	initAnimate();	//初始化动画对象
	initSprite();	//设置人物初始形象
	
	mini_avatar_ = Sprite::create(StringUtils::format("%s_avatar.png", name.c_str()));
	mini_avatar_->setAnchorPoint(Vec2(0.5f, 0.5f));
	mini_avatar_->setScale(3.5f);
	map_scene_ = map_scene;
	map_scene_->getMiniMap()->addChild(mini_avatar_, 50);
	setCurPos(cur_pos);
	return true;
}

void Character::initAnimate()
{
	character_frame_cache_ = SpriteFrameCache::getInstance();
	character_frame_cache_->addSpriteFramesWithFile(StringUtils::format("%s.plist", name_.c_str()), StringUtils::format("%s.png", name_.c_str()));

	Vector<SpriteFrame*>character_anim_down_vec;
	Vector<SpriteFrame*>character_anim_left_vec;
	Vector<SpriteFrame*>character_anim_right_vec;
	Vector<SpriteFrame*>character_anim_up_vec;

	for (int i = 0; i < 4; ++i)
	{
		auto frame = character_frame_cache_->getSpriteFrameByName(StringUtils::format("%s-%d.png", name_.c_str(), i));
		character_anim_down_vec.pushBack(frame);
	}
	for (int i = 4; i < 8; ++i)
	{
		auto frame = character_frame_cache_->getSpriteFrameByName(StringUtils::format("%s-%d.png", name_.c_str(), i));
		character_anim_left_vec.pushBack(frame);
	}
	for (int i = 8; i < 12; ++i)
	{
		auto frame = character_frame_cache_->getSpriteFrameByName(StringUtils::format("%s-%d.png", name_.c_str(), i));
		character_anim_right_vec.pushBack(frame);
	}
	for (int i = 12; i < 16; ++i)
	{
		auto frame = character_frame_cache_->getSpriteFrameByName(StringUtils::format("%s-%d.png", name_.c_str(), i));
		character_anim_up_vec.pushBack(frame);
	}
	
	character_anim_down_ = Animate::create(Animation::createWithSpriteFrames(character_anim_down_vec, character_walk_delay_time));
	character_anim_left_ = Animate::create(Animation::createWithSpriteFrames(character_anim_left_vec, character_walk_delay_time));
	character_anim_right_ = Animate::create(Animation::createWithSpriteFrames(character_anim_right_vec, character_walk_delay_time));
	character_anim_up_ = Animate::create(Animation::createWithSpriteFrames(character_anim_up_vec, character_walk_delay_time));

	//暂时不添加到父节点中，retain以防止被autorelease
	character_anim_down_->retain();
	character_anim_left_->retain();
	character_anim_right_->retain();
	character_anim_up_->retain();
}

void Character::initSprite()
{
	auto spf = character_frame_cache_->getSpriteFrameByName(StringUtils::format("%s-4.png", name_.c_str()));
	this->initWithSpriteFrame(spf);
	this->setAnchorPoint(Vec2(0.5f, 0.15f));
}

void Character::setMiniAvatar(int index)
{
	mini_avatar_->setPosition(map_scene_->pos(index));
}
