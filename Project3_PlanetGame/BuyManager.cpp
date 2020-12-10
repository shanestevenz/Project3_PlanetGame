#include "BuyManager.h"
#include <LogManager.h>
#include "Points.h"
#include <EventView.h>
#include <WorldManager.h>

#include "HeavyBlock.h"
#include "Block.h"
#include "Bomb.h"
#include "ChangeHealthEvent.h"

void BuyManager::step()
{
}



BuyManager::BuyManager()
{


    setType("BuyManager");
    setSprite("buymanager"); //sprite
    setLocation(df::BOTTOM_CENTER);
    //setAltitude(6);
    
    registerInterest(df::KEYBOARD_EVENT); //register event

    money = 100; //STARTING MONEY

    moneyView = new Points;
    blockPlacer = new BlockPlacer;
    moneyView->setValue(100);
}

BuyManager::~BuyManager()
{
}

int BuyManager::eventHandler(const df::Event* p_e)
{
    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const df::EventKeyboard* p_keyboard_event = dynamic_cast <const df::EventKeyboard*> (p_e);
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
        { 
            kbd(p_keyboard_event);
            return 1;
        }
    }
}

int BuyManager::draw()
{
    return df::Object::draw();
}

void BuyManager::kbd(const df::EventKeyboard* p_keyboard_event)
{


    switch (p_keyboard_event->getKey()) {
    case df::Keyboard::NUM1: 			//buy

        if (buy(25))
        {
            LM.writeLog("Buy Manager: Buy 1: Block");
            blockPlacer->currentBlock = new Block();
        }

        break;
    case df::Keyboard::NUM2:
        if (buy(50))
        {
            LM.writeLog("Buy Manager: Buy 2: Heavy Block");
            blockPlacer->currentBlock = new HeavyBlock();
        }

        break;
    case df::Keyboard::NUM3:
        if (buy(50))
        {
            LM.writeLog("Buy Manager: Buy 3: Bomb");
            blockPlacer->currentBlock = new Bomb();
        }

        break;
    case df::Keyboard::NUM4:
        if (buy(75))
        {
            LM.writeLog("Buy Manager: Buy 4: +25 health");

            ChangeHealthEvent h_ev(+25); //add health
            WM.onEvent(&h_ev);
        }
    case df::Keyboard::T:
        df::EventView ev(MONEY_STRING, +50, true); //add money
        WM.onEvent(&ev);
        break;
    
    }






}
bool BuyManager::buy(int price)
{


    if (moneyView->getValue() >= price)
    {
        df::EventView ev(MONEY_STRING, -price, true); //remove money
        WM.onEvent(&ev);

        return true;
    }
    else
        return false;
}