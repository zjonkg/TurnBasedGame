
#include "Enemy.h"
#include <string>


class BossEnemy : public Enemy
{
private:
	int heavyAttack;
	int poisonAttack;
	bool heavyAttackUsed;
	bool poisonAttackUsed;

public:
	BossEnemy(int pHp, std::string pName, int pAttack, int pHeavyAttack, int pPoisonAttack, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position);
	BossEnemy();
	~BossEnemy();
	bool isHeavyAttackUsed();
	bool isPoisonAttackUsed();

	int getHeavyAttack();
	int getPoisonAttack();

	void setHeavyAttack(bool used);
	void setPoisonAttack(bool used);
};

