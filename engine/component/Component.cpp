//
// EPITECH PROJECT, 2018
// rtype
// File description:
// IComponent
//

#include "ScriptedComponent.hpp"
#include "TaskObjective.hpp"
#include "TaskDirection.hpp"
#include "TransShoot.hpp"

using Engine::Component;

int Component::next_id = 0;

// Ctor & Dtor
Component::Component(Engine::GameEngine &engine, bool friendly)
: _engine(engine), _friendly(friendly)
{
	_id = Component::next_id;
	Component::next_id += 1;
}

Component::Component(Engine::GameEngine &engine,
const Engine::Transform &transform, bool friendly)
: _engine(engine), _friendly(friendly), _transform(transform)
{
	_id = Component::next_id;
	Component::next_id += 1;
}

Component::~Component()
{
	if (_renderer != nullptr)
		delete _renderer;
	if (_bullet != nullptr)
		delete _bullet;
	if (_brain != nullptr)
		delete _brain;
	if (_collider != nullptr)
		delete _collider;
}

// Setter
void	Component::setID(int id) noexcept
{
	_id = id;
}

void	Component::setObjective(bool state) noexcept
{
	_objective = state;
}

void	Component::setBrain(Engine::IBrain *brain) noexcept
{
	_brain = brain;
	if (_brain != nullptr) {
		brain->setComponent(*this);
	}
}

void	Component::setBullet(Engine::PreComponent *bullet) noexcept
{
	_bullet = bullet;
}

void	Component::setCollider(Engine::ICollider *collider) noexcept
{
	_collider = collider;
}

void	Component::setARenderer(Engine::ARenderer *renderer) noexcept
{
	_renderer = renderer;
}

// Getter
bool	Component::isObjective() const noexcept
{
	return _objective;
}

bool	Component::isFriendly() const noexcept
{
	return _friendly;
}

int	Component::getID() const noexcept
{
	return _id;
}

Engine::Feature		&Component::getFeature() noexcept
{
	return _feature;
}

Engine::Transform	&Component::getTransform() noexcept
{
	return _transform;
}

const Engine::Feature	&Component::getFeature() const noexcept
{
	return _feature;
}

const Engine::ICollider	*Component::getCollider() const noexcept
{
	return _collider;
}

const Engine::Transform	&Component::getTransform() const noexcept
{
	return _transform;
}

Engine::ARenderer	*Component::getARenderer() const noexcept
{
	return _renderer;
}

// Method
void	Component::doTick()
{
	if (_brain != nullptr)
		_brain->doTick();
}

void	Component::onColliding(IComponent &compo)
{
	compo.getFeature().damage(_feature.getDamages());
}

void	Component::shoot(const Engine::Vector &target, bool dir) const
{
	Engine::ScriptedComponent	*compo;
	Engine::ScriptObject::Task	task;

	if (_bullet == nullptr)
		return;
	compo = new Engine::ScriptedComponent(_engine, _transform,
							_friendly);
	if (dir)
		task = std::make_unique<Engine::TaskDirection>(target);
	else
		task = std::make_unique<Engine::TaskObjective>(target);
	compo->getScript().addTask(std::move(task));
	_engine.createComponent(Engine::GameEngine::Element(compo),
					*_bullet);
	_engine.translater->addAction(std::make_unique<Engine::TransShoot>
					(this->getID(), target));
}

// Extern operator
std::ostream	&operator<<(std::ostream &stream,
			const Engine::IComponent &target)
			noexcept
{
	stream << "[Component] " << target.getTransform();
	return stream;
}
