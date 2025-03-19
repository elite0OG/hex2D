#define DEBUG_INFO
#include"renderer.h"
 


WindowHandel handel;
Renderer renderer;

bool CheckCollision(glm::vec2 posA, glm::vec2 sizeA, glm::vec2 posB, glm::vec2 sizeB) {
    return (posA.x < posB.x + sizeB.x &&
        posA.x + sizeA.x > posB.x &&
        posA.y < posB.y + sizeB.y &&
        posA.y + sizeA.y > posB.y);
}
int main()
{

    handel.init(800, 600, "Hex2D example 1", API_GL);
    renderer.init(handel);
    renderer.RendererHint(DEFALT_RENDERER_TYPE, 4);
     
    while (!glfwWindowShouldClose(handel.GetHandel()))
    {
        
        handel.UpdatehandelDelta();
        renderer.beginDrawing();
        renderer.ClearBackground(HEXBLACK);
        renderer.DrawTriangle(glm::vec3(400.f, 300.f, 0.f), CONBLUE);
        renderer.endDrawing();
    }

    renderer.ShutDown();   
    handel.ShutDown();     

    return 0;
}

//int main()
//{
//
//    handel.init(800, 600, "Hex2D example 1",API_DIRECTX);
//    renderer.init(handel);
//    renderer.RendererHint(DEFALT_RENDERER_TYPE, 4);
//
//    glm::vec3 pos = glm::vec3{ 400.f,300.f,0.f};
//    glm::vec2 size = glm::vec2{ 100.f,100.f};
//    glm::vec3 pos2 = glm::vec3{ 500.f,300.f,0.f};
//    glm::vec2 size2 = glm::vec2{ 100.f,100.f };
//
//   
//    
//    while (!glfwWindowShouldClose(handel.GetHandel()))
//    {
//         
//        handel.UpdatehandelDelta();
//        
//        if (CheckCollision(glm::vec2(pos2.x, pos2.y), size2, glm::vec2(pos.x, pos.y), size)) { Hlog(LOG_INFO, "collisions");    }
//        
//
//        if (glfwGetKey(handel.GetHandel(), GLFW_KEY_D) == GLFW_PRESS) pos.x += 400.f * handel.GetDeltaT();
//        else if (glfwGetKey(handel.GetHandel(), GLFW_KEY_A) == GLFW_PRESS) pos.x -= 400.f * handel.GetDeltaT();
//        else if (glfwGetKey(handel.GetHandel(), GLFW_KEY_W) == GLFW_PRESS) pos.y -= 400.f * handel.GetDeltaT();
//        else if (glfwGetKey(handel.GetHandel(), GLFW_KEY_S) == GLFW_PRESS) pos.y += 400.f * handel.GetDeltaT();
//
//      
//        renderer.beginDrawing();
//       
//       // renderer.ClearBackground(HEXBLACK);
//
//        
//       // renderer.DrawQuadV(pos, size, vec2Zero, 0.f, RED);
//        //renderer.DrawQuadV(pos2, size2, vec2Zero, 0.f, BLUE);
//  
//       // ImGui::Begin("Hex win");
//       // ImGui::Text(("FPS: " + std::to_string(handel.GetFPS())).c_str());
//       // ImGui::End();
//
//        //gltBeginDraw();
//
//        // Draw any amount of text between begin and end
//        //gltColor(1.0f, 1.0f, 1.0f, 1.0f);
//        //gltDrawText2D(text, 0.f, 0.f, 2.f);
//
//        //Finish drawing text
//        //gltEndDraw();
//        renderer.endDrawing();
//      
//    }
//    renderer.ShutDown();
//    handel.ShutDown();
//    //gltDeleteText(text);
//    return 0;
//    //// Destroy glText
//    //gltTerminate();
//   
//
//}
