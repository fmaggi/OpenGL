#include "Application.h"

int main(void)
{  
    int failed = Application::Init();
    if (failed)
    {
        return failed;
    }

    while (Application::IsRunning())
    {
        Application::OnEvent();
        Application::Update();
        Application::Draw();
    }

    Application::Delete();
}