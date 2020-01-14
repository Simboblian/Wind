#include "Wind.h"

void Wind::Update(sf::Vector2f WindowSize, sf::Vector2f WindowPos, b2World& World)
{
	_summonCounter++;
	if (++_directionCounter > DIRECTIONCHANGERATE)
	{
		_directionCounter = 0;
		RandomizeStrength();
	}

	_strength = _strength + LERPSPEED * ((float)_targetStrength - (float)_strength);

	if (_summonCounter == _summon)
	{
		_summonCounter = 0;

		Blossom* newBlossom;
		newBlossom = new Blossom(BLOSSOMRADIUS, World);

		float x = rand() % (int)WindowSize.x - (WindowSize.x/2);

		newBlossom->SetPosition(sf::Vector2f(x, -(WindowSize.y/2)));

		_blossoms.push_back(newBlossom);
	}

	for (int i = 0; i < _blossoms.size(); i++)
	{
		if (_blossoms[i]->GetPosition().y > (WindowPos.y + (WindowSize.y / 2)))
		{
			_blossoms[i]->GetBody()->DestroyFixture(&_blossoms[i]->GetBody()->GetFixtureList()[0]);
			delete _blossoms[i];
			_blossoms.erase(_blossoms.begin() + i);

			if (_blossoms.size() == 0)
				break;
		}
		else
		{
			if (_strength > 0)
			{
				if (_blossoms[i]->GetPosition().x > (WindowPos.x + (WindowSize.x / 2) + BLOSSOMRADIUS))
					_blossoms[i]->SetPosition(sf::Vector2f(WindowPos.x - (WindowSize.x / 2) - BLOSSOMRADIUS, _blossoms[i]->GetPosition().y));
			}
			else if (_strength < 0)
			{
				if (_blossoms[i]->GetPosition().x < (WindowPos.x - (WindowSize.x / 2) - BLOSSOMRADIUS))
					_blossoms[i]->SetPosition(sf::Vector2f(WindowPos.x + (WindowSize.x / 2) + BLOSSOMRADIUS, _blossoms[i]->GetPosition().y));
			}

			_blossoms[i]->Update(_strength);
		}
	}

	std::cout << _blossoms.size() << std::endl;
}

void Wind::Draw(sf::RenderWindow* Window)
{
	for (int i = 0; i < _blossoms.size(); i++)
	{
		_blossoms[i]->Draw(Window);
	}
}

Wind::Wind(sf::Vector2f WindowSize, sf::Vector2f WindowPos, b2World& World)
{
	_targetStrength = 0;
	_strength = _targetStrength;
	_directionCounter = 0;
	_summonCounter = 0;
	_summon = SUMMONRATE;

	for (int i = 0; i < 20; i++) //Populate the sky
	{
		Blossom* newBlossom;
		newBlossom = new Blossom(BLOSSOMRADIUS, World);

		float x = rand() % (int)WindowSize.x - (WindowSize.x / 2);
		float y = rand() % (int)WindowSize.y - (WindowSize.y / 2);

		newBlossom->SetPosition(sf::Vector2f(x, y));

		_blossoms.push_back(newBlossom);
	}
}

Wind::Wind()
{
	RandomizeStrength();
	_strength = _targetStrength;
	_directionCounter = 0;
	_summonCounter = 0;
	_summon = SUMMONRATE;
}

Wind::~Wind()
{
}
