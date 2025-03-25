

//total day worked in the project 7 days  making on a game in this game engine  (the game have some BUGS PONG)


#include"GLRenderer.h"
#include"DxRenderer.h" 
#include"PhysicsSys.h"
#include"InputHandel.h"
#include <imgui.h>                // Core ImGui functions
 
WindowHandel handel;
namespace gui = ImGui;
static float speed = 348.f;
static float Ballspeed = 190.f;
void ShowOverlay(glm::vec2 pos,const char* c) {
    ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y), ImGuiCond_Always);  // Top-left corner
    //gui::SetNextWindowSize(ImVec2(size.x, size.y));
    ImGui::SetNextWindowBgAlpha(0.15f);  // Transparency

    ImGui::Begin(c, nullptr,
        ImGuiWindowFlags_NoTitleBar |
       // ImGuiWindowFlags_AlwaysAutoResize |
        
        ImGuiWindowFlags_NoFocusOnAppearing |
        ImGuiWindowFlags_NoNav);

}


void movementP1(glm::vec3& pos, float speed, float deltaT, GLFWwindow* handel,int re) {
    if(re != 1)
        if ( GetKey(handel,KEY_W,MODE_PRESS) )pos.y -= speed * deltaT;
    if(re != 2 )   
        if (GetKey(handel,KEY_S,MODE_PRESS)) pos.y += speed * deltaT;
}
void movementP2(glm::vec3& pos, float speed, float deltaT, GLFWwindow* handel, int re) {
    if (re != 1)
        if (GetKey(handel,KEY_UP,MODE_PRESS)) pos.y -= speed * deltaT;
    if (re != 2)
        if ( GetKey(handel,KEY_DOWN,MODE_PRESS)) pos.y += speed * deltaT;
}
 
int main()
{
    
    handel.init(800, 600, "Hex2D PONG DX", API_DIRECTX);
    DxRenderer renderer;
    
	
    //handel.init(800, 600, "Hex2D PONG GL", API_GL);
   // GLRenderer renderer;

    
    renderer.init(handel);
    //input in(handel);
	float pedding = 2.f;
    glm::vec2 size = glm::vec2{ 12.f,100.f };
    glm::vec3 pos = glm::vec3{ size.x / 2.f + pedding, 400.f - size.y , 0.f }; // Adjust if center-based
    glm::vec3 pos2 = glm::vec3{ 800.f - size.x / 2.f - pedding, 400.f - size.y , 0.f };

    glm::vec3 pos3 = glm::vec3(400.f, 300.f, 0.f);
	glm::vec2 velocity = glm::vec2(1.f, 1.f);
	glm::ivec2 scoore = glm::vec2(0.f, 0.f);
    int re;
    bool showUI = false;
	int o = 0;
    int ch = 1;
    while (!handel.WindowShouldClose())
    {
        handel.UpdatehandelDelta();
     /*   velocity.x += Ballspeed * handel.GetDeltaT();
        velocity.y += Ballspeed * handel.GetDeltaT();*/
       
        if( GetKey(handel.GetHandel(),KEY_SPACE,MODE_PRESS) || o == 1) {
			if (o == 0)
			{
				o = 1;
				//velocity = glm::vec2(1.f, 1.f);
			}
            re = phy::CheckScreenTopBottomCollsions(pos3, glm::vec2(15.f, 15.f), handel.GetScreenSize());


            if (re == 2)
            {
                pos3.y = handel.GetScreenSize().y - 15.f;
                velocity.y *= -1.f;
            }
            if (re == 1)
            {
                pos3.y = 15.f;
                velocity.y *= -1.f;
            }
            if (phy::CheckCollisionRec(glm::vec2(pos3.x, pos3.y), glm::vec2(15.f, 15.f), glm::vec2(pos2.x, pos2.y), size) && ch == 1)
            {
                ch = 0;
                
                velocity.x *= -1.f;
                //velocity.y *= -1.f;
                Hlog(LOG_INFO, "Collision B");
				
            }
            if (phy::CheckCollisionRec(glm::vec2(pos3.x, pos3.y), glm::vec2(15.f, 15.f), glm::vec2(pos.x, pos.y), size)&& ch == 0)
            {
                // pos3.y = pos.y + size.y + (15.f / 2.f);
                ch = 1;
                velocity.x *= -1.f;
                //velocity.y *= -1.f;
                Hlog(LOG_INFO, "Collision A");
            }
            if (pos3.x <= 0)
            {
                pos3 = glm::vec3(400.f, 300.f, 0.f);
                ch = 0;
                velocity.x *= +1.f;
                scoore.y++;
            }
            if (pos3.x >= handel.GetScreenSize().x)
            {
                pos3 = glm::vec3(400.f, 300.f, 0.f);
				ch = 1;
                scoore.x++;
            }



            pos3.x += velocity.x * Ballspeed * handel.GetDeltaT();
            pos3.y += velocity.y * Ballspeed * handel.GetDeltaT();

            re = phy::CheckScreenTopBottomCollsions(pos, size, handel.GetScreenSize());
            movementP1(pos, speed, handel.GetDeltaT(), handel.GetHandel(), re);
            re = phy::CheckScreenTopBottomCollsions(pos2, size, handel.GetScreenSize());
            movementP2(pos2, speed, handel.GetDeltaT(), handel.GetHandel(), re);

        }

        renderer.beginDrawing();
        renderer.ClearBackground(HEXBLACK);
		
	   renderer.DrawQuadV(pos, size, glm::vec2(1.f,1.f),  0.f , BLUE);
       renderer.DrawQuadV(pos2, size, glm::vec2(1.f, 1.f), 0.f, RED);
       renderer.DrawQuadV(pos3, glm::vec2(15.f, 15.f), vec2Zero, 0.f, WHITE);
       renderer.DrawImguiText(sstc("FPS: ", std::to_string(handel.GetFPS())).c_str(), glm::vec2(0.f, 0.f), 1.5f);
	   renderer.DrawImguiText(sstc("P1: ", std::to_string(scoore.x)).c_str(), glm::vec2(250.f, 40.f), 1.5f);
	   renderer.DrawImguiText(sstc("P2: ", std::to_string(scoore.y)).c_str(), glm::vec2(500.f, 40.f), 1.5f);
       if (o == 0)
       {
           renderer.DrawImguiText("Press 'Space' to Start Game", glm::vec2(320.f, 200.f), 1.5f);
       }
	    
#pragma region IMGUI


if(showUI)
{
    ShowOverlay(glm::vec2(640.f, 0.f),"Overlay");
    gui::TextUnformatted(sstc("FPS: ", std::to_string(handel.GetFPS())).c_str());

    gui::Checkbox("Vsinc", &renderer.v);
    gui::SliderFloat("BSpeed", &Ballspeed, 50.f, 700.f);
	//gui::SliderFloat("pedding", &pedding, 0.f, 10.f);
	gui::Checkbox("ShowUI", &showUI);
    gui::End();

}
else {
	//gui::Begin("Settings", &showUI);
	ShowOverlay(glm::vec2(720.f, 0.f), "settings");
	gui::Checkbox("ShowUI", &showUI);
	gui::End();
}
        if (renderer.v)
                 renderer.v = true;
        else   renderer.v = false; 
#pragma endregion
       renderer.endDrawing();
        
    }
    
    renderer.ShutDown();   
    handel.ShutDown();     

    return 0;
}