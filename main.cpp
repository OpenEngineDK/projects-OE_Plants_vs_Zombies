/*
 *	MAIN.CPP
 */

#include "Game.h"
#include "Board.h"

#include "Player.h"
#include "Players/PassivePlayer.h"

#include "Plant.h"
#include "Plants/PeaShooter.h"

//#include "ZombieSpawner.h"
#include "Zombie.h"
#include "Zombies/DefaultZombie.h"

// OpenEngine stuff
#include <Meta/Config.h>
#include <Logging/Logger.h>
#include <Logging/StreamLogger.h>
#include <Core/Engine.h>

#include <Scene/MeshNode.h>
#include <Scene/SceneNode.h>
#include <Scene/RenderStateNode.h>
#include <Scene/RenderNode.h>
#include <Scene/PointLightNode.h>

#include <Utils/SimpleSetup.h>
#include <Utils/MeshUtils.h>
#include <Utils/CameraTool.h>
#include <Utils/ToolChain.h>
#include <Utils/MouseSelection.h>
#include <Utils/ActionCallback.h>
#include <Utils/MeshCreator.h>
#include <Utils/BetterMoveHandler.h>

#include <Display/Camera.h>
#include <Display/SDLEnvironment.h>

#include <Resources/ITexture2D.h>
#include <Resources/ResourceManager.h>
#include <Resources/DirectoryManager.h>
#include <Resources/SDLImage.h>

using namespace OpenEngine::Logging;
using namespace OpenEngine::Core;
using namespace OpenEngine::Utils;
using namespace OpenEngine::Scene;
using namespace OpenEngine::Display;
using namespace OpenEngine::Devices;
using namespace OpenEngine::Math;
using namespace OpenEngine::Resources;
using namespace OpenEngine::Renderers::OpenGL;

class ActionHandler :   public IListener<OpenEngine::Core::ProcessEventArg>,
                        public IListener<OpenEngine::Devices::KeyboardEventArg>
{
    Game *game;
    Board *board;
    HUD *hud;

    ITexture2DPtr plantTex;
    ITexture2DPtr zombieTex;
    ITexture2DPtr peaTex;

    std::vector<HUD::Surface*> surfaces;

    public:
    ActionHandler(Game *g, Board *b, HUD *h)
        : game(g), board(b), hud(h)
    {
        ITexture2DPtr board = ResourceManager<ITexture2D>::Create("Board.jpg");
        board->Load();
        HUD::Surface *boardSurface = hud->CreateSurface(board);
        boardSurface->SetPosition(0, 0);
        boardSurface->SetScale(HUD::Surface::FULLSCREEN);

        plantTex = ResourceManager<ITexture2D>::Create("Plants/PeaShooter.png");
        plantTex->Load();
        zombieTex = ResourceManager<ITexture2D>::Create("Zombies/DefaultZombie.png");
        zombieTex->Load();
        peaTex = ResourceManager<ITexture2D>::Create("Peas/Pea.png");
        peaTex->Load();
    }

    void Handle(OpenEngine::Core::ProcessEventArg arg)
    {
        game->update();

        for(unsigned int x=0; x<surfaces.size(); x++)
        {
            delete surfaces.at(x);
        }
        surfaces.clear();

        std::vector<Plant*> plants = board->getPlantBoard();
        for(unsigned int x=0; x<board->numPlantsTotal(); x++)
        {
            unsigned int plantX = plants.at(x)->getX();
            unsigned int plantY = plants.at(x)->getY();
            HUD::Surface *plantSurface = hud->CreateSurface(plantTex);
            plantSurface->SetPosition(plantX*100, plantY*100);

            surfaces.push_back(plantSurface);
        }
        
        std::vector<Zombie*> zombies = board->getZombieBoard();
        for(unsigned int x=0; x<board->numZombiesTotal(); x++)
        {
            float zombieX = zombies.at(x)->getX();
            float zombieY = zombies.at(x)->getY();
            HUD::Surface *zombieSurface = hud->CreateSurface(zombieTex);
            zombieSurface->SetPosition(zombieX*100, zombieY*100);

            surfaces.push_back(zombieSurface);
        }
        
        std::vector<Pea*> peas = board->getPeaBoard();
        for(unsigned int x=0; x<board->numPeasTotal(); x++)
        {
            float peasX = peas.at(x)->getX();
            float peasY = peas.at(x)->getY();
            HUD::Surface *peaSurface = hud->CreateSurface(peaTex);
            peaSurface->SetPosition(25+peasX*100, 25+peasY*100);

            surfaces.push_back(peaSurface);
        }
        
    }

    void Handle(OpenEngine::Devices::KeyboardEventArg arg)
    {
    }
};

// main() is basically an infinite loop that just calls update on the game
int main(int argc, char* argv[])
{
    // Setup logging facilities.
    // Create simple setup
    IEnvironment* env = new SDLEnvironment(800,600);
    SimpleSetup* setup = new SimpleSetup("OE_Plants", env);

    // root
    RenderStateNode *rsn = new RenderStateNode();
    setup->GetRenderer().SetBackgroundColor(Vector<4,float>(0,0,1,1));

    // rsn->DisableOption(RenderStateNode::TEXTURE);
    rsn->EnableOption(RenderStateNode::COLOR_MATERIAL);
    rsn->EnableOption(RenderStateNode::LIGHTING);
    ISceneNode *root = rsn;
    setup->SetScene(*root);
    
	HUD* hud = new HUD();
    setup->GetRenderer().PostProcessEvent().Attach(*hud);
    setup->GetRenderer().PreProcessEvent().Attach(*hud);

    ResourceManager<ITexture2D>::AddPlugin(new SDLImagePlugin());
    
    string resources = "projects/OE_Plants_vs_Zombies/Data/";
    DirectoryManager::AppendPath(resources);

    // Show FPS
    setup->ShowFPS();

    // Game setup
    Game* game = new Game();
    Player* player = new PassivePlayer();
    Board* board = new Board();
    board->addValidPlant(new PeaShooter());
    //board->addListener(new ZombieSpawner(board));
    board->addZombie(new DefaultZombie(board->numColumns(), 0/*rand() % board->numLines()*/, -0.005f, 10));
    board->make_move("a0->PeaShooter");

    game->seedPlayer(player);
    game->seedBoard(board);
    
    ActionHandler *hdl = new ActionHandler(game, board, hud);
    setup->GetEngine().ProcessEvent().Attach(*hdl);
    setup->GetKeyboard().KeyEvent().Attach(*hdl);   
	
    // Start the engine.
    setup->GetEngine().Start();

    // Return when the engine stops.
    return EXIT_SUCCESS;
}


