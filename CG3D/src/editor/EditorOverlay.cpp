#include "editor/EditorOverlay.h"

// Additonal Includes
#include "data/Events.h"
#include "systems/input/InputManager.h"
#include "systems/input/Keyboard.h"
#include "systems/input/Mouse.h"
#include "graphics/Window.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


// Namespaces
using namespace cg3d;

EditorOverlay::EditorOverlay()
	: _isVisible(true)
	, _showCursor(true)
{
	InputManager::get().getKeyboard()->addObserver(this);
	InputManager::get().getMouse()->addObserver(this);
}

EditorOverlay::~EditorOverlay()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void EditorOverlay::onNotify(Event & event)
{
	switch (event._id)
	{	
	case EVENT_KEYBOARD_INPUT:
	{
		EventKeyboardInput& e = static_cast<EventKeyboardInput&>(event);
		if (e._action == KEY_DOWN)
		{
			switch (e._key)
			{
			case KEY_TILDE:
				_isVisible = !_isVisible;
				break;
			default:
				break;
			}
		}
	}
	case EVENT_MOUSE_CLICK:
	{
		EventMouseClick& e = static_cast<EventMouseClick&>(event);
		int a = e._action;
		switch (e._button)
		{
		case MOUSE_BUTTON_RIGHT:
			if (e._action == BUTTON_DOWN)
				_showCursor = false;
			else if (e._action == BUTTON_UP)
				_showCursor = true;
			break;
		default:
			break;
		}
	}
	default:
		break;
	}
}

void EditorOverlay::start(Window* window)
{
	// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window->getWindowHandle(), false);
	ImGui_ImplOpenGL3_Init();

	// Setup style
	ImGui::StyleColorsDark();
	ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

}

void EditorOverlay::update()
{

}

void EditorOverlay::redraw()
{
	if (!_isVisible)
		return;

	// Start frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("Performance"))
	{
		ImGui::Text("Dear ImGui %s", ImGui::GetVersion());
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Camera"))
	{
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();


	// End frame
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGui::EndFrame();
}
