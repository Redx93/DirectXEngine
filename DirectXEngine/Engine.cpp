#include "Engine.h"

bool Engine::Initialize(HINSTANCE hInstance, int width, int height, int nCmdShow)
{
	clock.Start();
	mouse = std::make_unique<Mouse>();

	if (!this->render_window.Initialize(hInstance,width, height, nCmdShow))
	{
		return false;
	}
	if (!gfx.Initialize(this->render_window.GetHWND(), width, height))
	{
		return false;
	}
	mouse->SetWindow(render_window.GetHWND());
	return true;

}

bool Engine::ProcessMessage()
{
	return this->render_window.ProcessMessages();	
}

void Engine::Update()
{
	float dt = clock.getMilisecondsElapsed();
	clock.Restart();
	
	auto state = mouse->GetState();
	
	if (state.rightButton)
	{
 		mouse->SetMode(Mouse::MODE_RELATIVE);
		float y = state.y;
		if (y > 0) {
			y = 1.0f;
		}
		else if (y < 0) {
			y = -1.0f;
		}
		else {
			y = 0.0f;
		}
		float x = state.x;
		if (x > 0) {
			x = 1.0f;
		}
		else if (x < 0) {
			x = -1.0f;
		}
		else {
			x = 0.0f;
		}

	/*	gfx.camera.AdjustRotation(x*0.01f ,
			y *0.01f, 0);*/
		gfx.camera.AdjustRotation(y*0.01f*dt,
			x *0.01f*dt, 0);
	}
	else
	{
		/*XMFLOAT3 look(0, 0, 0);
		gfx.camera.SetLookAtPos(gfx.LookAtPos);*/
		mouse->SetMode(Mouse::MODE_ABSOLUTE);
		mouse->SetVisible(true);
	}

	if (GetAsyncKeyState(0x41)) {//A
		XMFLOAT3 adjust(-0.01f*dt, 0.0f, 0.0f);
		gfx.camera.AdjustPosition(gfx.camera.GetLeftVector()*0.006*dt);
	}
	if (GetAsyncKeyState(0x44)) { //D
		XMFLOAT3 adjust(0.01f*dt, 0.0f, 0.0f);
		gfx.camera.AdjustPosition(gfx.camera.GetRightVector()*0.006*dt);
	}
	if (GetAsyncKeyState(0x57)) {//W
		XMFLOAT3 adjust(0.0f, 0.0f, 0.01f*dt);
		gfx.camera.AdjustPosition(gfx.camera.GetForwardVector()*0.006*dt);
	}
	if (GetAsyncKeyState(0x53)) { //S
		XMFLOAT3 adjust(0.00f, 0.0f, -0.01f*dt);
		gfx.camera.AdjustPosition(gfx.camera.GetBackwardVector()*0.006*dt);
	}
	if (GetAsyncKeyState(VK_SPACE)) { //backspace 
		gfx.camera.AdjustPosition(0.0f, 0.01f*dt, 0.0f);
	}
	if (GetAsyncKeyState(VK_CONTROL)) { //backspace 
		gfx.camera.AdjustPosition(0.0f, -0.01f*dt, 0.0f);
	}
	if (GetAsyncKeyState(VK_F1)) { //backspace 
		int testInt = gfx.came2 ? 1 : 0;
		if (testInt != 1) {
			gfx.came2 = true;
		}
		else {
			gfx.came2 = false;
			gfx.camera.AdjustPosition(gfx.LookAtPos);
		}
	}

	gfx.RenderFrame(dt);
}

void Engine::RenderFrame()
{
}

Engine::~Engine()
{
	
}
