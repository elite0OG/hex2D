#include"GLRenderer.h"
#include"DxRenderer.h" 
#include"PhysicsSys.h"

WindowHandel handel;
 

 //total day worked in the project 4 days 
int main()
{
    
    handel.init(800, 600, "Hex2D example 1 DX", API_DIRECTX);
    DxRenderer renderer;
    //handel.init(800, 600, "Hex2D example 1 GL", API_GL);
    //GLRenderer renderer;

    
    renderer.init(handel);
     
	glm::vec3 pos = glm::vec3{ 0.f,0.f,0.f };
    while (!glfwWindowShouldClose(handel.GetHandel()))
    {
        handel.UpdatehandelDelta();
        renderer.beginDrawing();
        renderer.ClearBackground(HEXBLACK);
        if (glfwGetKey(handel.GetHandel(), GLFW_KEY_W) == GLFW_PRESS) pos.y -= 200.0f * handel.GetDeltaT();
        if (glfwGetKey(handel.GetHandel(), GLFW_KEY_S) == GLFW_PRESS) pos.y += 200.0f * handel.GetDeltaT();
        if (glfwGetKey(handel.GetHandel(), GLFW_KEY_A) == GLFW_PRESS) pos.x -= 200.0f * handel.GetDeltaT();
        if (glfwGetKey(handel.GetHandel(), GLFW_KEY_D) == GLFW_PRESS) pos.x += 200.0f * handel.GetDeltaT();

        renderer.DrawTriangle(glm::vec3(400.f, 300.f, 0.f), BLUE);
       renderer.DrawQuad(pos, RED);
        
		
        ImGui::Begin("Sys info");
       ImGui::Text(sstc("FPS: ", std::to_string(handel.GetFPS())).c_str());
        ImGui::Checkbox("Vsinc", &renderer.v);

        ImGui::End();
        if (renderer.v)
                 renderer.v = true;
        else   renderer.v = false; 
        
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
//    GLRenderer.init(handel);
//    GLRenderer.GLRendererHint(DEFALT_GLRenderer_TYPE, 4);
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
//        GLRenderer.beginDrawing();
//       
//       // GLRenderer.ClearBackground(HEXBLACK);
//
//        
//       // GLRenderer.DrawQuadV(pos, size, vec2Zero, 0.f, RED);
//        //GLRenderer.DrawQuadV(pos2, size2, vec2Zero, 0.f, BLUE);
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
//        GLRenderer.endDrawing();
//      
//    }
//    GLRenderer.ShutDown();
//    handel.ShutDown();
//    //gltDeleteText(text);
//    return 0;
//    //// Destroy glText
//    //gltTerminate();
//   
//
//}
