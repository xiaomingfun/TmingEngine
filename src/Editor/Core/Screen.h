#ifndef Screen_h

#define Screen_h

#include "im.h"
#include "Core/Context.h"
#include "Console.h"
#include "Widget.h"
#include "ViewPoint.h"
#include "DemoMenu.h"
#include "Log/Log.h"
#include "demo.h"
#include "Project.h"
#include "Hierachy.h"
#include "Inspector.hpp"
#include "Game.hpp"
#include "Profiler.hpp"
#include "Console.h"

//#if Debug
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);




using namespace TmingEngine;

class Screen :public Subsystem
{
public:
	GLFWwindow * window;
	unsigned int texture1, texture2;
	Shader ourShader ,ourShaderCa, skyboxShader;
	unsigned int VBO, VAO ;
    
    unsigned int skyboxVAO, skyboxVBO;
    unsigned int cubemapTexture;
    
	vector<Widget *> m_widgets;

	vector<DemoTest *> m_testDemos;

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	Context * screenContext;
	int CurrentFrameTextureID = 0;
    int CurrentFrameTextureIDCa = 0;
    
	unsigned int framebuffer;
	unsigned int textureColorbuffer;
    
    unsigned int framebufferCa;
    unsigned int textureColorbufferCa;

	void Initialize(Context * context);
	void Update();
	void ShutDown();

	bool ScreenShouldClose();

	void InitOpenGL();

	void InitEditorWidget(Context * context);

	int GetCurrentFrameTexture();

	void CreateFrameBufer();
    void CreateFrameBuferCa();

	Screen(Context* context) : Subsystem(context)
	{
		context->RegisterSubsystem(this);
		Initialize(context);
        
        for (auto& widget : m_widgets)
        {
            if (widget->GetIsWindow())
            {
                widget->Begin();
            }
        }
	}
    
    ~Screen()
    {
        for (auto& widget : m_widgets)
        {
            if (widget->GetIsWindow())
            {
                widget->End();
            }
        }
        
    }

	void RegisteWidget(Widget *widget)
	{
		m_widgets.push_back(widget);
	}

	template <class T>
	T* GetSubWidget()
	{
		for (const auto& subwidget : m_widgets)
		{
			if (typeid(T) == typeid(*subwidget))
				return static_cast<T*>(subwidget);
		}

		return nullptr;
	}

	void DrawScreen()
	{
		for (auto& widget : m_widgets)
		{
			widget->Update();
		}
	}


private:
	void InitImgui();
	void Render_SceneObject_update();
    void Render_SceneObjectCa();
	void Render_SkyBox_init();
    void Render_SkyBox_update();
	void Render_EditorUI();
};

#endif // 
