//
// Created by Cedric on 2022-04-03.
//

#include "UI/TurretMenu.h"

#include <UI/PurchaseButton.h>
#include <GameAssets.h>
#include <UI/WordsButton.h>
#include <world/animal/state/AnimalIdleState.h>
#include <world/animal/state/SquirrelGatherState.h>
#include <world/animal/state/SquirrelReturnGatherState.h>
#include <world/animal/state/SquirrelGoGathertState.h>
#include <world/animal/state/SquirrelGoDefendTheHomelandState.h>

#include <memory>
#include "UI/AnimalMenu.h"
#include "ForestScreen.h"

TurretMenu::TurretMenu(const wiz::AssetLoader &assetLoader, Forest &forest) : Menu(assetLoader, forest) {

    turretMenu.setTexture(*assetLoader.get(GameAssets::TURRET_MENU));
    turretMenu.setPosition({25, 20});
    turretMenu.setColor(sf::Color::White);
    turretMenu.setScale({4.f, 4.f});

    buttons.push_back(
    new WordsButton(
        sf::IntRect({50, 125}, {200, 100}),
        forest,
        [&](Button* button) {
            Tree* tree = dynamic_cast<Tree*>(forest.getScreen().getEntityClickSelection().getSelectedEntity());
            if(tree != nullptr)
            {
                Squirrel* closestSquirrel = nullptr;
                float disClosest = 0.f;
                for(Entity* e : forest.getObjects())
                {
                    Squirrel* s = dynamic_cast<Squirrel*>(e);
                    if(s && (dynamic_pointer_cast<AnimalIdleState>(s->getState()).get()
                       || dynamic_pointer_cast<SquirrelGatherState>(s->getState()).get()
                       || dynamic_pointer_cast<SquirrelGoGatherState>(s->getState()).get()
                       || dynamic_pointer_cast<SquirrelReturnGatherState>(s->getState()).get()))
                    {
                        if(closestSquirrel == nullptr)
                        {
                            closestSquirrel = s;
                            disClosest = b2DistanceSquared(s->getPosition(), tree->getPosition());
                        }
                        else
                        {
                            float d = b2DistanceSquared(s->getPosition(), tree->getPosition());
                            if(d < disClosest)
                            {
                                disClosest = d;
                                closestSquirrel = s;
                            }
                        }
                    }
                }
                if(closestSquirrel)
                {
                    closestSquirrel->setState(std::make_shared<SquirrelGoDefendTheHomelandState>(closestSquirrel, tree));
                    forest.unassignSquirrel(closestSquirrel);
                }
            }
        },
        [&](){ return forest.getSquirrelCount() > 0; },
        "Assign Squirrel Archer"
    ));

    buttons.push_back(
    new WordsButton(
            sf::IntRect({50, 270}, {200, 100}),
            forest,
            [&](Button* button) {
                if (!dynamic_cast<Tree*>(forest.getScreen().getEntityClickSelection().getSelectedEntity()))
                    return;
                Tree* tree = dynamic_cast<Tree*>(forest.getScreen().getEntityClickSelection().getSelectedEntity());
                if(tree != nullptr)
                {
                    if(tree->getSquirrelCount() > 0)
                    {
                        tree->removeSquirrelTurret();
                        forest.respawnSquirrel(tree);
                    }
                }
            },
            [&](){

                Entity* entity = forest.getScreen().getEntityClickSelection().getSelectedEntity();
                if(entity == nullptr)
                    return false;

                Tree* tree = dynamic_cast<Tree*>(entity);

                if(tree == nullptr)
                    return false;


                return tree->getSquirrelCount() > 0;
                },
            "Unassign Squirrel Archer"
    ));
}

void TurretMenu::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    if(!hidden)
        target.draw(turretMenu);
    Menu::draw(target, states);
}
