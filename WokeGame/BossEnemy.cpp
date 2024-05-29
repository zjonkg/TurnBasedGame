
// Constructor
#include "BossEnemy.h"




BossEnemy::BossEnemy(int pHp, std::string pName, int pAttack, int pHeavyAttack, int pPoisonAttack, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position)
	: Enemy(pHp, pName, pAttack, texture, imageCount, switchTime, position), heavyAttack(pHeavyAttack), poisonAttack(pPoisonAttack)
{
}

BossEnemy::BossEnemy()
{
}

BossEnemy::~BossEnemy()
{
}

bool BossEnemy::isHeavyAttackUsed()
{
    return heavyAttackUsed;
}

bool BossEnemy::isPoisonAttackUsed()
{
    return poisonAttackUsed;
}

int BossEnemy::getHeavyAttack()
{
    return heavyAttack;
}

int BossEnemy::getPoisonAttack()
{
    return poisonAttack;
}

void BossEnemy::setHeavyAttack(bool used)
{
    heavyAttackUsed = used;
}

void BossEnemy::setPoisonAttack(bool used)
{
    poisonAttackUsed = used;
}


