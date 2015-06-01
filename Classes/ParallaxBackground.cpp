#include "ParallaxBackground.h"

USING_NS_CC;

class PointObject : public Ref
{
public:
	static PointObject * create(Vec2 ratio, Vec2 offset)
	{
		PointObject *ret = new (std::nothrow) PointObject();
		ret->initWithPoint(ratio, offset);
		ret->autorelease();
		return ret;
	}

	bool initWithPoint(Vec2 ratio, Vec2 offset)
	{
		_ratio = ratio;
		_offset = offset;
		_child = nullptr;
		return true;
	}

	inline const Vec2& getRatio() const { return _ratio; };
	inline void setRatio(const Vec2& ratio) { _ratio = ratio; };

	inline const Vec2& getOffset() const { return _offset; };
	inline void setOffset(const Vec2& offset) { _offset = offset; };

	inline Node* getChild() const { return _child; };
	inline void setChild(Node* child) { _child = child; };

private:
	Vec2 _ratio;
	Vec2 _offset;
	Node *_child; // weak ref
};

ParallaxBackground::ParallaxBackground()
	:ParallaxNode(),
	isAddNewNode(true),
	count(0),
	posX(0)
{

}

ParallaxBackground* ParallaxBackground::create()
{
	// Create an instance of InfiniteParallaxNode
	ParallaxBackground* node = new ParallaxBackground();
	if (node) {
		// Add it to autorelease pool
		node->autorelease();
	}
	else {
		// Otherwise delete
		delete node;
		node = 0;
	}
	return node;
}

void ParallaxBackground::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
	Vec2 pos = this->absolutePosition();
	if (!pos.equals(_lastPosition))
	{
		for (int i = 0; i < _parallaxArray->num; i++)
		{
			PointObject *point = (PointObject*)_parallaxArray->arr[i];
			float x = -pos.x + pos.x * point->getRatio().x + point->getOffset().x;
			float y = -pos.y + pos.y * point->getRatio().y + point->getOffset().y;
			point->getChild()->setPosition(x, y);

			// check condition
			float width_texture = point->getChild()->getContentSize().width * point->getChild()->getScale();
			posX = (-pos.x) - count * width_texture;
			if (posX >= width_texture)
			{
				count++;
			}

			// Add node 
			Size visibleSize = Director::getInstance()->getVisibleSize();
			PointObject *point_last = (PointObject*)_parallaxArray->arr[_parallaxArray->num - 1];
			float lastPosX = pos.x + point_last->getOffset().x;

			if (lastPosX + width_texture <= visibleSize.width)
			{
				Sprite* child2 = Sprite::createWithTexture(((Sprite*)point->getChild())->getTexture());	
				child2->setScale(point->getChild()->getScale());
				child2->setAnchorPoint(point->getChild()->getAnchorPoint());
				child2->setColor(point->getChild()->getColor());

				this->addChild(child2, point->getChild()->getZOrder(), point->getRatio(), Vec2(point_last->getOffset().x + width_texture, point->getOffset().y));
			}

			// remove node
			if (posX >= width_texture)
			{				
				this->removeChild(point->getChild(), true);				
			}
		}
		_lastPosition = pos;
	}
	Node::visit(renderer, parentTransform, parentFlags);
}